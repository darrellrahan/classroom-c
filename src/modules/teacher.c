// ==================================================
// FILE: src/modules/teacher.c
// ==================================================

#include "../headers/teacher.h"
#include "../headers/dataio.h"
#include "../headers/utils.h"
#include "../headers/structs.h"

void teacher_course_menu() {
    int choice;
    do {
        clear_screen();
        printf("=== COURSE MANAGEMENT ===\n");
        
        // Display courses
        Course *temp = courses_head;
        int count = 1;
        printf("Your Courses:\n");
        while(temp) {
            if(temp->teacher_id == current_teacher->teacher_id) {
                printf("%d. %s (Code: %s)\n", count++, temp->name, temp->code);
            }
            temp = temp->next;
        }
        
        printf("\n%d. Create New Course\n", count);
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if(choice == 0) return;
        if(choice == count) {
            // Create new course
            Course *new_course = (Course*)malloc(sizeof(Course));
            if(new_course) {
                new_course->course_id = next_course_id++;
                new_course->teacher_id = current_teacher->teacher_id;
                
                printf("Enter course name: ");
                getchar();
                fgets(new_course->name, MAX_STRING, stdin);
                new_course->name[strcspn(new_course->name, "\n")] = 0;
                
                printf("Enter course code: ");
                scanf("%s", new_course->code);
                
                printf("Enter description: ");
                getchar();
                fgets(new_course->description, MAX_STRING, stdin);
                new_course->description[strcspn(new_course->description, "\n")] = 0;
                
                new_course->enrolled_students = NULL;
                new_course->waitlist_students = NULL;
                new_course->topics = NULL;
                new_course->next = courses_head;
                courses_head = new_course;
                
                printf("Course created successfully!\n");
                pause_screen();
            }
        } else {
            // Select existing course
            temp = courses_head;
            int current_count = 1;
            while(temp) {
                if(temp->teacher_id == current_teacher->teacher_id) {
                    if(current_count == choice) {
                        // Course selected
                        int sub_choice;
                        do {
                            clear_screen();
                            printf("=== COURSE: %s ===\n", temp->name);
                            printf("1. See and Manage Topics\n");
                            printf("2. Review Requests\n");
                            printf("0. Back\n");
                            printf("Choice: ");
                            scanf("%d", &sub_choice);
                            
                            switch(sub_choice) {
                                case 1:
                                    teacher_manage_topics(temp);
                                    break;
                                case 2:
                                    teacher_review_requests(temp);
                                    break;
                            }
                        } while(sub_choice != 0);
                        break;
                    }
                    current_count++;
                }
                temp = temp->next;
            }
        }
    } while(true);
}

void teacher_manage_topics(Course *course) {
    int choice;
    do {
        clear_screen();
        printf("=== TOPICS: %s ===\n", course->name);
        
        Topic *temp = course->topics;
        int count = 1;
        while(temp) {
            printf("%d. %s\n", count++, temp->title);
            temp = temp->next;
        }
        
        printf("%d. Create New Topic\n", count);
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if(choice == 0) return;
        if(choice == count) {
            // Create new topic
            Topic *new_topic = (Topic*)malloc(sizeof(Topic));
            if(new_topic) {
                new_topic->topic_id = next_topic_id++;
                new_topic->course_id = course->course_id;
                
                printf("Enter topic title: ");
                getchar();
                fgets(new_topic->title, MAX_STRING, stdin);
                new_topic->title[strcspn(new_topic->title, "\n")] = 0;
                
                printf("Enter description: ");
                fgets(new_topic->description, MAX_STRING, stdin);
                new_topic->description[strcspn(new_topic->description, "\n")] = 0;
                
                get_current_time(&new_topic->created_at);
                new_topic->assignments = NULL;
                new_topic->materials = NULL;
                new_topic->announcements = NULL;
                new_topic->next = course->topics;
                course->topics = new_topic;
                
                printf("Topic created successfully!\n");
                pause_screen();
            }
        } else {
            // Select existing topic
            temp = course->topics;
            int current_count = 1;
            while(temp) {
                if(current_count == choice) {
                    teacher_topic_detail(course, temp);
                    break;
                }
                current_count++;
                temp = temp->next;
            }
        }
    } while(true);
}

void teacher_topic_detail(Course *course, Topic *topic) {
    int choice;
    do {
        clear_screen();
        printf("=== TOPIC: %s ===\n", topic->title);
        printf("1. Manage Materials\n");
        printf("2. Manage Announcements\n");
        printf("3. Manage Assignments\n");
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                teacher_manage_materials(course, topic);
                break;
            case 2:
                teacher_manage_announcements(course, topic);
                break;
            case 3:
                teacher_manage_assignments(course, topic);
                break;
            case 0:
                return;
        }
    } while(choice != 0);
}

void teacher_manage_assignments(Course *course, Topic *topic) {
    int choice;
    do {
        clear_screen();
        printf("=== ASSIGNMENTS: %s ===\n", topic->title);
        
        Assignment *temp = topic->assignments;
        int count = 1;
        while(temp) {
            printf("%d. %s (Deadline: ", count++, temp->title);
            print_timestamp(temp->deadline);
            printf(")\n");
            temp = temp->next;
        }
        
        printf("%d. Create New Assignment\n", count);
        printf("0. Back\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if(choice == 0) return;
        if(choice == count) {
            // Create new assignment
            Assignment *new_assignment = (Assignment*)malloc(sizeof(Assignment));
            if(new_assignment) {
                new_assignment->assignment_id = next_assignment_id++;
                new_assignment->course_id = course->course_id;
                new_assignment->topic_id = topic->topic_id;
                
                printf("Enter assignment title: ");
                getchar();
                fgets(new_assignment->title, MAX_STRING, stdin);
                new_assignment->title[strcspn(new_assignment->title, "\n")] = 0;
                
                printf("Enter deadline (DD MM YYYY HH MM): ");
                scanf("%d %d %d %d %d", &new_assignment->deadline.day,
                      &new_assignment->deadline.month, &new_assignment->deadline.year,
                      &new_assignment->deadline.hour, &new_assignment->deadline.minute);
                
                get_current_time(&new_assignment->created_at);
                new_assignment->graded_submissions = NULL;
                new_assignment->not_graded_submissions = NULL;
                new_assignment->next = topic->assignments;
                topic->assignments = new_assignment;
                
                printf("Assignment created successfully!\n");
                pause_screen();
            }
        } else {
            // Select existing assignment
            temp = topic->assignments;
            int current_count = 1;
            while(temp) {
                if(current_count == choice) {
                    int sub_choice;
                    do {
                        clear_screen();
                        printf("=== ASSIGNMENT: %s ===\n", temp->title);
                        printf("1. View Not Graded Submissions\n");
                        printf("2. View Graded Submissions\n");
                        printf("3. Start Grading\n");
                        printf("0. Back\n");
                        printf("Choice: ");
                        scanf("%d", &sub_choice);
                        
                        switch(sub_choice) {
                            case 1:
                                // Show not graded submissions
                                clear_screen();
                                printf("=== NOT GRADED SUBMISSIONS ===\n");
                                Submission *sub = temp->not_graded_submissions;
                                while(sub) {
                                    Student *student = find_student_by_id(sub->student_id);
                                    printf("Student: %s, URL: %s\n", 
                                           student ? student->name : "Unknown", sub->url);
                                    sub = sub->next;
                                }
                                pause_screen();
                                break;
                            case 2:
                                // Show graded submissions
                                clear_screen();
                                printf("=== GRADED SUBMISSIONS ===\n");
                                sub = temp->graded_submissions;
                                while(sub) {
                                    Student *student = find_student_by_id(sub->student_id);
                                    printf("Student: %s, Grade: %d, URL: %s\n", 
                                           student ? student->name : "Unknown", sub->grade, sub->url);
                                    sub = sub->next;
                                }
                                pause_screen();
                                break;
                            case 3:
                                teacher_grade_submissions(temp);
                                break;
                        }
                    } while(sub_choice != 0);
                    break;
                }
                current_count++;
                temp = temp->next;
            }
        }
    } while(true);
}

void teacher_grade_submissions(Assignment *assignment) {
    if (assignment == NULL) return;

    clear_screen();
    printf("=== GRADING SUBMISSIONS ===\n");
    
    Submission *current_sub;
    while((current_sub = dequeue_submission(&assignment->not_graded_submissions)) != NULL) {
        Student *student = find_student_by_id(current_sub->student_id);
        
        printf("Student: %s\n", student ? student->name : "Unknown");
        printf("Submission URL: %s\n", current_sub->url);
        printf("Submitted at: ");
        print_timestamp(current_sub->created_at);
        printf("\n");
        
        int grade;
        printf("Enter grade (0-100): ");
        scanf("%d", &grade);
        
        if(grade >= 0 && grade <= 100) {
            current_sub->grade = grade;
            current_sub->is_graded = true;
            
            // Move to graded queue
            enqueue_submission(&assignment->graded_submissions, current_sub);
            
            printf("Grade submitted successfully!\n");
        } else {
            printf("Invalid grade! Please enter a value between 0-100.\n");
            // Put back to queue if invalid grade
            enqueue_submission(&assignment->not_graded_submissions, current_sub);
        }
        
        // Check if there are more submissions and if user wants to continue
        if(assignment->not_graded_submissions) {
            printf("Continue grading? (1-Yes, 0-No): ");
            int continue_grading;
            scanf("%d", &continue_grading);
            if(!continue_grading) {
                break;
            }
        }
    }
    
    printf("Grading session completed!\n");
    pause_screen();
}

void teacher_review_requests(Course *course) {
    clear_screen();
    printf("=== REVIEW REQUESTS: %s ===\n", course->name);
    
    while(course->waitlist_students) {
        Student *student = course->waitlist_students;
        printf("Student Information:\n");
        printf("Name: %s\n", student->name);
        printf("Unique Number: %s\n", student->student_unique_number);
        printf("Email: %s\n", student->email);
        printf("Phone: %s\n", student->phone_number);
        
        int choice;
        printf("\n1. Accept\n2. Decline\n0. Back\nChoice: ");
        scanf("%d", &choice);
        
        if(choice == 1) {
            // Accept student
            course->waitlist_students = student->next;
            student->next = course->enrolled_students;
            course->enrolled_students = student;
            printf("Student accepted!\n");
        } else if(choice == 2) {
            // Decline student
            course->waitlist_students = student->next;
            printf("Student declined!\n");
        } else {
            return;
        }
        
        if(course->waitlist_students) {
            pause_screen();
        }
    }
    
    printf("No more requests to review.\n");
    pause_screen();
}
