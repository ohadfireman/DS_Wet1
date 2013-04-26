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

template <typename T>
class AVLNode{
public:
    int _Balance;
    int _Height;
    AVLNode *_Left, *_Right, *_Parent;
    T _Data;
    
    AVLNode<T>(){
        _Balance=0;
        _Height=0;
        _Left=NULL;
        _Right=NULL;
        _Parent=NULL;
    };
    AVLNode<T>(T Data):_Data(Data),_Balance(0),_Height(0),_Left(NULL),
                _Right(NULL),_Parent(NULL){}
    ~AVLNode(){}
};

template <typename T>
class AVLTree {
    AVLNode<T>* Root;
    
    /* UpdateHeights
     * Description: used to update the heights of nodes from a node in a tree
     *          to the root of the tree.
     * @param Node: Node to start updating from.
     * @param Mode: will be I if called from node insertion,
     *          R if called from node removal.
     * Note: insertion heights are calculated from the inserted node up,
     *       removal heights are calculated from the removed node's parent up.
     */
    void UpdateHeights (AVLNode<T>* Node, char Mode) {
        AVLNode<T>* Updater=Node;
        if (Mode == 'I'){
            while (Updater->_Parent){
                if (Updater->_Parent->_Height >= Updater->_Height+1){
                    break;
                }
                Updater->_Parent->_Height = Updater->_Height+1;
                Updater = Updater->_Parent;
            }
        } else if (Mode == 'R'){
            Node->_Height=0;
            Updater = Node->_Parent;
            while (Updater) {
                if (Updater->_Right){
                    if(Updater->_Height == Updater->_Right->_Height+1){
                        break;
                    }
                    if (Updater->_Left->_Height > Updater->_Right->_Height){
                        Updater->_Height = Updater->_Left->_Height+1;
                    } else {
                        Updater->_Height = Updater->_Right->_Height+1;
                    }
                } else {
                    (Updater->_Height)--;
                }
                Updater=Updater->_Parent;
            }
        }
        
    }
    
    void NodeBalanceUpdate(AVLNode<T>* Node){ //TODO write recursive!!!!
        if (!Node){
            return;
        }
        if (Node->_Left && Node->_Right){
            Node->_Balance = (Node->_Left->_Height) - (Node->_Right->_Height);
        } else if (Node->_Left == NULL){
            Node->_Balance = (-1)*(Node->_Right->_Height);
        } else if (Node->_Right == NULL){
            Node->_Balance = Node->_Left->_Height;
        }
    }
    
    AVLNode<T>* SubTreeMin (AVLNode<T>* SubRoot){
        if (SubRoot == NULL){
            return NULL;
        } else if ( SubRoot->_Left ==  NULL){
            return SubRoot;
        }
        AVLNode<T>* Min = SubRoot;
        while (Min->_Left){
            Min = Min->_Left;
        }
        return Min;
    }
    
    AVLNode<T>* Find (T* Data){
        if (Data == NULL){
            return NULL;
        }
        AVLNode<T>* ToReturn = Root;
        while (ToReturn){
            if (*Data < *(ToReturn->Data)){
                ToReturn=ToReturn->Left;
                continue;
            }
            if  (*Data > *(ToReturn->Data)){
                ToReturn=ToReturn->Right;
                continue;
            }
            break;
        }
        return ToReturn;
    }
    
    void SwapNodes (AVLNode<T>* A, AVLNode<T>* B){
        AVLNode<T>* Temp=new AVLNode<T>();
        Temp->Left = A->Left;
        Temp->Right = A->Right;
        Temp->Parent = A->Parent;
        Temp->Balance = A->Balance;
        Temp->Height = A->Height;
        A->Left = B->Left;
        A->Right = B->Right;
        A->Parent = B->Parent;
        A->Balance = B->Balance;
        A->Height = B->Height;
        B->Left = Temp->Left;
        B->Right = Temp->Right;
        B->Parent = Temp->Parent;
        B->Balance = Temp->Balance;
        B->Height = Temp->Height;
        delete Temp;
    }

public:
    AVLTree(){
        Root=NULL;
    }
    
    bool IsEmpty(){
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
        AVLNode<T>* Tmp = new AVLNode<T>();
        AVLNode<T>* Parent = NULL;
        Tmp->_Data = *Data;
        if (Root == NULL){
            Root = Tmp;
            return;
        }
        AVLNode<T>* Current = Root;
        //Step 1
        while (Current){
            Parent = Current;
            if (Tmp->_Data < Current->_Data) {
                Current = Current->_Left;
            } else{
                Current = Current->_Right;
            }
        }
        Tmp->_Parent = Parent;
        //Step 2
        if (Tmp->_Data < Parent->_Data){
            Parent->_Left = Tmp;
        }else {
            Parent->_Right = Tmp;
        }
        UpdateHeights(Tmp,'I');
        //Step 3
        while (Tmp->_Parent){
            Parent = Tmp->_Parent;
           /* if (Parent->Height >= Tmp->Height+1){
                return;
            }
            Parent->Height = Tmp->Height+1;*/
            NodeBalanceUpdate(Parent);
            if (Parent->_Balance >= -1 && Parent->_Balance <= 1){
                Tmp = Parent;
                continue;
            }
            if (Parent->_Balance >= 2){
                if (Parent->_Left->_Balance >= 0){
                    Parent=LeftLeft(Parent);
                } else if (Parent->_Left->_Balance == -1){
                    Parent=LeftRight(Parent);
                }
            }
            else {
                if (Parent->_Right->_Balance <= 0){
                    RightRight(Parent);
                } else if (Parent->_Right->_Balance == 1){
                    RightLeft(Parent);
                }
            }
            Tmp = Parent;
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
        return Node;
    }
};

#endif /* defined(__Mivne1__BTree__) */
