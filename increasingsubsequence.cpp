//
//  main.cpp
//  IncreasingSubSeq
//

/*
		Даны N целых чисел X1, X2, ..., XN. Требуется вычеркнуть из них 
		минимальное количество чисел так, чтобы оставшиеся шли в порядке возрастания.
 
		Ввод
 
		В первой строке находится число N. В следующей строке - N чисел через пробел.
 
		Вывод
 
		В первой строке выводится количество невычеркнутых чисел, 
		во второй - сами невычеркнутые числа через пробел в исходном порядке. 
		Если вариантов несколько, вывести любой.
 
		Ограничения
		1 ≤ N ≤ 10 000; 1 ≤ Xi ≤ 10 00.
 
		Ввод 1
		
		6
		2 5 3 4 6 1
 
		Вывод 1
		
		4
		2 3 4 6

 */

//#define TEST_RUN


#include <iostream>
#include <math.h>


long intCeil(long a, long b)
{
	long div = (a+b) / 2;
	long rem = (a+b) % 2;
	return div + rem;
}

int lis( long *arr, int n )
{
	int *lis, i, j, max = 0;
	lis = new int[n];
 
	for ( i = 0; i < n; i++ )
		lis[i] = 1;
	
	for ( i = 1; i < n; i++ )
		for ( j = 0; j < i; j++ )
			if ( arr[i] > arr[j] && lis[i] < lis[j] + 1)
				lis[i] = lis[j] + 1;
	
	for ( i = 0; i < n; i++ )
		if ( max < lis[i] )
			max = lis[i];
  
	return max;
}



int main(int argc, const char * argv[]) {

	long arraySize;
	
#ifdef TEST_RUN
	arraySize = 8;
	long x[8] = { 3, 2, 5, 3, 1, 4, 6, 1 };
	long * index = new long[6];
	long * out = new long[7];
#else

	std::cin >> arraySize;
	long *x = new long[arraySize];
	long *index = new long[arraySize];
	long *out = new long[arraySize + 1];
	
	for (long i = 0; i < arraySize; i++) {
		std::cin >> x[i];
	}
#endif

	/*
	for (int i = 0; i < arraySize; i++) {
		std::cout << x[i] << ' ';
	}
	std::cout << "\n";
	*/

	for (long i = 0; i < arraySize; i++) {
		index[i] = 1;		// по умолчанию все элементы cсчитаются изолированными
							// то есть длина их префикса равна 1
	}
	
	/* Рассчитываем максимальную длину последовательности для каждого символа масива*/
	for ( int i = 1; i < arraySize; i++ )
		for (int j = 0; j < i; j++ )
			if ( x[i] > x[j] && index[i] < index[j] + 1)
				index[i] = index[j] + 1;
	

	/*
	for (int i = 0; i < arraySize; i++) {
		std::cout << index[i] << ' ';
	}
	std::cout << "\n";
	*/

	/* Определяем  максимальное значение */
	long max = 0;
	long maxIndex;
	
	
	for ( long i = 0; i < arraySize; i++ )
		if ( max < index[i] ) {
			max = index[i];
			maxIndex = i;
		}

	std::cout << max << "\n";
	

	// формируем выходной массив
	int count = 0;
	long *seq = new long[maxIndex];
	seq[count] = x[maxIndex];
	max--;

	while (maxIndex > 0)
	{
		maxIndex--;
		if(index[maxIndex] == max)
		{
			count++;
			seq[count] = x[maxIndex];
			max--;
		}
	}
	
	for (int i = count; i >= 0; i--) {
		std::cout << seq[i] << ' ';
	}
	std::cout << "\n";	


	//system("pause");
	
}
