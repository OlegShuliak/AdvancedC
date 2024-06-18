/*
 Разыгрывается тираж лотереи. Участвует N номеров. Из них выпадает 
 M номеров. Сколькими вариантами набора номеров это может произойти? 
 Данные на вход: Два целых числа N и M Данные на выход: Одно целое 
 число – количество вариантов
 */


#include <stdio.h>

int cnk(int n, int k) { 
	int res = 1;    
	for (int i=n-k+1; i<=n; ++i)        
		res *= i;    
	for (int i=2; i<=k; ++i)        
		res /= i;    
	return res; 
} 

int main() {    
	int a,b;    
	scanf ("%d%d",&a,&b);    
	printf ("%d", cnk(a,b));    
	return 0; 
}

