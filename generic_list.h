//
// Created by sasso on 5/4/2019.
//



#ifndef WET_1_GENERIC_LIST_H
#define WET_1_GENERIC_LIST_H

#include "generic_tree.h"

;


template <class T>
class Listnode {
public :
    T data;
    Listnode *next;
    Listnode *previus;

    Listnode(T newdata,Listnode* nxt= NULL,Listnode* pre= NULL): data(newdata),next(nxt),previus(pre)
    {}
};

template<class T>
class LinkedList
{
public:
    Listnode<T>* first;
    Listnode<T>* last;
    LinkedList<T>() {
        first = NULL;
        last = NULL;
    }

    Listnode<T>* insert(Listnode<T>* ToInsert) {
        if(!first) {
            first = ToInsert;
            last=ToInsert;
            return first;
        } else {
            if(last == first) {
               first->next=ToInsert;
                ToInsert->previus = first;
                last=ToInsert;
                return ToInsert;
            } else {
                ToInsert->previus=last;
                last->next = ToInsert;
                last = ToInsert;
                last->next=NULL;
                return ToInsert;
            }
        }
    }

    Listnode<T>* exist(T data) {
        Listnode<T>* ptr=first;
        while(ptr)
        {
            if (ptr->data==data)
            {
                return ptr;
            }
            ptr=ptr->next;
        }
        return NULL;

    }

    Listnode<T>* remove(Listnode<T>* ToDelete)
    {

        if(ToDelete->previus)  // to delete is not first
        {ToDelete->previus->next=ToDelete->next;}
        else {
            first=ToDelete->next;
        }
        if(ToDelete->next)
        {
            ToDelete->next->previus=ToDelete->previus;
        }
        else {last=ToDelete->previus;}
        ToDelete->next=NULL;
        ToDelete->previus=NULL;
        return ToDelete;
    }
};





#endif //WET_1_GENERIC_LIST_H
