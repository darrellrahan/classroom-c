#include "headers/structs.h"
#include "headers/utils.h"
#include "headers/auth.h"
#include "headers/menu.h"
#include "headers/dataio.h"
#include "headers/queue.h"
#include "headers/stack.h"
#include "headers/student.h"
#include "headers/teacher.h"

// Global variables
Student *students_head = NULL;
Teacher *teachers_head = NULL;
Course *courses_head = NULL;
MenuStack *menu_stack = NULL;
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
