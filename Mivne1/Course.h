//
//  Course.h
//  Mivne1
//
//  Created by Aviad Rom on 4/21/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_Course_h
#define Mivne1_Course_h
#include "AVLTree.h"
#include "Student.h"

class PendingStudent {
    int _StudentID;
    int _PendTiming;
public:
    const int GetId() const{
        return _StudentID;
    }
    
    const int GetPend() const{
        return _PendTiming;
    }
};

class Course{
    int _ID;
    int _Size;
    int _AvailableSeats;
    AVLTree<Student> _EnrolledStudents; //TODO- maybe switch to int
    AVLTree<Student> _PendingStudents;  //TODO- switch to PendingStudent
public:
    Course(): _ID(-1), _Size(0){}
    Course(int Id,int Size):_ID(Id),_Size(Size),_AvailableSeats(Size){}
    ~Course(){}
    
    int GetID(){
        return _ID;
    }
    
    int GetSize(){
        return _Size;
    }
    
    void IncreaseSize(int Addition){
        _Size += Addition;
    }

    bool Enroll(int* StudentID){
        if (StudentID){
            Student student(*StudentID);
            if (_AvailableSeats){
                _EnrolledStudents.Insert(&student);
                _AvailableSeats--;
                return true;
            }
            _PendingStudents.Insert(&student);
        }
        return false;
    }
    
    bool Leave(int* StudentID){ //Refactored from "Drop"
        if (!StudentID){
            return false;
        }
        Student student(*StudentID);
        _EnrolledStudents.Remove(&student);
        _PendingStudents.Remove(&student);
        return true;
    }
    
    bool IsEnrolled(int* StudentID){ 
        Student student(*StudentID);
        return _EnrolledStudents.IsIn(&student);
    }
    
    const bool operator<(Course& Comperator) const{
        return (_ID < Comperator.GetID());
    }
    
    const bool operator>(Course& Comperator) const{
        return (_ID > Comperator.GetID());
    }
    
    const bool operator==(Course& Comperator) const{
        return (_ID == Comperator.GetID());
    }
    
};

#endif
