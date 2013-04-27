//
//  AVLTree.h
//  Mivne1
//
//  Created by Aviad Rom on 4/19/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef __Mivne1__AVLTree__
#define __Mivne1__AVLTree__
#include <iostream>
#include "exceptions.h"
#include "library1.h"
#include "AVLNode.h"

using std::string;
template <typename T>
class AVLTree {
    AVLNode<T>* Root;
    
    /* UpdateHeights
     * Description: used to update the heights of nodes from a node in a tree
     *          up to the root of the tree.
     * @param Node: Node to start updating from.
     * @param Mode: will be "Insert" if called from node insertion,
     *          "Remove" if called from node removal.
     *          "Roll" if called from a roll correction of the tree.
     * Note: insertion heights are calculated from the inserted node up,
     *       removal heights are calculated from the removed node's parent up.
     */
    void UpdateHeights (AVLNode<T>* Node, string Mode) {
        AVLNode<T>* updater=Node;
        if (Mode == "Insert"){
            while (updater->_Parent){
                if (updater->_Parent->_Height >= updater->_Height+1){
                    break;
                }
                updater->_Parent->_Height = updater->_Height+1;
                updater = updater->_Parent;
            }
        } else if (Mode == "Remove"){
            while (updater) {
                if (updater->_Left&&updater->_Right){
                    updater->_Height=MaxSubTreeHeight(updater)+1;
                }else if (updater->_Left){
                    updater->_Height=updater->_Left->_Height+1;
                }else if (updater->_Right){
                    updater->_Height=updater->_Right->_Height+1;
                } else {
                    updater->_Height=0;
                }
                updater=updater->_Parent;
            }
        } else if (Mode == "Roll"){
            while (updater) {
                updater->_Height =MaxSubTreeHeight(updater)+1;
                updater = updater->_Parent;
            }
        }
        
    }
    
    /* NodeBalanceUpdate
     * Description: used to update the balance factor of nodes from a node
     *              somewhere in a tree up to the root of the tree.
     * @param Node: Node to start updating from.
     */
    void NodeBalanceUpdate(AVLNode<T>* Node){
        if (!Node){
            return;
        }
        AVLNode<T>* updater = Node;
        while (updater){
            if (updater->_Left && updater->_Right){
                updater->_Balance = (updater->_Left->_Height) - (updater->_Right->_Height);
            } else if (updater->_Left == NULL){
                updater->_Balance = (-1)*(updater->_Height);
            } else if (updater->_Right == NULL){
                updater->_Balance = updater->_Height;
            }
            updater = updater->_Parent;
        }
    }
    
    /* SubTreeMin
     * Description: finds the minimum node in a sub-tree
     *              (assuming it's a binary search tree)
     * @param SubRoot: root of the sub-tree
     * @return: NULL if SubRoot is a null pointer.
     *          Pointer to minimum node elsewise.
     */
    AVLNode<T>* SubTreeMin (AVLNode<T>* SubRoot) const{
        if (SubRoot == NULL){
            return NULL;
        } else if ( SubRoot->_Left ==  NULL){
            return SubRoot;
        }
        AVLNode<T>* min = SubRoot;
        while (min->_Left){
            min = min->_Left;
        }
        return min;
    }
    
    /* SwapNodes
     * Description: swaps the places of two nodes as part of a binary search tree
     *              node removal.
     * @param A: first node to swap.
     * @param B: second node to swap.
     */
    void SwapNodes (AVLNode<T>* A, AVLNode<T>* B){
       /* AVLNode<T>* temp=new AVLNode<T>();
        temp->Left = A->Left;
        temp->Right = A->Right;
        temp->Parent = A->Parent;
        temp->Balance = A->Balance;
        temp->Height = A->Height;
        A->Left = B->Left;
        A->Right = B->Right;
        A->Parent = B->Parent;
        A->Balance = B->Balance;
        A->Height = B->Height;
        B->Left = temp->Left;
        B->Right = temp->Right;
        B->Parent = temp->Parent;
        B->Balance = temp->Balance;
        B->Height = temp->Height;
        delete temp;*/
        T temp=A->_Data;
        A->_Data=B->_Data;
        B->_Data=temp;

    }
    
    /* MaxSubTreeHeight
     * Description: finds the maximum height of a subtree of a node.
     * @param Node: Node to find sub-trees' heights.
     */
    const int MaxSubTreeHeight (AVLNode<T>* Node) const{
        AVLNode<T>* left = Node->_Left;
        AVLNode<T>* right = Node->_Right;
        int toReturn = -1;
        if (left == NULL && right == NULL) toReturn = 0;
        else if (right == NULL) toReturn = left->_Height;
         else if (left == NULL) toReturn = right->_Height;
          else if (left->_Height > right->_Height) toReturn = left->_Height;
           else toReturn = right->_Height;
        return toReturn;
    }

public:
    AVLTree(){
        Root=NULL;
    }
    
    /* IsEmpty
     * Description: Checks wether the tree is empty or not.
     * @return True if empty.
     *         False if not empty.
     */
    const bool IsEmpty() const{
        return (Root == NULL);
    }
    
    /* Insert
     * Description: Adds a node with provided data to the tree.
     */
    void Insert(T* Data){
        /*
         * 1. find parent (if tree is empty add as root and return)
         * 2. add new element under parent, new vertex's height=0
         * 3. while the vertex is not the root:
         **     1.is parent's height >= new vertex's height+1? yes-> return.
         **     2.assign parent's height to be new vertex's+1.
         **     3.is parent balanced? no-> roll and return.
         **     4. point vertex at parent.
         */
        if (Data == NULL){
            throw new NullPtrException;
        }
        AVLNode<T>* tmp = new AVLNode<T>(*Data);
        AVLNode<T>* parent = NULL;
        if (Root == NULL){
            Root = tmp;
            return;
        }
        AVLNode<T>* current = Root;
        while (current){
            parent = current;
            if (*tmp < *current) {
                current = current->_Left;
            } else{
                current = current->_Right;
            }
        }
        tmp->_Parent = parent;
        if (*tmp < *parent){
            parent->_Left = tmp;
        }else {
            parent->_Right = tmp;
        }
        UpdateHeights(tmp,"Insert");
        NodeBalanceUpdate(parent);
        while (tmp->_Parent){
            parent = tmp->_Parent;
            if (parent->_Balance >= -1 && parent->_Balance <= 1){
                tmp = parent;
                continue;
            }
            if (parent->_Balance >= 2){
                if (parent->_Left->_Balance >= 0){
                    parent = LeftLeft(parent);
                } else if (parent->_Left->_Balance == -1){
                    parent = LeftRight(parent);
                }
            }
            else {
                if (parent->_Right->_Balance <= 0){
                    parent = RightRight(parent);
                } else if (parent->_Right->_Balance == 1){
                    parent = RightLeft(parent);
                }
            }
            tmp = parent;
        }
    }
    
    void Remove(T* Data){
        /*
         * 1. if pointer is null or data is not in the tree- return.
         * 2. get a pointer to node where provided data is stored in the tree
         * 3. remove node as if it were a regular binary search tree
         * 4. update root heights and balance factors.
         * 5. perform rotations if needed.
         */
        if ((Data == NULL) || (!IsIn(Data))){
            return;
        }
        AVLNode<T>* tmp = Find(Data);
        AVLNode<T>* parent = tmp->_Parent;
        AVLNode<T>* start=parent;
        if (tmp->_Height == 0){								//a leaf
            if (parent){
                if ( parent->_Left->_Data == tmp->_Data){
                    delete tmp;
                    parent->_Left = NULL;
                } else {
                    delete tmp;
                    parent->_Right = NULL;
                }
            } else{
                delete tmp;
                Root = NULL;
            }
        } else if (tmp->_Left && tmp->_Right==NULL){	//only left son
            if (parent->_Left == tmp){
                parent->_Left = tmp->_Left;
                delete tmp;
            } else if (parent->_Right == tmp){
                parent->_Right = tmp->_Left;
                delete tmp;
            }
        } else if (tmp->_Right && tmp->_Left==NULL){	//only right son
            if (parent->_Left == tmp){
                parent->_Left = tmp->_Right;
                delete tmp;
            } else if (parent->_Right == tmp){
                parent->_Right = tmp->_Right;
                delete tmp;
            }
        } else {										//two sons
            AVLNode<T>* toSwap = SubTreeMin(tmp->_Right);		//find the preceding node
            AVLNode<T>* swapParent = toSwap->_Parent;
            swapParent->_Left=tmp;
            SwapNodes(tmp, toSwap);
            if (toSwap->_Right != NULL){
            	swapParent->_Left=toSwap->_Right;
            	toSwap->_Parent=swapParent;
            }
            swapParent->_Left=NULL;
            start=swapParent;
            
            delete toSwap;
            
        }
        while (start != NULL){
        	UpdateHeights(start, "Remove");
        	NodeBalanceUpdate(start);
        	if (start->_Balance == 2){
        		if (start->_Left->_Balance>=0){
        			start=LeftLeft(start);
        		} else {
        			start=LeftRight(start);
        		}
            }
            if (start->_Balance == -2){
                if (start->_Right->_Balance <= 0){
                    start=RightRight(start);
                } else {
                    start=RightLeft(start);
                }
            }
            start=start->_Parent;
        }
    }

    /* IsIn
     * Description: Checks wether certain data is in the tree or not.
     * @param Data: data to check for.
     * @return: True if a node with supplied data exists in the tree.
     *          False if supplied data is a null pointer or doesn't exist in the tree.
     */
    bool IsIn(T* Data){
        /*AVLNode<T>* current = Root;
        while(current){
            if (*Data < *(current->_Data)){
                current=current->_Left;
                continue;
            }
            if  (*Data > *(current->_Data)){
                current=current->_Right;
                continue;
            }
            return true;
        }
        return false;*/
        if (Find(Data)){
            return true;
        }
        return false;
    }
    
    /* Find
     * Description: finds a node with certain data in the tree.
     * @param Data: data to match node.
     * @return: NULL if Data is a null pointer or if not found in the tree.
     *          Pointer to the node elsewise.
     */
    AVLNode<T>* Find (T* Data) const{
        if (Data == NULL){
            return NULL;
        }
        AVLNode<T>* toReturn = Root;
        while (toReturn){
            if (*Data < toReturn->_Data){
                toReturn=toReturn->_Left;
                continue;
            }
            if  (*Data > toReturn->_Data){
                toReturn=toReturn->_Right;
                continue;
            }
            break;
        }
        return toReturn;
    }

    /* GetMin
     * Description: Gets a pointer to the minimal node value in the tree.
     * @return: NULL if tree is empty.
     *          Pointer to minimal node elsewise.
     */
    AVLNode<T>* GetMin (){
        return SubTreeMin(Root);
    }
    
    /* RightRight
     * Description: Performs a right-right roll correction in order
     *              to maintain AVL qualities of the tree.
     * @param Node: Node that's out of AVL balance.
     * @return: //TODO
     */
    AVLNode<T>* RightRight (AVLNode<T>* Node){
        AVLNode<T>* child = Node->_Right;
        AVLNode<T>* parent = Node->_Parent;
        Node->_Right = child->_Left;
        child->_Parent = parent;
        if (Node->_Right == NULL){
            if (Node->_Left){
                Node->_Height = Node->_Left->_Height+1;
                
            } else {
                Node->_Height = 0;
            }
        }
        child->_Right = Node;
        if (parent){
            if (parent->_Left == Node){
                parent->_Left = child;
            } else {
                parent->_Right = child;
            }
        }
        UpdateHeights(child, "Roll");
        NodeBalanceUpdate(child->_Right);
        NodeBalanceUpdate(Node);
        return Node;
    }
    
    /* RightLeft
     * Description: Performs a right-left roll correction in order
     *              to maintain AVL qualities of the tree.
     * @param Node: Node that's out of AVL balance.
     * @return: //TODO
     */
    AVLNode<T>* RightLeft (AVLNode<T>* Node){
        AVLNode<T>* child = Node->_Right;
        AVLNode<T>* grandChild = child->_Left;
        AVLNode<T>* parent = Node->_Parent;
        child->_Left = grandChild->_Right;
        Node->_Right = grandChild->_Left;
        grandChild->_Left = child;
        grandChild->_Right = Node;
        child->_Parent = grandChild;
        grandChild->_Parent = parent;
        if (parent){
            if (parent->_Left == Node){
                parent->_Left = grandChild;
            } else {
                parent->_Right = grandChild;
            }
        } else Root = grandChild;
        UpdateHeights(Node, "Roll");
        Node->_Parent=grandChild;
        UpdateHeights(child, "Roll");
        NodeBalanceUpdate(Node);
        NodeBalanceUpdate(child);
        return grandChild;
    }
    
    /* LeftRight
     * Description: Performs a left-right roll correction in order
     *              to maintain AVL qualities of the tree.
     * @param Node: Node that's out of AVL balance.
     * @return: //TODO
     */
    AVLNode<T>* LeftRight (AVLNode<T>* Node){
        AVLNode<T>* child = Node->_Left;
        AVLNode<T>* grandChild = child->_Right;
        AVLNode<T>* parent = Node->_Parent;
        Node->_Left = grandChild->_Right;
        child->_Right = grandChild->_Left;
        grandChild->_Left = child;
        child->_Parent = grandChild;
        grandChild->_Right = Node;
        grandChild->_Parent = parent;
        if (parent){
            if (parent->_Left == Node){
                parent->_Left = grandChild;
            } else {
                parent->_Right = grandChild;
            }
        } else Root = grandChild;
        UpdateHeights(Node, "Roll");
        Node->_Parent=grandChild;
        UpdateHeights(child, "Roll");
        NodeBalanceUpdate(Node);
        NodeBalanceUpdate(child);
        return grandChild;
    }
    
    /* LeftLeft
     * Description: Performs a right-right roll correction in order
     *              to maintain AVL qualities of the tree.
     * @param Node: Node that's out of AVL balance.
     * @return: //TODO
     */
    AVLNode<T>* LeftLeft (AVLNode<T>* Node){
        AVLNode<T>* child = Node->_Left;
        AVLNode<T>* parent = Node->_Parent;
        Node->_Left = child->_Right;
        child->_Parent = parent;
        if (Node->_Left == NULL){
            if (Node->_Right){
                Node->_Height = Node->_Right->_Height+1;
                
            } else {
                Node->_Height = 0;
            }
        }
        child->_Right = Node;
        if (parent){
            if (parent->_Left == Node){
                parent->_Left = child;
            } else {
                parent->_Right = child;
            }
        }
        UpdateHeights(child, "Roll");
        NodeBalanceUpdate(child->_Left);
        NodeBalanceUpdate(Node);
        return Node;
    }
    
};

#endif /* defined(__Mivne1__BTree__) */
