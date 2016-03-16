//
//  main.cpp
//  CountingSort
//

/*
 
 В первой строке файла записано число элементов массива N (1 ≤ N ≤ 10^6), а во второй строке N неотрицательных чисел, меньших 100.
 
 Отсортируйте массив, использую сортировку подсчетом. В первой строке выходного файла 
 выведите отсортированный исходный массив, а во второй - массив из 100 чисел, 
 показывающих, сколько раз встретилось число в исходной последовательности.
 
 Ввод
 6
 4 3 2 9 8 8
 
 Вывод
 
 2 3 4 8 8 9
 0 0 1 1 1 0 0 0 2 1 0 0 ... 0

 */

#include <iostream>

int main(int argc, const char * argv[]) {
	long arraySize = 0;
	
	std::cin >> arraySize;
	
	//long *input = (long *) malloc(arraySize * sizeof(long));
	long *input = new long[arraySize];
	for (long i = 0; i < arraySize; i++) {
		std::cin >> input[i];
	}
	
	// Формируем индексный массив
	long index[100];
	//std::memset(index,0,sizeof(long)*100);
	//bzero(index, sizeof(long)*100);	// прописываем нули в счетчик
	// заполняем индексный массив

	for (long i = 0; i < 100; i++) {
		index[i] = 0;
	}

	for (long i = 0; i < arraySize; i++) {
		index[input[i]]++;
	}
	
	// Первая строка - отсортированный массив
	for (int i = 0; i < 100; i++) {
		if (index[i] > 0) {
			// Этот элемент есть в массиве!
			for (long j = 0; j < index[i]; j++) {
				std::cout << i << ' ';
			 }
		}
	}
	std::cout << '\n';
	
	// Вторая строка вывода - сколько раз встретилось число в последовательности
	for (long i = 0; i < 100; i++) {
		std::cout << index[i] << ' ';
	}
	//std::cout << '\n';
	
	//system("pause");
}
