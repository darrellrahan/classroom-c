// ==================================================
// FILE: src/modules/menu.c
// ==================================================

#include "../headers/menu.h"
#include "../headers/dataio.h"
#include "../headers/utils.h"
#include "../headers/auth.h"
#include "../headers/teacher.h"
#include "../headers/student.h"
#include "../headers/structs.h"

void register_menu() {
    int choice;
    do {
        clear_screen();
        printf("=== REGISTER MENU ===\n");
        printf("1. Register as Teacher\n");
        printf("2. Register as Student\n");
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if(register_teacher()) {
                    printf("Teacher registration successful!\n");
                    pause_screen();
                    return;
                }
                break;
            case 2:
                if(register_student()) {
                    printf("Student registration successful!\n");
                    pause_screen();
                    return;
                }
                break;
            case 0:
                return;
            default:
                printf("Invalid choice!\n");
                pause_screen();
        }
    } while(choice != 0);
}

void login_menu() {
    int choice;
    do {
        clear_screen();
        printf("=== LOGIN MENU ===\n");
        printf("1. Login as Teacher\n");
        printf("2. Login as Student\n");
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if(login_teacher()) {
                    teacher_dashboard();
                    current_teacher = NULL;
                }
                break;
            case 2:
                if(login_student()) {
                    student_dashboard();
                    current_student = NULL;
                }
                break;
            case 0:
                return;
            default:
                printf("Invalid choice!\n");
                pause_screen();
        }
    } while(choice != 0);
}

void teacher_dashboard() {
    int choice;
    do {
        clear_screen();
        printf("=== TEACHER DASHBOARD ===\n");
        printf("Welcome, %s!\n\n", current_teacher->name);
        printf("1. Manage Courses\n");
        printf("2. Account Settings\n");
        printf("3. Logout\n");
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                teacher_course_menu();
                break;
            case 2:
                clear_screen();
                printf("=== ACCOUNT SETTINGS ===\n");
                printf("Name: %s\n", current_teacher->name);
                printf("Unique Number: %s\n", current_teacher->teacher_unique_number);
                printf("Email: %s\n", current_teacher->email);
                printf("Phone: %s\n", current_teacher->phone_number);
                printf("\n1. Back to Dashboard\n");
                scanf("%d", &choice);
                break;
            case 3:
                return;
            case 0:
                return;
            default:
                printf("Invalid choice!\n");
                pause_screen();
        }
    } while(choice != 3);
}

void student_dashboard() {
    int choice;
    do {
        clear_screen();
        printf("=== STUDENT DASHBOARD ===\n");
        printf("Welcome, %s!\n\n", current_student->name);
        
        // Show enrolled courses
        printf("Your Courses:\n");
        Course *temp = courses_head;
        int count = 1;
        while(temp) {
            if(is_student_enrolled(temp, current_student->student_id)) {
                printf("%d. %s (Code: %s)\n", count++, temp->name, temp->code);
            }
            temp = temp->next;
        }
        
        printf("\n%d. Join New Course\n", count);
        printf("%d. Account Settings\n", count + 1);
        printf("%d. Logout\n", count + 2);
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if(choice == 0 || choice == count + 2) return;
        
        if(choice == count) {
            // Join new course
            char course_code[MAX_STRING];
            printf("Enter course code: ");
            scanf("%s", course_code);
            
            Course *course = find_course_by_code(course_code);
            if(course) {
                if(!is_student_enrolled(course, current_student->student_id)) {
                    // Add to waitlist
                    Student *new_waitlist = (Student*)malloc(sizeof(Student));
                    *new_waitlist = *current_student;
                    new_waitlist->next = course->waitlist_students;
                    course->waitlist_students = new_waitlist;
                    printf("Join request sent! Waiting for teacher approval.\n");
                } else {
                    printf("You are already enrolled in this course!\n");
                }
            } else {
                printf("Course not found!\n");
            }
            pause_screen();
        } else if(choice == count + 1) {
            // Account settings
            clear_screen();
            printf("=== ACCOUNT SETTINGS ===\n");
            printf("Name: %s\n", current_student->name);
            printf("Unique Number: %s\n", current_student->student_unique_number);
            printf("Email: %s\n", current_student->email);
            printf("Phone: %s\n", current_student->phone_number);
            printf("\n1. Back to Dashboard\n");
            scanf("%d", &choice);
        } else {
            // Select course
            temp = courses_head;
            int current_count = 1;
            while(temp) {
                if(is_student_enrolled(temp, current_student->student_id)) {
                    if(current_count == choice) {
                        student_topic_menu(temp);
                        break;
                    }
                    current_count++;
                }
                temp = temp->next;
            }
        }
    } while(true);
}
