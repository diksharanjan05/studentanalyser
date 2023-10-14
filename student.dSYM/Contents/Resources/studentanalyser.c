#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct Student {
    char name[MAX_NAME_LENGTH];
    int attendance[5];
    int grades[5];
    struct Student *next;
};

struct Student *input_data(struct Student *head);
void generate_report(struct Student *head);
void search_student(struct Student *head, char search_name[]);
void save_data(struct Student *head);
float calculate_average(struct Student *student);
void find_best_and_worst_subjects(struct Student *student, int *best_subject, int *worst_subject);
void has_attendance_shortage(struct Student *student);
void delete_student_by_name(struct Student *head, char *name);
void update_data(struct Student *head, char name[]);

int main() {
    int ch;
    char search_name[MAX_NAME_LENGTH];
    struct Student *head = NULL;

    while(1)
    {
        printf("Enter 1:Add new student \n 2:Generate report \n 3:Searching of data\n 4:Delete student \n 5:Update student data\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:head=input_data(head);
                   save_data(head);
                   break;

            case 2:generate_report(head);
                   break;

            case 3:printf("Enter the name of the student to search for: ");
                   scanf("%s",search_name);
                   search_student(head,search_name);
                   break;

            case 4:printf("Enter the name of the student to deleted: ");
                   scanf("%s",search_name);   
                   delete_student_by_name(head,search_name);
                   break;
            case 5:printf("Enter the name of the student to deleted: ");
                   scanf("%s",search_name);
                   update_data(head,search_name);
                   break;

            default :exit(0);        
        }

    }
}

void has_attendance_shortage(struct Student *student) {
    for(int i=0;i<5;i++){
    if (student->attendance[i]<85){
        printf("shortage in subject %d\n",i+1);
    }
    }
}

void update_data(struct Student *head, char name[]) {
    // Search for node with matching name
    struct Student *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // Found matching node, get updated data from user
            printf("enter new attendance \n");
            for(int i=0;i<5;i++)
                scanf("%d",&current->attendance[i]);
            printf("Enter new marks ");
            for (int j = 0; j < 5; j++) {
            scanf("%d", &current->grades[j]);
        }
            printf("Data updated successfully.\n");
            return;
        }
        current = current->next;
    }
    
    // Node with matching name not found
    printf("No data found for student '%s'.\n", name);
}

void find_best_and_worst_subjects(struct Student *student, int *best_subject, int *worst_subject) {
    int max_grade = -1;
    int min_grade = 101;

    for (int i = 0; i < 5; i++) {
        if (student->grades[i] > max_grade) 
        {
            max_grade = student->grades[i];
            *best_subject = i;

        }
        if (student->grades[i] < min_grade) {
            min_grade = student->grades[i];
            *worst_subject = i;
        }
    }
}

float calculate_average(struct Student *student)
{
    float sum = 0;
    for (int i = 0; i < 5; i++) 
    {
        sum += student->grades[i];
    }
    float average = sum / 5.0;
    return average;
}

struct Student *input_data(struct Student *head) {
    // Input data for each student and add to linked list
    int num_students;
    printf("Enter the number of students: ");
    scanf("%d", &num_students);

    for (int i = 0; i < num_students; i++) {
        struct Student *new_student = malloc(sizeof(struct Student));

        printf("Enter the name of student %d: ", i+1);
        scanf("%s", new_student->name);

        printf("Enter the attendance for student %d (out of 100): ", i+1);
        for (int j = 0; j < 5; j++){
        scanf("%d", &new_student->attendance[j]);
        } 

        printf("Enter the grades (out of 100) for student %d, separated by spaces: ", i+1);
        for (int j = 0; j < 5; j++) {
            scanf("%d", &new_student->grades[j]);
        }
        //inserting node at the front of sll
        new_student->next = head;
        head = new_student;
    }
    return head;
}
void delete_student_by_name(struct Student *head, char *name) {
    //deleting data
    struct Student *current = head;
    struct Student *prev = NULL;
    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Student with name %s not found.\n", name);
        return;
    }
    if (prev == NULL) {
        head = current->next;
    }
    else {
        prev->next = current->next;
    }
    free(current);
    printf("Student with name %s deleted.\n", name);
}

void generate_report(struct Student *head) {
    // Display report for each student in linked list
    printf("STUDENT DETAILS:\n");
    printf("---------------------------------------------------------------------------- \n");
    struct Student *current = head;
    while (current != NULL) {
        printf("Name: %s\n", current->name);
        printf("Attendance: ");
        for (int j = 0; j < 5; j++) {
        printf("%d ",current->attendance[j]);
        }
        printf("\n");
        printf("Grades: ");
        for (int j = 0; j < 5; j++) {
            printf("%d ", current->grades[j]);
        }
        printf("\n");
        float average = calculate_average(current);
        printf("Average grade: %.2f\n", average);
        int best_subject, worst_subject;
        find_best_and_worst_subjects(current, &best_subject, &worst_subject);
        printf("Best subject: Subject %d -GOOD \n", best_subject + 1);
        printf("Worst subject: Subject %d - NEED TO WORK HARD \n", worst_subject + 1);
        has_attendance_shortage(current);
        printf("\n");

        printf("---------------------------------------------------------------------------- \n");

        current = current->next;
    }
}

void search_student(struct Student *head, char search_name[]) {
    // Search for a student by name in linked list
    struct Student *current = head;
    while (current != NULL) {
        if (strcmp(current->name, search_name) == 0) {
            printf("Name: %s\n", current->name);
            printf("Attendance: ");
            for (int j = 0; j < 5; j++) {
            printf("%d ",current->attendance[j]);
            }
            printf("Grades: ");
            for (int j = 0; j < 5; j++) {
                printf("%d ", current->grades[j]);
            }
            printf("\n");
            return;
        }

        current = current->next;
    }
    printf("Student not found.\n");
}

void save_data(struct Student *head) 
{
    // Save student data to file
    FILE *fp;
    fp = fopen("student_data.txt", "w");
    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }

    struct Student *current = head;
    while (current != NULL) {
        fprintf(fp, "%s", current->name);
        for (int j = 0; j < 5; j++) {
            fprintf(fp, "%d ", current->attendance[j]);
        }
        for (int j = 0; j < 5; j++) {
            fprintf(fp, "%d ", current->grades[j]);
        }
        fprintf(fp, "\n");

        current = current->next;
    }
    fclose(fp);
    printf("Student data saved to file.\n");
}
