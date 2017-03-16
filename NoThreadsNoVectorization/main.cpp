#include <cstdlib>
#include <ctime>

#include <fstream>

using namespace std;

void matrixComputation(float **A, float **B, int size)
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

	ofstream txt("results_nTnV.txt");
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