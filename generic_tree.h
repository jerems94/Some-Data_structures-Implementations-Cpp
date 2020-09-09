//
// Created by sasso on 5/4/2019.
//

#ifndef WET_1_GENERIC_TREE_H
#define WET_1_GENERIC_TREE_H
#include <iostream>
#include <new>
#include <cassert>
#include <cmath>
#include <ostream>
#include "lecture.h"
using namespace std;





template <class T>
class node
{
public:
    T data;
    node* parent;
    node *left;
    node *right;
    int height;
    node(const T& data=T()) : data(data),parent(NULL),left(NULL),right(NULL),height(0) { }
    template <class Type>
    friend node<Type>* BuildAvlSubtree(int n);

};



template <class Type>
node<Type>* BuildAvlSubtree(int n)
{

    node<Type>* node1=new node<Type>();
    if(n==0)
    {
        return node1;
    }
    /*if(n==2 || n==3)
    {
        node1->left=new node<Type>();
        node1->left->parent=node1;
        node1->height=height_update(node1);
        node1->right=new node<Type>();
        node1->right->parent=node1;
        node1->height=height_update(node1);
        return node1;
    }*/
    node1->left = BuildAvlSubtree<Type>(n-1);
    node1->left->parent=node1;
    node1->height=height_update(node1);
    node1->right = BuildAvlSubtree<Type>(n-1);
    node1->right->parent=node1;
    node1->height= height_update(node1);
    return node1;

}


template <class T>
int height(node<T> *N)
{
    if (N == NULL)
        return -1;
    return N->height;
}
template <class T>
int BF(node<T>* p){return height(p->left)-height(p->right);}


template <class T>
class AVLtree {

protected:
    node<T> *root;

public :
    AVLtree() : root(NULL) {};

    AVLtree(node<T>* root1): root(root1){}


    node<T> *getRoot() const { return root; }

    void SetRoot(node<T> *new_root){
        this->root = new_root;
    }

   virtual node<T> *insert(node<T> *new_node) {
        if (!root) {
            root = new_node;
            root->parent = NULL;
        } else {
            node<T> *parent = NULL, *ptr = root;
            bool left = false;
            while (ptr) {
                parent = ptr;
                if (new_node->data < ptr->data) {
                    node<T> *x = (ptr->left ? ptr->left : NULL);
                    ptr = x;
                    left = true;
                } else if (new_node->data > ptr->data) {
                    node<T> *x = (ptr->right ? ptr->right : NULL);
                    ptr = x;
                    left = false;
                } else if (new_node->data == ptr->data) { return NULL; }
            }
            new_node->parent = parent;
            new_node->height = 0;
            new_node->right = NULL;
            new_node->left = NULL;
            if (left) parent->left = new_node;
            else parent->right = new_node;

            node<T> *v = new_node;
            while (v != root) {
                node<T> *p = v->parent;
                if ((p->height) >= (v->height + 1))         // check if need for update height, if no you can break
                {
                    break;
                } else p->height = v->height + 1;
                balanceSubTree(p);
                v = p;
            }                 // end of while loop.

        }
        return new_node;

    }



    virtual void balanceSubTree(node<T> *p) {
        if (BF(p) == 2)             // check if balance is ok ///
        {
            if (BF(p->left) >= 0) { doubleLeftRotation(p, p->left); }
            else if (BF(p->left) == -1) { leftRightRotation(p, p->left, p->left->right); }

        } else if (BF(p) == -2) {
            if (BF(p->right) <= 0) { doubleRightRotation(p, p->right); }
            else if (BF(p->right) == 1) { rightLeftRotation(p, p->right, p->right->left); }
        }
    }

    virtual node<T> *remove(const T& toDelete) {
        node<T> *ptr = root;
        node<T> *temp = NULL;
        node<T> * ancestor;
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
            } else if ((ptr->left && ptr->right)) // case 4
            {
                bool left2 = true;
                node<T> *first_left = ptr->left;
                if (!first_left->right) { left2 = true; }
                else {
                    while (first_left->right) {
                        first_left = first_left->right;
                    }
                    left2 = false;
                }
                // T x = ptr->data;
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
            while (ancestor) {
                ancestor->height = height_update(ancestor);
                balanceSubTree(ancestor);
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

    void doubleLeftRotation(node<T> *p1, node<T> *p2) {
        p1->left = p2->right;
        if (p2->right) { p2->right->parent = p1; }
        p2->right = p1;
        p2->parent = p1->parent;
        p1->parent = p2;
        p1->height = max((height(p1->left)),
                         height(p1->right)) + 1;
        p2->height = max(height(p2->left),
                         height(p2->right)) + 1;

        if (root == p1) {
            root = p2;
        }
        if (p2->parent && p2->parent->data < p2->data) {
            p2->parent->right = p2;
        } else if (p2->parent) { p2->parent->left = p2; }

    }

    void doubleRightRotation(node<T> *p1, node<T> *p2) {
        node<T> *x = (p2->left ? p2->left : NULL);
        p1->right = x;
        if (p2->left) { p2->left->parent = p1; }
        p2->left = p1;
        p2->parent = p1->parent;
        p1->parent = p2;
        p1->height = height_update(p1);
        p2->height = height_update(p2);
        if (root == p1) {
            root = p2;
        }
        if (p2->parent && p2->parent->data < p2->data) {
            p2->parent->right = p2;
        } else if (p2->parent) { p2->parent->left = p2; }

    }

    void leftRightRotation(node<T> *p1, node<T> *p2, node<T> *p3) {
        p1->left = p3->right;
        p2->right = p3->left;
        if (p3->left) { p3->left->parent = p2; }
        if (p3->right) { p3->right->parent = p1; }
        p3->right = p1;
        p3->left = p2;
        p3->parent = p1->parent;
        p1->parent = p3;
        p2->parent = p3;

        if (root == p1) {
            root = p3;
        }
        if (p3->parent && p3->parent->data < p3->data) {
            p3->parent->right = p3;
        } else if (p3->parent) { p3->parent->left = p3; }


        p1->height = height_update(p1);
        p2->height = height_update(p2);
        p3->height = height_update(p3);
    }

    void rightLeftRotation(node<T> *p1, node<T> *p2, node<T> *p3) {
        p1->right = p3->left;
        p2->left = p3->right;
        if (p3->left) { p3->left->parent = p1; }
        if (p3->right) { p3->right->parent = p2; }
        p3->right = p2;
        p3->left = p1;
        p3->parent = p1->parent;
        p1->parent = p3;
        p2->parent = p3;

        if (root == p1) {
            root = p3;
        }
        if (p3->parent && p3->parent->data < p3->data) {
            p3->parent->right = p3;
        } else if (p3->parent) { p3->parent->left = p3; }


        p1->height = height_update(p1);
        p2->height = height_update(p2);
        p3->height = height_update(p3);

    }


    node<T> *exist(const T& data) const {
        if (!root) {
            return NULL;
        } else {
            node<T> *ptr = root;
            while (ptr) {
                if (data < ptr->data) {
                    node<T> *x = (ptr->left ? ptr->left : NULL);
                    ptr = x;
                } else if (data > ptr->data) {
                    node<T> *x = (ptr->right ? ptr->right : NULL);
                    ptr = x;
                } else if (data == ptr->data) { return ptr; }
            }
            return NULL;


        }
    }

    int height_update(node<T> *p) {
        return (max(height(p->left),
                    height(p->right))) + 1;
    }

    virtual ~AVLtree()
    {}

};


template <class T>
int height_update(node<T> *p) {
    return (max(height(p->left),
                height(p->right))) + 1;
}



template <class T>
void printInorder(node<T>* root)
{
    if (root== NULL)
        return;

    printInorder(root->left);

    cout << root->data << " ";

    printInorder(root->right);
}
template <class T>
int countElement(node<T>* root)
{
    if(!root){return 0;}
    int count = 1;
    if (root->left != NULL) {
        count += countElement(root->left);
    }
    if (root->right != NULL) {
        count += countElement(root->right);
    }
    return count;
}

template <class T>
void treeToArrayInorder(node<T>* root,T* array, int* index)
{
    if (root == NULL || array==NULL)
        return;

    /* first recur on left child */
    treeToArrayInorder(root->left, array, index);

    array[*index]=root->data;
    (*index)++; // increase index for next entry

    /* now recur on right child */
    treeToArrayInorder(root->right, array, index);
}


template <class T>
void ArrayToTreeInorder(node<T>* root,T* array, int* index)
{
    if (root == NULL || array ==NULL)
        return;

    ArrayToTreeInorder(root->left, array, index);

    root->data=array[*index];
    (*index)++;

    ArrayToTreeInorder(root->right, array, index);
}
template <class T>
void updateAllHeight (node<T>* root)
{
    if (root == NULL)
        return;


    updateAllHeight(root->left);

    updateAllHeight(root->right);
    root->height=height_update(root);
}



template <class T>
void CompleteToSemiComplete (node<T>* root,int* toErase)
{
    if (root == NULL)
        return;

    if(height(root)==0)
    {
        if(root->parent && root->parent->right)
        {if(height(root->parent->right)==0)
            {
                root->parent->right=NULL;
                delete(root);
                *toErase-=1;
                {return;}
            }
        }
        if (root->parent && root->parent->left)
        {
            if(height(root->parent->left)==0)
            {
                root->parent->left=NULL;
                delete(root);
                *toErase-=1;
                {return;}
            }
        }
    }

    if(*toErase==0){return;}
    CompleteToSemiComplete(root->right,toErase);
    if(*toErase==0){return;}
    CompleteToSemiComplete(root->left,toErase);
    if(*toErase==0){return;}
}



template <class T>
void print2DUtil(node<T> *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 5;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout<<endl;
    for (int i = 5; i < space; i++)
        cout<<" ";
    cout<<root->data<<"\n";

    // Process left child
    print2DUtil(root->left, space);

}

// Wrapper over print2DUtil()
template <class T>
void print2D(const AVLtree<T> &t)
{
    // Pass initial space count as 0
    node<T>* root=t.getRoot();
    print2DUtil(root, 2);
}


#endif //WET_1_GENERIC_TREE_H
