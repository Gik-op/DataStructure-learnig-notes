#ifndef ARRAY_LIST_ARRAYLIST_H
#define ARRAY_LIST_ARRAYLIST_H

#include <iostream>
#include <vector>

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
    iterator begin() { return element->begin();}
    iterator end() { return  element->end();}
};

#endif //ARRAY_LIST_ARRAYLIST_H