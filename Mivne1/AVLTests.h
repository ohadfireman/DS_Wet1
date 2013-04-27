//
//  AVLTests.h
//  Mivne1
//
//  Created by Aviad Rom on 4/27/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_AVLTests_h
#define Mivne1_AVLTests_h
#include "AVLTree.h"
using namespace std;

// testing on int primitive
void InsertRemoveBasic(){
    AVLTree<int> tester;
    int nodes[]={6,4,8,3,5,7,9};
    for (int i = 0 ; i < 7 ; i++){
        tester.Insert(nodes+i);
        if (!tester.IsIn(nodes+i)){
            cout <<  "InsertRemoveBasic: Insertion failed. node " << nodes+i << "failed to insert"<< endl;
            return;
        }
    }
    for (int i = 6 ; i >= 0 ; i--){
        tester.Remove(nodes+i);
        if (tester.IsIn(nodes+i)){
            cout << "InsertRemoveBasic: Removal failed. node " << nodes+i << "still in tree" << endl;
            return;
        }
    }
    if (!tester.IsEmpty()){
        cout << "InsertRemoveBasic:Test Failed. did not remove all nodes from tree" << endl;
        return;
    }
        cout << "InsertRemoveBasic: Test passed."<<endl;

}

void LeftLeftInsertionBasic(){
    AVLTree<int> tester;
    int nodes[]={12,8,15,6,10,14,24,4,11,13,20,29,19,18};
    for (int i = 0; i < 14; i++)
        tester.Insert(nodes+i);
    AVLNode<int>* actual = tester.Find(nodes);
    if (actual->_Balance == -1 && actual->_Height == 4){
        cout << "LeftLeftInsertionBasic: Test Passed." << endl;
    } else {
        cout << "LeftLeftInsertionBasic: Test failed. check right branch on debug" <<endl;
    }
}

void LeftRightInsertionBasic(){
    AVLTree<int> tester;
    int nodes[12]={15,10,20,6,13,17,24,4,7,12,14,11};
    for (int i = 0; i < 12; i++)
        tester.Insert(nodes+i);
    AVLNode<int>* actual = tester.Find(nodes);
    if (actual->_Parent){
        actual = actual->_Parent;
    }
    if  (actual->_Data == 13 && actual->_Height == 3 && actual->_Balance == 0){
        cout << "LeftRightInsertionBasic: Test passed." <<  endl;
    } else {
        cout << "LeftRightInsertionBasic:Test failed. actual root is:" << actual->_Data << endl;
        cout << "Root info: Height=" << actual->_Height << " Balance=" << actual->_Balance <<endl;
    }

}

void RightRightInsertionBasic(){
    AVLTree<int> tester;
    int nodes[]={3,2,6,1,5,7,4,8,9};
    for (int i = 0; i < 9; i++){
        tester.Insert(nodes+i);
    }
    AVLNode<int>* actual = tester.Find(nodes);
    if (actual->_Height != 3){
        cout << "RightRightInsertion: Test failed. Debug right branch (did not perform roll correctly)" <<endl;
    }else {
        cout << "RightRightInsertion: Test Passed." << endl;
    }
}



//testing code is generic with strings

#endif
