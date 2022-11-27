#ifndef ARRAY_LIST_ARRAYLIST_H
#define ARRAY_LIST_ARRAYLIST_H

#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <algorithm>

// C++模板类不能将实现与接口分离，否则无法通过编译

template<class T>
class linearList
{
public:
    virtual ~linearList()=default;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int theIndex) const = 0;
    virtual int indexOf(const T &theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex,const T &theElement) = 0;
    virtual void output(std::ostream &os) const = 0;
};

// use array to build a linear list
template<class T>
class arrayList : public linearList<T>
{
protected:
    void checkIndex(int theIndex) const;
    T *element;
    int arrayLength;
    int listSize;
public:
    explicit arrayList(int initialCapacity=10);
    arrayList(const arrayList<T>&);
    ~arrayList() {delete[] element;}

    // ADT functions
    bool empty() const { return listSize==0;}
    int size() const { return listSize;}
    T& get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex,const T &theElement);
    void output(std::ostream &os) const;

    // other functions
    int capacity() const {return arrayLength;}
};

using std::vector;

template<class T>
class vectorList : public linearList<T>
{
protected:
    void checkIndex(int theIndex) const;
    vector<T> *element;
public:
    explicit vectorList(int initialCapacity=10);
    vectorList(const vectorList<T>&);
    ~vectorList() {delete element;}

    // ADT functions
    bool empty() const { return element->empty();}
    int size() const { return (int)element->size();}
    T& get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex,const T &theElement);
    void output(std::ostream &os) const;

    // other functions
    int capacity() const {return (int)element->capacity();}

    // iterators
    typedef typename vector<T>::iterator iterator;
    iterator begin() const { return element->begin();}
    iterator end() const { return  element->end();}
};

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
    for(int i=0;i<oldLength;i++)
        temp[i]=a[i];
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
        os.width(3);
        os.setf(std::ios_base::adjustfield, std::ios_base::left);
        os << element[i] << " ";
        if((i+1)%5==0)
            os << std::endl;
    }
    if((listSize)%5!=0)
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
    return (*element)[theIndex];
}

template<class T>
int vectorList<T>::indexOf(const T &theElement) const
{
    int theIndex = (int)(find(begin(),end(),theElement)-begin());
    if(theIndex == size())
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
        os.width(3);
        os.setf(std::ios_base::adjustfield, std::ios_base::left);
        os << (*element)[i] << " ";
        if((i+1)%5==0)
            os << std::endl;
    }
    if((element->size())%5!=0)
        os << std::endl;
}

#endif //ARRAY_LIST_ARRAYLIST_H
