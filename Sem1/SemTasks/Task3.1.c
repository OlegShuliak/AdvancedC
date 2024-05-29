/*
 На вход программе подается беззнаковое 32-битное целое число N и 
 натуральное число K (1 ≤ K ≤ 31). Требуется взять K подряд идущих 
 битов числа N так, чтобы полученное число было максимальным. 
 Программа должна вывести полученное число.
 */


#include <stdio.h>
#include <stdint.h> 

int main(int argc, char **argv)
{
	unsigned int K;
	uint32_t N;
	scanf("%u %u", &N, &K);
	
	uint32_t mask = ~0;
	mask <<= (32 - K);
	
	uint32_t max = 0;
	for(int i = 0; i <= 32; ++i){
		uint32_t v = mask & N >> (32 - K - i);
		if (v > max) {
			max = v;
		}
		mask >>=1;
	}
	
	printf("%u", max);
	
	return 0;
}

