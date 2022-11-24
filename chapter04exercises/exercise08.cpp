#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>

// change the number of random permutations (20 to 50)
// and the lower time limit (10 to 100)

template<class T>
void selectSort(T list[],int n);
template<class T>
void selectSort_rapid(T list[],int n);

int main()
{
    using namespace std;
    int test[1000],step=10;
    double clockPerMill = double(CLOCKS_PER_SEC)/1000;
    cout << "The average time for selectSort(), in milliseconds, are\n";
    cout << "n \tTime per Sort\tTime per Sort(terminate in time)\n";

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

            selectSort(test, n);
        } while (numberOfRepetitions < 50 || clock() - startTime < 100);

        double elapseMill = (clock() - startTime) / clockPerMill;
        cout << n << '\t';
        cout.setf(ios_base::floatfield,ios_base::fixed);
        cout.precision(8);
        cout << elapseMill / numberOfRepetitions << "\t\t";

        numberOfRepetitions = 0;
        clock_t startTime2 = clock();
        do{
            numberOfRepetitions++;
            // random case
            for(int i=0;i<n;i++)
                test[i]=n-i;
            unsigned seed = std::chrono::system_clock::now ().time_since_epoch ().count ();
            std::shuffle(test,test+n,std::default_random_engine(seed));

            selectSort_rapid(test,n);
        }while(numberOfRepetitions < 50 || clock()-startTime2<100);

        elapseMill = (clock()-startTime2)/clockPerMill;
        cout << elapseMill/numberOfRepetitions << endl;

        if(n==100) step = 100;
        cout.precision(0);
    }
    return 0;
}

template<class T>
static int index4Max(T list[],int n)
{
    int max=0;
    for(int i=0;i<n;i++)
        if(list[i]>list[max])
            max=i;
    return max;
}

template<class T>
static void swap(T &x,T &y)
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
