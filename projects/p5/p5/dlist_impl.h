//
// Created by Administrator on 2019/12/3.
//


#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include "dlist.h"
using namespace std;


template <class T>
bool Dlist<T>::isEmpty() const{
    return !(last&&first);
}

template <class T>
void Dlist<T>::insertFront(T *op){
    node *np=new node;
    np->op=op;
    np->prev= nullptr;
    if (!isEmpty()) {
        np->next = first;
        first->prev = np;
        first=np;
    }
    else{
        first=last=np;
        np->next= nullptr;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op){
    node *np=new node;
    np->op=op;
    np->next= nullptr;
    if(!isEmpty()) {
        last->next = np;
        np->prev = last;
        last = np;
    }
    else{
        first=last=np;
        np->prev=nullptr;
    }
}

template<class T>
T * Dlist<T>::removeFront(){
    // MODIFIES this
    // EFFECTS removes and returns first object from non-empty list
    //         throws an instance of emptyList if empty
    node *victim=first;
    T *result;
    if(isEmpty()){
        emptyList e;
        throw e;
    }
    result=victim->op;
    first->prev = nullptr;
    first = victim->next;
    delete victim;
    return result;
}
template<class T>
T * Dlist<T>::removeBack(){
    node * victim=last;
    T *result;
    if(isEmpty()){
        emptyList e;
        throw e;
    }
    result=victim->op;
    last->next= nullptr;
    last=victim->prev;
    delete victim;
    return  result;
}

template <class T>
    Dlist<T>::Dlist(){
        first=last=nullptr;
    }

template<class T>
void Dlist<T>::copyAll(const Dlist &l){
    this->removeAll();

    node* temp_now=l.first;
    if(!temp_now) return;
    while(temp_now){
        T* np=new T(*temp_now->op);
        insertBack(np);
        temp_now=temp_now->next;
    }
}

template <class T>
Dlist<T>::Dlist(const Dlist &l){
    first= nullptr;
    last= nullptr;
    copyAll(l);
}


template<class T>
void Dlist<T>::removeAll(){
    while (!isEmpty()){
        T* op=removeFront();
        delete op;
    }
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l){
    this->removeAll();
    this->copyAll(l);
    return *this;
}

template<class T>
Dlist<T>::~Dlist(){
    removeAll();
}

