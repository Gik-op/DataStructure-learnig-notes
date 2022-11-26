#include <iostream>

template<class T>
int binarySearch(T list[],int n,const T &aim);

template<class T>
void insertSort(T list[],int n);

template<class T>
void Show(T list[],int n)
{
    std::cout.setf(std::ios_base::adjustfield,std::ios_base::left);
    for(int i=0;i<n;i++)
    {
        std::cout.width(4);
        std::cout << list[i];
    }
    std::cout<<std::endl;
}

int main()
{
    using namespace std;
    int search,aim;
    int tst[]={1,4,6,8,12,4,7};
    cout << "Please enter a number you want to search:";
    cin >> aim;
    if(cin.fail())
    {
        cout << "Invalid input!\n";
        exit(1);
    }
    insertSort(tst,sizeof(tst)/sizeof(int));
    cout << "The list:\n";
    Show(tst,sizeof(tst)/sizeof(int));
    search = binarySearch(tst,sizeof(tst)/ sizeof(int),aim);
    if(search!=-1)
        cout << "The index of " << aim << " is " << search <<endl;
    else
        cout << "Can't find " << aim << endl;
    return 0;
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

// sorted List before
template<class T>
int binarySearch(T list[],int n,const T &aim)
{
    int left=0,right=n-1;
    while(left<=right)
    {
        int middle=(left+right)/2;
        if(aim<list[middle])
            right=middle;
        else if(aim>list[middle])
            left=middle;
        else
            return middle;
    }
    return -1;
}