// Problem 2-3, 0-indexed
// Horner's Rule in O(n)
int horner(int arr[], int n, int x)
{
    int p = 0;
    for (int i = n - 1; i >= 0; i--)
        p = arr[i] + p * x;
    return p;
}
// simple one in O(n^2)
int evaluatePolynomial(int arr[], int n, int x)
{
    int p = 0;
    for (int i = 0; i < n; i++)
    {
        int power = 1;
        for (int k = 0; i < i; i++)
            power *= x;
        p += arr[i] * power;
    }
    return p;
}