#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

void matrixComputation(float *A, float *B, float *C, int size)
{
#pragma vector aligned
	for (int i = 0; i < size; i++)
	{
		C[i] = (A[i] + B[i])*(A[i] - B[i]);
	}
}

double mean(vector<double> results)
{
	double sum = 0;
	for (double v : results)
	{
		sum += v;
	}
	return sum / results.size();
}

double sampleStdDeviation(vector<double> results)
{
	double m = mean(results);
	double sampleVariance = 0;

	for (int i = 0; i < (results.size() - 1); i++)
	{
		double diff = results[i] - m;
		sampleVariance += diff * diff;
	}

	sampleVariance /= (results.size() - 1);
	return sqrt(sampleVariance);
}

double ci(vector<double> results)
{
	return 1.96 * (sampleStdDeviation(results) / sqrt(results.size()));
}

int main(int argc, char* argv[])
{
	if (argc < 2)
		return 1;

	size_t reps = atoi(argv[1]);
	size_t size = 8 * 25000;
	size_t align = 16;

	float *A = (float*)_mm_malloc(size * sizeof(float), align);
	float *B = (float*)_mm_malloc(size * sizeof(float), align);
	float *C = (float*)_mm_malloc(size * sizeof(float), align);

	for (int i = 0; i < size; ++i)
	{
		A[i] = rand() * (float)(1 << 15);
		B[i] = rand() * (float)(1 << 15);
		C[i] = rand() * (float)(1 << 15);
	}

	ofstream txt("results_nTbV.txt");
	txt.clear();
	int tests = 150;
	vector<double> results;

	for (int i = 0; i < tests; i++)
	{
		clock_t start = clock();
		for (int j = 0; j < reps; ++j)
		{
			matrixComputation(A, B, C, size);
		}
		double duration = (clock() - start) / ((double)CLOCKS_PER_SEC);

		results.push_back(duration);
		Sleep(50);
	}

	txt << "Mean: " << mean(results) << " +- " << ci(results) << endl;
	txt << endl;
	for (double value : results)
	{
		txt << value << endl;
	}
	txt.close();

#define MAX 5
	int  a[2], b[2], x[2], x2[2], index[2], n, length, s;

	for (j = 1; j<MAX; j++)  
		a[j] = a[j - n] + b[j];

#define SIZE 5

	for (int i = 0; i<SIZE; i += 2)  
		b[i] += a[i] * x[i];

	for (int i = 0; i<length; i++)
		if (s >= 0) 
			x2[i] = (-b[i] + sqrt(s)) / (2.*a[i]);

	for (int i = 0; i<SIZE; i++)
		b[i] += a[i] * x[index[i]];

}
