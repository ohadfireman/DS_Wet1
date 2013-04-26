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


template <typename T>
class AVLTree {
    AVLNode<T>* Root;
    
    /* UpdateHeights
     * Description: used to update the heights of nodes from a node in a tree
     *          up to the root of the tree.
     * @param Node: Node to start updating from.
     * @param Mode: will be I if called from node insertion,
     *          R if called from node removal.
     * Note: insertion heights are calculated from the inserted node up,
     *       removal heights are calculated from the removed node's parent up.
     */
    void UpdateHeights (AVLNode<T>* Node, char Mode) {
        AVLNode<T>* updater=Node;
        if (Mode == 'I'){
            while (updater->_Parent){
                if (updater->_Parent->_Height >= updater->_Height+1){
                    break;
                }
                updater->_Parent->_Height = updater->_Height+1;
                updater = updater->_Parent;
            }
        } else if (Mode == 'R'){
            Node->_Height=0;
            updater = Node->_Parent;
            while (updater) {
                if (updater->_Right){
                    if(updater->_Height == updater->_Right->_Height+1){
                        break;
                    }
                    if (updater->_Left->_Height > updater->_Right->_Height){
                        updater->_Height = updater->_Left->_Height+1;
                    } else {
                        updater->_Height = updater->_Right->_Height+1;
                    }
                } else {
                    (updater->_Height)--;
                }
                updater=updater->_Parent;
            }
        }
        
    }
    
    /* NodeBalanceUpdate
     * Description: used to update the balance factor of nodes from a node
     *              somewhere in a tree up to the root of the tree.
     * @param Node: Node to start updating from.
     */
    void NodeBalanceUpdate(AVLNode<T>* Node){ //TODO write recursive!!!!
        if (!Node){
            return;
        }
        AVLNode<T>* updater = Node;
        while (updater){
            if (updater->_Left && updater->_Right){
                updater->_Balance = (updater->_Left->_Height) - (updater->_Right->_Height);
            } else if (updater->_Left == NULL){
                updater->_Balance = (-1)*(updater->_Height);
              /*  if (updater->_Right->_Height){
                    updater->_Balance = (-1)*(updater->_Right->_Height);
                } else {
                    updater->_Balance = -1;
                }*/
            } else if (updater->_Right == NULL){
                updater->_Balance = updater->_Height;
              /*  if (updater->_Left->_Height){
                    updater->_Balance = (updater->_Left->_Height);
                } else {
                    updater->_Balance = 1;
                }*/
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
    AVLNode<T>* SubTreeMin (AVLNode<T>* SubRoot){
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
    
    /* Find
     * Description: finds a node with certain data in the tree.
     * @param Data: data to match node.
     * @return: NULL if Data is a null pointer or if not found in the tree.
     *          Pointer to the node elsewise.
     */
    AVLNode<T>* Find (T* Data){
        if (Data == NULL){
            return NULL;
        }
        AVLNode<T>* toReturn = Root;
        while (toReturn){
            if (*Data < *(toReturn->Data)){
                toReturn=toReturn->Left;
                continue;
            }
            if  (*Data > *(toReturn->Data)){
                toReturn=toReturn->Right;
                continue;
            }
            break;
        }
        return toReturn;
    }
    
    /* SwapNodes
     * Description: swaps the places of two nodes as part of a binary search tree
     *              node removal.
     * @param A: first node to swap.
     * @param B: second node to swap.
     */
    void SwapNodes (AVLNode<T>* A, AVLNode<T>* B){
        AVLNode<T>* temp=new AVLNode<T>();
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
        delete temp;
    }

public:
    AVLTree(){
        Root=NULL;
    }
    
    bool IsEmpty() const{
        return (Root == NULL);
    }
    
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
        AVLNode<T>* Current = Root;
        //Step 1
        while (Current){
            parent = Current;
            if (*tmp < *Current) {
                Current = Current->_Left;
            } else{
                Current = Current->_Right;
            }
        }
        tmp->_Parent = parent;
        //Step 2
        if (*tmp < *parent){
            parent->_Left = tmp;
        }else {
            parent->_Right = tmp;
        }
        UpdateHeights(tmp,'I');
        NodeBalanceUpdate(parent);
        //Step 3
        while (tmp->_Parent){
            parent = tmp->_Parent;
            if (parent->_Balance >= -1 && parent->_Balance <= 1){
                tmp = parent;
                continue;
            }
            if (parent->_Balance >= 2){
                if (parent->_Left->_Balance >= 0){
                    parent=LeftLeft(parent);
                } else if (parent->_Left->_Balance == -1){
                    parent=LeftRight(parent);
                }
            }
            else {
                if (parent->_Right->_Balance <= 0){
                    RightRight(parent);
                } else if (parent->_Right->_Balance == 1){
                    RightLeft(parent);
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
        AVLNode<T>* Tmp = Find(Data);
        AVLNode<T>* Parent = Tmp->Parent;
        if (Tmp->Height == 0){
            if ( *(Parent->Left->Data) == *(Tmp->Data)){
                delete Tmp;
                Parent->Left = NULL;
            } else {
                delete Tmp;
                Parent->Right = NULL;
            }
        } else if (Tmp->Left && Tmp->Right==NULL){
            if (Parent->Left == Tmp){
                Parent->Left = Tmp->Left;
                delete Tmp;
            } else if (Parent->Right == Tmp){
                Parent->Right = Tmp->Left;
                delete Tmp;
            }
        } else if (Tmp->Right && Tmp->Left==NULL){
            if (Parent->Left == Tmp){
                Parent->Left = Tmp->Right;
                delete Tmp;
            } else if (Parent->Right == Tmp){
            Parent->Right = Tmp->Right;
                delete Tmp;
            }
        } else {
            AVLNode<T>* ToSwap = SubTreeMin(Tmp->Right);
            AVLNode<T>* SwapParent = ToSwap->Parent;
            SwapParent->Left=NULL;
            if (Parent->Right == Tmp){
                Parent->Right = ToSwap;
                SwapNodes(Tmp, ToSwap);
            }else {
                Parent->Left = ToSwap;
                SwapNodes(Tmp, ToSwap);
            }
            delete Tmp;
            if (SwapParent->Height >= 2){
                NodeBalanceUpdate(SwapParent);
            } else {
                if (SwapParent->Right){
                    NodeBalanceUpdate(SwapParent);
                }else{
                    UpdateHeights(SwapParent, 'R');
                    NodeBalanceUpdate(SwapParent);
                }
            }
            
        }
        
    }

    bool IsIn(T* Data){
        AVLNode<T>* Current = Root;
        while(Current){
            if (*Data < *(Current->Data)){
                Current=Current->Left;
                continue;
            }
            if  (*Data > *(Current->Data)){
                Current=Current->Right;
                continue;
            }
            return true;
        }
        return false;
    }

    AVLNode<T>* GetMin (){
        return SubTreeMin(Root);
    }
    
    AVLNode<T>* RightRight (AVLNode<T>* Node){
        return Node;
    }
    AVLNode<T>* RightLeft (AVLNode<T>* Node){
        return Node;
    }
    AVLNode<T>* LeftRight (AVLNode<T>* Node){
        return Node;
    }
    AVLNode<T>* LeftLeft (AVLNode<T>* Node){
        AVLNode<T>* child = Node->_Left;
        AVLNode<T>* grandChild= child->_Left;
        AVLNode<T>* parent = Node->_Parent;
        Node->_Left = child->_Right;
        child->_Parent = parent;
        if (Node->_Left == NULL){
            if (Node->_Right){
                Node->_Height = Node->_Right->_Height+1;
                //update its balance as well
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
        UpdateHeights(child, 'I');
        NodeBalanceUpdate(grandChild);
        return Node;
    }
};

#endif /* defined(__Mivne1__BTree__) */
