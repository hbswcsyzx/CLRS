// Problem 2-4
// modeled on merge sort, count while merging
// 0-indexed, l & r represent the index rather than num
int mergeInversions(int arr[], int l, int m, int r)
{
    // two halves already sorted
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2]; // valid

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    int inversions = 0; // initialize

    while (i < n1 && j < n2)
        if (L[i] > R[j]) // 官方solution有误
        {
            arr[k++] = R[j++];
            inversions += n1 - i;
        }
        else
            arr[k++] = L[i++];

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
    return inversions;
}

int countInversions(int arr[], int l, int r)
{
    int inversions = 0;
    if (l < r)
    {
        int m = l + (r - l) / 2;
        inversions += countInversions(arr, l, m);
        inversions += countInversions(arr, m + 1, r);
        inversions += mergeInversions(arr, l, m, r);
    }
    return inversions;
}