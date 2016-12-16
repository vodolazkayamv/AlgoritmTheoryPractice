// LIS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


// C++ implementation to find longest increasing subsequence
// in O(n Log n) time.

// Binary search
int GetCeilIndex(int arr[], vector<int> &T, int l, int r,
	int key)
{
	while (r - l > 1)
	{
		int m = l + (r - l) / 2;
		if (arr[T[m]] >= key)
			r = m;
		else
			l = m;
	}

	return r;
}

int LongestIncreasingSubsequence(int arr[], int n)
{
	// Add boundary case, when array n is zero
	// Depend on smart pointers

	vector<int> tailIndices(n, 0); // Initialized with 0 
	vector<int> prevIndices(n, -1); // initialized with -1

	int len = 1; // it will always point to empty location
	for (int i = 1; i < n; i++)
	{
		if (arr[i] < arr[tailIndices[0]])
		{
			// new smallest value
			tailIndices[0] = i;
		}
		else if (arr[i] > arr[tailIndices[len - 1]])
		{
			// arr[i] wants to extend largest subsequence
			prevIndices[i] = tailIndices[len - 1];
			tailIndices[len++] = i;
		}
		else
		{
			// arr[i] wants to be a potential condidate of
			// future subsequence
			// It will replace ceil value in tailIndices
			int pos = GetCeilIndex(arr, tailIndices, -1,
				len - 1, arr[i]);

			prevIndices[i] = tailIndices[pos - 1];
			tailIndices[pos] = i;
		}
	}

	return len;
}

int main()
{
	int arr[] = { 2, 5, 3, 7, 11, 8, 10, 13, 6 };
	int n = sizeof(arr) / sizeof(arr[0]);

	long arraySize;
	// ���� ������� �������� �������
	std::cin >> arraySize;

	int *x = new int[arraySize]; // ������� ������
	int *index = new int[arraySize]; // ����� �������� ��� ������� �������� �������� �������

	// ���� �������� �������
	for (long i = 0; i < arraySize; i++) {
		std::cin >> x[i];
	}

	printf("%d\n", LongestIncreasingSubsequence(x, arraySize));
	system("pause");
	return 0;
}


