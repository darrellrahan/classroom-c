// ==================================================
// FILE: src/modules/student.c
// ==================================================

#include "../headers/student.h"
#include "../headers/dataio.h"
#include "../headers/utils.h"
#include "../headers/structs.h"

void student_topic_menu(Course *course) {
    int choice;
    do {
        clear_screen();
        printf("=== COURSE: %s ===\n", course->name);
        printf("Topics:\n");
        
        Topic *temp = course->topics;
        int count = 1;
        while(temp) {
            printf("%d. %s\n", count++, temp->title);
            temp = temp->next;
        }
        
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if(choice == 0) return;
        
        // Select topic
        temp = course->topics;
        int current_count = 1;
        while(temp) {
            if(current_count == choice) {
                student_topic_detail(course, temp);
                break;
            }
            current_count++;
            temp = temp->next;
        }
    } while(true);
}

void student_topic_detail(Course *course, Topic *topic) {
    int choice;
    do {
        clear_screen();
        printf("=== TOPIC: %s ===\n", topic->title);
        printf("1. See Assignments\n");
        printf("2. See Materials\n");
        printf("3. See Announcements\n");
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                student_view_assignments(course, topic);
                break;
            case 2:
                // View materials
                clear_screen();
                printf("=== MATERIALS: %s ===\n", topic->title);
                Material *mat = topic->materials;
                while(mat) {
                    printf("Title: %s\n", mat->title);
                    printf("Description: %s\n", mat->description);
                    printf("URL: %s\n", mat->url);
                    printf("Created at: ");
                    print_timestamp(mat->created_at);
                    printf("\n\n");
                    mat = mat->next;
                }
                pause_screen();
                break;
            case 3:
                // View announcements
                clear_screen();
                printf("=== ANNOUNCEMENTS: %s ===\n", topic->title);
                Announcement *ann = topic->announcements;
                while(ann) {
                    printf("Title: %s\n", ann->title);
                    printf("Description: %s\n", ann->description);
                    printf("Created at: ");
                    print_timestamp(ann->created_at);
                    printf("\n\n");
                    ann = ann->next;
                }
                pause_screen();
                break;
            case 0:
                return;
        }
    } while(choice != 0);
}

void student_view_assignments(Course *course, Topic *topic) {
    int choice;
    do {
        clear_screen();
        printf("=== ASSIGNMENTS: %s ===\n", topic->title);
        
        Assignment *temp = topic->assignments;
        int count = 1;
        while(temp) {
            printf("%d. %s", count++, temp->title);
            
            // Check status
            bool submitted = has_student_submitted(temp, current_student->student_id);
            bool overdue = is_deadline_passed(temp->deadline);
            
            if(submitted) {
                printf(" [SUBMITTED]");
            } else if(overdue) {
                printf(" [OVERDUE]");
            } else {
                printf(" [AVAILABLE]");
            }
            
            printf(" (Deadline: ");
            print_timestamp(temp->deadline);
            printf(")\n");
            temp = temp->next;
        }
        
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if(choice == 0) return;
        
        // Select assignment
        temp = topic->assignments;
        int current_count = 1;
        while(temp) {
            if(current_count == choice) {
                bool submitted = has_student_submitted(temp, current_student->student_id);
                bool overdue = is_deadline_passed(temp->deadline);
                
                if(submitted) {
                    printf("You have already submitted this assignment!\n");
                } else if(overdue) {
                    printf("This assignment is overdue and cannot be submitted!\n");
                } else {
                    student_submit_assignment(temp);
                }
                pause_screen();
                break;
            }
            current_count++;
            temp = temp->next;
        }
    } while(true);
}

void student_submit_assignment(Assignment *assignment) {
    clear_screen();
    printf("=== SUBMIT ASSIGNMENT: %s ===\n", assignment->title);
    
    Submission *new_submission = (Submission*)malloc(sizeof(Submission));
    if(!new_submission) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    new_submission->submission_id = next_submission_id++;
    new_submission->student_id = current_student->student_id;
    new_submission->assignment_id = assignment->assignment_id;
    new_submission->grade = 0;
    new_submission->is_graded = false;
    new_submission->is_submitted = true;
    new_submission->student = current_student;
    
    printf("Enter submission URL: ");
    scanf("%s", new_submission->url);
    
    if(!validate_url(new_submission->url)) {
        printf("Invalid URL format!\n");
        free(new_submission);
        return;
    }
    
    get_current_time(&new_submission->created_at);

    new_submission->next = NULL;
    
    // Add to not graded submissions queue
    enqueue_submission(&assignment->not_graded_submissions, new_submission);
    
    save_courses();
    printf("Assignment submitted successfully!\n");
}
