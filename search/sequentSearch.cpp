#include <iostream>

template<class T>
int sequentSearch(T list[],int n,const T &aim);

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
    search = sequentSearch(tst,sizeof(tst)/ sizeof(int),aim);
    if(search!=-1)
        cout << "The index of " << aim << " is " << search <<endl;
    else
        cout << "Can't find " << aim << endl;
    return 0;
}

template<class T>
int sequentSearch(T list[],int n,const T &aim)
{
    int i;
    for(i=0;i<n;i++)
        if(list[i]==aim)
            break;
    if(i==n)
        i=-1;
    return i;
}