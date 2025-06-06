// ==================================================
// FILE: src/modules/queue.c
// ==================================================

#include "../headers/queue.h"
#include "../headers/structs.h"

void enqueue_submission(Submission **queue, Submission *new_submission) {
    if (new_submission == NULL) return;
    
    new_submission->next = NULL;
    
    if(*queue == NULL) {
        *queue = new_submission;
        return;
    }
    
    Submission *temp = *queue;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_submission;
}

Submission* dequeue_submission(Submission **queue) {
    if(*queue == NULL) return NULL;
    
    Submission *temp = *queue;
    *queue = (*queue)->next;
    temp->next = NULL;
    return temp;
}

void add_student_to_enrolled_list(Course *course, Student *student) {
    Student *new_enrolled = (Student*)malloc(sizeof(Student));
    if(new_enrolled) {
        *new_enrolled = *student;
        
        new_enrolled->next = course->enrolled_students;
        course->enrolled_students = new_enrolled;
    }
}

void add_student_to_waitlist(Course *course, Student *student) {
    Student *new_waitlist = (Student*)malloc(sizeof(Student));
    if(new_waitlist) {
        *new_waitlist = *student;

        new_waitlist->next = course->waitlist_students;
        course->waitlist_students = new_waitlist;
    }
}
