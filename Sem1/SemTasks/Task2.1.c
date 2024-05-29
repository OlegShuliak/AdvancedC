/*
 На вход программе подается беззнаковое 32-битное целое число N и 
 натуральное число K (1 ≤ K ≤ 31). Требуется взять K младших битов 
 числа N и вывести полученное таким образом число.
 */


#include <stdio.h>
#include <stdint.h> 

int main(int argc, char **argv)
{
	unsigned int K;
	uint32_t N, res;
	scanf("%u %u", &N, &K);
	
	uint32_t mask = ~0;
	mask >>= (32 - K);
	
	res = N & mask;
	
	printf("%u", res);
	
	return 0;
}

