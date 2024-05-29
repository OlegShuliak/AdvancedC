/*
 В программе реализована структура данных: 
 struct pack_array{    
	uint32_t array; // поле для хранения упакованного массива из 0 и 1    
	uint32_t count0 : 8; // счетчик нулей в array    
	uint32_t count1 : 8; // счетчик единиц в array } 
Необходимо программу, которая упаковывает переданный ей массив из 
32-ух элементов 0 и 1 в указанную структуру данных. 
Функция должна строго соответствовать прототипу: 
	void array2struct(int [], struct pack_array *)
 */


#include <stdio.h>
#include <stdint.h>

struct pack_array { 
	uint32_t array; // поле для хранения упакованного массива из 0 и 1 
	uint32_t count0 : 8; // счетчик нулей в array 
	uint32_t count1 : 8; // счетчик единиц в array 
}; 

void array2struct(int origin[] , struct pack_array *res){ 
	for (int i =0; i<32; i++) {        
		res->count1 += origin[i];        
		res->array  |= origin[i];        
		i<31 ? res->array<<=1 : 1;// <<=1 - укороченная операция сдвига на 1 
	}    
	res->count0 = 32-res->count1; 
}

int main(int argc, char **argv)
{
	int arr[32]; 
	struct pack_array res; 
	
	for (int i=0; i<32; i++) {        
		scanf("%d", arr+i); 
	}    
	
	array2struct(arr, &res);    
	printf("array: 0x%x\ncount0: %d\ncount1 %d\n", res.array, res.count0, res.count1);
	return 0;
}

