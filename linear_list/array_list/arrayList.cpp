#include "arrayList.h"
#include <sstream>
#include <utility>

class illegalIndex : public std::exception
{
private:
    std::string mes;
public:
    explicit illegalIndex(std::string s="Wrong.") : mes(std::move(s)) { }
    const char* what() {return mes.c_str();}
};

class illegalParameter : public std::exception
{
private:
    std::string mess;
public:
    explicit illegalParameter(std::string s="Illegal parameter value") : mess(std::move(s)) { }
    const char* what() {return mess.c_str();}
};

template<class T>
void changeLengthDB(T *&a,int oldLength)
{
    T *temp = new T [oldLength*2];
    copy(a,a+oldLength,temp);
    delete a;
    a = temp;
}

template<class T>
void arrayList<T>::checkIndex(int theIndex) const
{
    if(theIndex<0||theIndex>=listSize)
    {
        std::ostringstream s;
        s <<"index = " << theIndex << "size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
    if(initialCapacity<=0)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameter(s.str());
    }
    element = new T [initialCapacity];
    arrayLength = initialCapacity;
    listSize = 0;
}

template<class T>
arrayList<T>::arrayList(const arrayList<T> &theList)
{
    arrayLength = theList.arrayLength;
    listSize = theList.listSize;
    element = new T [arrayLength];
    for(int i=0;i<listSize;i++)
        element[i]=theList.element[i];
}
template<class T>
T &arrayList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex];
}

template<class T>
int arrayList<T>::indexOf(const T &theElement) const
{
    int i;
    for(i=0;i<listSize;i++)
        if(element[i]==theElement)
            break;
    if(i==listSize)  // Can't find
        i=-1;
    return i;
}

template<class T>
void arrayList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    for(int i=theIndex;i<listSize-1;i++)
        element[i]=element[i+1];
    element[--listSize].~T(); // delete the excess space
}

template<class T>
void arrayList<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex<0||theIndex>listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
    if(listSize==arrayLength)
    {
        changeLengthDB(element,arrayLength);
        arrayLength *=2;
    }
    for(int i=theIndex;i<listSize;i++)
        element[i+1]=element[i];
    element[theIndex]=theElement;
    listSize++;
}

template<class T>
void arrayList<T>::output(std::ostream &os) const
{
    for(int i=0;i<listSize;i++)
    {
        os << element[i] << " ";
        if(i%5==0)
            os << std::endl;
    }
    if((listSize-1)%5)
        os << std::endl;
}

// vector list
template<class T>
void vectorList<T>::checkIndex(int theIndex) const
{
    if(theIndex<0||theIndex>=element->size())
    {
        std::ostringstream s;
        s <<"index = " << theIndex << "size = " << element->size();
        throw illegalIndex(s.str());
    }
}

template<class T>
vectorList<T>::vectorList(int initialCapacity)
{
    if(initialCapacity<=0)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameter(s.str());
    }
    element = new vector<T>;
    element->reserve(initialCapacity);
}

template<class T>
vectorList<T>::vectorList(const vectorList<T> &theList)
{
    element = new vector<T>(*theList.element);
}

template<class T>
T &vectorList<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    return element[theIndex];
}

template<class T>
int vectorList<T>::indexOf(const T &theElement) const
{
    int theIndex = (int)(find(element,element+element->size(),theElement)-element);
    if(theIndex==element->size())
        theIndex = -1;
    return theIndex;
}

template<class T>
void vectorList<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    element->erase(begin()+theIndex);
}

template<class T>
void vectorList<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex<0||theIndex>element->size())
    {
        std::ostringstream s;
        s <<"index = " << theIndex << "size = " << element->size();
        throw illegalIndex(s.str());
    }
    element->insert(begin()+theIndex,theElement);
}

template<class T>
void vectorList<T>::output(std::ostream &os) const
{
    for(int i=0;i<element->size();i++)
    {
        os << element[i] << " ";
        if(i%5==0)
            os << std::endl;
    }
    if((element->size()-1)%5)
        os << std::endl;
}