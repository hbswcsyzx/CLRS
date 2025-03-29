// Exercise 2.1-5
int *addBinaryIntegers(int A[], int B[], int n)
{
    int *C = (int *)malloc((n + 1) * sizeof(int));
    int carry = 0;
    for (int i = 0; i < n; i++)
    {
        int sum = A[i] + B[i] + carry;
        C[i] = sum % 2;
        if (sum < 2)
            carry = 0;
        else
            carry = 1;
    }
    C[n] = carry;
    return C; // 必须用malloc，否则返回值为局部变量
}