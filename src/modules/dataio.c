// ==================================================
// FILE: src/modules/dataio.c
// ==================================================

#include "../headers/dataio.h"
#include "../headers/queue.h"
#include "../headers/utils.h"
#include "../headers/structs.h"

void save_students() {
    FILE *file = fopen("src/data/students.txt", "w");
    if(!file) return;
    
    Student *temp = students_head;
    while(temp) {
        fprintf(file, "%d|%s|%s|%s|%s|%s\n",
                temp->student_id, temp->student_unique_number,
                temp->email, temp->password, temp->name, temp->phone_number);
        temp = temp->next;
    }
    
    fclose(file);
}

void save_teachers() {
    FILE *file = fopen("src/data/teachers.txt", "w");
    if(!file) {
    	perror("Error opening file teachers.txt");
		return;
	}
	
    Teacher *temp = teachers_head;
    while(temp) {
        fprintf(file, "%d|%s|%s|%s|%s|%s\n",
                temp->teacher_id, temp->teacher_unique_number,
                temp->email, temp->password, temp->name, temp->phone_number);
        temp = temp->next;
    }
    
    fclose(file);
}

// void save_enrolled

void save_courses() {
    FILE *file = fopen("src/data/courses.txt", "w");
    if(!file) return;
    
    Course *course = courses_head;
    while(course) {
        fprintf(file, "COURSE|%d|%s|%s|%s|%d\n",
                course->course_id, course->code, course->name,
                course->description, course->teacher_id);
        
        // Save enrolled students
        Student *student_enrolled = course->enrolled_students;
        while (student_enrolled) {
            fprintf(file, "ENROLLED_STUDENT|%s|%s\n",
                    course->code, student_enrolled->student_unique_number);
            student_enrolled = student_enrolled->next;
        }

        // Save waitinglist (student)
        Student *student_waitinglist = course->waitlist_students;
        while (student_waitinglist) {
            fprintf(file, "WAITINGLIST_STUDENT|%s|%s\n",
                    course->code, student_waitinglist->student_unique_number);
            student_waitinglist = student_waitinglist->next;
        }

        // Save topics
        Topic *topic = course->topics;
        while(topic) {
            fprintf(file, "TOPIC|%d|%s|%s|%d|%d|%d-%d-%d %d:%d\n",
                    topic->topic_id, topic->title, topic->description,
                    topic->course_id, course->course_id,
                    topic->created_at.day, topic->created_at.month,
                    topic->created_at.year, topic->created_at.hour,
                    topic->created_at.minute);
            
            // Save assignments
            Assignment *assignment = topic->assignments;
            while(assignment) {
                fprintf(file, "ASSIGNMENT|%d|%s|%d|%d|%d-%d-%d %d:%d|%d-%d-%d %d:%d\n",
                        assignment->assignment_id, assignment->title,
                        assignment->course_id, assignment->topic_id,
                        assignment->deadline.day, assignment->deadline.month,
                        assignment->deadline.year, assignment->deadline.hour,
                        assignment->deadline.minute,
                        assignment->created_at.day, assignment->created_at.month,
                        assignment->created_at.year, assignment->created_at.hour,
                        assignment->created_at.minute);
                
                // Save submissions
                Submission *submission = assignment->graded_submissions;
                while(submission) {
                    fprintf(file, "SUBMISSION|%d|%d|%s|%d|%d|%d|%d|%d-%d-%d %d:%d\n",
                            submission->submission_id, submission->grade,
                            submission->url, submission->is_graded ? 1 : 0,
                            submission->is_submitted ? 1 : 0,
                            submission->student_id, submission->assignment_id,
                            submission->created_at.day, submission->created_at.month,
                            submission->created_at.year, submission->created_at.hour,
                            submission->created_at.minute);
                    submission = submission->next;
                }
                
                submission = assignment->not_graded_submissions;
                while(submission) {
                    fprintf(file, "SUBMISSION|%d|%d|%s|%d|%d|%d|%d|%d-%d-%d %d:%d\n",
                            submission->submission_id, submission->grade,
                            submission->url, submission->is_graded ? 1 : 0,
                            submission->is_submitted ? 1 : 0,
                            submission->student_id, submission->assignment_id,
                            submission->created_at.day, submission->created_at.month,
                            submission->created_at.year, submission->created_at.hour,
                            submission->created_at.minute);
                    submission = submission->next;
                }
                
                assignment = assignment->next;
            }
            
            // Save materials
            Material *material = topic->materials;
            while(material) {
                fprintf(file, "MATERIAL|%d|%d|%d|%s|%s|%s|%d-%d-%d %d:%d\n",
                        material->material_id, material->course_id,
                        material->topic_id, material->title,
                        material->description, material->url,
                        material->created_at.day, material->created_at.month,
                        material->created_at.year, material->created_at.hour,
                        material->created_at.minute);
                material = material->next;
            }
            
            // Save announcements
            Announcement *announcement = topic->announcements;
            while(announcement) {
                fprintf(file, "ANNOUNCEMENT|%d|%d|%d|%s|%s|%d-%d-%d %d:%d\n",
                        announcement->announcement_id, announcement->course_id,
                        announcement->topic_id, announcement->title,
                        announcement->description,
                        announcement->created_at.day, announcement->created_at.month,
                        announcement->created_at.year, announcement->created_at.hour,
                        announcement->created_at.minute);
                announcement = announcement->next;
            }
            
            topic = topic->next;
        }
        
        course = course->next;
    }
    
    fclose(file);
}

void load_students() {
    FILE *file = fopen("src/data/students.txt", "r");
    if(!file) return;
    
    char line[1024];
    while(fgets(line, sizeof(line), file)) {
        Student *new_student = (Student*)malloc(sizeof(Student));
        if(new_student) {
            sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
                   &new_student->student_id, new_student->student_unique_number,
                   new_student->email, new_student->password,
                   new_student->name, new_student->phone_number);
            
            new_student->next = students_head;
            students_head = new_student;
            
            if(new_student->student_id >= next_student_id) {
                next_student_id = new_student->student_id + 1;
            }
        }
    }
    
    fclose(file);
}

void load_teachers() {
    FILE *file = fopen("src/data/teachers.txt", "r");
    if(!file) return;
    
    char line[1024];
    while(fgets(line, sizeof(line), file)) {
        Teacher *new_teacher = (Teacher*)malloc(sizeof(Teacher));
        if(new_teacher) {
            sscanf(line, "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
                   &new_teacher->teacher_id, new_teacher->teacher_unique_number,
                   new_teacher->email, new_teacher->password,
                   new_teacher->name, new_teacher->phone_number);
            
            new_teacher->next = teachers_head;
            teachers_head = new_teacher;
            
            if(new_teacher->teacher_id >= next_teacher_id) {
                next_teacher_id = new_teacher->teacher_id + 1;
            }
        }
    }
    
    fclose(file);
}

void load_courses() {
    FILE *file = fopen("src/data/courses.txt", "r");
    if(!file) return;
    
    char line[1024];
    Course *current_course = NULL;
    Topic *current_topic = NULL;
    Assignment *current_assignment = NULL;
    
    while(fgets(line, sizeof(line), file)) {
        char type[20];
        sscanf(line, "%[^|]", type);
        
        if(strcmp(type, "COURSE") == 0) {
            Course *new_course = (Course*)malloc(sizeof(Course));
            if(new_course) {
                sscanf(line, "COURSE|%d|%[^|]|%[^|]|%[^|]|%d",
                       &new_course->course_id, new_course->code,
                       new_course->name, new_course->description,
                       &new_course->teacher_id);
                
                new_course->enrolled_students = NULL;
                new_course->waitlist_students = NULL;
                new_course->topics = NULL;
                new_course->next = courses_head;
                courses_head = new_course;
                current_course = new_course;
                
                if(new_course->course_id >= next_course_id) {
                    next_course_id = new_course->course_id + 1;
                }
            }
        }
        else if(strcmp(type, "ENROLLED_STUDENT") == 0) {
            char course_code[MAX_STRING];
            char student_unique_number[MAX_UNIQUE_NUM];
            
            sscanf(line, "ENROLLED_STUDENT|%[^|]|%s", course_code, student_unique_number);
            
            // Find the course and student
            Course *course = find_course_by_code(course_code);
            Student *student = find_student_by_unique_number(student_unique_number);
            
            if(course && student) {
                add_student_to_enrolled_list(course, student);
            }
        }
        else if(strcmp(type, "WAITINGLIST_STUDENT") == 0) {
            char course_code[MAX_STRING];
            char student_unique_number[MAX_UNIQUE_NUM];
            
            sscanf(line, "WAITINGLIST_STUDENT|%[^|]|%s", course_code, student_unique_number);
            
            // Find the course and student
            Course *course = find_course_by_code(course_code);
            Student *student = find_student_by_unique_number(student_unique_number);
            
            if(course && student) {
                add_student_to_waitlist(course, student);
            }
        }
        else if(strcmp(type, "TOPIC") == 0) {
            Topic *new_topic = (Topic*)malloc(sizeof(Topic));
            if(new_topic && current_course) {
                sscanf(line, "TOPIC|%d|%[^|]|%[^|]|%d|%d|%d-%d-%d %d:%d",
                       &new_topic->topic_id, new_topic->title, new_topic->description,
                       &new_topic->course_id, &new_topic->course_id,
                       &new_topic->created_at.day, &new_topic->created_at.month,
                       &new_topic->created_at.year, &new_topic->created_at.hour,
                       &new_topic->created_at.minute);
                
                new_topic->assignments = NULL;
                new_topic->materials = NULL;
                new_topic->announcements = NULL;
                new_topic->next = current_course->topics;
                current_course->topics = new_topic;
                current_topic = new_topic;
                
                if(new_topic->topic_id >= next_topic_id) {
                    next_topic_id = new_topic->topic_id + 1;
                }
            }
        }
        else if(strcmp(type, "ASSIGNMENT") == 0) {
            Assignment *new_assignment = (Assignment*)malloc(sizeof(Assignment));
            if(new_assignment && current_topic) {
                sscanf(line, "ASSIGNMENT|%d|%[^|]|%d|%d|%d-%d-%d %d:%d|%d-%d-%d %d:%d",
                       &new_assignment->assignment_id, new_assignment->title,
                       &new_assignment->course_id, &new_assignment->topic_id,
                       &new_assignment->deadline.day, &new_assignment->deadline.month,
                       &new_assignment->deadline.year, &new_assignment->deadline.hour,
                       &new_assignment->deadline.minute,
                       &new_assignment->created_at.day, &new_assignment->created_at.month,
                       &new_assignment->created_at.year, &new_assignment->created_at.hour,
                       &new_assignment->created_at.minute);
                
                new_assignment->graded_submissions = NULL;
                new_assignment->not_graded_submissions = NULL;
                new_assignment->next = current_topic->assignments;
                current_topic->assignments = new_assignment;
                current_assignment = new_assignment;
                
                if(new_assignment->assignment_id >= next_assignment_id) {
                    next_assignment_id = new_assignment->assignment_id + 1;
                }
            }
        }
        else if(strcmp(type, "SUBMISSION") == 0) {
            Submission *new_submission = (Submission*)malloc(sizeof(Submission));
            if(new_submission && current_assignment) {
                int is_graded_int, is_submitted_int;
                sscanf(line, "SUBMISSION|%d|%d|%[^|]|%d|%d|%d|%d|%d-%d-%d %d:%d",
                       &new_submission->submission_id, &new_submission->grade,
                       new_submission->url, &is_graded_int, &is_submitted_int,
                       &new_submission->student_id, &new_submission->assignment_id,
                       &new_submission->created_at.day, &new_submission->created_at.month,
                       &new_submission->created_at.year, &new_submission->created_at.hour,
                       &new_submission->created_at.minute);
                
                new_submission->is_graded = (is_graded_int == 1);
                new_submission->is_submitted = (is_submitted_int == 1);
                new_submission->student = find_student_by_id(new_submission->student_id);
                
                // Add to appropriate queue based on grading status
                if(new_submission->is_graded) {
                    enqueue_submission(&current_assignment->graded_submissions, new_submission);
                } else {
                    enqueue_submission(&current_assignment->not_graded_submissions, new_submission);
                }
                
                if(new_submission->submission_id >= next_submission_id) {
                    next_submission_id = new_submission->submission_id + 1;
                }
            }
        }
        else if(strcmp(type, "MATERIAL") == 0) {
            Material *new_material = (Material*)malloc(sizeof(Material));
            if(new_material && current_topic) {
                sscanf(line, "MATERIAL|%d|%d|%d|%[^|]|%[^|]|%[^|]|%d-%d-%d %d:%d",
                       &new_material->material_id, &new_material->course_id,
                       &new_material->topic_id, new_material->title,
                       new_material->description, new_material->url,
                       &new_material->created_at.day, &new_material->created_at.month,
                       &new_material->created_at.year, &new_material->created_at.hour,
                       &new_material->created_at.minute);
                
                new_material->next = current_topic->materials;
                current_topic->materials = new_material;
                
                if(new_material->material_id >= next_material_id) {
                    next_material_id = new_material->material_id + 1;
                }
            }
        }
        else if(strcmp(type, "ANNOUNCEMENT") == 0) {
            Announcement *new_announcement = (Announcement*)malloc(sizeof(Announcement));
            if(new_announcement && current_topic) {
                sscanf(line, "ANNOUNCEMENT|%d|%d|%d|%[^|]|%[^|]|%d-%d-%d %d:%d",
                       &new_announcement->announcement_id, &new_announcement->course_id,
                       &new_announcement->topic_id, new_announcement->title,
                       new_announcement->description,
                       &new_announcement->created_at.day, &new_announcement->created_at.month,
                       &new_announcement->created_at.year, &new_announcement->created_at.hour,
                       &new_announcement->created_at.minute);
                
                new_announcement->next = current_topic->announcements;
                current_topic->announcements = new_announcement;
                
                if(new_announcement->announcement_id >= next_announcement_id) {
                    next_announcement_id = new_announcement->announcement_id + 1;
                }
            }
        }
    }
    
    fclose(file);
}
