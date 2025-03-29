void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1; // length of the left half of A
    int n2 = r - m;     // length of the right half of A

    int L[n1], R[n2]; // valid

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i]; // copy left part into L
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j]; // copy right part into R

    i = 0; // the smallest remaining element in L
    j = 0; // the smallest remaining element in R
    k = l; // the location in A to fill
    // As long as each of the arrays L and R contains an unmerged element,
    //     copy the smallest unmerged element back into array A.
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Having gone through one of L and R entirely,
    //     copy the remainder of the other to the end of A.
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    // if zero or one element, return directly
    if (l < r)
    {
        int m = l + (r - l) / 2;  // midpoint of A
        mergeSort(arr, l, m);     // recursively sort left part of A
        mergeSort(arr, m + 1, r); // recursively sort right part of A
        // Merge two halves
        merge(arr, l, m, r);
    }
}