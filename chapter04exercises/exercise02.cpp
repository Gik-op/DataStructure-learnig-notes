#include <iostream>
#include <ctime>

template<class T>
void insert(T list[],int n,const T& x)
{
    int i;
    for(i=-1;i>=0&&x<list[i];i--)
        list[i+1]=list[i];
    list[i+1]=x;
}
template<class T>
void insertionSort(T list[],int n)
{
    for(int i=1;i<n;i++)
    {
        T t=list[i];
        insert(list,i,t);
    }
}

template<class T>
void insertionSort2(T list[],int n)
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

int main()
{
    using namespace std;
    int test[1000],step=10;
    double clockPerMill = double(CLOCKS_PER_SEC)/1000;
    cout << "The worst-case time for insertionSort(), in milliseconds, are\n";
    cout << "type\t n \tRepetitions \t Total Ticks \tTime per Sort\n";

    for(int n=0;n<=1000;n+=step)
    {
        long numberOfRepetitions = 0;
        clock_t startTime = clock();
        do{
           numberOfRepetitions++;

            // worst-case
            for(int i=0;i<n;i++)
                test[i]=n-i;

            insertionSort(test,n);
        }while(clock()-startTime<1000);

        double elapseMill = (clock()-startTime)/clockPerMill;
        cout << "1.0\t" << n << '\t' << numberOfRepetitions << '\t' << elapseMill
             << '\t' << elapseMill/numberOfRepetitions << endl;

        numberOfRepetitions = 0;
        clock_t startTime2 = clock();
        do{
            numberOfRepetitions++;

            // worst-case
            for(int i=0;i<n;i++)
                test[i]=n-i;

            insertionSort2(test,n);
        }while(clock()-startTime2<1000);

        elapseMill = (clock()-startTime2)/clockPerMill;
        cout << "2.0\t" << n << '\t' << numberOfRepetitions << '\t' << elapseMill
             << '\t' << elapseMill/numberOfRepetitions << endl;

        if(n==100) step = 100;
    }

    return 0;
}
