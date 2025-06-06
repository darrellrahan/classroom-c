// ==================================================
// FILE: src/headers/teacher.h
// ==================================================

#ifndef TEACHER_H
#define TEACHER_H

#include "structs.h"

// Teacher functions
void teacher_manage_topics(Course *course);
void teacher_topic_detail(Course *course, Topic *topic);
void teacher_manage_assignments(Course *course, Topic *topic);
void teacher_grade_submissions(Assignment *assignment);

#endif
