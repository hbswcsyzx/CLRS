// Exercise 2.3-8
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int hasTwoSum(int arr[], int n, int sum)
{
    if (n < 2)
        return 0; // 不足两个元素

    qsort(arr, n, sizeof(int), compare); // 排序 O(nlogn)

    int left = 0, right = n - 1;
    while (left < right)
    {
        int current_sum = arr[left] + arr[right];
        if (current_sum == sum)
            return 1; // 找到解
        else if (current_sum < sum)
            left++; // 必须增大和，故左指针右移
        else
            right--; // 必须减小和，故右指针左移
    }
    return 0; // 未找到
}