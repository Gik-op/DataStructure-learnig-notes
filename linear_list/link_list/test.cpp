#include <iostream>
#include "chain.h"

int main()
{
    using std::cout;
    using std::endl;
    chain<int> one;
    cout << "The size of List #1 is " << one.size() << endl;

    chain<int> two(30);
    for(int i=0;i<30;i++)
        two.insert(i,i);
    cout << "List #2:\n";
    two.output(std::cout);
    cout << "index of 3 in List #2: " << two.indexOf(3) << endl;
    cout << "number of index 3 in List #2: " << two.get(3) << endl;

    chain<int> three(two);
    cout << "List #3:\n";
    three.output(std::cout);
    three.erase(8);
    cout << "After erasing, List #3:\n";
    three.output(std::cout);

    return 0;
}
