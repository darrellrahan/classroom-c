/******************************************************************************
 * File: structs.h (src/headers/structs.h)
 *
 * Copyright 2025 TLBB team
 * All Rights Reserved.
 *
 * File ini dibuat untuk memenuhi tugas besar SDA (Struktur Data dan Algoritma). 
 * Dilarang menyalin atau mendistribusikan berkas ini tanpa izin.
 *
 * Authors:     Darrell, Dimas, Thoriq
 * Created:     May 23, 2025
 *
 * Description: 
 *      Representasi dari kebutuhan data untuk aplikasi Classroom II atau 
 *      Courseroom. Berisikan implementasi struktur data yang menerapkan
 *      Stack, Queue, dan Tree.
 * 
 *      
 * Note:
 *      Program ini ditujukan untuk tujuan pendidikan saja. 
 *      Program ini tidak dioptimalkan untuk penggunaan produksi.
 ******************************************************************************/


#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

// Constants
#define MAX_STRING 256
#define MAX_URL 512
#define MAX_PHONE 20
#define MAX_EMAIL 100
#define MAX_PASSWORD 50
#define MAX_UNIQUE_NUM 20
#define MAX_STACK_SIZE 100

// Navigation String
#define MAIN_MENU "MAIN_MENU"
#define REGISTER_MENU "REGISTER_MENU"
#define LOGIN_MENU "LOGIN_MENU"

#define STUDENT_DASHBOARD "STUDENT_DASHBOARD"
#define STUDENT_ACCOUNT_SETTINGS "STUDENT_ACCOUNT_SETTINGS"
#define STUDENT_SEE_ACCOUNT "STUDENT_SEE_ACCOUNT"
#define STUDENT_SEE_OTHER_STUDENTS "STUDENT_SEE_OTHER_STUDENTS"
#define STUDENT_TOPIC_MENU "STUDENT_TOPIC_MENU"
#define STUDENT_TOPIC_DETAIL "STUDENT_TOPIC_DETAIL"
#define STUDENT_VIEW_MATERIALS "STUDENT_VIEW_MATERIALS"
#define STUDENT_VIEW_ANNOUNCEMENTS "STUDENT_VIEW_ANNOUNCEMENTS"
#define STUDENT_VIEW_ASSIGNMENTS "STUDENT_VIEW_ASSIGNMENTS"
#define STUDENT_SUBMIT_ASSIGNMENT "STUDENT_SUBMIT_ASSIGNMENT"

#define TEACHER_DASHBOARD "TEACHER_DASHBOARD"
#define TEACHER_ACCOUNT_SETTINGS "TEACHER_ACCOUNT_SETTINGS"
#define TEACHER_SEE_ACCOUNT "TEACHER_SEE_ACCOUNT"
#define TEACHER_COURSE_MENU "TEACHER_COURSE_MENU"
#define TEACHER_SEE_STUDENTS "TEACHER_SEE_STUDENTS"
#define TEACHER_MANAGE_TOPICS "TEACHER_MANAGE_TOPICS"
#define TEACHER_TOPIC_DETAIL "TEACHER_TOPIC_DETAIL"
#define TEACHER_MANAGE_ASSIGNMENTS "TEACHER_MANAGE_ASSIGNMENTS"
#define TEACHER_SHOW_NOTGRADED_SUBMISSIONS "TEACHER_SHOW_NOTGRADED_SUBMISSIONS"
#define TEACHER_SHOW_GRADED_SUBMISSIONS "TEACHER_SHOW_GRADED_SUBMISSIONS"
#define TEACHER_GRADE_SUBMISSIONS "TEACHER_GRADE_SUBMISSIONS"
#define TEACHER_MANAGE_MATERIALS "TEACHER_MANAGE_MATERIALS"
#define TEACHER_MANAGE_ANNOUNCEMENTS "TEACHER_MANAGE_ANNOUNCEMENTS"
#define TEACHER_REVIEW_REQUESTS "TEACHER_REVIEW_REQUESTS"

// Data
typedef struct {
    int day, month, year, hour, minute;
} Timestamp;

// Forward declarations
typedef struct Student Student;
typedef struct Teacher Teacher;
typedef struct Course Course;
typedef struct Topic Topic;
typedef struct Assignment Assignment;
typedef struct Submission Submission;
typedef struct Material Material;
typedef struct Announcement Announcement;

// Stack ADT untuk Navigation
typedef struct StackNode {
    char menu_name[MAX_STRING];
    void* data; // untuk menyimpan data context (course, topic, etc.)
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    int size;
} NavigationStack;

// Student
struct Student {
    int student_id;
    char student_unique_number[MAX_UNIQUE_NUM];
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
    char name[MAX_STRING];
    char phone_number[MAX_PHONE];
    Student *next;
};

// Teacher - Hierarchy Level 1
struct Teacher {
    int teacher_id;
    char teacher_unique_number[MAX_UNIQUE_NUM];
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
    char name[MAX_STRING];
    char phone_number[MAX_PHONE];
    Teacher *next;
};

// Course - Hierarchy Level 2
struct Course {
    int course_id;
    char code[MAX_STRING];
    char name[MAX_STRING];
    char description[MAX_STRING];
    int teacher_id;
    Student *enrolled_students;
    Student *waitlist_students;
    Topic *topics;
    Course *next;
};

// Topic - Hierarchy Level 3
struct Topic {
    int topic_id;
    char title[MAX_STRING];
    char description[MAX_STRING];
    Timestamp created_at;
    int course_id;
    Assignment *assignments;
    Material *materials;
    Announcement *announcements;
    Topic *next;
};

// Assignment - Hierarchy Level 4
struct Assignment {
    int assignment_id;
    char title[MAX_STRING];
    Timestamp deadline;
    Timestamp created_at;
    int course_id;
    int topic_id;
    Submission *graded_submissions;
    Submission *not_graded_submissions;
    Assignment *next;
};

// Submission - Hierarchy Level 5
struct Submission {
    int submission_id;
    int grade;
    char url[MAX_URL];
    Timestamp created_at;
    bool is_graded;
    bool is_submitted;
    int student_id;
    int assignment_id;
    Student *student;
    Submission *next;
};

// Material - Hierarchy Level 4
struct Material {
    int material_id;
    int course_id;
    int topic_id;
    Timestamp created_at;
    char title[MAX_STRING];
    char description[MAX_STRING];
    char url[MAX_URL];
    Material *next;
};

// Announcement - Hierarchy Level 4
struct Announcement {
    int announcement_id;
    int course_id;
    int topic_id;
    Timestamp created_at;
    char title[MAX_STRING];
    char description[MAX_STRING];
    Announcement *next;
};

// Global variables
extern Student *students_head;
extern Teacher *teachers_head;
extern Course *courses_head;
extern Student *current_student;
extern Teacher *current_teacher;
extern int next_student_id;
extern int next_teacher_id;
extern int next_course_id;
extern int next_topic_id;
extern int next_assignment_id;
extern int next_submission_id;
extern int next_material_id;
extern int next_announcement_id;

#endif
