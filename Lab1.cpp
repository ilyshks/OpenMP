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
            array[j] = rand() % 1000 + 1;
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

int main()
{
    srand(time(NULL));
    int M = generateInt();
    int N = generateInt();
    cout << M << " " << N << endl;
    int** matrix = generateMatrix(M, N);
    printMatrix(matrix, M, N);
    return 0;

}

