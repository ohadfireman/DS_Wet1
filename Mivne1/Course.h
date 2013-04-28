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
};

class Course{
    int _ID;
    int _Size;
    int _AvailableSeats;
    AVLTree<Student> _EnrolledStudents;
    AVLTree<Student> _PendingStudents;
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
            if (_AvailableSeats){ //user would get exception for null ptr insert
                _EnrolledStudents.Insert(&student);
                _AvailableSeats--;
                return true;
            }
            _PendingStudents.Insert(&student);
        }
        return false;
    }
    
    bool Drop(int* StudentID){
        if (!StudentID){
            return false;
        }
        Student student(*StudentID);
        _EnrolledStudents.Remove(&student);
        _PendingStudents.Remove(&student);
        return true;
    }
    
    bool operator<(Course& Compared) const{
        return (_ID < Compared.GetID());
    }
    
    bool operator>(Course& Compared) const{
        return (_ID > Compared.GetID());
    }
    
};

#endif
