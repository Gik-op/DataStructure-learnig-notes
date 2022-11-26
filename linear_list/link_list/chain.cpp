#include "linkList.h"
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
void chain<T>::checkIndex(int theIndex) const
{
    if(theIndex<0||theIndex>=listSize)
    {
        std::ostringstream s;
        s <<"index = " << theIndex << "size = " << listSize;
        throw illegalIndex(s.str());
    }
}

template<class T>
chain<T>::chain(int initialCapacity)
{
    if(initialCapacity<=0)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameter(s.str());
    }
    firstNode = NULL;
    listSize = 0;
}

template<class T>
chain<T>::chain(const chain<T> &theChain)
{
    listSize = theChain.listSize;
    if(listSize==0)
    {
        firstNode = NULL;
        return;
    }

    chainNode<T> *sourceNode = theChain.firstNode;
    chainNode<T> *targetNode;
    firstNode = new chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    targetNode = firstNode;
    while(sourceNode!=NULL)
    {
        targetNode->next = new chainNode<T>(sourceNode->element);
        sourceNode = sourceNode->next;
        targetNode = targetNode->next;
    }
    targetNode->next = NULL;
}

template<class T>
chain<T>::~chain()
{
    while(firstNode!=NULL)
    {
        chainNode<T> *temp = firstNode->next;
        delete firstNode;
        firstNode = temp;
    }
}

template<class T>
T &chain<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    chainNode<T> *seekNode = firstNode;
    for(int i=0;i<theIndex;i++)
        seekNode = seekNode->next;
    return seekNode->element;
}

template<class T>
int chain<T>::indexOf(const T &theElement) const
{
    int index=0;
    chainNode<T> *seekNode = firstNode;
    while(seekNode!=NULL)
    {
        if(seekNode->element==theElement)
            break;
        index++;
        seekNode = seekNode->next;
    }
    if(seekNode==NULL)
        index = -1;
    return index;
}

template<class T>
void chain<T>::erase(int theIndex)
{
    checkIndex(theIndex);

    chainNode<T> *deleteNode;
    if(theIndex==0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        chainNode<T> *prevNode = firstNode;
        for(int i=0;i<theIndex-1;i++)
            prevNode = prevNode->next;
        deleteNode = prevNode->next;
        prevNode->next = prevNode->next->next;
    }
    delete deleteNode;
    listSize--;
}

template<class T>
void chain<T>::insert(int theIndex, const T &theElement)
{
    if(theIndex<0||theIndex>listSize)
    {
        std::ostringstream s;
        s <<"index = " << theIndex << "size = " << listSize;
        throw illegalIndex(s.str());
    }
    // find the prev node
    if(theIndex==0)
        firstNode = new chainNode<T>(theElement,firstNode);
    else
    {
        chainNode<T> *prevNode = firstNode;
        for(int i=0;i<theIndex-1;i++)
            prevNode = prevNode->next;
        prevNode->next = new chainNode<T>(theElement,prevNode->next);
    }
    listSize++;
}

template<class T>
void chain<T>::output(std::ostream &os) const
{
    chainNode<T> *currentNode = firstNode;
    for(int i=0;i<listSize;i++)
    {
        os << currentNode->element << " ";
        currentNode = currentNode->next;
        if(i%5==0)
            os << std::endl;
    }
    if((listSize-1)%5)
        os << std::endl;
}