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

class DS{
    AVLTree<Course> Courses;
    int _NumberOfCourses;
    AVLTree<Student> Students;
public:
    DS():_NumberOfCourses(0){}
    
    StatusType AddCourse(int CourseID, int Size){
        
    }
    
    StatusType RemoveCourse(int CourseID){
        
    }
    
    StatusType AddStudent(int StudentId){
        
    }
    
    StatusType RemoveStudent(int StudentId){
        
    }
    
    StatusType TakeCourse(int StudentId){
        
    }
    
    StatusType LeaveCourse(int StudentId,int CourseID){
        
    }
    
    StatusType EnlargeCourse(int CourseID,int ExtraSize){
    
    }
    
    StatusType GetAllCourses(void *DS, int ***courses, int**coursesSize, int *numOfCourses){
        
    }

};


#endif
