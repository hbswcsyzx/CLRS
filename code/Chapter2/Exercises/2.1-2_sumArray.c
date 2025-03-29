// Exercise 2.1-2
int sumArray(int arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum = sum + arr[i];
    return sum;
}