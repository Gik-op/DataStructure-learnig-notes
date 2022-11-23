#include <iostream>

template<class T>
void selectSort_rapid(T list[],int n);
template<class T>
void insertSort(T list[],int n);
template<class T>
void bubbleSort_rapid(T list[],int n);

int main()
{
    using namespace std;
    int test[1000],step=10;
    double clockPerMill = double(CLOCKS_PER_SEC)/1000;
    cout << "The worst-case time for Sort(), in milliseconds, are\n";
    cout << "n \tIn-time selectSort\tIn-time bubbleSort\tInsertSort\n";

    for(int n=0;n<=1000;n+=step)
    {
        long numberOfRepetitions = 0;
        clock_t startTime = clock();
        do{
            numberOfRepetitions++;
            // worst-case
            for(int i=0;i<n;i++)
            {
                if(i==n-1)
                    test[i]=0;
                else
                    test[i]=i+1;
            }

            selectSort_rapid(test,n);
        }while(clock()-startTime<1000);

        double elapseMill = (clock()-startTime)/clockPerMill;
        cout << n << '\t';
        cout.setf(ios_base::floatfield,ios_base::fixed);
        cout.precision(8);
        cout << elapseMill/numberOfRepetitions << "\t\t";

        numberOfRepetitions = 0;
        clock_t startTime2 = clock();
        do{
            numberOfRepetitions++;
            // worst-case
            for(int i=0;i<n;i++)
                test[i]=n-i;

            bubbleSort_rapid(test,n);
        }while(clock()-startTime2<1000);

        elapseMill = (clock()-startTime2)/clockPerMill;
        cout << elapseMill/numberOfRepetitions << "\t\t";

        numberOfRepetitions = 0;
        clock_t startTime3 = clock();
        do{
            numberOfRepetitions++;
            // worst-case
            for(int i=0;i<n;i++)
                test[i]=n-i;

            insertSort(test,n);
        }while(clock()-startTime3<1000);

        elapseMill = (clock()-startTime3)/clockPerMill;
        cout << elapseMill/numberOfRepetitions << endl;

        if(n==100) step = 100;
        cout.precision(0);
    }
    return 0;
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