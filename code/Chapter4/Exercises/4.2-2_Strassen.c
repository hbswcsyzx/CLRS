// Exercise 4.2-2
// many thanks to https://www.oryoy.com/news/jie-mi-strassen-suan-fa-c-yu-yan-shi-xian-gao-xiao-ju-zhen-cheng-fa-ao-mi-a14229004.html
// and https://www.doubao.com/
#include <stdio.h>
#include <stdlib.h>

// 创建并初始化一个 size×size 的矩阵
double **createMatrix(int size)
{
    double **matrix = (double **)malloc(size * sizeof(double *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (double *)malloc(size * sizeof(double));
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = 0; // 初始化矩阵元素为 0
        }
    }
    return matrix;
}

// 分割矩阵，将 A 中从 (row, col) 开始的子矩阵复制到 subMatrix
void partition(double **A, double **subMatrix, int n, int row, int col)
{
    int half = n / 2;
    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            subMatrix[i][j] = A[row + i][col + j];
        }
    }
}

// 释放矩阵内存
void freeMatrix(double **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// Strassen 矩阵乘法核心函数
void STRASSEN(double **A, double **B, double **C, int n)
{
    if (n == 1)
    {
        C[0][0] += A[0][0] * B[0][0];
        return;
    }
    int half = n / 2;

    // 分割矩阵 A、B、C 为子矩阵
    double **A11 = createMatrix(half);
    double **A12 = createMatrix(half);
    double **A21 = createMatrix(half);
    double **A22 = createMatrix(half);
    double **B11 = createMatrix(half);
    double **B12 = createMatrix(half);
    double **B21 = createMatrix(half);
    double **B22 = createMatrix(half);
    double **C11 = createMatrix(half);
    double **C12 = createMatrix(half);
    double **C21 = createMatrix(half);
    double **C22 = createMatrix(half);

    partition(A, A11, n, 0, 0);
    partition(A, A12, n, 0, half);
    partition(A, A21, n, half, 0);
    partition(A, A22, n, half, half);
    partition(B, B11, n, 0, 0);
    partition(B, B12, n, 0, half);
    partition(B, B21, n, half, 0);
    partition(B, B22, n, half, half);
    partition(C, C11, n, 0, 0);
    partition(C, C12, n, 0, half);
    partition(C, C21, n, half, 0);
    partition(C, C22, n, half, half);

    // 创建中间矩阵 S1-S10 和 P1-P7
    double **S1 = createMatrix(half);
    double **S2 = createMatrix(half);
    double **S3 = createMatrix(half);
    double **S4 = createMatrix(half);
    double **S5 = createMatrix(half);
    double **S6 = createMatrix(half);
    double **S7 = createMatrix(half);
    double **S8 = createMatrix(half);
    double **S9 = createMatrix(half);
    double **S10 = createMatrix(half);
    double **P1 = createMatrix(half);
    double **P2 = createMatrix(half);
    double **P3 = createMatrix(half);
    double **P4 = createMatrix(half);
    double **P5 = createMatrix(half);
    double **P6 = createMatrix(half);
    double **P7 = createMatrix(half);

    // 计算中间矩阵 S1-S10
    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            S1[i][j] = B12[i][j] - B22[i][j];
            S2[i][j] = A11[i][j] + A12[i][j];
            S3[i][j] = A12[i][j] + A22[i][j];
            S4[i][j] = B21[i][j] - B11[i][j];
            S5[i][j] = A11[i][j] + A22[i][j];
            S6[i][j] = B11[i][j] + B22[i][j];
            S7[i][j] = A12[i][j] - A22[i][j];
            S8[i][j] = B21[i][j] + B22[i][j];
            S9[i][j] = A11[i][j] - A21[i][j];
            S10[i][j] = B11[i][j] + B12[i][j];
        }
    }

    // 递归计算 P1-P7
    STRASSEN(A11, S1, P1, half);
    STRASSEN(S2, B22, P2, half);
    STRASSEN(S3, B11, P3, half);
    STRASSEN(A22, S4, P4, half);
    STRASSEN(S5, S6, P5, half);
    STRASSEN(S7, S8, P6, half);
    STRASSEN(S9, S10, P7, half);

    // 组合结果到 C 的子矩阵
    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            C11[i][j] += P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
            C12[i][j] += P1[i][j] + P2[i][j];
            C21[i][j] += P3[i][j] + P4[i][j];
            C22[i][j] += P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
        }
    }

    // 合并子矩阵到 C
    for (int i = 0; i < half; i++)
    {
        for (int j = 0; j < half; j++)
        {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    // 释放所有中间矩阵的内存
    freeMatrix(A11, half);
    freeMatrix(A12, half);
    freeMatrix(A21, half);
    freeMatrix(A22, half);
    freeMatrix(B11, half);
    freeMatrix(B12, half);
    freeMatrix(B21, half);
    freeMatrix(B22, half);
    freeMatrix(C11, half);
    freeMatrix(C12, half);
    freeMatrix(C21, half);
    freeMatrix(C22, half);
    freeMatrix(S1, half);
    freeMatrix(S2, half);
    freeMatrix(S3, half);
    freeMatrix(S4, half);
    freeMatrix(S5, half);
    freeMatrix(S6, half);
    freeMatrix(S7, half);
    freeMatrix(S8, half);
    freeMatrix(S9, half);
    freeMatrix(S10, half);
    freeMatrix(P1, half);
    freeMatrix(P2, half);
    freeMatrix(P3, half);
    freeMatrix(P4, half);
    freeMatrix(P5, half);
    freeMatrix(P6, half);
    freeMatrix(P7, half);
}

int main()
{
    int n = 4; // 假设矩阵大小为 4×4（2 的幂）
    double **A = createMatrix(n);
    double **B = createMatrix(n);
    double **C = createMatrix(n);

    // 简单初始化矩阵 A 和 B（可根据实际需求修改）
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = i + j;
            B[i][j] = j + 1;
        }
    }

    STRASSEN(A, B, C, n);

    // 输出结果矩阵 C
    printf("Result of Strassen matrix multiplication:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%9.3lf ", C[i][j]);
        }
        printf("\n");
    }

    // 释放矩阵 A、B、C 的内存
    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);

    return 0;
}