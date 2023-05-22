#include <string.h>
#include "student.h"

// Function to clone a student
elem_t student_clone(elem_t e) {
    pstudent_t student = malloc(sizeof(student_t));
    // Check if memory allocation is successful
    if (student == NULL) {
        return NULL;
    }
    pstudent_t source_student = e;
    // Allocate memory for the student's name
    student->name = malloc(strlen(source_student->name));
    // Copy the name from the source student to the new student
    strcpy(student->name, source_student->name);
    // Copy the age and id from the source student to the new student
    student->age = source_student->age;
    student->id = source_student->id;
    return student;
}

// Function to destroy a student
void student_destroy(elem_t e) {
    if (e == NULL) {
        return;
    }
    pstudent_t source_student = e;
    // Free the memory allocated for the student's name
    if (source_student->name != NULL) {
        free(source_student->name);
    }
    // Free the memory allocated for the student structure
    free(source_student);
}

// Function to print a student
void student_print(elem_t e) {
    if (e == NULL) {
        return;
    }
    pstudent_t source_student = e;
    // Print the student's name, age, and id
    printf("student name: %s, age: %d, id: %d.\n",
           source_student->name, source_student->age, source_student->id);
    return;
}
