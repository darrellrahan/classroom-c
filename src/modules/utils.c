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

void get_current_time(Timestamp *ts) {
    time_t now = time(0);
    struct tm *local = localtime(&now);
    ts->day = local->tm_mday;
    ts->month = local->tm_mon + 1;
    ts->year = local->tm_year + 1900;
    ts->hour = local->tm_hour;
    ts->minute = local->tm_min;
}

void print_timestamp(Timestamp ts) {
    printf("%02d-%02d-%d %02d:%02d", ts.day, ts.month, ts.year, ts.hour, ts.minute);
}

bool is_deadline_passed(Timestamp deadline) {
    Timestamp now;
    get_current_time(&now);
    
    if(now.year > deadline.year) return true;
    if(now.year < deadline.year) return false;
    
    if(now.month > deadline.month) return true;
    if(now.month < deadline.month) return false;
    
    if(now.day > deadline.day) return true;
    if(now.day < deadline.day) return false;
    
    if(now.hour > deadline.hour) return true;
    if(now.hour < deadline.hour) return false;
    
    return now.minute > deadline.minute;
}

bool validate_url(char *url) {
    // Simple URL validation - check if it contains http:// or https://
    return (strstr(url, "http://") == url || strstr(url, "https://") == url);
}

bool is_student_enrolled(Course *course, int student_id) {
    Student *temp = course->enrolled_students;
    while(temp) {
        if(temp->student_id == student_id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool has_student_submitted(Assignment *assignment, int student_id) {
    // Check in both graded and not graded submissions
    Submission *temp = assignment->graded_submissions;
    while(temp) {
        if(temp->student_id == student_id) {
            return true;
        }
        temp = temp->next;
    }
    
    temp = assignment->not_graded_submissions;
    while(temp) {
        if(temp->student_id == student_id) {
            return true;
        }
        temp = temp->next;
    }
    
    return false;
}

bool is_unique_number_taken(char *unique_number) {
    // Check in students
    Student *student = students_head;
    while(student) {
        if(strcmp(student->student_unique_number, unique_number) == 0) {
            return true;
        }
        student = student->next;
    }
    
    // Check in teachers
    Teacher *teacher = teachers_head;
    while(teacher) {
        if(strcmp(teacher->teacher_unique_number, unique_number) == 0) {
            return true;
        }
        teacher = teacher->next;
    }
    
    return false;
}
