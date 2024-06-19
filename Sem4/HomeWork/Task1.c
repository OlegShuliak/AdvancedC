/*
Реализовать программу  1-го практического задания с помощью 
биномиального коэффициента. 
 */


#include <stdio.h>

int cnk(int n, int k) { 
	int max = n;
	int cnk[max + 1][max + 1];
	for (int i = 0; i <= max; ++i){
		cnk[i][0] = cnk [i][i] = 1;
		for (int j = 1; j < i; ++j){
			cnk[i][j] = cnk[i - 1][j - 1] + cnk[i - 1][j];
		}
	}
	return cnk[n][k];
} 

int main() {    
	int a,b;    
	scanf ("%d%d",&a,&b);    
	printf ("%d", cnk(a,b));    
	return 0; 
}

