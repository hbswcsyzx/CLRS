// Problem 10-3
// 具体问题自行见答案
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NIL -1

int compactListSearch(int key[], int next[], int head, int n, int k);
int compactListSearchPrime(int key[], int next[], int head, int n, int k, int t);

int compactListSearch(int key[], int next[], int head, int n, int k)
{
    int i = head;
    while (i != NIL && key[i] < k)
    {
        int j = rand() % n + 1; // 生成1到n的随机数
        if (key[i] < key[j] && key[j] <= k)
        {
            i = j;
            if (key[i] == k)
            {
                return i;
            }
        }
        i = next[i];
    }
    if (i == NIL || key[i] > k)
    {
        return NIL;
    }
    else
    {
        return i;
    }
}

int compactListSearchPrime(int key[], int next[], int head, int n, int k, int t)
{
    int i = head;
    for (int q = 1; q <= t; q++)
    {
        int j = rand() % n + 1;
        if (key[i] < key[j] && key[j] <= k)
        {
            i = j;
            if (key[i] == k)
            {
                return i;
            }
        }
    }
    while (i != NIL && key[i] < k)
    {
        i = next[i];
    }
    if (i == NIL || key[i] > k)
    {
        return NIL;
    }
    else
    {
        return i;
    }
}

int main()
{
    srand(time(0)); // 初始化随机数种子

    // 示例数据
    int key[] = {1, 3, 5, 7, 9};
    int next[] = {1, 2, 3, 4, NIL};
    int head = 0;
    int n = 5;
    int k = 5;
    int t = 3;

    // 测试第一个函数
    int result1 = compactListSearch(key, next, head, n, k);
    if (result1 != NIL)
    {
        printf("compactListSearch找到元素，索引为: %d\n", result1);
    }
    else
    {
        printf("compactListSearch未找到元素\n");
    }

    // 测试第二个函数
    int result2 = compactListSearchPrime(key, next, head, n, k, t);
    if (result2 != NIL)
    {
        printf("compactListSearchPrime找到元素，索引为: %d\n", result2);
    }
    else
    {
        printf("compactListSearchPrime未找到元素\n");
    }

    return 0;
}