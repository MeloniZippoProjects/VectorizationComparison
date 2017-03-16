#include <cstdlib>
#include <ctime>
#include <fstream>
#include <thread>

using namespace std;

void matrixComputationWorker(float **A, float **B, int size)
{
	for (int i = 0; i < 10; i++)
	{
		for (int i = 0; i < size; i++)
		{
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

int main(int argc, char* argv[])
{
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

	ofstream txt("results_yTyV.txt");
	double total_time = 0;
	int times = 15;

	for (int i = 0; i < times; i++)
	{
		clock_t start = clock();
		matrixComputation(A, B, size);
		double duration = (clock() - start) / ((double)CLOCKS_PER_SEC);
		total_time += duration;

		txt << duration << endl;
	}

	txt << endl << "Mean: " << total_time / times << endl;
}