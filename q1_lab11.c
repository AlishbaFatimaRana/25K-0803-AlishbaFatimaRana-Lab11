#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    char name[50];
    int roll;
    float marks[3];
    float percentage;
    char grade;
};

void inputStudents(struct Student s[], int n);
void calculatePercentageAndGrade(struct Student s[], int n);
void displayStudents(struct Student s[], int n);
void searchByRollOrName(struct Student s[], int n);
void searchByGrade(struct Student s[], int n);
void displayClassAverage(struct Student s[], int n);
void displayRank(struct Student s[], int n);

int main() {
    struct Student s[MAX];
    int n, choice;
    
    printf("Enter number of students: ");
    scanf("%d", &n);
    
    inputStudents(s, n);
    calculatePercentageAndGrade(s, n);
    
    do {
        printf("\n Student Record System \n");
        printf("1. Display all students\n");
        printf("2. Search student by Roll Number or Name\n");
        printf("3. Search students by Grade\n");
        printf("4. Display Class Average & Above/Below Average\n");
        printf("5. Display Student Ranking\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: displayStudents(s, n); break;
            case 2: searchByRollOrName(s, n); break;
            case 3: searchByGrade(s, n); break;
            case 4: displayClassAverage(s, n); break;
            case 5: displayRank(s, n); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(choice != 0);
    
    return 0;
}

void inputStudents(struct Student s[], int n) {
    for(int i = 0; i < n; i++) {
        printf("\nEnter details of student %d:\n", i+1);
        printf("Name: ");
        scanf(" %[^\n]", s[i].name);  // Read full line
        printf("Roll Number: ");
        scanf("%d", &s[i].roll);
        
        for(int j = 0; j < 3; j++) {
            do {
                printf("Marks in subject %d (0-100): ", j+1);
                scanf("%f", &s[i].marks[j]);
                if(s[i].marks[j] < 0 || s[i].marks[j] > 100)
                    printf("Invalid marks! Please enter between 0 and 100.\n");
            } while(s[i].marks[j] < 0 || s[i].marks[j] > 100);
        }
    }
}

void calculatePercentageAndGrade(struct Student s[], int n) {
    for(int i = 0; i < n; i++) {
        float total = s[i].marks[0] + s[i].marks[1] + s[i].marks[2];
        s[i].percentage = total / 3;
        
        if(s[i].percentage >= 90) s[i].grade = 'A';
        else if(s[i].percentage >= 80) s[i].grade = 'B';
        else if(s[i].percentage >= 70) s[i].grade = 'C';
        else if(s[i].percentage >= 60) s[i].grade = 'D';
        else if(s[i].percentage >= 50) s[i].grade = 'E';
        else s[i].grade = 'F';
    }
}

void displayStudents(struct Student s[], int n) {
    printf("\n%-20s %-10s %-10s %-10s\n", "Name", "Roll", "Percentage", "Grade");
    for(int i = 0; i < n; i++) {
        printf("%-20s %-10d %-10.2f %-10c\n", s[i].name, s[i].roll, s[i].percentage, s[i].grade);
    }
}

void searchByRollOrName(struct Student s[], int n) {
    int choice, roll;
    char name[50];
    
    printf("\n1. Search by Roll Number\n");
    printf("2. Search by Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    if(choice == 1) {
        printf("Enter Roll Number: ");
        scanf("%d", &roll);
        for(int i = 0; i < n; i++) {
            if(s[i].roll == roll) {
                printf("Student found: %s, Percentage: %.2f, Grade: %c\n", s[i].name, s[i].percentage, s[i].grade);
                return;
            }
        }
        printf("Student not found!\n");
    }
    else if(choice == 2) {
        printf("Enter Name: ");
        scanf(" %[^\n]", name);
        for(int i = 0; i < n; i++) {
            if(strcmp(s[i].name, name) == 0) {
                printf("Student found: Roll: %d, Percentage: %.2f, Grade: %c\n", s[i].roll, s[i].percentage, s[i].grade);
                return;
            }
        }
        printf("Student not found!\n");
    }
}

void searchByGrade(struct Student s[], int n) {
    char grade;
    printf("Enter Grade to search: ");
    scanf(" %c", &grade);
    
    printf("\nStudents with Grade '%c':\n", grade);
    for(int i = 0; i < n; i++) {
        if(s[i].grade == grade)
            printf("%s (Roll: %d, Percentage: %.2f)\n", s[i].name, s[i].roll, s[i].percentage);
    }
}

void displayClassAverage(struct Student s[], int n) {
    float total = 0, avg;
    for(int i = 0; i < n; i++) total += s[i].percentage;
    avg = total / n;
    
    printf("\nClass Average: %.2f\n", avg);
    printf("Students Above Average:\n");
    for(int i = 0; i < n; i++)
        if(s[i].percentage > avg)
            printf("%s (%.2f)\n", s[i].name, s[i].percentage);
    
    printf("Students Below Average:\n");
    for(int i = 0; i < n; i++)
        if(s[i].percentage < avg)
            printf("%s (%.2f)\n", s[i].name, s[i].percentage);
}


void displayRank(struct Student s[], int n) {
    struct Student temp;
    
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(s[i].percentage < s[j].percentage) {
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
    
    printf("\nStudent Ranking\n");
    for(int i = 0; i < n; i++)
        printf("Rank %d: %s (%.2f%%)\n", i+1, s[i].name, s[i].percentage);
}

