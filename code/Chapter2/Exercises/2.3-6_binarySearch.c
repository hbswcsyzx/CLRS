// Exercise 2.3-6
int interativeBinarySearch(int arr[], int x, int low, int high)
{
    while (low <= high)
    {
        int mid = (high - low) / 2 + low;
        if (x == arr[mid])
            return mid;
        else if (x > arr[mid])
            low = mid + 1;
        else
            high = mid - 1;
        return -1;
    }
}

int recursiveBinarySearch(int arr[], int x, int low, int high)
{
    if (low > high)
        return -1;
    int mid = (high - low) / 2 + low;
    if (x == arr[mid])
        return mid;
    else if (x > arr[mid])
        return recursiveBinarySearch(arr, x, mid + 1, high);
    else
        return recursiveBinarySearch(arr, x, low, high - 1);
}