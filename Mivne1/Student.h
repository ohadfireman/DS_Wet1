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
    AVLTree<int> _CoursesPending;
public:
    Student():_ID(-1){}
    
    Student(int ID):_ID(ID){}
    
    ~Student(){}
    
    int GetID(){
        return _ID;
    }
    
    const bool AddCourseTaken(int* CourseID){
        if (CourseID){
            _CoursesTaken.Insert(CourseID);
            if (_CoursesPending.IsIn(CourseID)){
                _CoursesPending.Remove(CourseID);
            }
            return true;
        }
        return false;
    }
    
    const bool AddCoursePending (int* CourseID){
        if (CourseID && !_CoursesTaken.IsIn(CourseID)){
            _CoursesPending.Insert(CourseID);
            return true;
        }
        return false;
    }
    
    const bool removeCourse(int* CourseID){
        if (CourseID){
            _CoursesTaken.Remove(CourseID);
            _CoursesPending.Remove(CourseID);
            return true;
        }
        return false;
    }
    
    
    const bool operator< (Student& Comperator) const{
        return (_ID < Comperator.GetID());
    }
    
    const bool operator> (Student& Comperator) const{
        return (_ID > Comperator.GetID());
    }
};

#endif
