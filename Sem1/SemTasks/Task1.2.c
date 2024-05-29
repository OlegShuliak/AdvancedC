/*
 На вход программе подается беззнаковое 32-битное целое число N 
 и натуральное число K (1 ≤ K ≤ 31).
 Требуется циклически сдвинуть биты числа N вправо на K 
 битов и вывести полученное таким образом число.
 */


#include <stdio.h>
#include <stdint.h> 

uint32_t worker(uint32_t , unsigned int);

int main(int argc, char **argv)
{
	unsigned int k; 
	uint32_t n, res;    
		scanf("%u %u", &n, &k);
		res = worker (n, k); 
		printf("%u\n", res);
	return 0;
}

uint32_t worker (uint32_t n, unsigned int k) {
	return n>>k | n<<(32-k); 
}

