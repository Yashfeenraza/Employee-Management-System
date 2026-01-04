#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Employee {
    long id;
    char name[50];
    char department[30];
    char designation[30];
    int joinDay;
    int joinMonth;
    int joinYear;
    double salary;
    char phone[15];
    char email[50];
};

struct Employee *employees = NULL;
int count = 0;
//generate employee id
long generateEmployeeID() {
    if(count == 0)
        return 1;
    else
        return employees[count - 1].id + 1;
}
//validate employees
int validateEmployeeData(struct Employee emp) {
    if(strlen(emp.name) == 0) {
        printf("Invalid name!\n");
        return 0;
    }

    if(emp.salary <= 0) {
        printf("Invalid salary!\n");
        return 0;
    }

    if(emp.joinDay < 1 || emp.joinDay > 31 ||
       emp.joinMonth < 1 || emp.joinMonth > 12 ||
       emp.joinYear < 1990) {
        printf("Invalid joining date!\n");
        return 0;
    }

    int digits = 0;
    for(int i = 0; emp.phone[i]; i++)
        if(emp.phone[i] >= '0' && emp.phone[i] <= '9')
         digits++;
    if(digits < 10) {
        printf("Invalid phone number!\n");
        return 0;
    }

    if(strchr(emp.email, '@') == NULL || strchr(emp.email, '.') == NULL) {
        printf("Invalid email!\n");
        return 0;
    }
    return 1;
}

//add employee
void addEmployee() {
    employees = realloc(employees, (count + 1) * sizeof(struct Employee));
    if(employees == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    employees[count].id = generateEmployeeID();
    printf("Generated Employee ID: %ld\n", employees[count].id);

    printf("Enter Name: ");
    scanf(" %[^\n]", employees[count].name);

    printf("Enter Department: ");
    scanf(" %[^\n]", employees[count].department);

    printf("Enter Designation: ");
    scanf(" %[^\n]", employees[count].designation);

    printf("Enter Joining Date (dd mm yyyy): ");
    scanf("%d %d %d", &employees[count].joinDay,
                      &employees[count].joinMonth,
                      &employees[count].joinYear);

    printf("Enter Salary: ");
    scanf("%lf", &employees[count].salary);

    printf("Enter Phone: ");
    scanf(" %[^\n]", employees[count].phone);

    printf("Enter Email: ");
    scanf(" %[^\n]", employees[count].email);

    if(validateEmployeeData(employees[count])) {
        count++;
        printf("\nEmployee Added Successfully!\n");
    } else {
        printf("\nEmployee Not Added (Invalid Data)\n");
    }
}

// calculate total salary
double calculateTotalSalary(struct Employee employees[], int count) {
    double total = 0;
    for(int i = 0; i < count; i++)
     total += employees[i].salary;
    return total;
}

//sort by salary bubble sort on salary
void sortEmployeesBySalary(struct Employee employees[], int count) {
    struct Employee temp;
    for(int i = 0; i < count - 1; i++){
        for(int j = i + 1; j < count; j++){
            if(employees[i].salary > employees[j].salary){
                temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }
    printf("\nEmployees Sorted by Salary.\n");
}

void printMenu() {
    printf("\n====== Employee Management System ======\n");
    printf("1.  Load From File\n");
    printf("2.  Add Employee\n");
    printf("3.  Search Employee\n");
    printf("4.  Update Employee\n");
    printf("5.  Delete Employee\n");
    printf("6.  Sort Employees by Salary\n");
    printf("7.  Calculate Total Salary\n");
    printf("8.  Calculate Average Salary\n");
    printf("9.  Display All Employees\n");
    printf("10. Save Employee Data to File\n");
    printf("11. Exit\n");
}

//average salary
double calculateAverageSalary(struct Employee employees[], int count) {
    if(count == 0)
     return 0;
    return calculateTotalSalary(employees, count) / count;
}

//save to file
//in write mode
void saveToFile(struct Employee employees[], int count) {
    FILE *fp = fopen("employees.txt","w");
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }

    for(int i = 0; i < count; i++){
        fprintf(fp,"%ld,%s,%s,%s,%d,%d,%d,%.2lf,%s,%s\n",
            employees[i].id, employees[i].name, employees[i].department, employees[i].designation,
            employees[i].joinDay, employees[i].joinMonth, employees[i].joinYear,
            employees[i].salary, employees[i].phone, employees[i].email);
    }
    fclose(fp);
    printf("Data saved successfully to employees.txt\n");
}

//search employee
void searchEmployee(struct Employee employees[], int count) {
    long id;
    printf("\nEnter Employee ID to Search: ");
    scanf("%ld",&id);

    for(int i = 0; i < count; i++){
        if(employees[i].id == id){
            printf("\nEmployee Found!\n");
            printf("ID: %ld\nName: %s\nDepartment: %s\nDesignation: %s\nJoining Date: %d-%d-%d\nSalary: %.2lf\nPhone: %s\nEmail: %s\n",
                employees[i].id, employees[i].name, employees[i].department, employees[i].designation,
                employees[i].joinDay, employees[i].joinMonth, employees[i].joinYear,
                employees[i].salary, employees[i].phone, employees[i].email);
            return;
        }
    }
    printf("\nEmployee NOT Found!\n");
}

//update employee
void updateEmployee(struct Employee employees[], int count) {
    long id;
    printf("\nEnter Employee ID to Update: ");
    scanf("%ld",&id);

    for(int i = 0; i < count; i++){
        if(employees[i].id == id){
            int choice;
            printf("\nWhat do you want to update?\n1.Name\n2.Department\n3.Designation\n4.Salary\n5.Phone\n6.Email\n");
            scanf("%d",&choice);

            switch(choice){
                case 1: 
                    printf("Enter New Name: "); 
                    scanf(" %[^\n]", employees[i].name); 
                    break;
                case 2: 
                    printf("Enter New Department: "); 
                    scanf(" %[^\n]", employees[i].department); 
                    break;
                case 3: 
                    printf("Enter New Designation: "); 
                    scanf(" %[^\n]", employees[i].designation); 
                    break;
                case 4: 
                    printf("Enter New Salary: "); 
                    scanf("%lf",&employees[i].salary); 
                    break;
                case 5: 
                    printf("Enter New Phone: "); 
                    scanf(" %[^\n]", employees[i].phone); 
                    break;
                case 6: 
                    printf("Enter New Email: ");
                     scanf(" %[^\n]", employees[i].email); 
                    break;
                default: 
                    printf("Invalid option!\n"); 
                    return;
            }

            printf("\nEmployee Updated Successfully!\n");
            return;
        }
    }
    printf("\nEmployee NOT Found!\n");
}

//delete employee
void deleteEmployee() {
    long id;
    int index = -1;

    printf("\nEnter Employee ID to Delete: ");
    scanf("%ld",&id);

    for(int i = 0; i < count; i++){
        if(employees[i].id == id){
            index = i;
            break;
        }
    }

    if(index == -1){
        printf("\nEmployee Not Found!\n"); 
        return;
    }

    for(int i = index; i < count - 1; i++) 
    employees[i] = employees[i + 1];

    count--;
    employees = realloc(employees, count * sizeof(struct Employee));

    printf("\nEmployee Deleted Successfully!\n");
}

//load from file
//read mode does reading from file
void loadFromFile() {
    FILE *fp = fopen("employees.txt", "r");
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    if (employees != NULL) {
        free(employees);
        employees = NULL;
        count = 0;
    }

    char line[300];
    while (fgets(line, sizeof(line), fp)) {
        employees = realloc(employees, (count + 1) * sizeof(struct Employee));
        if (employees == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }

        if (sscanf(line, "%ld,%49[^,],%29[^,],%29[^,],%d,%d,%d,%lf,%14[^,],%49[^\n]",
                   &employees[count].id, employees[count].name, employees[count].department,
                   employees[count].designation, &employees[count].joinDay, &employees[count].joinMonth,
                   &employees[count].joinYear, &employees[count].salary, employees[count].phone,
                   employees[count].email) != 10) {
            continue;
        }
        count++;
    }
    fclose(fp);
    printf("\nLoaded %d employees from file.\n", count);
}

//display all employee
void displayEmployees(struct Employee employees[], int count) {
    if(count == 0){
        printf("No employees to display.\n");
        return;
    }

    printf("\n===== Employee Records =====\n");
    for(int i = 0; i < count; i++){
        printf("ID: %ld | Name: %s | Dept: %s | Designation: %s | Date: %d-%d-%d | Salary: %.2lf | Phone: %s | Email: %s\n",
               employees[i].id, employees[i].name, employees[i].department,
               employees[i].designation, employees[i].joinDay, employees[i].joinMonth,
               employees[i].joinYear, employees[i].salary, employees[i].phone,
               employees[i].email);
    }
    printf("All employees displayed successfully.\n");
}

int main() {
    int choice;

    while(1){
        printMenu();
        printf("\nEnter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1: {
                char yes_no[5];
                printf("Warning: This will replace all existing data within this memory.\n");
                printf("Do you wish to continue? (yes/no): ");
                scanf(" %s", yes_no); 
                if(strcmp(yes_no, "yes") == 0){  
                    loadFromFile(); 
                } else {
                    printf("Loading from file is cancelled.\n");
                }
                break;
            }
            case 2: 
                addEmployee(); 
                break;
            case 3: 
                searchEmployee(employees, count); 
                break;
            case 4: 
                updateEmployee(employees, count); 
                break;
            case 5: 
                deleteEmployee(); 
                break;
            case 6: 
                sortEmployeesBySalary(employees, count); 
                break;
            case 7: 
                printf("\nTotal Salary = %.2lf\n", calculateTotalSalary(employees, count)); 
                break;
            case 8: 
                printf("\nAverage Salary = %.2lf\n", calculateAverageSalary(employees, count)); 
                break;
            case 9: 
                displayEmployees(employees, count); 
                break;
            case 10: 
                saveToFile(employees, count); 
                break;
            case 11:
                printf("\nExiting Program...\n");
                free(employees);
                return 0;

            default: 
                printf("\nInvalid Choice! Try Again.\n"); 
                break;
        }
    }
    return 0;
}