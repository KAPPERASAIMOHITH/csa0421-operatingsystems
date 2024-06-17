#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50
#define FILENAME "employee_data.dat"

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
} Employee;

void addEmployee();
void displayEmployee();
void updateEmployee();
void deleteEmployee();

int main() {
    char choice;
    do {
        printf("\nEmployee Database\n1. Add Employee\n2. Display Employee Details\n3. Update Employee Details\n4. Delete Employee\n5. Exit\nEnter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1': addEmployee(); break;
            case '2': displayEmployee(); break;
            case '3': updateEmployee(); break;
            case '4': deleteEmployee(); break;
            case '5': printf("Exiting program.\n"); break;
            default: printf("Invalid choice. Please enter again.\n");
        }
    } while (choice != '5');
    return 0;
}

void addEmployee() {
    FILE *fp = fopen(FILENAME, "ab+");
    if (!fp) { printf("Error opening file.\n"); return; }

    Employee emp;
    printf("Enter employee ID: "); scanf("%d", &emp.id);
    printf("Enter employee name: "); scanf("%s", emp.name);
    printf("Enter employee salary: "); scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(Employee), 1, fp);
    fclose(fp);
    printf("Employee added successfully.\n");
}

void displayEmployee() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) { printf("Error opening file.\n"); return; }

    Employee emp;
    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        if (emp.id != -1)
            printf("ID: %d, Name: %s, Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }
    fclose(fp);
}

void updateEmployee() {
    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp) { printf("Error opening file.\n"); return; }

    int searchId, found = 0;
    printf("Enter employee ID to update: "); scanf("%d", &searchId);

    Employee emp;
    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        if (emp.id == searchId) {
            printf("Enter new name: "); scanf("%s", emp.name);
            printf("Enter new salary: "); scanf("%f", &emp.salary);

            fseek(fp, -sizeof(Employee), SEEK_CUR);
            fwrite(&emp, sizeof(Employee), 1, fp);
            found = 1;
            break;
        }
    }
    fclose(fp);
    printf(found ? "Employee details updated successfully.\n" : "Employee not found.\n");
}

void deleteEmployee() {
    FILE *fp = fopen(FILENAME, "rb+");
    if (!fp) { printf("Error opening file.\n"); return; }

    int searchId, found = 0;
    printf("Enter employee ID to delete: "); scanf("%d", &searchId);

    Employee emp;
    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        if (emp.id == searchId) {
            emp.id = -1; // Mark as deleted
            fseek(fp, -sizeof(Employee), SEEK_CUR);
            fwrite(&emp, sizeof(Employee), 1, fp);
            found = 1;
            break;
        }
    }
    fclose(fp);
    printf(found ? "Employee deleted successfully.\n" : "Employee not found.\n");
}

