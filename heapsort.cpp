//
//  main.cpp
//  HeapSorting
//

/*
 Сначала задаётся число N (1 ≤ N ≤ 10^6), а затем N целых чисел, по модулю не превышающих 10^6.
 
 Выведите N чисел в порядке неубывания, используя метод сортировки кучей.
 
 Ввод
 5
 3 1 2 4 2
 
 Вывод
 1 2 2 3 4

 
 */

#include <iostream>

//#define TEST_RUN

void swap (long *arr, long i, long j) {
	long tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void heapify (long pos, long n, long *arr) {
	while (2 * pos + 1 < n) {
		
		long t = 2 * pos +1;
		if (2 * pos + 2 < n && arr[2 * pos + 2] >= arr[t])
		{
			t = 2 * pos + 2;
		}
		if (arr[pos] < arr[t]) {
			swap(arr, pos, t);
			pos = t;
		}
		else break;
		
	}
}

void heap_make(int n, long *arr)
{
	for (int i = n - 1; i >= 0; i--) {
		heapify(i, n, arr);
	}
}


void heap_sort(long n, long *arr)
{
	heap_make(n, arr);
	while(n > 0) {
		swap(arr,0 ,n-1);
		n--;
		heapify(0,n,arr);
	}
}



int main(int argc, const char * argv[]) {
	
	long arraySize;
	
#ifdef TEST_RUN
	arraySize = 5;
	long input[5] = { 3, 1, 2, 4, 2 };
#else
	std::cin >> arraySize;
	long *input = new long[arraySize];
	for (long i = 0; i < arraySize; i++) {
		std::cin >> input[i];
	}
#endif
	
	
	heap_sort(arraySize, input);
	
	for (int i = 0; i < arraySize; i++) {
		std::cout << input[i] << ' ';
	}
	std::cout << '\n';
	
	//system("pause");
	
}
