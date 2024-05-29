/*
 На стандартном потоке ввода задается натуральное число N (N > 0), 
 после которого следует последовательность из N целых чисел. 
 На стандартный поток вывода напечатайте, сколько раз в этой 
 последовательности встречается максимум. Указание: использовать 
 массивы запрещается.
 */


#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
	int N, x, count = 1, max;
	scanf("%d", &N);
	scanf("%d", &x);
	max = x;
	
	for (int i = 1; i < N; ++i){
		scanf("%d", &x);
		if (x > max) {
			max = x;
			count = 1;
		} else  if (x == max){
			count++;
		}
	}
	
	printf("%d", count);
	
	return 0;
}

