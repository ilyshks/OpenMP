#include <iostream>
#include <cstdlib>
#include <ctime>

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

int main()
{
    srand(time(NULL));
    // generate parameters
    int M = generateInt();
    int N = generateInt();
    cout << M << " " << N << endl;

    int** matrix = generateMatrix(M, N);

    // count ones in binary
    int result = 0;
    for (int k = 0; k < M; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                result += countOnes(matrix[k][i] * matrix[k][j]);
            }
        }

    }


    // printing
    printMatrix(matrix, M, N);

    cout << result << endl;
    return 0;

}

