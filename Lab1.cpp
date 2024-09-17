#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int generateInt() {
    return rand() % 10 + 1;
}

int** generateMatrix(int rows, int columns) {
    int** mas = new int* [rows];
    for (int i = 0; i < rows; i++) {
        int* array = new int[columns];
        for (int j = 0; j < columns; j++) {
            array[j] = rand() % 10 + 1;
        }
        mas[i] = array;
    }
    return mas;
}

void printMatrix(int** mas, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << mas[i][j] << " ";
        }
        cout << endl;
    }
}

int countOnes(int num) {
    int cnt = 0;
    while (num > 0) {
        cnt += num % 2;
        num = num / 2;
    }
    return cnt;
}

void oneFlow(int** matrix, int M, int N) {

    for (int k = 0; k < M; k++) {
        int result = 0;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                result += countOnes(matrix[k][i] * matrix[k][j]);
            }
        }
    }

}

void Lab1() {
    srand(time(NULL));
    // generate parameters
    int M = 1000;
    int N = 1000;
    cout << M << " " << N << endl;

    int** matrix = generateMatrix(M, N);

    int i, j, k;
    int result;
    double start;
    double end;

    start = omp_get_wtime();

    // count ones in binary
    #pragma omp parallel shared(matrix, result) private(k) num_threads(15)
    {
        #pragma omp for private(i, j) collapse(3)
        for (k = 0; k < M; k++) {
            result = 0;
            for (i = 0; i < N; i++) {
                for (j = i + 1; j < N; j++) {
                    result += countOnes(matrix[k][i] * matrix[k][j]);
                }
            }

        }
    }

    end = omp_get_wtime();

    // printing
    //printMatrix(matrix, M, N);

    cout << "Work took " << end - start << " seconds\n";

    start = omp_get_wtime();

    for (k = 0; k < M; k++) {
        result = 0;
        for (i = 0; i < N; i++) {
            for (j = i + 1; j < N; j++) {
                result += countOnes(matrix[k][i] * matrix[k][j]);
            }
        }
    }

    end = omp_get_wtime();

    cout << "Work with 1 flow took " << end - start << " seconds\n";
}

void Lab2() {
    const int NMAX = 886;
    const int LIMIT = 885;
    int i, j;
    float sum;
    float** a = new float* [NMAX];
    double start;
    double end;

    cout << NMAX << endl;

    for (i = 0; i < NMAX; i++) {
        a[i] = new float[NMAX];
        for (j = 0; j < NMAX; j++)
            a[i][j] = (float) i + j;
    }


    start = omp_get_wtime();

    for (i = 0; i < NMAX; i++)
    {
        sum = 0;
        for (j = 0; j < NMAX; j++)
            sum += a[i][j];
    }

    end = omp_get_wtime();
    cout << "Work with 1 flow took " << end - start << " seconds\n";

    start = omp_get_wtime();
    #pragma omp parallel shared(a) if (NMAX>LIMIT)
    {
        #pragma omp for private(i,j,sum) 
        for (i = 0; i < NMAX; i++)
        {
            sum = 0;
            for (j = 0; j < NMAX; j++)
                sum += a[i][j];
        }
    }
    end = omp_get_wtime();

    cout << "Work took " << end - start << " seconds\n";

}

int main()
{
    //Lab1();
    Lab2();

    return 0;

}

