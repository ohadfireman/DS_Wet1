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
    
     void unsignStudent(int courseID,AVLNode<Student>* root,char mode){
           if (root == NULL){
       		return;
       	}
       	unsignStudent(courseID,root->_Left,mode);							////This function was not checked!
       	if(mode == 'T'){
       		(root->_Data._CoursesTaken).Remove(&courseID);
       	}
       	if (mode == 'P'){
       		(root->_Data._CoursesPending).Remove(&courseID);
       	}
       	unsignStudent(courseID,root->_Right,mode);
    }

public:
    DS():_NumberOfCourses(0){}
    
    bool IsCourseExists(int CourseId){
        Course course(CourseId,0);
    	return Courses.IsIn(&course);
    }

    StatusType AddCourse(int CourseID, int Size){
    	try {
       	if (Size<0){
    	   return INVALID_INPUT;
       }
    	Course course(CourseID,Size);		//This function was not checked!
    	if (Courses.IsIn(&course)){
    		return FAILURE;
    	}
    	Courses.Insert(&course);
    	return SUCCESS;
    	} catch (bad_alloc& BadAlloc) {
             return ALLOCATION_ERROR;
        }
    }
    



    StatusType RemoveCourse(int CourseID){
    	try {
    	Course course(CourseID,0);
    	if (!Courses.IsIn(&course)){
      		return FAILURE;
       	}													//This function was not checked!
       	Courses.Remove(&course);
       	unsignStudent(CourseID,Students.GetRoot(),'T');
       	unsignStudent(CourseID,Students.GetRoot(),'P');
       	return SUCCESS;
    	} catch (bad_alloc& BadAlloc) {
    	       return ALLOCATION_ERROR;
        }
        
    }
    
    StatusType AddStudent(int StudentId){ //TODO Test
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

    StatusType RemoveStudent(int StudentId){ //TODO Test
        Student student(StudentId);
        AVLNode<Student>* studentNode = Students.Find(&student);
        if (!studentNode) return FAILURE;
        if (studentNode->_Data.GetNumberOfCoursesTaken()){
            return FAILURE;
        }
        return SUCCESS;
    }
    
    StatusType TakeCourse(int StudentID,int CourseID){ //TODO Test
        Student student(StudentID);
        Course course(CourseID,0);
        AVLNode<Student>* studentNode = Students.Find(&student);
        AVLNode<Course>* courseNode = Courses.Find(&course);
        if (!studentNode || !courseNode || courseNode->_Data.IsEnrolled(&StudentID)){
            return FAILURE;
        }
        try{
            if (courseNode->_Data.Enroll(&StudentID)){
                studentNode->_Data.AddCourseTaken(&CourseID);
            }else {
                studentNode->_Data.AddCoursePending(&CourseID);
            }
        } catch (bad_alloc& BadAlloc){
            studentNode->_Data.removeCourse(&CourseID);
            courseNode->_Data.Leave(&StudentID);
            return ALLOCATION_ERROR;
        }
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
