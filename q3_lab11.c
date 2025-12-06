#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int id;
    char name[50];
    char department[20];
    char designation[20];
    float salary;
    char phone[20];
    char email[50];
    int joiningYear;         
} Employee;


int calculateExperience(int joiningYear) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int currentYear = tm->tm_year + 1900;

    return currentYear - joiningYear;
}

void addEmployee(Employee *e) {
    printf("Enter ID: ");
    scanf("%d", &e->id);

    printf("Name: ");
    scanf("%s", e->name);

    printf("Department (IT/HR/Finance/Marketing/Operations): ");
    scanf("%s", e->department);

    printf("Designation (Intern/Junior/Senior/Manager/Director): ");
    scanf("%s", e->designation);

    printf("Salary: ");
    scanf("%f", &e->salary);

    printf("Phone: ");
    scanf("%s", e->phone);

    printf("Email: ");
    scanf("%s", e->email);

    printf("Joining Year: ");
    scanf("%d", &e->joiningYear);
}


void showEmployee(Employee e) {
    printf("\nID: %d\nName: %s\nDept: %s\nDesignation: %s\nSalary: %.2f\nPhone: %s\nEmail: %s\nExperience: %d years\n",
        e.id, e.name, e.department, e.designation, e.salary, e.phone, e.email,
        calculateExperience(e.joiningYear));
}

void departmentSalaryStats(Employee *e, int n) {
    char dept[20];
    printf("Enter department: ");
    scanf("%s", dept);

    float total = 0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(e[i].department, dept) == 0) {
            total += e[i].salary;
            count++;
        }
    }

    if (count == 0) {
        printf("No employees in this department.\n");
        return;
    }

    printf("Total Salary: %.2f\nAverage Salary: %.2f\n", total, total / count);
}

void applyAppraisal(Employee *e) {
    int percent;
    printf("Enter performance percentage (5-15): ");
    scanf("%d", &percent);

    if (percent < 5 || percent > 15) {
        printf("Invalid.\n");
        return;
    }

    e->salary += (e->salary * percent / 100);
}

void searchByDepartment(Employee *e, int n) {
    char dept[20];
    printf("Enter department: ");
    scanf("%s", dept);

    for (int i = 0; i < n; i++)
        if (strcmp(e[i].department, dept) == 0)
            showEmployee(e[i]);
}

void searchByDesignation(Employee *e, int n) {
    char des[20];
    printf("Enter designation: ");
    scanf("%s", des);

    for (int i = 0; i < n; i++)
        if (strcmp(e[i].designation, des) == 0)
            showEmployee(e[i]);
}

void searchByExperience(Employee *e, int n) {
    int exp;
    printf("Enter minimum experience: ");
    scanf("%d", &exp);

    for (int i = 0; i < n; i++)
        if (calculateExperience(e[i].joiningYear) >= exp)
            showEmployee(e[i]);
}

void promotionEligibility(Employee *e, int n) {
    printf("\nEmployees eligible for promotion (>3 years):\n");
    for (int i = 0; i < n; i++) {
        if (calculateExperience(e[i].joiningYear) > 3)
            showEmployee(e[i]);
    }
}

int main() {
    int n, choice;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    Employee *e = malloc(n * sizeof(Employee));

    for (int i = 0; i < n; i++) {
        printf("\n--- Enter Employee %d ---\n", i + 1);
        addEmployee(&e[i]);
    }

    do {
        printf("\n1. Search by Department\n2. Search by Designation\n3. Search by Experience\n4. Department Salary Stats\n5. Appraisal\n6. Promotion Eligibility\n7. Exit\nChoose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: searchByDepartment(e, n); break;
            case 2: searchByDesignation(e, n); break;
            case 3: searchByExperience(e, n); break;
            case 4: departmentSalaryStats(e, n); break;
            case 5: {
                int id;
                printf("Enter employee ID: ");
                scanf("%d", &id);

                for (int i = 0; i < n; i++)
                    if (e[i].id == id)
                        applyAppraisal(&e[i]);
                break;
            }
            case 6: promotionEligibility(e, n); break;
            case 7: break;
        }
    } while (choice != 7);

    free(e);
    return 0;
}
