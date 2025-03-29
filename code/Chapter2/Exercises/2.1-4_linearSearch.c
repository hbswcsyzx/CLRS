// Exercise 2.1-4
int linearSearch(int arr[], int n, int x)
{
    int i = 0;
    while (i < n && arr[i] != x)
        i++;
    if (i < n)
        return i;
    else
        return -1;
}