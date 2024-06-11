/*
 Описана структура данных для хранения информации об использованной 
 памяти: 
 typedef struct list {    
	void *address;    
	size_t size;    
	char comment[64];    
	struct list *next; 
}list; 
Составить программу, которая анализирует данный список и возвращает 
сколько всего памяти используется. Адрес хранится в поле address, поле 
size - соответствующий размер данного блока. Если список пустой, то 
программа должна возвращать NULL. 
Прототип функции: size_t totalMemoryUsage(list *);
 */


#include <stdio.h>

typedef struct list {    
	void *address;    
	size_t size;    
	char comment[64];    
	struct list *next; 
}list; 

size_t totalMemoryUsage(list *); 
void print_elem(list * );

int main(int argc, char **argv)
{
	list test_v[3] ; 
	test_v[0].size = 1000; 
	test_v[1].size = 200; 
	test_v[2].size = 100; 
	test_v[0].next = test_v+1; 
	test_v[1].next = test_v+2; 
	test_v[2].next = (struct list*) NULL; 
	test_v[0].address = &test_v[0]; 
	test_v[1].address = &test_v[1]; 
	test_v[2].address = &test_v[2];    
	size_t r = totalMemoryUsage(test_v); 
	printf("%llu\n", r);
	return 0;
}

size_t totalMemoryUsage(list *head) {    
	size_t res=0; 
	while((struct list *)NULL != head) { 
		res+=head->size; 
		head = head->next; 
	} 
	return res; 
}

void print_elem(list * elem) {
	if (elem != NULL) {
		printf("\
Real address:\t 0x%p\n\
Int address:\t 0x%p\n\
Size:\t\t %lld\n\
Comment:\t %s\n\
Next:\t\t 0x%p\n", elem, elem->address, elem->size, elem->comment, elem->next);
	} else {
		printf("(NULL)\n");
	}
}

