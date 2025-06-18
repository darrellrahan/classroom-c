// ==================================================
// FILE: src/headers/menu.h
// ==================================================

#ifndef MENU_H
#define MENU_H

#include "structs.h"

// global variables
extern char next_menu[MAX_STRING];
extern void* next_data;

// executor
void execute_menu(const char* menu_name, void* data);

// Function prototypes
void register_menu();
void login_menu();
void teacher_dashboard();
void student_dashboard();

// Students
void student_see_account();
void student_topic_menu(Course *course);
void student_topic_detail(Topic *topic);
void student_view_materials(Topic *topic);
void student_view_announcements(Topic *topic);
void student_view_assignments(Topic *topic);
void student_submit_assignment(Assignment *assignment);

void student_see_other_students(Course *course);

// Teacher functions
void teacher_see_account();
void teacher_course_menu();
void teacher_manage_topics(Course *course);
void teacher_review_requests(Course *course);
void teacher_topic_detail(Topic *topic);
void teacher_manage_assignments(Topic *topic);
void teacher_show_notgraded_submissions(Assignment *assignment);
void teacher_show_graded_submissions(Assignment *assignment);
void teacher_grade_submissions(Assignment *assignment);
void teacher_manage_materials(Topic *topic);
void teacher_manage_announcements(Topic *topic);

void teacher_see_students(Course *course);

#endif
