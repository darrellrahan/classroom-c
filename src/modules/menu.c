// ==================================================
// FILE: src/modules/menu.c
// ==================================================


#include "../headers/menu.h"
#include "../headers/dataio.h"
#include "../headers/utils.h"
#include "../headers/auth.h"
#include "../headers/stack.h"

void execute_menu(const char* menu_name, void* data) {
    if (strcmp(menu_name, MAIN_MENU) == 0) {
        main_menu();
    }
    else if (strcmp(menu_name, REGISTER_MENU) == 0) {
        register_menu();
    }
    else if (strcmp(menu_name, LOGIN_MENU) == 0) {
        login_menu();
    }
    else if (strcmp(menu_name, STUDENT_DASHBOARD) == 0) {
        student_dashboard();
    }
    else if (strcmp(menu_name, STUDENT_SEE_ACCOUNT) == 0) {
        student_see_account();
    }
    else if (strcmp(menu_name, STUDENT_SEE_OTHER_STUDENTS) == 0) {
        student_see_other_students((Course*)data);
    }
    else if (strcmp(menu_name, STUDENT_TOPIC_MENU) == 0) {
        student_topic_menu((Course*)data);
    }
    else if (strcmp(menu_name, STUDENT_TOPIC_DETAIL) == 0) {
        student_topic_detail((Topic*)data);
    }
    else if (strcmp(menu_name, STUDENT_VIEW_MATERIALS) == 0) {
        student_view_materials((Topic*)data);
    }
    else if (strcmp(menu_name, STUDENT_VIEW_ANNOUNCEMENTS) == 0) {
        student_view_announcements((Topic*)data);
    }
    else if (strcmp(menu_name, STUDENT_VIEW_ASSIGNMENTS) == 0) {
        student_view_assignments((Topic*)data);
    }
    else if (strcmp(menu_name, STUDENT_SUBMIT_ASSIGNMENT) == 0) {
        student_submit_assignment((Assignment*)data);
    }
    else if (strcmp(menu_name, TEACHER_DASHBOARD) == 0) {
        teacher_dashboard();
    }
    else if (strcmp(menu_name, TEACHER_SEE_ACCOUNT) == 0) {
        teacher_see_account();
    }
    else if (strcmp(menu_name, TEACHER_COURSE_MENU) == 0) {
        teacher_course_menu();
    }
    else if (strcmp(menu_name, TEACHER_SEE_STUDENTS) == 0) {
        teacher_see_students((Course*)data);
    }
    else if (strcmp(menu_name, TEACHER_MANAGE_TOPICS) == 0) {
        teacher_manage_topics((Course*)data);
    }
    else if (strcmp(menu_name, TEACHER_TOPIC_DETAIL) == 0) {
        teacher_topic_detail((Topic*)data);
    }
    else if (strcmp(menu_name, TEACHER_MANAGE_ASSIGNMENTS) == 0) {
        teacher_manage_assignments((Topic*)data);
    }
    else if (strcmp(menu_name, TEACHER_SHOW_NOTGRADED_SUBMISSIONS) == 0) {
        teacher_show_notgraded_submissions((Assignment*)data);
    }
    else if (strcmp(menu_name, TEACHER_SHOW_GRADED_SUBMISSIONS) == 0) {
        teacher_show_graded_submissions((Assignment*)data);
    }
    else if (strcmp(menu_name, TEACHER_GRADE_SUBMISSIONS) == 0) {
        teacher_grade_submissions((Assignment*)data);
    }
    else if (strcmp(menu_name, TEACHER_MANAGE_MATERIALS) == 0) {
        teacher_manage_materials((Topic*)data);
    }
    else if (strcmp(menu_name, TEACHER_MANAGE_ANNOUNCEMENTS) == 0) {
        teacher_manage_announcements((Topic*)data);
    }
    else if (strcmp(menu_name, TEACHER_REVIEW_REQUESTS) == 0) {
        teacher_review_requests((Course*)data);
    }
    else {
        printf("Menu tidak ditemukan: %s\n", menu_name);
    }
}

void register_menu() {
    do {
        int choice = 0;
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
    } while(true);
}

void login_menu() {
    do {
        char choice_str[32] = {0};
        clear_screen();
        printf("=== LOGIN MENU ===\n");
        printf("1. Login as Teacher\n");
        printf("2. Login as Student\n");
        printf("\n");
        printf("commands: back, redo\n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        
        if (strcmp(choice_str, "1") == 0) {
            initialize_current_menu(LOGIN_MENU, NULL);
            if (login_teacher()) {
                execute_menu(TEACHER_DASHBOARD, NULL);
                return;
                // current_teacher = NULL; // Clear current teacher after logout
            }
            execute_menu(MAIN_MENU, NULL);
            return;
        }
        else if (strcmp(choice_str, "2") == 0) {
            initialize_current_menu(LOGIN_MENU, NULL);
            if (login_student()) {
                execute_menu(STUDENT_DASHBOARD, NULL);
                return;
                // current_student = NULL; // clear current student after logout
            }
            execute_menu(MAIN_MENU, NULL);
            return;
        }
        else if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        }
        else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        }
        else {
            printf("Invalid choice!\n");
            pause_screen();
        }
    } while(true);
}

void teacher_dashboard() {
    do {
        char choice_str[32] = {0};
        clear_screen();
        printf("=== TEACHER DASHBOARD ===\n");
        printf("Welcome, %s!\n\n", current_teacher->name);
        printf("1. Manage Courses\n");
        printf("2. See Account\n");
        printf("\n");
        printf("commands: back, redo \n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);

        if (strcmp(choice_str, "1") == 0) {
            initialize_current_menu(TEACHER_DASHBOARD, NULL);
            execute_menu(TEACHER_COURSE_MENU, NULL);
            return;
        } else if (strcmp(choice_str, "2") == 0) {
            initialize_current_menu(TEACHER_DASHBOARD, NULL);
            execute_menu(TEACHER_SEE_ACCOUNT, NULL);
            return;
        } else if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        } else {
            printf("Invalid choice!\n");
            pause_screen();
        }
    } while(true);
}

void student_dashboard() {
    do {
        int choice_int = 0;
        char choice_str[32] = {0};
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
        
        printf("\n");
        printf("commands: back, redo, join, account\n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        if (is_number(choice_str)) {
            choice_int = atoi(choice_str);
        }
        
        if(strcmp(choice_str, "join") == 0) {
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
                    save_courses();
                    printf("Join request sent! Waiting for teacher approval.\n");
                } else {
                    printf("You are already enrolled in this course!\n");
                }
            } else {
                printf("Course not found!\n");
            }
            pause_screen();
        } else if(strcmp(choice_str, "account") == 0) {
            initialize_current_menu(STUDENT_DASHBOARD, NULL);
            execute_menu(STUDENT_SEE_ACCOUNT, NULL);
            return;
        } else if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        } else if (choice_int > 0 && choice_int < count) {
            // Select course
            temp = courses_head;
            int current_count = 1;
            while(temp) {
                if(is_student_enrolled(temp, current_student->student_id)) {
                    if(current_count == choice_int) {
                        initialize_current_menu(STUDENT_DASHBOARD, NULL);
                        execute_menu(STUDENT_TOPIC_MENU, temp);
                        return;
                    }
                    current_count++;
                }
                temp = temp->next;
            }
        } else {
            printf("Invalid choice!\n");
            pause_screen();
        }
    } while(true);
}

/**************************************************

                    STUDENT MENUS

**************************************************/

void student_see_account() {
    clear_screen();
    printf("=== ACCOUNT ===\n");
    printf("Name: %s\n", current_student->name);
    printf("Unique Number (NISN/NIM): %s\n", current_student->student_unique_number);
    printf("Email: %s\n", current_student->email);
    printf("Phone: %s\n", current_student->phone_number);
    printf("\n Back (auto undo) \n");
    pause_screen();

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
}

void student_topic_menu(Course *course) {
    if (!course) {
        printf("No course data available.\n");
        pause_screen();
        return;
    }

    do {
        int choice_int = 0;
        char choice_str[32] = {0};

        clear_screen();
        printf("=== COURSE: %s ===\n", course->name);

        printf("Topics:\n");
        Topic *temp = course->topics;
        int count = 1;
        while(temp) {
            printf("%d. %s\n", count++, temp->title);
            temp = temp->next;
        }
        
        printf("\n");
        printf("commands: back, redo, see OR students OR student \n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        if (is_number(choice_str)) {
            choice_int = atoi(choice_str);
        }

        if (strcmp(choice_str, "see") == 0 || strcmp(choice_str, "students") == 0 || strcmp(choice_str, "student") == 0) {
            initialize_current_menu(STUDENT_TOPIC_MENU, course);
            execute_menu(STUDENT_SEE_OTHER_STUDENTS, course);
            return;
        } else if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        } else if (choice_int > 0 && choice_int < count) {
            // Select topic
            temp = course->topics;
            int current_count = 1;
            while(temp) {
                if(current_count == choice_int) {
                    initialize_current_menu(STUDENT_TOPIC_MENU, course);
                    execute_menu(STUDENT_TOPIC_DETAIL, temp);
                    return;
                }
                current_count++;
                temp = temp->next;
            }
        } else {
            printf("Invalid choice!\n");
            pause_screen();
        }
    } while(true);
}

void student_see_other_students(Course *course) {
    if (!course) {
        printf("No course data available.\n");
        pause_screen();
        return;
    }

    clear_screen();
    printf("=== ENROLLED STUDENTS (%d) ===\n", count_enrolled_student(course));
    
    Student *temp = course->enrolled_students;
    if(!temp) {
        printf("No students enrolled in this course.\n");
    } else {
        while(temp) {
            printf("ID: %d, Name: %s, Unique Number: %s\n", 
                   temp->student_id, temp->name, temp->student_unique_number);
            temp = temp->next;
        }
    }
    
    pause_screen();

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
}

void student_topic_detail(Topic *topic) {
    if (!topic) {
        printf("No topic data available.\n");
        pause_screen();
        return;
    }

    do {
        int choice_int = 0;
        char choice_str[32] = {0};

        clear_screen();
        printf("=== TOPIC: %s ===\n", topic->title);
        printf("1. See Assignments\n");
        printf("2. See Materials\n");
        printf("3. See Announcements\n");
        printf("\n");
        printf("commands: back, redo\n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        if (is_number(choice_str)) {
            choice_int = atoi(choice_str);
        }
        
        if (choice_int == 1) {
            initialize_current_menu(STUDENT_TOPIC_DETAIL, topic);
            execute_menu(STUDENT_VIEW_ASSIGNMENTS, topic);
            return;
        } else if (choice_int == 2) {
            initialize_current_menu(STUDENT_TOPIC_DETAIL, topic);
            execute_menu(STUDENT_VIEW_MATERIALS, topic);
            return;
        } else if (choice_int == 3) {
            initialize_current_menu(STUDENT_TOPIC_DETAIL, topic);
            execute_menu(STUDENT_VIEW_ANNOUNCEMENTS, topic);
            return;
        } else if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        }
    } while(true);
}

void student_view_materials(Topic *topic) {
    if (!topic) {
        printf("No topic data available.\n");
        pause_screen();
        return;
    }

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

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
}

void student_view_announcements(Topic *topic) {
    if (!topic) {
        printf("No topic data available.\n");
        pause_screen();
        return;
    }

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

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
}

void student_view_assignments(Topic *topic) {
    if (!topic) {
        printf("No topic data available.\n");
        pause_screen();
        return;
    }

    do {
        int choice_int = 0;
        char choice_str[32] = {0};

        clear_screen();
        printf("=== ASSIGNMENTS: %s ===\n", topic->title);
        
        Assignment *temp = topic->assignments;
        int count = 1;
        while(temp) {
            printf("%d. %s", count++, temp->title);
            
            // Check status
            bool submitted = has_student_submitted(temp, current_student->student_id);
            bool overdue = is_deadline_passed(temp->deadline);
            bool graded = has_student_graded(temp, current_student->student_id);
            
            if(submitted) {
                if (graded) {
                    printf(" [GRADED: %d]", get_student_grade(temp, current_student->student_id));
                } else {
                    printf(" [SUBMITTED]");
                }
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

        printf("\n");
        printf("commands: back, redo\n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        if (is_number(choice_str)) {
            choice_int = atoi(choice_str);
        }

        if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        } else if (choice_int > 0 && choice_int < count) {
            // Select assignment
            temp = topic->assignments;
            int current_count = 1;
            while(temp) {
                if(current_count == choice_int) {
                    bool submitted = has_student_submitted(temp, current_student->student_id);
                    bool overdue = is_deadline_passed(temp->deadline);
                    
                    if(submitted) {
                        printf("You have already submitted this assignment!\n");
                        pause_screen();
                        break;
                    } else if(overdue) {
                        printf("This assignment is overdue and cannot be submitted!\n");
                        pause_screen();
                        break;
                    } else {
                        // Proceed to submit assignment
                        initialize_current_menu(STUDENT_VIEW_ASSIGNMENTS, topic);
                        execute_menu(STUDENT_SUBMIT_ASSIGNMENT, temp);
                        return;
                    }
                }
                current_count++;
                temp = temp->next;
            }
        } else {
            printf("Invalid choice!\n");
            pause_screen();
        }
    } while(true);
}

void student_submit_assignment(Assignment *assignment) {
    if (!assignment) {
        printf("Invalid assignment data.\n");
        pause_screen();
        return;
    }

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
    
    while (true) {
        if (validate_url(new_submission->url)) {
            break;
        } else {
            printf("Invalid URL format! Please enter a valid URL: ");
            scanf("%s", new_submission->url);
        }
    }
    
    get_current_time(&new_submission->created_at);

    new_submission->next = NULL;
    
    // Add to not graded submissions queue
    enqueue_submission(&assignment->not_graded_submissions, new_submission);
    
    save_courses();
    printf("Assignment submitted successfully!\n");
    pause_screen();

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
}

/*************************************************

                    TEACHER MENUS

*************************************************/

void teacher_see_account() {
    clear_screen();
    printf("=== ACCOUNT ===\n");
    printf("Name: %s\n", current_teacher->name);
    printf("Unique Number (NUPTK/NIDN): %s\n", current_teacher->teacher_unique_number);
    printf("Email: %s\n", current_teacher->email);
    printf("Phone: %s\n", current_teacher->phone_number);
    printf("\n1. Back to Dashboard\n");
    pause_screen();

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
}

void teacher_course_menu() {
    do {
        int choice_int = 0;
        char choice_str[32] = {0};
        
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
        
        printf("\n");
        printf("commands: back, redo, create\n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        if (is_number(choice_str)) {
            choice_int = atoi(choice_str);
        }

        if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        } else if(strcmp(choice_str, "create") == 0) {
            // Create new course
            Course *new_course = (Course*)malloc(sizeof(Course));
            if(new_course) {
                new_course->course_id = next_course_id++;
                new_course->teacher_id = current_teacher->teacher_id;
                
                printf("Enter course name: ");
                getchar();
                fgets(new_course->name, MAX_STRING, stdin);
                new_course->name[strcspn(new_course->name, "\n")] = 0;
                
                do {
                    printf("Enter course code: ");
                    scanf("%s", new_course->code);
                    
                    if(find_course_by_code(new_course->code)) {
                        printf("This course code is already taken. Please try another one.\n");
                        pause_screen();
                        continue;
                    } else {
                        break;
                    }
                } while(true);
                
                printf("Enter description: ");
                getchar();
                fgets(new_course->description, MAX_STRING, stdin);
                new_course->description[strcspn(new_course->description, "\n")] = 0;
                
                new_course->enrolled_students = NULL;
                new_course->waitlist_students = NULL;
                new_course->topics = NULL;
                new_course->next = courses_head;
                courses_head = new_course;
                
                save_courses();
                printf("Course created successfully!\n");
                pause_screen();
            }
        } else if (choice_int > 0 && choice_int < count) {
            // Select existing course
            temp = courses_head;
            int current_count = 1;
            while(temp) {
                if(temp->teacher_id == current_teacher->teacher_id) {
                    if(current_count == choice_int) {
                        // Course selected
                        int choice_int2 = 0;
                        char choice_str2[10] = {0};
                        do {
                            clear_screen();
                            printf("=== COURSE: %s ===\n", temp->name);
                            printf("1. See Students\n");
                            printf("2. See and Manage Topics\n");
                            printf("3. Review Requests (%d)\n", count_waitinglist_student(temp));
                            printf("\n");
                            printf("commands: back, redo\n");
                            printf("\n");
                            printf("Choice: ");
                            scanf("%32s", choice_str2);
                            if (is_number(choice_str2)) {
                                choice_int2 = atoi(choice_str2);
                            }

                            if (strcmp(choice_str2, "back") == 0) {
                                if (undo_navigation(next_menu, &next_data)) {
                                    execute_menu(next_menu, next_data);
                                    return;
                                } else {
                                    printf("No previous menu to undo!\n");
                                    pause_screen();
                                }
                            } else if (strcmp(choice_str2, "redo") == 0) {
                                if (redo_navigation(next_menu, &next_data)) {
                                    execute_menu(next_menu, next_data);
                                    return;
                                } else {
                                    printf("No menu to redo!\n");
                                    pause_screen();
                                }
                            } else {
                                if (choice_int2 == 1) {
                                    // See students
                                    initialize_current_menu(TEACHER_COURSE_MENU, NULL);
                                    execute_menu(TEACHER_SEE_STUDENTS, temp);
                                    return;
                                } else if (choice_int2 == 2) {
                                    // Manage topics
                                    initialize_current_menu(TEACHER_COURSE_MENU, NULL);
                                    execute_menu(TEACHER_MANAGE_TOPICS, temp);
                                    return;
                                } else if (choice_int2 == 3) {
                                    // Review requests
                                    initialize_current_menu(TEACHER_COURSE_MENU, NULL);
                                    execute_menu(TEACHER_REVIEW_REQUESTS, temp);
                                    return;
                                } else {
                                    printf("Invalid choice!\n");
                                    pause_screen();
                                }
                            }
                        } while(true);
                        break;
                    }
                    current_count++;
                }
                temp = temp->next;
            }
        } else {
            printf("Invalid choice!\n");
            pause_screen();
        }
    } while(true);
}

void teacher_see_students(Course *course) {
    if (!course) {
        printf("No course data available.\n");
        pause_screen();
        return;
    }

    clear_screen();
    printf("=== STUDENTS ENROLLED IN: %s (%d) ===\n", course->name, count_enrolled_student(course));
    
    Student *temp = course->enrolled_students;
    if(!temp) {
        printf("No students enrolled in this course.\n");
    } else {
        while(temp) {
            printf("Name: %s, Unique Number (NIS(N)/NIM): %s, Email: %s, Phone: %s\n",
                   temp->name, temp->student_unique_number, temp->email, temp->phone_number);
            temp = temp->next;
        }
    }
    
    pause_screen();

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
}

void teacher_manage_topics(Course *course) {
    if (!course) {
        printf("No course data available.\n");
        pause_screen();
        return;
    }

    do {
        int choice_int = 0;
        char choice_str[32] = {0};

        clear_screen();
        printf("=== TOPICS: %s ===\n", course->name);
        
        Topic *temp = course->topics;
        int count = 1;
        while(temp) {
            printf("%d. %s\n", count++, temp->title);
            temp = temp->next;
        }
        
        printf("\n");
        printf("commands: back, redo, create\n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        if (is_number(choice_str)) {
            choice_int = atoi(choice_str);
        }
        
        if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        }
        else if(strcmp(choice_str, "create") == 0) {
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
                
                save_courses();
                printf("Topic created successfully!\n");
                pause_screen();
            }
        } else if (choice_int > 0 && choice_int < count) {
            // Select existing topic
            temp = course->topics;
            int current_count = 1;
            while(temp) {
                if(current_count == choice_int) {
                    initialize_current_menu(TEACHER_MANAGE_TOPICS, course);
                    execute_menu(TEACHER_TOPIC_DETAIL, temp);
                    return;
                }
                current_count++;
                temp = temp->next;
            }
        } else {
            printf("Invalid choice!\n");
            pause_screen();
        }
    } while(true);
}

void teacher_topic_detail(Topic *topic) {
    if (!topic) {
        printf("No topic data available.\n");
        pause_screen();
        return;
    }

    do {
        int choice_int = 0;
        char choice_str[32] = {0};

        clear_screen();
        printf("=== TOPIC: %s ===\n", topic->title);
        printf("1. Manage Assignments\n");
        printf("2. Manage Materials\n");
        printf("3. Manage Announcements\n");
        printf("\n");
        printf("commands: back, redo\n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        if (is_number(choice_str)) {
            choice_int = atoi(choice_str);
        }

        if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        } else {
            if (choice_int == 1) {
                initialize_current_menu(TEACHER_TOPIC_DETAIL, topic);
                execute_menu(TEACHER_MANAGE_ASSIGNMENTS, topic);
                return;
            } else if (choice_int == 2) {
                initialize_current_menu(TEACHER_TOPIC_DETAIL, topic);
                execute_menu(TEACHER_MANAGE_MATERIALS, topic);
                return;
            } else if (choice_int == 3) {
                initialize_current_menu(TEACHER_TOPIC_DETAIL, topic);
                execute_menu(TEACHER_MANAGE_ANNOUNCEMENTS, topic);
                return;
            } else {
                printf("Invalid choice!\n");
                pause_screen();
            }
        }
    } while(true);
}

void teacher_manage_assignments(Topic *topic) {
    if (!topic) {
        printf("No topic data available.\n");
        pause_screen();
        return;
    }

    do {
        int choice_int = 0;
        char choice_str[32] = {0};

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
        
        
        printf("\n");
        printf("commands: back, redo, create\n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        if (is_number(choice_str)) {
            choice_int = atoi(choice_str);
        }

        if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        } else if(strcmp(choice_str, "create") == 0) {
            // Create new assignment
            Assignment *new_assignment = (Assignment*)malloc(sizeof(Assignment));
            if(new_assignment) {
                new_assignment->assignment_id = next_assignment_id++;
                new_assignment->course_id = topic->course_id;
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
                
                save_courses();
                printf("Assignment created successfully!\n");
                pause_screen();
            }
        } else if (choice_int > 0 && choice_int < count) {
            // Select existing assignment
            temp = topic->assignments;
            int current_count = 1;
            while(temp) {
                if(current_count == choice_int) {
                    int choice_int2 = 0;
                    char choice_str2[10] = {0};
                    do {
                        clear_screen();
                        printf("=== ASSIGNMENT: %s ===\n", temp->title);
                        printf("1. View Not Graded Submissions (%d)\n", count_notgraded_submissions(temp));
                        printf("2. View Graded Submissions (%d)\n", count_graded_submissions(temp));
                        printf("3. Start Grading\n");
                        printf("\n");
                        printf("commands: back, redo\n");
                        printf("\n");
                        printf("Choice: ");
                        scanf("%32s", choice_str2);
                        if (is_number(choice_str2)) {
                            choice_int2 = atoi(choice_str2);
                        }

                        if (strcmp(choice_str2, "back") == 0) {
                            if (undo_navigation(next_menu, &next_data)) {
                                execute_menu(next_menu, next_data);
                                return;
                            } else {
                                printf("No previous menu to undo!\n");
                                pause_screen();
                            }
                        } else if (strcmp(choice_str2, "redo") == 0) {
                            if (redo_navigation(next_menu, &next_data)) {
                                execute_menu(next_menu, next_data);
                                return;
                            } else {
                                printf("No menu to redo!\n");
                                pause_screen();
                            }
                        } else {
                            if (choice_int2 == 1) {
                                initialize_current_menu(TEACHER_MANAGE_ASSIGNMENTS, topic);
                                execute_menu(TEACHER_SHOW_NOTGRADED_SUBMISSIONS, temp);
                                return;
                            } else if (choice_int2 == 2) {
                                initialize_current_menu(TEACHER_MANAGE_ASSIGNMENTS, topic);
                                execute_menu(TEACHER_SHOW_GRADED_SUBMISSIONS, temp);
                                return;
                            } else if (choice_int2 == 3) {
                                initialize_current_menu(TEACHER_MANAGE_ASSIGNMENTS, topic);
                                execute_menu(TEACHER_GRADE_SUBMISSIONS, temp);
                                return;
                            } else {
                                printf("Invalid choice!\n");
                                pause_screen();
                            }
                        }
                    } while(true);
                    break;
                }
                current_count++;
                temp = temp->next;
            }
        } else {
            printf("Invalid choice!\n");
            pause_screen();
        }
    } while(true);
}

void teacher_show_notgraded_submissions(Assignment *assignment) {
    clear_screen();
    printf("=== NOT GRADED SUBMISSIONS ===\n");
    Submission *sub = assignment->not_graded_submissions;
    while(sub) {
        Student *student = find_student_by_id(sub->student_id);
        printf("Student: %s, URL: %s\n", 
                student ? student->name : "Unknown", sub->url);
        sub = sub->next;
    }
    pause_screen();

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
}

void teacher_show_graded_submissions(Assignment *assignment) {
    clear_screen();
    printf("=== GRADED SUBMISSIONS ===\n");
    Submission *sub = assignment->graded_submissions;
    while(sub) {
        Student *student = find_student_by_id(sub->student_id);
        printf("Student: %s, Grade: %d, URL: %s\n", 
                student ? student->name : "Unknown", sub->grade, sub->url);
        sub = sub->next;
    }
    pause_screen();

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
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
            
            save_courses();
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

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
}

void teacher_review_requests(Course *course) {
    clear_screen();
    printf("=== REVIEW REQUESTS: %s ===\n", course->name);
    
    while(course->waitlist_students) {
        Student *student = course->waitlist_students;
        printf("Student Information:\n");
        printf("Name: %s\n", student->name);
        printf("Unique Number (NISN/NIM): %s\n", student->student_unique_number);
        printf("Email: %s\n", student->email);
        printf("Phone: %s\n", student->phone_number);
        
        int choice = 0;
        printf("\n1. Accept\n2. Decline\n0. Back\nChoice: ");
        scanf("%d", &choice);
        
        if(choice == 1) {
            // Accept student
            course->waitlist_students = student->next;
            student->next = course->enrolled_students;
            course->enrolled_students = student;
            save_courses();
            printf("Student accepted!\n");
        } else if(choice == 2) {
            // Decline student
            course->waitlist_students = student->next;
            save_courses();
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

    if (undo_navigation(next_menu, &next_data)) {
        execute_menu(next_menu, next_data);
        return;
    } else {
        printf("No previous menu to undo!\n");
        pause_screen();
    }
}

void teacher_manage_materials(Topic *topic) {
    if (!topic) {
        printf("No topic data available.\n");
        pause_screen();
        return;
    }
    
    do {
        int choice_int = 0;
        char choice_str[32] = {0};

        clear_screen();
        printf("=== MATERIALS: %s ===\n", topic->title);
        
        Material *temp = topic->materials;
        int count = 1;
        while(temp) {
            printf("%d. %s\n", count++, temp->title);
            temp = temp->next;
        }
        
        printf("\n");
        printf("commands: back, redo, create\n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        if (is_number(choice_str)) {
            choice_int = atoi(choice_str);
        }

        if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "create") == 0) {
            // Create new material
            Material *new_material = (Material*)malloc(sizeof(Material));
            if(new_material) {
                new_material->material_id = next_material_id++;
                new_material->course_id = topic->course_id;
                new_material->topic_id = topic->topic_id;
                
                printf("Enter material title: ");
                getchar();
                fgets(new_material->title, MAX_STRING, stdin);
                new_material->title[strcspn(new_material->title, "\n")] = 0;
                
                printf("Enter description: ");
                fgets(new_material->description, MAX_STRING, stdin);
                new_material->description[strcspn(new_material->description, "\n")] = 0;
                
                printf("Enter material URL: ");
                scanf("%s", new_material->url);
                
                get_current_time(&new_material->created_at);
                new_material->next = topic->materials;
                topic->materials = new_material;
                
                save_courses();
                printf("Material created successfully!\n");
                pause_screen();
            }
        } else {
            printf("Invalid choice!\n");
            pause_screen();
        }
    } while(true);
}

void teacher_manage_announcements(Topic *topic) {
    if (!topic) {
        printf("No topic data available.\n");
        pause_screen();
        return;
    }

    do {
        int choice_int = 0;
        char choice_str[32] = {0};

        clear_screen();
        printf("=== ANNOUNCEMENTS: %s ===\n", topic->title);
        
        Announcement *temp = topic->announcements;
        int count = 1;
        while(temp) {
            printf("%d. %s\n", count++, temp->title);
            temp = temp->next;
        }

        printf("commands: back, redo, create \n");
        printf("\n");
        printf("Choice: ");
        scanf("%32s", choice_str);
        if (is_number(choice_str)) {
            choice_int = atoi(choice_str);
        }

        if (strcmp(choice_str, "back") == 0) {
            if (undo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No previous menu to undo!\n");
                pause_screen();
            }
        } else if (strcmp(choice_str, "redo") == 0) {
            if (redo_navigation(next_menu, &next_data)) {
                execute_menu(next_menu, next_data);
                return;
            } else {
                printf("No menu to redo!\n");
                pause_screen();
            }
        } else if(strcmp(choice_str, "create") == 0) {
            // Create new announcement
            Announcement *new_announcement = (Announcement*)malloc(sizeof(Announcement));
            if(new_announcement) {
                new_announcement->announcement_id = next_announcement_id++;
                new_announcement->course_id = topic->course_id;
                new_announcement->topic_id = topic->topic_id;
                
                printf("Enter announcement title: ");
                getchar();
                fgets(new_announcement->title, MAX_STRING, stdin);
                new_announcement->title[strcspn(new_announcement->title, "\n")] = 0;
                
                printf("Enter description: ");
                fgets(new_announcement->description, MAX_STRING, stdin);
                new_announcement->description[strcspn(new_announcement->description, "\n")] = 0;
                
                get_current_time(&new_announcement->created_at);
                new_announcement->next = topic->announcements;
                topic->announcements = new_announcement;
                
                save_courses();
                printf("Announcement created successfully!\n");
                pause_screen();
            }
        } else {
            printf("Invalid choice!\n");
            pause_screen();
        }
    } while(true);
}
