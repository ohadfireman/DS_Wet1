//
//  Student.h
//  Mivne1
//
//  Created by Aviad Rom on 4/22/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_Student_h
#define Mivne1_Student_h
#include "AVLTree.h"

class Student {
    int _ID;
    AVLTree<int> _CoursesTaken;
public:
    Student():_ID(-1){}
    
    Student(int ID):_ID(ID){}
    
    ~Student(){}
    
    int GetID(){
        return _ID;
    }
    
    bool AddCourse(int* CourseID){
        if (CourseID){
            _CoursesTaken.Insert(CourseID);
            return true;
        }
        return false;
    }
    
    bool operator< (Student& Comperator) const{
        return (_ID < Comperator.GetID());
    }
    
    bool operator> (Student& Comperator) const{
        return (_ID > Comperator.GetID());
    }
};

#endif
