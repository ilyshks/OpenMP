#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

int generateInt() {
    return rand() % 10 + 1;
}

int* generateArray(int columns) {
    int* mas = new int[columns];
    for (int i = 0; i < columns; i++) {
        mas[i] = rand() % 100 + 1;
    }
    return mas;
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

void printArray(int* mas, int columns) {
    for (int i = 0; i < columns; i++) {
        cout << mas[i] << " ";
    }
    cout << endl;
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
    int M = 100;
    int N = 100;
    cout << M << " " << N << endl;

    int** matrix = generateMatrix(M, N);

    int i, j, k;
    int result;
    double start;
    double end;

    start = omp_get_wtime();

    // count ones in binary
    #pragma omp parallel shared(matrix, result) private(k) num_threads(7)
    {
        #pragma omp for private(i, j) collapse(2)
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
    const int NMAX = 1500;
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

void Lab3() {
    int N = 1000000;
    int* A = generateArray(N);
    int* B = generateArray(N);
    int* C = new int[N];
    int s = 0;
    double start;
    double end;

    start = omp_get_wtime();

    #pragma omp parallel shared(A, B, C)
    {
    #pragma omp for reduction(+:s)
        for (int i = 0; i < N; i++) {
            C[i] = max(A[i], B[i]);
            s += C[i];
        }
    }
    end = omp_get_wtime();
    //printArray(A, N);
    //printArray(B, N);
    //printArray(C, N);
    cout << "N = " << N << endl << endl;
    cout << "S = " << s << endl;
    cout << "Work took " << end - start << " seconds\n\n";

    s = 0;
    start = omp_get_wtime();

    for (int i = 0; i < N; i++) {
        C[i] = max(A[i], B[i]);
        s += C[i];
    }

    end = omp_get_wtime();
    cout << "S = " << s << endl;
    cout << "Work with 1 flow took " << end - start << " seconds\n";
}

int main()
{
    srand(time(NULL));
    //Lab1();
    //Lab2();
    Lab3();

    return 0;

}

