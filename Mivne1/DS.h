//
//  DS.h
//  Mivne1
//
//  Created by Aviad Rom on 4/22/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_DS_h
#define Mivne1_DS_h
#include "library1.h"
#include "AVLTree.h"
#include "Student.h"
#include "Course.h"
#include <iostream>
using namespace std;

class DS{
    AVLTree<Course> Courses;
    int _NumberOfCourses;
    AVLTree<Student> Students;
    
    void unsignStudent(int courseID,AVLNode<Student>* root){//TODO-Rename
       	if (root == NULL){
       		return;
       	}
       	unsignStudent(courseID, root->_Left);
       	root->_Data.removeCourse(&courseID);
       	unsignStudent(courseID,root->_Right);
    }

public:
    DS():_NumberOfCourses(0){}
    
    StatusType AddCourse(int CourseID, int Size){
        if (Size < 0){
            return INVALID_INPUT;
        }
    	Course course(CourseID,Size);		//how to check if allocation error occured?how to check if DS is NULL?
    	if (Courses.IsIn(&course)){
    		return FAILURE;
    	}
    	Courses.Insert(&course);
    	return SUCCESS;
    }

    
    StatusType RemoveCourse(int CourseID){
        Course course(CourseID,0);
    	if (!Courses.IsIn(&course)){
      		return FAILURE;
       	}
       	Courses.Remove(&course);
       	unsignStudent(CourseID,Students.GetRoot());
        
       	return SUCCESS;
    }
    
    StatusType AddStudent(int StudentId){
        Student student(StudentId);
        if (Students.IsIn(&student)){
            return FAILURE;
        }
        try {
            Students.Insert(&student);
            
        } catch (bad_alloc& BadAlloc) {
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    StatusType RemoveStudent(int StudentId){
        return SUCCESS;
    }
    
    StatusType TakeCourse(int StudentId){
        return SUCCESS;
    }
    
    StatusType LeaveCourse(int StudentId,int CourseID){
        return SUCCESS;
    }
    
    StatusType EnlargeCourse(int CourseID,int ExtraSize){
        return SUCCESS;
    }
    
    StatusType GetAllCourses(void *DS, int ***courses, int**coursesSize, int *numOfCourses){
        return SUCCESS;
    }

};


#endif
