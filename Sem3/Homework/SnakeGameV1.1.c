
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <curses.h>

#define MIN_Y  2
 
enum {LEFT=1, UP, RIGHT, DOWN, STOP_GAME=KEY_F(10)}; 
enum {MAX_TAIL_SIZE=100, START_TAIL_SIZE=3, MAX_FOOD_SIZE=20, FOOD_EXPIRE_SECONDS=10, SEED_NUMBER=3};

struct control_buttons {    
	int down;    
	int up;    
	int left;    
	int right; 
}control_buttons; 

typedef struct snake_t { 
	int x; 
	int y; 
	int direction; 
	size_t tsize; 
	struct tail_t *tail; 
	struct control_buttons *controls; 
} snake_t;

typedef struct tail_t { 
	int x; 
	int y; 
} tail_t;

struct food {    
	int x;    
	int y;    
	time_t put_time;    
	char point;    
	uint8_t enable; 
} food[MAX_FOOD_SIZE];

struct control_buttons default_controls [3] = {{KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT}, {'s', 'w', 'a', 'd'}, {'S', 'W', 'A', 'D'}};


void initTail(struct tail_t t[], size_t size) { 
	struct tail_t init_t={0,0}; 
	for(size_t i=0; i<size; i++) {   
		t[i]=init_t; 
	} 
}

void initHead(struct snake_t *head, int x, int y) { 
	head->x = x; 
	head->y = y; 
	head->direction = RIGHT; 
}

void initSnake(snake_t *head, size_t size, int x, int y) { 
	tail_t*  tail  = (tail_t*) malloc(MAX_TAIL_SIZE*sizeof(tail_t)); 
	initTail(tail, MAX_TAIL_SIZE); 
	initHead(head, x, y); 
	head->tail = tail; // прикрепляем к голове хвост 
	head->tsize = size+1; 
	head->controls = default_controls;
}

void initFood(struct food f[], size_t size) {    
	struct food init = {0,0,0,0,0};    
	int max_y=0, max_x=0;    
	getmaxyx(stdscr, max_y, max_x);    
	for(size_t i=0; i<size; i++){        
		f[i] = init;    
	} 
}

void putFoodSeed(struct food *fp) {    // Обновить/разместить текущее зерно на поле
	int max_x=0, max_y=0;    
	char spoint[2] = {0};    
	getmaxyx(stdscr, max_y, max_x);    
	mvprintw(fp->y, fp->x, " ");    
	fp->x = rand() % (max_x - 1);    
	fp->y = rand() % (max_y - 2) + 1; //Не занимаем верхнюю строку    
	fp->put_time = time(NULL);    
	fp->point = '$';    
	fp->enable = 1;    
	spoint[0] = fp->point;    
	mvprintw(fp->y, fp->x, "%s", spoint); 
}

void putFood(struct food f[], size_t number_seeds) {    //Разместить еду на поле
	for(size_t i=0; i<number_seeds; i++) {        
		putFoodSeed(&f[i]);    
	} 
}

void refreshFood(struct food f[], int nfood) {    //Обновление еды
	int max_x=0, max_y=0;    
	char spoint[2] = {0};    
	getmaxyx(stdscr, max_y, max_x);    
	for(size_t i=0; i<nfood; i++) {        
		if( f[i].put_time ) {            
			if( !f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS ) {                
				putFoodSeed(&f[i]);            
			}        
		}    
	} 
}

_Bool haveEat(struct snake_t *head, struct food f[]) {   //Поедания зерна змейкой 
	for(size_t i=0; i<MAX_FOOD_SIZE; i++) {       
		if( f[i].enable && head->x == f[i].x && head->y == f[i].y  ) {            
			f[i].enable = 0;            
			return 1;        
		}    
	}
	return 0; 
}

void addTail(struct snake_t *head) {    //Увеличение хвоста на 1 элемент
	if(head == NULL || head->tsize>MAX_TAIL_SIZE) {        
		mvprintw(0, 0, "Can't add tail");        
		return;    
	}    
	head->tsize++; 
}

void go(struct snake_t *head){ 
	char ch = '@'; int max_x=0, max_y=0;    
	getmaxyx(stdscr, max_y, max_x); // macro - размер терминала    
	mvprintw(head->y, head->x, " "); // очищаем один символ 
	switch (head->direction) { 
		case LEFT: 
			if(head->x <= 0) {
				head->x = max_x;
			}
			mvprintw(head->y, --(head->x), "%c", ch); 
			break; 
		case RIGHT: 
			if(head->x >= max_x) {       
				head->x = 0;
			}    
			mvprintw(head->y, ++(head->x), "%c", ch); 
			break; 
		case UP: 
			if(head->y <= MIN_Y) {
				head->y = max_y;
			}
			mvprintw(--(head->y), head->x, "%c", ch); 
			break; 
		case DOWN: 
			if(head->y >= max_y) {
				head->y = MIN_Y;
			}    
			mvprintw(++(head->y), head->x, "%c", ch); 
			break; 
		default: 
			break; 
	}    
	refresh(); 
}

void goTail(struct snake_t *head) { 
	char ch = '*';    
	mvprintw(head->tail[head->tsize-1].y, head->tail[head->tsize-1].x, " "); 
	for(size_t i = head->tsize-1; i>0; i--) {        
		head->tail[i] = head->tail[i-1]; 
		if( head->tail[i].y || head->tail[i].x) {           
			mvprintw(head->tail[i].y, head->tail[i].x, "%c", ch);    
		}    
	}
	head->tail[0].x = head->x;    
	head->tail[0].y = head->y; 
}

void changeDirection(snake_t* snake, const int32_t key) {    
	for (int i = 0; i < 3; i++) {
		if (key == snake->controls[i].down) {       
			snake->direction = DOWN;    
		} else if (key == snake->controls[i].up) {
			snake->direction = UP;    
		} else if (key == snake->controls[i].right) {       
			snake->direction = RIGHT;    
		} else if (key == snake->controls[i].left) {       
			snake->direction = LEFT; 
		}
	}
}

int checkDirection(snake_t* snake, int32_t key) {
	int checkDir = 1;
	for (int i = 0; i < 3; i++) {
		if (key == snake->controls[i].down && snake->direction == UP) {       
			checkDir =0;    
		} else if (key == snake->controls[i].up && snake->direction == DOWN) {
			checkDir =0;    
		} else if (key == snake->controls[i].right && snake->direction == LEFT) {       
			checkDir =0;    
		} else if (key == snake->controls[i].left && snake->direction == RIGHT) {       
			checkDir =0; 
		}
	}
	return checkDir;
}

int main(int argc, char **argv)
{
	snake_t* snake = (snake_t*)malloc(sizeof(snake_t)); 
	initSnake(snake,START_TAIL_SIZE,10,10); 
	initFood(food, MAX_FOOD_SIZE);
	initscr(); 
	keypad(stdscr, TRUE); // Включаем F1, F2, стрелки и т.д. 
	raw();            // Откдючаем line buffering 
	noecho();        // Отключаем echo() режим при вызове getch 
	curs_set(FALSE); //Отключаем курсор 
	mvprintw(0, 0,"Use arrows for control. Press 'F10' for EXIT"); 
	timeout(0); //Отключаем таймаут после нажатия клавиши в цикле 
	int key_pressed=0; 
	putFood(food, SEED_NUMBER);
	while( key_pressed != STOP_GAME ) {    
		key_pressed = getch(); // Считываем клавишу
		refreshFood(food, SEED_NUMBER);    
		go(snake);    
		goTail(snake);    
		timeout(100); // Задержка при отрисовке
		if (checkDirection(snake, key_pressed)) {   
			changeDirection(snake, key_pressed); 
		}
	} 
	free(snake->tail); 
	free(snake); 
	endwin(); // Завершаем режим curses mod
	return 0;
}

