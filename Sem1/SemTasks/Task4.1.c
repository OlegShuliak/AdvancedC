/*
 На вход программе подается беззнаковое 32-битное целое число N. 
 Требуется найти количество единичных битов в двоичном представлении 
 данного числа.
 */


#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	uint32_t N;
	uint32_t mask = 1;
	uint32_t count = 0;
	scanf("%u", &N);
	
	for(int i = 0; i < 32; ++i){
		uint32_t v = mask & N;
		count += v;
		N >>=1;
	}
	
	printf("%u", count);
	
	return 0;
}

