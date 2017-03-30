#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <thread>

using namespace std;

void matrixComputationWorker(float **A, float **B, int size)
{
	#pragma loop(no_vector)
	for (int i = 0; i < 10; i++)
	{
		#pragma loop(no_vector)
		for (int i = 0; i < size; i++)
		{
			#pragma loop(no_vector)
			for (int j = 0; j < size; j++)
			{
				A[i][j] += B[i][j];
			}
		}
	}
}

void matrixComputation(float **A, float **B, int size)
{
	thread t1(matrixComputationWorker, A, B, size / 2);
	thread t2(matrixComputationWorker, A + size / 2, B, size / 2);
	thread t3(matrixComputationWorker, A, B + size / 2, size / 2);
	thread t4(matrixComputationWorker, A + size / 2, B + size / 2, size / 2);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
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
		return;

	int size = atoi(argv[1]);

	float **A = new float*[size];
	float **B = new float*[size];

	for (int i = 0; i < size; i++)
	{
		A[i] = new float[size];
		B[i] = new float[size];

		for (int j = 0; j < size; j++)
		{
			A[i][j] = rand() * (float)(1 << 15);
			B[i][j] = rand() * (float)(1 << 15);
		}
	}

	ofstream txt("results_yTnV.txt");
	txt.clear();
	int tests = 40;
	vector<double> results;

	for (int i = 0; i < tests; i++)
	{
		clock_t start = clock();
		matrixComputation(A, B, size);
		double duration = (clock() - start) / ((double)CLOCKS_PER_SEC);

		results.push_back(duration);
	}

	txt << "Mean: " << mean(results) << " +- " << ci(results) << endl;
	txt << endl;
	for (double value : results)
	{
		txt << value << endl;
	}
}