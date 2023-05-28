#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linked-list.h"

//-----------------------------------------------------------------------------
//Structures' definitions
//-----------------------------------------------------------------------------


/**
 * @brief student element for linked list in 'grades'.
 * @note type name: student_t, pointer to type: pstudent_t
 */
typedef struct student {
    int id;
    char *name;
    struct list* courses;
} *pstudent_t, student_t;

typedef struct course {
    int grade;
    char *name;
} *pcourse_t, course_t;

typedef struct grades {
    struct list* students;
} *pgrades_t, grades_t;

//-----------------------------------------------------------------------------
//Linked-list user functions
//-----------------------------------------------------------------------------

/**
 * @brief Receives pointers to source and target. Clones source course to
 * target.
 * @param *element A pointer to the given course to clone.
 * @param **output A pointer to the target pointer address.
 * @returns 0 on success, -1 on failure.
 */
int course_clone(void *element, void **output) {
    pcourse_t course = malloc(sizeof(course_t));
    if(course == NULL)
    {
        return -1;
    }
    pcourse_t source_course = element;
    course->name = malloc((strlen( source_course->name ) + 1)*sizeof(char));
    if(course->name == NULL)
    {
        return -1;
    }
    course->grade = source_course->grade;
    strcpy(course->name, source_course->name);
    *output = course;
    return 0;
}

/**
 * @brief Deletes element of the type "struct student"
 * @param *element A pointer to the given student to delete.
 */
void student_destroy(void *element) {
    pstudent_t student = element;
    list_destroy(student->courses);
    free(student->name);
    free(student);
}

/**
 * @brief Deletes element of the type "struct course"
 * @param *element A pointer to the given course to delete.
 */
void course_destroy(void *element) {
    pcourse_t course = element;
    free(course->name);
    free(course);
}

/**
 * @brief Receives pointers to source and target. Clones source student to
 * target.
 * @param *element A pointer to the given student to clone.
 * @param **output A pointer to the target pointer address.
 * @returns 0 on success, -1 on failure.
 */
int student_clone(void *element, void **output) {
    pstudent_t student = malloc(sizeof(student_t));
    if(student == NULL)
    {
        return -1;
    }
    pstudent_t source_student = element;
    student->name = malloc((strlen(source_student->name) + 1) * sizeof(char));
    if(student->name == NULL)
    {
        return -1;
    }
    student->id = source_student->id;
    strcpy(student->name, source_student->name);
    student->courses = list_init(course_clone, course_destroy);
    struct iterator* it = list_begin(source_student->courses);
    while(it != NULL)
    {
        pcourse_t course = list_get(it);
        list_push_back(student->courses, course);
        it = list_next(it);
    }
    *output = student;
    return 0;
}


//-----------------------------------------------------------------------------
//ADT functions
//-----------------------------------------------------------------------------

/**
 * @brief Initializes the "grades" data-structure.
 * @returns A pointer to the data-structure, of NULL in case of an error
 */
struct grades* grades_init() {
    pgrades_t grades = malloc(sizeof(grades_t));
    if(grades == NULL)
    {
        return NULL;
    }
    grades->students = list_init(student_clone, student_destroy);
    if(grades->students == NULL)
    {
        free(grades);
        return NULL;
    }
    return grades;
}

/**
 * @brief Destroys "grades", de-allocate all memory!
 */
void grades_destroy(struct grades *grades) {
    list_destroy(grades->students);
    free(grades);
}

/**
 * @brief Adds a student with "name" and "id" to "grades"
 * @returns 0 on success
 * @note Failes if "grades" is invalid, or a student with 
 * the same "id" already exists in "grades"
 */
int grades_add_student(struct grades *grades, const char *name, int id) {
    if(grades == NULL) {
        return -1;
    }
    struct iterator* it = list_begin(grades->students);
    while(it != NULL)
    {
        pstudent_t st = list_get(it);
        if(st->id == id) {
            return -1;
        }
        it = list_next(it);
    }
    pstudent_t student = malloc(sizeof(student_t));
    student->name = malloc(strlen((name)+1)*sizeof(char));
    if(student->name == NULL)
    {
        free(student);
        return -1;
    }
    strcpy(student->name, name);
    student->id = id;
    list_push_back(grades->students, student);
    free(student->name);
    free(student);
    return 0;
}

/**
 * @brief Adds a course with "name" and "grade" to the student with "id"
 * @return 0 on success
 * @note Failes if "grades" is invalid, if a student with "id" does not exist
 * in "grades", if the student already has a course with "name", or if "grade"
 * is not between 0 to 100.
 */
int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade)
{
    if(grades == NULL)
    {
        return -1;
    }
    if( (grade < 0) || (grade > 100) )
    {
        return -1;
    }
    struct iterator* it = list_begin(grades->students);
    while (it != NULL)
    {
        pstudent_t student = list_get(it);
        if(student->id == id)
        {
            struct iterator* jt = list_begin(student->courses);
            while(jt != NULL)
            {
                pcourse_t temp = list_get(jt);
                if(strcmp(temp->name, name) == 0)
                {
                    return -1;
                }
                jt = list_next(jt);
            }
            pcourse_t course = malloc(sizeof(course_t));
            if(course == NULL)
            {
                return -1;
            }
            course->grade = grade;
            course->name = malloc((strlen(name) + 1)*sizeof(char));
            if(course->name == NULL)
            {
                free(course);
                return -1;
            }
            strcpy(course->name, name);
            list_push_back(student->courses, course);
            free(course->name);
            free(course);
            return 0;
        }
        it = list_next(it);
    }
    return -1;
}

/**
 * @brief Calcs the average of the student with "id" in "grades".
 * @param[out] out This method sets the variable pointed by "out" to the
 * student's name. Needs to allocate memory. The user is responsible for
 * freeing the memory.
 * @returns The average, or -1 on error
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note If the student has no courses, the average is 0.
 * @note On error, sets "out" to NULL.
 */
float grades_calc_avg(struct grades *grades, int id, char **out) {
    if(grades == NULL)
    {
        *out = NULL;
        return -1;
    }
    struct iterator *it = list_begin(grades->students);
    pstudent_t student = NULL;
    while(it != NULL)
    {
        student = list_get(it);
        if(student->id == id)
        {
            *out =(char*)malloc(strlen(student->name)+1);
            if (!*out)
            {
                return -1;
            }
            strcpy(*out,student->name);
            break;
        }
        it = list_next(it);
    }
    if(it == NULL)
    {
        *out = NULL;
        return -1;
    }
    float sum = 0;
    int count = 0;
    struct iterator *jt = list_begin(student->courses);
    while(jt != NULL)
    {
        pcourse_t course = list_get(jt);
        sum += course->grade;
        count ++;
        jt = list_next(jt);
    }
    return (count == 0) ? 0 : (sum / count) * 1.0;
}

/**
 * @brief Prints the courses of the student with "id" in the following format:
 * STUDENT-NAME STUDENT-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid, or if a student with "id" does not exist
 * in "grades".
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_student(struct grades *grades, int id) {
    if(grades == NULL)
    {
        return -1;
    }
    pstudent_t student = NULL;
    struct iterator *it = list_begin(grades->students);
    while(it != NULL)
    {
        student = list_get(it);
        if(student->id == id)
        {
            break;
        }
        it = list_next(it);
    }
    if(it == NULL)
    {
        return -1;
    }
    pcourse_t course = NULL;
    struct iterator *jt = list_begin(student->courses);
    struct iterator *last = list_end(student->courses);
    if(jt == last )
    {
        printf("%s %d:", student->name, student->id);
    }
    else
    {
    printf("%s %d:", student->name, student->id);
    }
    while(jt != NULL)
    {
        course = list_get(jt);
        if(jt != last)
        {
            printf(" %s %d,", course->name, course->grade);
        }
        if(jt == last)
        {
            printf(" %s %d", course->name, course->grade);
        }
        jt = list_next(jt);
    }
    printf("\n");
    return 0;
}

/**
 * @brief Prints all students in "grade", in the following format:
 * STUDENT-1-NAME STUDENT-1-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * STUDENT-2-NAME STUDENT-2-ID: COURSE-1-NAME COURSE-1-GRADE, [...]
 * @returns 0 on success
 * @note Fails if "grades" is invalid
 * @note The students should be printed according to the order 
 * in which they were inserted into "grades"
 * @note The courses should be printed according to the order 
 * in which they were inserted into "grades"
 */
int grades_print_all(struct grades *grades) {
    struct iterator *it ;
    pstudent_t student = NULL;
    for(it = list_begin(grades->students); it!=NULL ; it=list_next(it))
    {
        student = list_get(it);
        int true = grades_print_student(grades,student->id);
         if(true){
            //grades_print_student failed
            return -1;
         }
    }
    return 0;
}