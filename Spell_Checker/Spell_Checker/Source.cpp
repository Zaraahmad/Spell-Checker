#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <fstream>
#include"windows.h"
#include "myconsole.h"
#include "color.h"
#include <conio.h>
using namespace std;

class BitVector
{
	unsigned char *bytes;
	int n;

public:
	BitVector(int bno=728000){
		n = bno;
		int size = ceil(n / 8);
		bytes = new unsigned char[size];
		for (int i = 0; i < size; i++){
			bytes[i] = '0';
		}

	}

	void set(int k)
	{
		int byteno = k / 8;
		int bno = k % 8;
		unsigned char mask = 0x80;
		mask = mask >> bno;
		bytes[byteno] = bytes[byteno] | mask;
	}

	void clear(int k)
	{
		int byteno = k / 8;
		int bno = k % 8;
		unsigned char mask = 0x80;
		mask = mask >> bno;
		bytes[byteno] = bytes[byteno] & !mask;
	}

	bool get(int k)
	{
		int byteno = k / 8;
		int bno = k % 8;
		unsigned char mask = 0x80;
		mask = mask >> bno;
		return (mask & bytes[byteno]);
	}

	void print()
	{
		cout << "strat\n";
		for (int i = 0; i < n / 8; i++)
			cout << bytes[i];// << endl;
		cout << "end\n";
	}
};

class BloomFilter
{
private:
	int p = 16777213;	//prime number
	int *a;	//for storing 6 random a
	//int *px;	
	string *dic;	//for reading the dictionary
	BitVector myBitVec;	//object of bit vector
	
	int genRand()
	{
		
		int size = 23;	//23 bits long
		int a[23];
		unsigned int num = 0, mul = 0;

		//srand(time(0));

		do {
			for (int i = 0; i < 23; i++)
				a[i] = rand() % 2;

			
			for (int i = size - 1; i >= 0; i--)
			{
				num = num + a[i] * pow(2, mul);
				mul = mul + 1;
			}

		} while (num > p);

		return num;
	}

	void readDic()
	{
		float size = 91000;int i = 0;
		dic = new string[size];
		ifstream inputStream("dict.txt");
		if (inputStream.is_open())
		{
			cout << "Loading dictionary";
			while (!inputStream.eof())
			{
				//inputStream >> dic[i];
				getline(inputStream, dic[i], '\n');
				i++;
				int q= i / size * 100.0;
				PlaceCursor(20, 0);
				cout << q;
				//Sleep(500);
				//ClearScreen();
				
			}
			//PlaceCursor(20, 0);
			//	cout << "100";
			cout << endl;
			
	
		}
	}

	void readFile()
	{
		//int size = 1000, i = 0;
		//dic = new string[size];
		string word;
		char c;
		char arr[30];
		bool found;
		int count = 0;
		ifstream inputStream("check.txt");
		if (inputStream.is_open())
		{
			while (!inputStream.eof())
			{
				found = true;
				inputStream.get(c);
				if (c >= 65 && c <= 90)
				{
					int i = c - 65;
					c = i + 97;
				}
				if(c >= 79 && c <= 122 || c >=48 && c <= 57)
				{
					arr[count] = c;
					count++;
					arr[count] = NULL;
				}
				//inputStream >> word;
				else
				{
					if(!inputStream.eof()){
						count = 0;
						word = string(arr);
						//cout << word << endl;
					
						int size = word.length();
						int h;
						for (int j = 0; j < 6 && found; j++) {
							h = calhx(a[j], word, size);
							found = myBitVec.get(h);
						}
						if (!found){
							gotorc(4);
							cout << word << " ";
						}
						else
						{
							gotorc(15);
							cout << word << " ";
						}
					}
				}
			}

		}
	}

	int calPow(int a, int pow)
	{
		if (pow == 0)
			return 1;
		if (pow == 1)
			return a;
		else
		{
			int ans = a;
			for (int i = 0; i < pow - 1; i++)
				ans = (ans % p * a % p) % p;
			
			return ans;
		}
	}	

	int calhx(int a, string dict, int size)
	{
		unsigned int sum=0, term, hx;
		int pow = size - 1;
		for (int i = 0; i < size; i++)
		{
			term = dict[i] * calPow(a, pow);
			sum = ((sum % p) + (term % p)) % p;
			pow = pow - 1;
		}

		hx = (sum % p) % 728000;
		return hx;
	}

	void hashing()
	{
		for (int i = 0; i < 91000; i++)
		{
			int size = dic[i].length();
			int h;
			for(int j = 0; j < 6; j++){
				h = calhx(a[j], dic[i], size);
				myBitVec.set(h);				
			}		
		}

	}

public:
	
	BloomFilter()
	{
		a = new int[6];
		for (int i = 0; i < 6; i++)
			a[i] = genRand();
		readDic();
		
		hashing();
		readFile();
		//cout << "done\n";
	}
	
};

int main()
{
	BloomFilter b_fltr;
	_getch();
	return 0;
}