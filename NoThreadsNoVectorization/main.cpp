#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

void matrixComputation(float *A, float *B, float *C, int size)
{
	#pragma novector
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

	size_t size = atoi(argv[1]);
	size_t align = 32;

	float *A = (float*)_mm_malloc(size * sizeof(float), align);
	float *B = (float*)_mm_malloc(size * sizeof(float), align);
	float *C = (float*)_mm_malloc(size * sizeof(float), align);

	for (int i = 0; i < size; ++i)
	{
		A[i] = rand() * (float)(1 << 15);
		B[i] = rand() * (float)(1 << 15);
		C[i] = rand() * (float)(1 << 15);
	}

	ofstream txt("results_nTnV.txt");
	txt.clear();
	int tests = 40;
	vector<double> results;

	for (int i = 0; i < tests; i++)
	{
		clock_t start = clock();
		matrixComputation(A, B, C, size);
		double duration = (clock() - start) / ((double)CLOCKS_PER_SEC);

		results.push_back(duration);
	}

	txt << "Mean: " << mean(results) << " +- " << ci(results) << endl;
	txt << endl;
	for (double value : results)
	{
		txt << value << endl;
	}
	txt.close();
}