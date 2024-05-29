/*
 На вход программе подается беззнаковое 32-битное целое число N 
 и натуральное число K (1 ≤ K ≤ 31).
 Требуется циклически сдвинуть биты числа N вправо на K 
 битов и вывести полученное таким образом число.
 */


#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	uint32_t N;
	unsigned int K;
	scanf("%u %u", &N, &K);
	
	uint32_t res;
	uint32_t temp;
	
	uint32_t mask = ~0;
	mask >>= (32 - K);
	
	temp = N | mask;
	temp <<= (32 - K);
	
	res = N >> K;
	res = res | temp;
	
	printf("%d", res);
	
	return 0;
}

