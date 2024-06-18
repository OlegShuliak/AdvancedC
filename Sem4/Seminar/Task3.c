/*
 На стандартном потоке ввода задаются две символьные строки, разделённые 
 символом перевода строки. Каждая из строк не превышает по длине 104. 
 В строках не встречаются пробельные символы. На стандартный поток 
 вывода напечатайте два числа, разделённых пробелом: первое число — 
 длина наибольшего префикса первой строки, являющегося суффиксом второй; 
 второе число — наоборот, длина наибольшего суффикса первой строки, 
 являющегося префиксом второй. Сравнение символов проводите с учётом 
 регистра (т.е. символы 'a' и 'A' различны).
 */


#include <stdio.h> 
#include <string.h> 

enum{maxlength = 10001}; 
int search_prefix(char*, char*); 

int main () {    
	char s1[maxlength ], s2[maxlength];     
	scanf("%10001s", s1);    
	scanf("%10001s", s2);    
	printf("%d %d\n", search_prefix(s2,s1), search_prefix(s1,s2));     
	return 0; 
}

int search_prefix(char*s1, char*s2) {    
	int l1 = strlen(s1);    
	int l2 = strlen(s2);    
	int l = l1<l2 ? l1 : l2;    
	int i1, i2, max=0;    
	char c1, c2; 
	for (i1 = l1-l; i1<l1; i1++) { 
		for(i2 = 0; i2<l2; i2++) { 
			c1 = s1[i1+i2]; 
			c2 = s2[i2]; 
#ifdef DEBUG 
			printf("%c/%c ", c1, c2); 
#endif                        
			if(c1 != c2 ) 
				break; 
		} 
#ifdef DEBUG 
		printf("\n"); 
#endif 
		if(s1[l1-1] == s2[i2-1] && i2 > max) 
			max = i2; 
	} 
	return max; 
}


