// ==================================================
// FILE: src/headers/student.h
// ==================================================

#ifndef STUDENT_H
#define STUDENT_H

#include "structs.h"

// Student functions
void student_topic_menu(Course *course);
void student_topic_detail(Course *course, Topic *topic);
void student_view_assignments(Course *course, Topic *topic);
void student_submit_assignment(Assignment *assignment);

#endif
