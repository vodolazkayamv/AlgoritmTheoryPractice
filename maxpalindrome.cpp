//
//  main.cpp
//  MaxPalindrome
//

/*
		В первой строке входного файла задаётся число N (1 ≤ N ≤ 10^6), 
		а во второй - строка длины N, содержащая латинские символы.

		В выходном файле выведите N чисел, разделенных пробелами,
		где i-ое число равно длине наибольшего палиндрома с центром в i-том символе.

		Ввод	   Вывод
		4
		a b c d    1 1 1 1

		5
		a b a b a   1 3 5 3 1

 */

#include <iostream>

int main(int argc, const char * argv[]) {
	
	long arraySize;
	
	std::cin >> arraySize;
	char *input = new char[arraySize];
	for (long i = 0; i < arraySize; i++) {
		std::cin >> input[i];
	}
	long *output = new long[arraySize];
	
	for (long i = 0; i < arraySize; i++) {
		if (i == 0 || i == arraySize - 1) {
			output[i] = 1;		// краевые элементы по определению несимметричны
		} else {
			// оцениваем максимальный возможный плаиндрома - это минимальное
			// расстояние до начала или конца масива
			long leftOffset = i;
			long rightOffset = arraySize - i;
			long maxPalindromSize = (leftOffset < rightOffset ? leftOffset : rightOffset);
			long currentOffset = 1;
			bool broken = false;
			do  {
				if (input[i - currentOffset] == input[i+currentOffset]) {
					currentOffset ++;
				} else {
					// возвращаемся к последнему успешному значению
					currentOffset--;
					broken = true;
					break;
				}
			} while (currentOffset <= maxPalindromSize);
			output[i] = (broken ? currentOffset*2 + 1 : currentOffset*2 - 1);
		}
	}
	
	
	// выводим полученный результат
	for (long i = 0; i < arraySize; i++) {
		std::cout << output[i] << " ";
	}
	std::cout<<"\n";

}
