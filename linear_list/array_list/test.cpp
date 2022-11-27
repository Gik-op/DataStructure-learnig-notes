#include "arrayList.h"

int main()
{
    using std::cout;
    using std::endl;
    arrayList<int> one;
    cout << "The size of List #1 is " << one.size() << endl;
    cout << "The capacity of List #1 is " << one.capacity() << endl;

    arrayList<int> two(30);
    for(int i=0;i<30;i++)
        two.insert(i,i);
    cout << "List #2:\n";
    two.output(std::cout);
    cout << "index of 3 in List #2: " << two.indexOf(3) << endl;
    cout << "number of index 3 in List #2: " << two.get(3) << endl;

    arrayList<int> three(two);
    cout << "List #3:\n";
    three.output(std::cout);
    three.erase(8);
    cout << "After erasing, List #3:\n";
    three.output(std::cout);

    vectorList<int> four;
    cout << "The size of List #4 is " << four.size() << endl;
    cout << "The capacity of List #4 is " << four.capacity() << endl;

    vectorList<int> five(30);
    for(int i=0;i<30;i++)
        five.insert(i,i);
    cout << "List #5:\n";
    five.output(std::cout);
    cout << "index of 3 in List #5: " << five.indexOf(3) << endl;
    cout << "number of index 3 in List #5: " << five.get(3) << endl;

    vectorList<int> six(five);
    cout << "List #6:\n";
    six.output(std::cout);
    six.erase(18);
    cout << "After erasing, List #6:\n";
    six.output(std::cout);

    return 0;
}
