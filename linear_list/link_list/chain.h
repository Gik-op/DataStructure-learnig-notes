#ifndef LINKED_LIST_LINKLIST_H
#define LINKED_LIST_LINKLIST_H

#include <iostream>

template<class T>
struct chainNode
{
    // data members
    T element;
    chainNode<T> *next;

    // functions
    chainNode()=default;
    explicit chainNode(const T&element) { this->element=element;}
    chainNode(const T&element,chainNode<T> *next)
    { this->element=element;this->next=next;}
};

// linear list
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

// singly linked list
template<class T>
class chain : public linearList<T>
{
protected:
    void checkIndex(int theIndex) const;
    chainNode<T> *firstNode;
    int listSize;
public:
    explicit chain(int initialCapacity=10);
    chain(const chain<T>&);
    ~chain();

    // ADT functions
    bool empty() const { return listSize==0;}
    int size() const { return listSize;}
    T& get(int theIndex) const;
    int indexOf(const T &theElement) const;
    void erase(int theIndex);
    void insert(int theIndex,const T &theElement);
    void output(std::ostream &os) const;
};
#endif //LINKED_LIST_LINKLIST_H
