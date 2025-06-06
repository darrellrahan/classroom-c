// ==================================================
// FILE: src/headers/queue.h
// ==================================================

#ifndef QUEUE_H
#define QUEUE_H

#include "structs.h"

// submissions
void enqueue_submission(Submission **queue, Submission *new_submission);
Submission* dequeue_submission(Submission **queue);

// students in course
void add_student_to_enrolled_list(Course *course, Student *student);
void add_student_to_waitlist(Course *course, Student *student);

#endif
