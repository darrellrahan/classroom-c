// ==================================================
// FILE: src/main.c
// ==================================================

#include "headers/structs.h"
#include "headers/utils.h"
#include "headers/auth.h"
#include "headers/menu.h"
#include "headers/dataio.h"
#include "headers/queue.h"
#include "headers/stack.h"

// Global variables
Student *students_head = NULL;
Teacher *teachers_head = NULL;
Course *courses_head = NULL;
Student *current_student = NULL;
Teacher *current_teacher = NULL;
int next_student_id = 1;
int next_teacher_id = 1;
int next_course_id = 1;
int next_topic_id = 1;
int next_assignment_id = 1;
int next_submission_id = 1;
int next_material_id = 1;
int next_announcement_id = 1;

void init_system();
void main_menu();
void save_data();
void load_data();
void cleanup();

// Implementation
int main() {
    init_system();
    load_data();
    main_menu();
    save_data();
    cleanup();
    return 0;
}

void init_system() {
    clear_screen();
    printf("=== Courseroom Learning Management System ===\n");
    printf("Initializing system...\n");
    pause_screen();
}

void main_menu() {
    char choice_str[10];
    char next_menu[MAX_STRING];
    void* next_data;

    do {
        clear_screen();
        printf("=== COURSEROOM MAIN MENU ===\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("0. Exit Program\n");
        printf("00. Redo\n");
        printf("Choice: ");
        scanf("%s", choice_str);
        
        if (strcmp(choice_str, "1") == 0) {
            navigate_to(MAIN_MENU, NULL);
            execute_menu(REGISTER_MENU, NULL);
        }
        else if (strcmp(choice_str, "2") == 0) {
            navigate_to(MAIN_MENU, NULL);
            execute_menu(LOGIN_MENU, NULL);
        }
        else if (strcmp(choice_str, "0") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                if (strcmp(next_menu, MAIN_MENU) != 0) {
                    execute_menu(next_menu, next_data);
                }
            } else {
                printf("Thank you for using Courseroom!\n");
                return;
            }
        }
        else if (strcmp(choice_str, "00") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        }
        else {
            printf("Invalid choice! Please try again.\n");
            pause_screen();
        }
    } while(strcmp(choice_str, "0") != 0);
}

void save_data() {
    save_students();
    save_teachers();
    save_courses();
}

void load_data() {
    load_students();
    load_teachers();
    load_courses();
}

void cleanup() {
    // Free all allocated memory
    while(students_head) {
        Student *temp = students_head;
        students_head = students_head->next;
        free(temp);
    }
    
    while(teachers_head) {
        Teacher *temp = teachers_head;
        teachers_head = teachers_head->next;
        free(temp);
    }
    
    while(courses_head) {
        Course *temp = courses_head;
        courses_head = courses_head->next;
        
        // Free topics and related data
        while(temp->topics) {
            Topic *topic_temp = temp->topics;
            temp->topics = temp->topics->next;
            
            // Free assignments and submissions
            while(topic_temp->assignments) {
                Assignment *assign_temp = topic_temp->assignments;
                topic_temp->assignments = topic_temp->assignments->next;
                
                while(assign_temp->graded_submissions) {
                    Submission *sub_temp = assign_temp->graded_submissions;
                    assign_temp->graded_submissions = assign_temp->graded_submissions->next;
                    free(sub_temp);
                }
                
                while(assign_temp->not_graded_submissions) {
                    Submission *sub_temp = assign_temp->not_graded_submissions;
                    assign_temp->not_graded_submissions = assign_temp->not_graded_submissions->next;
                    free(sub_temp);
                }
                
                free(assign_temp);
            }
            
            // Free materials
            while(topic_temp->materials) {
                Material *mat_temp = topic_temp->materials;
                topic_temp->materials = topic_temp->materials->next;
                free(mat_temp);
            }
            
            // Free announcements
            while(topic_temp->announcements) {
                Announcement *ann_temp = topic_temp->announcements;
                topic_temp->announcements = topic_temp->announcements->next;
                free(ann_temp);
            }
            
            free(topic_temp);
        }
        
        free(temp);
    }
}
