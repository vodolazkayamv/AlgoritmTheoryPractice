//
//  main.cpp
//  ZFunction
//

//
// В первой строке входного файла задаётся число N (1 ≤ N ≤ 10^6),
// а во второй - строка длины N, содержащая латинские символы.
//
//
// В выходном файле выведите значения Z-функции для строки из входного файла.
// Ввод
//
// 5
// a a b c a
//
// Вывод:
//
// 5 1 0 0 1
//
// См. https://ru.wikipedia.org/wiki/Z-функция
//


#include <stdlib.h>
#include <iostream>


int main(int argc, const char * argv[]) {
	long stringLength;
	long L = 0;						// начальные значения индексов L и R
	long R = 0;
	
	std::cin >> stringLength;		// вводим длину строки

	long i = 0;
	
	char * s = new char[stringLength];
	long * z = new long [stringLength];
	while (i < stringLength) 
	{
		char symbol = ' ';
		while (symbol == ' ' && i < stringLength) {
			std::cin >> symbol;		// пропускаем все служебные пробелы
		}
		s[i] = symbol;
		i++;
	}
	
	z[0] = stringLength;
	long j;
	for (long i = 1; i < stringLength; i++)
		if (i > R) {
			for (j = 0; ((j + i) < stringLength) && (s[i + j] == s[j]) ; j++);
			z[i] = j;
			L = i;
			R = i + j - 1;
		}
		else
			if (z[i - L] < R - i + 1)
				z[i] = z[i - L];
			else{
				for (j = 1; ((j + R) < stringLength) && (s[R + j] == s[R - i + j]); j++);
				z[i] = R - i + j;
				L = i;
				R = R + j - 1;
			}
	for (int i = 0; i < stringLength; i++) {
		std::cout << z[i] << ' ';
	}

}
