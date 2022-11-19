#include <iostream>
#include "sort.h"

int main()
{
    using namespace std;
    long size=10000;
    int arr[7][size];
    srand(time(nullptr));
    for(int i=0;i<size;i++)
        arr[0][i]=arr[1][i]=arr[2][i]=arr[3][i]=arr[4][i]=arr[5][i]=arr[6][i]=rand();

    // test rank sort
    cout << "The result for rank-sort:";
    {
        clock_t start_v = clock();
        int index[size];
        Rank(arr[0],size,index);
        rankSort(arr[0],size,index);
        clock_t end_v = clock();
        cout << (double)(end_v-start_v)/CLOCKS_PER_SEC << endl;
    }

    // test rearrange rank sort
    cout << "The result for rearrange rank-sort:";
    {
        clock_t start_v = clock();
        int index[size];
        Rank(arr[1],size,index);
        rankSortIn(arr[1],size,index);
        clock_t end_v = clock();
        cout << (double)(end_v-start_v)/CLOCKS_PER_SEC << endl;
    }

    // test select sort
    cout << "The result for select-sort:";
    {
        clock_t start_v = clock();
        selectSort(arr[2],size);
        clock_t end_v = clock();
        cout << (double)(end_v-start_v)/CLOCKS_PER_SEC << endl;
    }

    // test rapid select sort
    cout << "The result for terminate-in-time select-sort:";
    {
        clock_t start_v = clock();
        selectSort_rapid(arr[3],size);
        clock_t end_v = clock();
        cout << (double)(end_v-start_v)/CLOCKS_PER_SEC << endl;
    }

    // test bubble sort
    cout << "The result for bubble-sort:";
    {
        clock_t start_v = clock();
        bubbleSort(arr[4],size);
        clock_t end_v = clock();
        cout << (double)(end_v-start_v)/CLOCKS_PER_SEC << endl;
    }

    // test rapid bubble sort
    cout << "The result for terminate-in-time bubble-sort:";
    {
        clock_t start_v = clock();
        bubbleSort_rapid(arr[5],size);
        clock_t end_v = clock();
        cout << (double)(end_v-start_v)/CLOCKS_PER_SEC << endl;
    }

    // test insert sort
    cout << "The result for insert-sort:";
    {
        clock_t start_v = clock();
        insertSort(arr[6],size);
        clock_t end_v = clock();
        cout << (double)(end_v-start_v)/CLOCKS_PER_SEC << endl;
    }

    cout << "Done.\n";
    return 0;
}

/* select sort */

template<class T>
int index4Max(T list[],int n)
{
    int max=0;
    for(int i=0;i<n;i++)
        if(list[i]>list[max])
            max=i;
    return max;
}

template<class T>
void swap(T &x,T &y)
{
    T t;
    t = x;
    x = y;
    y = t;
}

template<class T>
void selectSort(T list[],int n)
{
    for(int i=n-1;i>=0;i--)
    {
        swap(list[i],list[index4Max(list,i+1)]);
    }
}

template<class T>
void selectSort_rapid(T list[],int n)
{
    bool IsSorted=false;
    for(int i=n-1;!IsSorted&&i>=0;i--)
    {
        int max=0;
        IsSorted = true;
        for(int j=0;j<=i;j++)
            if(list[max]<=list[j])
                max=j;
            else
                IsSorted=false;
        swap(list[i],list[max]);
    }
}

/* rank sort two editions */

template<class T>
void Rank(T list[],int n,int rk[])
{
    // initialize rank list
    for(int i=0;i<n;i++)
        rk[i]=0;
    // only compare the members in left, avoid repeating comparison
    for(int i=1;i<n;i++)
        for(int j=0;j<i;j++)
        {
            if(list[j]<=list[i]) // guarantee the stability
                rk[i]++;
            else
                rk[j]++;
        }
}

template<class T>
void rankSort(T list[],int n,const int rk[])
{
    T temp[n];
    for(int i=0;i<n;i++)
        temp[rk[i]]=list[i];
    for(int i=0;i<n;i++)
        list[i]=temp[i];
}

// rank in place, save the space
template<class T>
void rankSortIn(T list[],int n,int rk[])
{
    int i=0;
    while(i<n)
    {
        // move the value to the right place, until rk[i]==i, then step forward
        if(rk[i]!=i)
        {
            int t=rk[i];
            swap(rk[i],rk[t]);
            swap(list[i],list[t]);
        }
        else
            i++;
    }
}

/* bubble sort */

template<class T>
void bubbleSort(T list[],int n)
{
    for(int i=n;i>0;i--)
        for(int j=0;j<i-1;j++)
        {
            if(list[j]>list[j+1])
                swap(list[j],list[j+1]);
        }
}

template<class T>
void bubbleSort_rapid(T list[],int n)
{
    bool IsSorted = false;
    for(int i=n;!IsSorted&&i>0;i--)
    {
        IsSorted = true;
        for(int j=0;j<i-1;j++)
            if(list[j]>list[j+1])
            {
                swap(list[j],list[j+1]);
                IsSorted = false;
            }
    }
}

/* insert sort */

template<class T>
void insertSort(T list[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        // list[0:i] already sorted
        T temp=list[i+1];
        int j;
        for(j=i;j>=0&&temp<list[j];j--)
            list[j+1]=list[j]; // move backward
        list[j+1]=temp;
    }
}