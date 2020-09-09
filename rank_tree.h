//
// Created by sasso on 6/10/2019.
//

#ifndef WET_2_RANK_TREE_H
#define WET_2_RANK_TREE_H

#include "lecture.h"
#include "generic_tree.h"



class AVLRankedTree : public AVLtree <lectureByStudents>
{

public:
    AVLRankedTree():AVLtree<lectureByStudents>(){}

    AVLRankedTree(node<lectureByStudents>* root1) : AVLtree<lectureByStudents>(root1){};

    node<lectureByStudents> *insert(node<lectureByStudents> *new_node) override;

    node<lectureByStudents> *remove(const lectureByStudents& toDelete) override ;

    void balanceSubTree(node<lectureByStudents> *p) override ;

};

void rank_update (node <lectureByStudents> * p);

void totalStud_update (node <lectureByStudents> * p);


#endif //WET_2_RANK_TREE_H
