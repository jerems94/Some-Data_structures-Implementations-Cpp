//
// Created by sasso on 6/4/2019.
//

#ifndef WET_2_GENRERIC_REVERSE_TREE_H
#define WET_2_GENRERIC_REVERSE_TREE_H
#include <iostream>
#include <new>
#include <cassert>
#include <cmath>
#include <ostream>

template <class T,class G>
class ReverseNode {
public:
    T element;
    ReverseNode *parent;
    G* group;
    ReverseNode(const T& data=T(), G* group=NULL ) : element(data),  parent(NULL),group(group){}

};







#endif //WET_2_GENRERIC_REVERSE_TREE_H
