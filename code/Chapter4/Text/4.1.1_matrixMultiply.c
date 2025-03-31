void matrixMultiply(int *A[], int *B[], int **C, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
}