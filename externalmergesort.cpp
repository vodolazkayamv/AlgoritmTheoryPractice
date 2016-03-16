/*
 
Time limit 2000000/4000/4000/4000 ms. Memory limit 4096/65000/65000/65000 Kb. 

В первой строке файла находится число N (10^6 ≤ N ≤ 10^8), а во второй - N целых чисел, по модулю не превышающих 10^6.

Выведите N чисел в порядке неубывания, используя метод внешней сортировки.

Ввод				Вывод
1000000
3 1 2 4 ... 2		1 2 2 3 ... 4


 */


#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdio>
#include <sys/stat.h>
 
using namespace std;

struct oss // ordered sub sequence
{
	long int length;  // oss capacity
	long int offset;  // oss first element offset from the file begining
};

struct files
{
	FILE* Generic; // input data
	FILE* OSS;     // oss data
	bool sorted;   
};


//
// control print methods
//

void ShowFile(FILE *File)
{
	//rewind(File);
	fseek(File , 0L , SEEK_SET );
	long int a = 0;
	int i = 0;
	while (!feof(File))
	{		
		a = 0;
		if (fread(&a, sizeof(long int), 1, File) == 1)
		{
			cout << a << " ";
		}
		else
			break;
	}
	cout << "\n";
}

void ShowOSSFile(FILE *OSSFile, FILE* GenericFile)
{
	rewind(OSSFile);
	oss a;
	while (!feof(OSSFile))
	{		
		if (fread(&a, sizeof(oss), 1, OSSFile) == 1)
		{
			long int val = 0;
			fseek(GenericFile, a.offset * sizeof(long int), SEEK_SET);
			for( int i = 0; i < a.length; i++)
				if (fread(&val, sizeof(long int), 1, GenericFile) == 1)
					cout << val << " ";
				else
					break;
			cout << "| ";
		}
		else
			break;
	}
	cout << "\n";
}

//
// find OSS in file
//
oss FindOSS(FILE *GenericFile)
{
	oss found;

	long int a1, a2;

	// oss contains at least one element
	fread(&a1, sizeof(long int),1, GenericFile);
	found.length = 1;
	found.offset = (ftell(GenericFile))/sizeof(long int) - 1;

	// if next element is in order -> expand oss capacity
	while (! feof(GenericFile))
    {
        if (fread(&a2, sizeof(long int), 1, GenericFile) != 0)
			if (a2 >=  a1)
			{
				found.length++;
			}
			else {
				// rewind cursor to previous position (one element back)
				fseek(GenericFile, -(sizeof(long int)), SEEK_CUR);
				break;
			}
		// move along
        a1 = a2;
    }

	return found;
}


//
// Merge OSSs method
//
files Merge (FILE* OSSs, FILE* GenericFile)
{
	files result;
	result.Generic = tmpfile();
	result.OSS = tmpfile();

	fseek(OSSs,0,SEEK_END);
	long int struct_count = ftell(OSSs)/sizeof(oss);

	if (struct_count == 1)
	{
		//recursion ends
		fclose(result.Generic);
		fclose(result.OSS);
		result.sorted = true;
		return result;
	} 
	else
	{
		oss merged;
		rewind(OSSs);

		while(!feof(OSSs))
		{
			oss a, b;
			if (fread(&a, sizeof(oss), 1, OSSs) != 1)
			{
				result.sorted = false;
				return result;
			}
			long int index1 = 0;
			long int index2 = 0;
			if (fread(&b, sizeof(oss), 1, OSSs) != 1)
			{
				merged.length = a.length;
				merged.offset = ftell(result.Generic)/sizeof(long int);
				fwrite(&merged, sizeof(oss), 1, result.OSS);
				long int val1 = 0;
				while (index1 <= a.length)
					{												
						fseek(GenericFile, (a.offset + index1) * sizeof(long int), SEEK_SET); 
						fread(&val1, sizeof(long int), 1, GenericFile);
						fwrite(&val1, sizeof(long int), 1, result.Generic);
						//ShowFile(result.Generic);
						index1++;
					}
				result.sorted = false;
				return result;
				}
			else
			{			
				merged.length = a.length + b.length;
				merged.offset = ftell(result.Generic)/sizeof(long int);
				fwrite(&merged, sizeof(oss), 1, result.OSS);

				long int val1 = 0, val2 = 0;
				fseek(GenericFile, (a.offset + index1) * sizeof(long int), SEEK_SET);
				fread(&val1, sizeof(long int), 1, GenericFile);
				index1++;

				fseek(GenericFile, (b.offset + index2) * sizeof(long int) , SEEK_SET);
				fread(&val2, sizeof(long int), 1, GenericFile);
				index2++;

				//слияние двух структур в одну 
				while(index1 <= a.length && index2 <= b.length)
				{
					if (val1 < val2)
					{
						fwrite(&val1, sizeof(long int), 1, result.Generic);
						//ShowFile(result.Generic);
						fseek(GenericFile, (a.offset + index1) * sizeof(long int) , SEEK_SET); 
						fread(&val1, sizeof(long int), 1, GenericFile);
						index1++;
					}
					else
					{
						fwrite(&val2, sizeof(long int), 1, result.Generic);
						//ShowFile(result.Generic);
						fseek(GenericFile, (b.offset + index2) * sizeof(long int), SEEK_SET);
						fread(&val2, sizeof(long int), 1, GenericFile);
						index2++;
					}
				}
				if (index1 > a.length) //закончилась первая УПП
				{
					while (index2 <= b.length)
					{
						fwrite(&val2, sizeof(long int), 1, result.Generic);
						//ShowFile(result.Generic);
						fseek(GenericFile, (b.offset + index2) * sizeof(long int), SEEK_SET);
						fread(&val2, sizeof(long int), 1, GenericFile);
						index2++;
					}
				}
				else if (index2 > b.length) //закончилась вторая УПП
				{
					while (index1 <= a.length)
					{
						fwrite(&val1, sizeof(long int), 1, result.Generic);
						//ShowFile(result.Generic);
						fseek(GenericFile, (a.offset + index1) * sizeof(long int), SEEK_SET); 
						fread(&val1, sizeof(long int), 1, GenericFile);
						index1++;
					}
				}
			}
		}
	}

	result.sorted = false;
	return result;
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	FILE* GenericFile = tmpfile(); 
	//FILE* ResultFile = fopen("Result.txt", "w+");
	//freopen("Result.txt","w",stdout);
	long int N = 0; //количество элементов
	cin >> N; 

	for (int i = 0; i < N; i++)
	{
		long int elem = 0;
		cin >> elem;
		//elem = rand() %10;
		fwrite(&elem, sizeof(long int), 1, GenericFile);
	}
	fflush(GenericFile);
	//rewind(GenericFile);
	long size = 0;
	fseek(GenericFile, 0, SEEK_END);
	size = ftell(GenericFile);
	fseek(GenericFile, 0, SEEK_SET);
	
	/*
	cout << "GenericFile: ";
	ShowFile(GenericFile);
	rewind(GenericFile);
	cout << "\n\n";
	*/

	FILE* OSSs = tmpfile();
	while (!feof(GenericFile))
	{
		oss found = FindOSS(GenericFile);
		fwrite(&found, sizeof(oss), 1, OSSs);
	}

	/*
	cout << "OSSs File: ";
	ShowOSSFile(OSSs,GenericFile);
	rewind(GenericFile);
	cout << "\n";
	*/

	files f;

	do
	{
		f = Merge(OSSs,GenericFile);
	
		if (f.sorted)
			break;

		fclose(OSSs);
		fclose(GenericFile);
		OSSs = f.OSS;
		GenericFile = f.Generic;

	} while (!f.sorted);

	//cout << "GenericFile: ";
	ShowFile(GenericFile);
	//rewind(GenericFile);
	//cout << "\n\n";

	//system("pause");

	return 0;
}