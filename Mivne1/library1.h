/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 1                                          */ 
/*                                                                          */ 
/****************************************************************************/

/****************************************************************************/
/*                                                                          */ 
/* File Name : library1.h                                                   */ 
/*                                                                          */ 
/****************************************************************************/

#ifndef _234218_WET1_
#define _234218_WET1_


#ifdef __cplusplus
extern "C" {
#endif




/* Return Values
 * ----------------------------------- */
typedef enum {
    SUCCESS = 0,
    FAILURE = -1,
    ALLOCATION_ERROR = -2,
    INVALID_INPUT = -3
} StatusType;



/* Required Interface for the Data Structure
 * -----------------------------------------*/



/* Description:   Initiates the data structure.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void*       Init();


/* Description:   Adds a new course.
 * Input:         DS - A pointer to the data structure.
 *                courseID, - The course ID of the course to add.
 *		  size - the maximum amount of student that can take the course
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or if size < 0.
 *                FAILURE - if courseID is already in the DS or any other error.
 *                SUCCESS - Otherwise.
 */
StatusType AddCourse(void *DS, int courseID, int size);


/* Description:   Removes a course from the DS.
 * Input:         DS - A pointer to the data structure.
 *                courseID- ID of the course to be removed.
 *
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL
 *                FAILURE - If courseID is not in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType RemoveCourse(void *DS,int courseID);

/* Description:   Adds a new student
 * Input:         DS - A pointer to the data structure.
 *                studentID- The student ID of the student to add.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - if studentID is already in the DS or any other error.
 *                SUCCESS - Otherwise.
 */
StatusType AddStudent(void *DS, int studentID);


/* Description:   Removes a student from the DS.
 * Input:         DS - A pointer to the data structure.
 *                studentID - ID of the course to be removed.
 *
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL
 *                FAILURE - If studentID is not in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType RemoveStudent(void *DS,int studentID);

/* Description:   student number studentID takes course courseID
 * Input:         DS - A pointer to the data structure.
 *                studentID- The studentID of the student
 *		  courseID - The courseID of the course to take.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - if studentID is already in the course or studentID or CourseID are not in the DS or any other error.
 *                SUCCESS - Otherwise.
 */
StatusType TakeCourse(void *DS, int studentID, int courseID);

/* Description:   student number studentID leave course courseID
 * Input:         DS - A pointer to the data structure.
 *                studentID- The studentID of the student
 *		  courseID - The courseID of the course to leave.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - if studentID is not signed to the course or studentID or CourseID are not in the DS or any other error.
 *                SUCCESS - Otherwise.
 */
StatusType LeaveCourse(void *DS, int studentID, int courseID);

/* Description:   student number studentID leave course courseID
 * Input:         DS - A pointer to the data structure.
 *                extrasize - The number of extra student that can take the course.
 *		  courseID - The courseID of the course to leave.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL or if extrasize < 0.
 *                FAILURE - if coursID is not in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType EnlargeCourse(void *DS, int courseID, int extrasize);

/* Description:   Returns all the courses currently in the DS sorted by the courseID.
 * Input:         DS - A pointer to the data structure.
 * Output:        courses - A pointer to a to an array that you should update with the arrays containings courses and students.
 *                coursesSize - A pointer to a to an array that you should update with the size of each course
 *                *numOfCourses) - A pointer to a variable that should be updated to the number of courses.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If any of the arguments is NULL.
 *                FAILURE - In case of any other error ( no courses is not an error, just allocate zero sized arrays and zero in numOfCourses)
 *                SUCCESS - Otherwise.
 */
    StatusType GetAllCourses(void *DS, int ***courses, int**coursesSize, int *numOfCourses);


/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void        Quit(void** DS);



#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1_ */ 

