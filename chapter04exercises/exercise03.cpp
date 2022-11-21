#include <iostream>
#include <ctime>

template<class T>
void swap(T &x,T &y)
{
    T t;
    t = x;
    x = y;
    y = t;
}
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

int main()
{
    using namespace std;
    int test[1000],step=10;
    double clockPerMill = double(CLOCKS_PER_SEC)/1000;
    cout << "The worst-case time for insertionSort(), in milliseconds, are\n";
    cout << "n \tTime per bubbleSort\tTime per In-time bubbleSort\n";

    for(int n=0;n<=1000;n+=step)
    {
        long numberOfRepetitions = 0;
        clock_t startTime = clock();
        do{
            numberOfRepetitions++;

            // worst-case
            for(int i=0;i<n;i++)
                test[i]=n-i;

            bubbleSort(test,n);
        }while(clock()-startTime<1000);

        double elapseMill = (clock()-startTime)/clockPerMill;
        cout << n << '\t' << elapseMill/numberOfRepetitions << "\t\t";

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
        if(n>600)
            cout << "\t";
        cout << elapseMill/numberOfRepetitions << endl;

        if(n==100) step = 100;
    }

    return 0;
}
