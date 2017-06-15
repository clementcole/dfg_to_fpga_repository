#include <complex>
#include <iostream>
#include <valarray>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <bitset>
#include "ieee754_converter.hpp"


#include <stdint.h>

int32_t __32_bit_int__;

const double PI = 3.141592653589793238460;
 
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
#define rdtsc __asm __emit 0fh __asm __emit 031h
#define cpuid __asm __emit 0fh __asm __emit 0a2h

#define CPUID __asm __emit 0fh __asm __emit 0a2h
#define RDTSC __asm __emit 0fh __asm __emit 031h


//typedef std::vector<Complex> CArray;
using namespace std;
time_t start = time(0);

template <typename T> 
inline void print(const char* name, T value)
{
	cout << name << " = "
		 << bitset <8> (value).to_string()
		 << " = "
		 << (int)value << endl;
}

int histogram_compute_blue(int data)
{
	data = data + 1;
	data = data & (255);
	return data;
}

int histogram_compute_green(int data)
{
	data = data >> (8);
	data = data & 255;
	return data;
}

int histogram_compute_red(int data)
{
	data = data >> (16);
	data = data & 255;
	return data;
}

void histogram(vector<int>& row, vector<int>& col, vector<int>& Hred, vector<int>& Hgreen, vector<int>& Hblue)
{
	int datar, datag, datab = 0;
	for (int i = 0; i < row.size(); i ++)
	{
		datar = row[i];
		datag = row[i];
		datab = row[i];
		Hred.push_back(histogram_compute_blue(datar));
		Hgreen.push_back(histogram_compute_green(datag));
		Hblue.push_back(histogram_compute_red(datab));
	}
}

int main()
{

	//ofstream outfile;
	//outfile.open("histogram_output.txt");
	//outfile  << setfill('0') << setw(8) << hex << 2005 << endl;
	vector<int> row = {
		550, 620, 820, 960, 150, 780, 900, 820, 560, 1200, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
	};
	vector<int> red;
	vector<int> blue;
	vector<int> green;
	vector<int> col ={0};
	histogram(row, col, red, green, blue);
	for (int i = 0; i < red.size(); i++)
		{cout << "	red: "<<red[i] << " green:" <<green[i]<< " blue:"<<blue[i]<<endl;}

	for (int i = 0; i < green.size(); i++) cout << green[i] << endl;
	//int j;
	//bitset<32> bitset1{j};
	//cout << bitset1 << endl;
	cout<< (4 & 5) <<endl;
	return 0;
}