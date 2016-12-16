// LCS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <vector>

using namespace std;

int max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}

void lcs(vector<int> &seq1, vector<int> &seq2)
{
	int i, j, seq1_Size = seq1.size(), seq2_Size = seq2.size(), c;

	vector<vector<int> > distance(seq1_Size + 1, vector<int>(seq2_Size + 1, 0));



	for (i = 1; i <= seq1_Size; i++)
	{
		for (j = 1; j <= seq2_Size; j++)
		{
			if (seq1[i - 1] == seq2[j - 1])
				distance[i][j] = distance[i - 1][j - 1] + 1;
			else
				distance[i][j] = max(distance[i - 1][j], distance[i][j - 1]);
		}
	}

	
	i = seq1_Size;
	j = seq2_Size;
	c = distance[seq1_Size][seq2_Size]; // size of the LCP
	vector<int> res(c);

	// myers trace from the end
	while ((i != 0) & (j != 0) & (c != 0))
	{
		while (distance[i - 1][j] == c) 
			i--;
		while (distance[i][j - 1] == c) 
			j--;
		res[c - 1] = seq1[i - 1];
		c--;
	}

	if (res.size()) cout << res[0];
	for (i = 1; i < res.size(); i++) cout << ' ' << res[i];
}

int main()
{
	int n, m, i, t;

	cin >> n;
	cin >> m;

	vector<int> a;
	for (i = 0; i < n; i++) {
		cin >> t;
		a.push_back(t);
	}

	vector<int> b;
	for (i = 0; i < m; i++) {
		cin >> t;
		b.push_back(t);
	}

	if (n < m)
		lcs(b, a);
	else
		lcs(a, b);

	system("pause");
	return 0;
}
