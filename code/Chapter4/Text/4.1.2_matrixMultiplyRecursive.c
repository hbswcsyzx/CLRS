// Assuming n is an integer power of 2
void matrixMultiplyRecursive(int **A, int **B, int **C, int n, int aRow, int aCol, int bRow, int bCol, int cRow, int cCol)
{
    if (n == 1) // Base case
    {
        C[cRow][cCol] += A[aRow][aCol] * B[bRow][bCol];
        return;
    }
    int half = n / 2;
    // Divide and conquer
    // A11, B11, C11
    matrixMultiplyRecursive(A, B, C, half, aRow, aCol, bRow, bCol, cRow, cCol);
    // A11, B12, C12
    matrixMultiplyRecursive(A, B, C, half, aRow, aCol, bRow, bCol + half, cRow, cCol + half);
    // A21, B11, C21
    matrixMultiplyRecursive(A, B, C, half, aRow + half, aCol, bRow, bCol, cRow + half, cCol);
    // A21, B12, C22
    matrixMultiplyRecursive(A, B, C, half, aRow + half, aCol, bRow, bCol + half, cRow + half, cCol + half);
    // A12, B21, C11
    matrixMultiplyRecursive(A, B, C, half, aRow, aCol + half, bRow + half, bCol, cRow, cCol);
    // A12, B22, C12
    matrixMultiplyRecursive(A, B, C, half, aRow, aCol + half, bRow + half, bCol + half, cRow, cCol + half);
    // A22, B21, C21
    matrixMultiplyRecursive(A, B, C, half, aRow + half, aCol + half, bRow + half, bCol, cRow + half, cCol);
    // A22, B22, C22
    matrixMultiplyRecursive(A, B, C, half, aRow + half, aCol + half, bRow + half, bCol + half, cRow + half, cCol + half);
}