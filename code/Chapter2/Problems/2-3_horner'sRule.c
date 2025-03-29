// Problem 2-3
int horner(int arr[], int n, int x)
{
    int p = 0;
    for (int i = n - 1; i >= 0; i--)
        p = arr[i] + p * x;
    return p;
}