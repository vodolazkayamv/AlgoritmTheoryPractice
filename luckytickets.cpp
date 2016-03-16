//
//  main.cpp
//  LuckyTiclets
//
/*
 Имеется лента билетов с восьмизначными номерами. Первый билет имеет номер M, последний – N. Величины M и N отвечают следующему соотношению: 10000000 ≤ M < N ≤ 99999999. Необходимо определить количество "счастливых" билетов в ленте. Билет считается "счастливым", если сумма первых четырех цифр равна сумме последних четырех цифр.
 
 Ввод
 Ввод содержит построчно номера первого и последнего билетов в ленте.

 Вывод
 Необходимо вывести искомое количество "счастливых" билетов в ленте.
 
 Ввод 1			Ввод 2
 11111110		10000000
 11111112		99999999
 
 Вывод 1		Вывод 2
 1				4379055

 */
#include <iostream>



int digitsSum(int src)
{
	int sum = 0;
	while (src > 0) {		// если слева остались нули, на сумму они не повлияют
		int digit = src % 10;
		src = src / 10;
		sum += digit;
	}
	return sum;
}



int main(int argc, const char * argv[]) {
	long startTicket;
	long endTicket;
	long luckyNumber = 0;
	
	std::cin >> startTicket;
	std::cin >> endTicket;
	
	int minblock = (int) startTicket / 1000;	// левый минимальный блок
	int maxBlock = (int) endTicket / 1000;		// правый блок
	
	int index[37];		// индексный массив для возможных значений сумм
	if (maxBlock > minblock) {
		// В этом случае нам понадобится индексный массив - в случае, если минимальный и
		// максимальный блок сопадают, на его вычисление у нас уйдет больше времени
		// чем мы выиграем
		//bzero(index, sizeof(int)*37);
		for (int i = 0; i < 37; i++)
			index[i] = 0;
		for (int i = 0; i < 10000; i++) {
			index[digitsSum(i)]++;
		}
	}
	
	for (int blockNum = minblock; blockNum <= maxBlock; blockNum++) {
		int currentLucky = digitsSum(blockNum);
		if ((blockNum == minblock || blockNum == maxBlock)) {
			// специальный случай! нужно рассчитывать вручную
			int startLeft = 0;
			int endRight = 9999;
			if (blockNum == minblock) {
				startLeft = startTicket % 1000;
			} else {
				endRight = endTicket % 1000;
			}
			for (int k = startLeft; k <= endRight; k++) {
				int tmp = digitsSum(k);
				if (tmp == currentLucky) {
					luckyNumber++;
				}
			}
		} else {
			// в этом блоке у нас присутствуют все номера от 0 до 9999, а значит
			//
			luckyNumber += index[currentLucky];
		}
	}

	std::cout << luckyNumber;
	system("pause");
	
}
