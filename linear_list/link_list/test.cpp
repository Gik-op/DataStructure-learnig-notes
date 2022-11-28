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
    cout << "Index of 3 in List #2: " << two.indexOf(3) << endl;
    cout << "Number of index 3 in List #2: " << two.get(3) << endl;

    chain<int> three(two);
    cout << "List #3:\n";
    three.output(std::cout);
    three.erase(8);
    cout << "After erasing, List #3:\n";
    three.output(std::cout);

    extendedChain<int> four;
    for(int i=0;i<15;i++)
        four.push_back(i+2);
    cout << "List #4:\n";
    four.output(std::cout);
    cout << "Index of 3 in List #4: " << four.indexOf(3) << endl;
    cout << "Number of index 12 in List #4: " << four.get(12) << endl;
    four.erase(8);
    cout << "After erasing, List #4:\n";
    four.output(std::cout);
    four.insert(four.size(),666);
    cout << "After inserting 666, List #4:\n";
    four.output(std::cout);
    four.clear();
    cout << "After clearing, the size of List #4 is " << four.size() << endl;

    return 0;
}
