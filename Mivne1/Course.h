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
#include "LList.h"

class PendingStudent {
    int _StudentID;
    int _PendTiming;
public:
    PendingStudent(int ID,int Timing):_StudentID(ID),_PendTiming(Timing){}
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
    int _NumOfPending;
    AVLTree<int> _EnrolledStudents; //switched to int-doesn't need any extra info in here.
    LListNode<int>* _PendingHead;
    LListNode<int>* _PendingTail;
public:
    Course(): _ID(-1), _Size(0){}
    Course(int Id,int Size):_ID(Id),_Size(Size),_AvailableSeats(Size),_NumOfPending(0){}
    ~Course(){}
    
    int GetID(){
        return _ID;
    }
    
    int GetSize(){
        return _Size;
    }
    
    void IncreaseSize(int Addition){
        _Size += Addition;
        //TODO- continue working on this.
        //if there are pending students they need to move from pending to enrolled
        // according to the new course size
    }

    const bool Enroll(int* StudentID){
        if (StudentID){
            Student student(*StudentID);
            if (_AvailableSeats){
                _EnrolledStudents.Insert(&student);
                _AvailableSeats--;
                return true;
            }
            PendingStudent pend(*StudentID,_NumOfPending+1);
            _PendingStudents.Insert(&pend);
        }
        return false;
    }
    
    const bool Leave(int* StudentID){ //Refactored from "Drop"
        if (!StudentID){
            return false;
        }
        Student student(*StudentID);
        PendingStudent pend(*StudentID);
        if (_EnrolledStudents.IsIn(&student)){
            _EnrolledStudents.Remove(&student);
            if (!_PendingStudents.IsEmpty()){
                _PendingStudents.Remove(<#PendingStudent *Data#>)
            } else {
                _AvailableSeats++;
            }

        }else {
            _PendingStudents.Remove(&student);

        }
        return true;
    }
    
    //used to check if student is either on course enrolled tree or pending tree.
    const bool IsEnrolled(int* StudentID) {
        Student student(*StudentID);
        if (_EnrolledStudents.IsIn(&student) || _PendingStudents.IsIn(&student)){
            return true;
        }
            return false;
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
