// ==================================================
// FILE: src/modules/auth.c
// ==================================================

#include "../headers/auth.h"
#include "../headers/dataio.h"
#include "../headers/utils.h"
#include "../headers/structs.h"

bool register_teacher() {
    Teacher *new_teacher = (Teacher*)malloc(sizeof(Teacher));
    if(!new_teacher) return false;
    
    clear_screen();
    printf("=== TEACHER REGISTRATION ===\n");
    
    new_teacher->teacher_id = next_teacher_id++;
    
    do {
        printf("Enter unique number: ");
        scanf("%s", new_teacher->teacher_unique_number);
        
        if(is_unique_number_taken(new_teacher->teacher_unique_number)) {
            printf("This unique number is already taken. Please try another one.\n");
            pause_screen();
            clear_screen();
            printf("=== TEACHER REGISTRATION ===\n");
        } else {
            break;
        }
    } while(true);
    
    printf("Enter name: ");
    getchar(); // consume newline
    fgets(new_teacher->name, MAX_STRING, stdin);
    new_teacher->name[strcspn(new_teacher->name, "\n")] = 0;
    
    printf("Enter email: ");
    scanf("%s", new_teacher->email);
    
    printf("Enter phone number: ");
    scanf("%s", new_teacher->phone_number);
    
    printf("Create password: ");
    char plain_password[MAX_PASSWORD];
    strcpy(plain_password, get_password());
    hash_password(plain_password, new_teacher->password);
    
    new_teacher->next = teachers_head;
    teachers_head = new_teacher;
    
    return true;
}

bool register_student() {
    Student *new_student = (Student*)malloc(sizeof(Student));
    if(!new_student) return false;
    
    clear_screen();
    printf("=== STUDENT REGISTRATION ===\n");
    
    new_student->student_id = next_student_id++;
    
    do {
        printf("Enter unique number: ");
        scanf("%s", new_student->student_unique_number);
        
        if(is_unique_number_taken(new_student->student_unique_number)) {
            printf("This unique number is already taken. Please try another one.\n");
            pause_screen();
            clear_screen();
            printf("=== STUDENT REGISTRATION ===\n");
        } else {
            break;
        }
    } while(true);
    
    printf("Enter name: ");
    getchar(); // consume newline
    fgets(new_student->name, MAX_STRING, stdin);
    new_student->name[strcspn(new_student->name, "\n")] = 0;
    
    printf("Enter email: ");
    scanf("%s", new_student->email);
    
    printf("Enter phone number: ");
    scanf("%s", new_student->phone_number);
    
    printf("Create password: ");
    char plain_password[MAX_PASSWORD];
    strcpy(plain_password, get_password());
    hash_password(plain_password, new_student->password);
    
    new_student->next = students_head;
    students_head = new_student;
    
    return true;
}

bool login_teacher() {
    char unique_num[MAX_UNIQUE_NUM];
    char password[MAX_PASSWORD];
    
    clear_screen();
    printf("=== TEACHER LOGIN ===\n");
    printf("Enter unique number: ");
    scanf("%s", unique_num);
    
    printf("Enter password: ");
    strcpy(password, get_password());
    
    Teacher *temp = teachers_head;
    while(temp) {
        if(strcmp(temp->teacher_unique_number, unique_num) == 0 && 
           verify_password(password, temp->password)) {
            current_teacher = temp;
            printf("Login successful! Welcome %s\n", temp->name);
            pause_screen();
            return true;
        }
        temp = temp->next;
    }
    
    printf("Invalid credentials!\n");
    pause_screen();
    return false;
}

bool login_student() {
    char unique_num[MAX_UNIQUE_NUM];
    char password[MAX_PASSWORD];
    
    clear_screen();
    printf("=== STUDENT LOGIN ===\n");
    printf("Enter unique number: ");
    scanf("%s", unique_num);
    
    printf("Enter password: ");
    strcpy(password, get_password());
    
    Student *temp = students_head;
    while(temp) {
        if(strcmp(temp->student_unique_number, unique_num) == 0 && 
           verify_password(password, temp->password)) {
            current_student = temp;
            printf("Login successful! Welcome %s\n", temp->name);
            pause_screen();
            return true;
        }
        temp = temp->next;
    }
    
    printf("Invalid credentials!\n");
    pause_screen();
    return false;
}

char* get_password() {
    static char password[MAX_PASSWORD];
    int i = 0;
    char ch;
    
    while((ch = getch()) != '\r' && i < MAX_PASSWORD - 1) {
        if(ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        } else if(ch != '\b') {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
    return password;
}
