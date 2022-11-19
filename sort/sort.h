#ifndef SORT_TEST_SORT_H
#define SORT_TEST_SORT_H

#include <iostream>

template<class T>
void selectSort(T list[],int n);
template<class T>
void selectSort_rapid(T list[],int n);

template<class T>
void Rank(T list[],int n,int rk[]);
template<class T>
void rankSort(T list[],int n,const int rk[]);
template<class T>
void rankSortIn(T list[],int n,int rk[]);

template<class T>
void bubbleSort(T list[],int n);
template<class T>
void bubbleSort_rapid(T list[],int n);

template<class T>
void insertSort(T list[],int n);

#endif //SORT_TEST_SORT_H