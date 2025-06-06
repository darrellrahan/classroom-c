// ==================================================
// FILE: src/modules/utils.c
// ==================================================

#include "../headers/utils.h"
#include "../headers/dataio.h"
#include "../headers/structs.h"

void clear_screen() {
    system("cls");
}

void pause_screen() {
    printf("Press any key to continue...\n");
    getch();
}

Course* find_course_by_code(char *code) {
    Course *temp = courses_head;
    while(temp) {
        if(strcmp(temp->code, code) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Course* find_course_by_id(int id) {
    Course *temp = courses_head;
    while(temp) {
        if(temp->course_id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Student* find_student_by_id(int id) {
    Student *temp = students_head;
    while(temp) {
        if(temp->student_id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Student* find_student_by_unique_number(char *unique_number) {
    Student *temp = students_head;
    while(temp) {
        if(strcmp(temp->student_unique_number, unique_number) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Assignment* find_assignment_by_id(int assignment_id) {
    Course *course = courses_head;
    while(course) {
        Topic *topic = course->topics;
        while(topic) {
            Assignment *assignment = topic->assignments;
            while(assignment) {
                if(assignment->assignment_id == assignment_id) {
                    return assignment;
                }
                assignment = assignment->next;
            }
            topic = topic->next;
        }
        course = course->next;
    }
    return NULL;
}

