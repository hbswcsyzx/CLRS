// Exercise 2.3-5
void recursiveInsertionSort(int arr[], int n)
{
    if (n > 1)
    {
        recursiveInsertionSort(arr, n - 1);
        int key = arr[n - 1];
        int j = n - 2;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}