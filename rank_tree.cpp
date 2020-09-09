//
// Created by sasso on 6/10/2019.
//

#include "rank_tree.h"


node<lectureByStudents> * AVLRankedTree::insert(node<lectureByStudents> *new_node)
{
    if (!this->root) {
    this->root = new_node;
    this->root->parent = NULL;
}
else {
    node<lectureByStudents> *parent = NULL, *ptr = this->root;
    bool left = false;
    while (ptr)
    {
        parent = ptr;
        if (new_node->data < ptr->data) {
            node<lectureByStudents> *x = (ptr->left ? ptr->left : NULL);
            ptr = x;
            left = true;
        }
        else if (new_node->data > ptr->data) {
            node<lectureByStudents> *x = (ptr->right ? ptr->right : NULL);
            ptr = x;
            left = false;
        }
        else if (new_node->data == ptr->data) { return ptr; }
     }
    new_node->parent = parent;
    new_node->height = 0;
    new_node->right = NULL;
    new_node->left = NULL;
    if (left) parent->left = new_node;
    else parent->right = new_node;

    node<lectureByStudents> * ptr2 = new_node;    // before the rotations update rank and total student num in each node from new to root
    while (ptr2)
    {
        rank_update(ptr2);
        totalStud_update(ptr2);
        ptr2=ptr2->parent;
    }

    node<lectureByStudents> *v = new_node;
    while (v != this->root)
    {
        node<lectureByStudents> *p = v->parent;
        if ((p->height) >= (v->height + 1))         // check if need for update height, if no you can break
        {
            break;
        }
        else p->height = v->height + 1;
        balanceSubTree(p);
        v = p;
    }  // end of while loop.

    }
return new_node;

}

 node<lectureByStudents> * AVLRankedTree :: remove(const lectureByStudents& toDelete) {
    node<lectureByStudents> *ptr = root;
    node<lectureByStudents> *temp = NULL;
    node<lectureByStudents> * ancestor;
     node<lectureByStudents> * start;
    bool left = false;
    while (ptr != NULL && ptr->data != toDelete) {
        if (ptr->data < toDelete) {
            ptr = ptr->right;
            left = false;
        } else {
            ptr = ptr->left;
            left = true;
        }
    }
    if (ptr) {
        if (!ptr->left && !ptr->right) // case 1
        {
            if (left) {
                if (ptr->parent)
                {ptr->parent->left = NULL;}
                else {root=NULL;}
            } else {
                if (ptr->parent) {ptr->parent->right = NULL;}
                else root=NULL; }
            temp = ptr;
            ancestor = temp->parent;
            start=ptr->parent;
        } else if ((!ptr->left && ptr->right)) // case 2
        {
            if (left) {
                if (ptr->parent)
                {ptr->parent->left = ptr->right;
                    ptr->right->parent = ptr->parent;}
                else
                {
                    ptr->right->parent=NULL;
                    root=ptr->right;
                }
            } else {
                if (ptr->parent)
                {ptr->parent->right = ptr->right;
                    ptr->right->parent = ptr->parent;}
                else
                {
                    ptr->right->parent=NULL;
                    root=ptr->right;
                }
            }
            temp = ptr;
            ancestor = temp->parent;
            start=ptr->parent;
        } else if ((ptr->left && !ptr->right)) // case 3
        {
            if (left) {
                if (ptr->parent)
                {ptr->parent->left = ptr->left;
                    ptr->left->parent = ptr->parent;}
                else
                {
                    ptr->left->parent=NULL;
                    root=ptr->left;
                }
            } else {
                if (ptr->parent)
                {ptr->parent->right = ptr->left;
                    ptr->left->parent = ptr->parent;}
                else
                {
                    ptr->left->parent=NULL;
                    root=ptr->left;
                }
            }
            temp = ptr;
            ancestor = temp->parent;
            start=ptr->parent;
        } else if ((ptr->left && ptr->right)) // case 4
        {
            bool left2 = true;
            node<lectureByStudents> *first_left = ptr->left;
            if (!first_left->right) {
                start=first_left;
                left2 = true; }
            else {
                while (first_left->right) {
                    first_left = first_left->right;
                }
                left2 = false;
                start=first_left->parent;
            }
            // lectureByStudents x = ptr->data;
            //ptr->data = first_left->data;
            //first_left->data = x;
            if (left2) {
                first_left->parent->left = first_left->left;
                ancestor=first_left;
                if (first_left->left) { first_left->left->parent = first_left->parent; }
            } else {
                first_left->parent->right = first_left->left;
                ancestor = first_left->parent;
                if (first_left->left) { first_left->left->parent = first_left->parent; }
            }
            if (root == ptr) { root = first_left; }
            first_left->parent = ptr->parent;
            first_left->left = ptr->left;
            first_left->right = ptr->right;
            if (ptr->left){ptr->left->parent = first_left;}
            if(ptr->right){ptr->right->parent = first_left;}
            if (left) {
                if (ptr->parent) { ptr->parent->left = first_left; } }
            else { if (ptr->parent) { ptr->parent->right = first_left; }}
            temp = ptr;

        }
        while (start)   // update ranks  from start to root before rotations
        {
            rank_update(start);
            totalStud_update(start);
            start=start->parent;
        }

        while (ancestor) {
            ancestor->height = height_update(ancestor);
            balanceSubTree(ancestor);  // rotations also update ranks
            ancestor = ancestor->parent;
        }
        if (temp)
        {temp->parent=NULL;
            temp->right=NULL;
            temp->left=NULL;}
        return temp;
    }
    return temp;

}


void rank_update (node <lectureByStudents> * p)
{
    if(!p)
    {
        return;
    }
    int newtotal=0;
    if(p->left){newtotal+=p->left->data.getNumOflecInSubtree();}
    if(p->right){newtotal+=p->right->data.getNumOflecInSubtree();}
    p->data.setTotalLecture(newtotal+1);
}

void totalStud_update (node <lectureByStudents> * p)
{
    if(!p)
    {
        return;
    }
    int newtotal2 = 0;
    if(p->left){newtotal2+=p->left->data.getNumOfStudInSubtree();}
    if(p->right){newtotal2+=p->right->data.getNumOfStudInSubtree();}
    p->data.setTotalStudent(newtotal2+p->data.getNumOfStud());
}

void AVLRankedTree:: balanceSubTree(node<lectureByStudents> *p) {
    if (BF(p) == 2)             // check if balance is ok ///
    {
        if (BF(p->left) >= 0)
        {
            doubleLeftRotation(p, p->left);
            rank_update(p);
            totalStud_update(p);
            rank_update(p->parent);
            totalStud_update((p->parent));
        }
        else if (BF(p->left) == -1)
        {
            leftRightRotation(p, p->left, p->left->right);
            rank_update(p);
            totalStud_update(p);
            if (p->parent){rank_update(p->parent->left);}
            if (p->parent){totalStud_update(p->parent->left);}
            rank_update(p->parent);
            totalStud_update(p->parent);
        }

    } else if (BF(p) == -2) {
        if (BF(p->right) <= 0)
        {
            doubleRightRotation(p, p->right);
            rank_update(p);
            totalStud_update(p);
            rank_update(p->parent);
            totalStud_update((p->parent));
        }
        else if (BF(p->right) == 1)
        {
            rightLeftRotation(p, p->right, p->right->left);
            rank_update(p);
            totalStud_update(p);
            if (p->parent){rank_update(p->parent->right);}
            if (p->parent){totalStud_update(p->parent->right);}
            rank_update(p->parent);
            totalStud_update(p->parent);

        }
    }
}