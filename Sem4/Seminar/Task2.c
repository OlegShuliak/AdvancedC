/*
 Традиционная запись выражения выглядит так: (1+2) * 4+3. Она не удобна 
 для вычислителя (компьютера), поэтому в микрокалькуляторах 
 (спецвычислителях), например БЗ-34 и МК-61, применяется обратная 
 польская запись: 1 2 + 4 × 3 +. Напишем такого вида спецвычислитель. 
 Необходимо вычислить выражение, написанное в обратной польской записи. 
 На вход подается строка, состоящая из целых, неотрицательных чисел и 
 арифметических символов. В ответ единственное целое число - результат. 
 Выражение работает на сложение и вычитание.
 */


#include <stdio.h>

#define max_stack 500 

typedef struct stack_t {    
	unsigned int numbers[max_stack+1];    
	int size; 
} stack_t; 

stack_t stack; 
stack_t *st = &stack; 
unsigned int pop(); 
int push( unsigned int );

int main(int argc, char **argv)
{
	st->size = 0;    
	int ch;    
	int res=0;    
	unsigned int a=0, b=0; 
	
	while(EOF != (ch = getchar())) { 
		switch(ch) {    
			case '+': 
				a = pop(); 
				b = pop(); 
				push(a+b); 
				break; 
			case '-': 
				a = pop(); 
				b = pop(); 
				push(b-a); 
				break; 
			case '\n': 
			case ' ': 
			case '.': 
			case '=': 
			break; 
			default: 
				ungetc(ch,stdin);//возвращаем символ 
				scanf("%u", &a);//чтобы вычитать снова 
				push(a); 
		} 
		if(ch == '\n' || ch == '.'|| ch == '=' ) 
			break; 
	} 
	printf("%d\n", pop()); 
}

unsigned int pop() { 
	if(st->size) { 
		st->size--; 
#ifdef DEBUG 
		printf("Popped %u\n", st->numbers[st->size]); 
#endif 
		return st->numbers[st->size]; 
	} 
	return 0; 
}

int push(unsigned int n) { 
	if((st->size) < max_stack ) { 
		st->numbers[st->size] = n;        
		unsigned int res = (st->size); 
		st->size ++; 
#ifdef DEBUG 
		printf("Pushed %u, stack size = %d\n", st->numbers[st->size], st->size); 
#endif 
		return st->size; 
	} else { 
		return -1; 
	} 
}















