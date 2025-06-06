// ==================================================
// FILE: src/headers/utils.h
// ==================================================

#ifndef UTILS_H
#define UTILS_H

#include "structs.h"

// Utility functions
void clear_screen();
void pause_screen();
Course* find_course_by_code(char *code);
Course* find_course_by_id(int id);
Student* find_student_by_id(int id);
Student* find_student_by_unique_number(char *unique_number);
Assignment* find_assignment_by_id(int assignment_id);
void get_current_time(Timestamp *ts);
void print_timestamp(Timestamp ts);
bool is_deadline_passed(Timestamp deadline);
bool validate_url(char *url);
bool is_student_enrolled(Course *course, int student_id);
bool has_student_submitted(Assignment *assignment, int student_id);

#endif
