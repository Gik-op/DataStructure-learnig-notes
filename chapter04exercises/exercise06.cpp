#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>

template<class T>
void insertionSort(T list[],int n)
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
    cout << "The average time for insertionSort(), in milliseconds, are\n";
    cout << "n \tRepetitions \tTotal Ticks \tTime per Sort\n";

    for(int n=0;n<=1000;n+=step)
    {
        long numberOfRepetitions = 0;
        clock_t startTime = clock();

        do {
            numberOfRepetitions++;

            // random case
            for (int i = 0; i < n; i++)
                test[i] = i;
            unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
            std::shuffle(test,test+n,std::default_random_engine(seed));

            insertionSort(test, n);
        } while (numberOfRepetitions < 20 || clock() - startTime < 10);

        double elapseMill = (clock() - startTime) / clockPerMill;
        cout << n << '\t' << numberOfRepetitions << "\t\t" << elapseMill << "\t\t";
        cout.setf(ios_base::floatfield,ios_base::fixed);
        cout.precision(8);
        cout << elapseMill / numberOfRepetitions << endl;

        if(n==100) step = 100;
        cout.precision(0);
    }
    return 0;
}
