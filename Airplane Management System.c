#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<conio.h>

// Structure for flight booking info
struct booking
{
    char flight_name[40];
    char passenger_name[50];
    char date[20];
    char seat_class[15];
    char user_id[15];
};

// Function declarations
void perform_booking(struct booking);
int get_input();
void print_menu();
void aboutAirline();
void book_flight();
void check_booking();
void cancel_booking();
void add_booking();
void generate_ticket(struct booking b);
void display_flight();
void view_all_bookings();
void convert_to_lowercase(char str[]);
int id_exists(char id[]);
void generate_id(char id[]);
void trim(char *str);

int main()
{
    srand(time(NULL)); // produces  new user ids everytime
    int choice;

    while (1)
    {
        system("cls");
        printf("\n========= Welcome To Air Reservation System =========\n\n");
        print_menu();

        printf("Enter your choice: ");
        choice = get_input();

        switch (choice)
        {
        case 1:
            aboutAirline();
            break;
        case 2:
            book_flight();
            break;
        case 3:
            check_booking();
            break;
        case 4:
            cancel_booking();
            break;
        case 5:
            display_flight();
            printf("\nPress Enter to return to menu...");
            getchar();
            break;
        case 6:
            view_all_bookings();
            break;
        case 7:
            printf("\nThank you for using our system! Goodbye!\n");
            return 0;
        default:
            printf("\nInvalid choice! Please enter a number between 1-7.\n");
            printf("Press Enter to continue...");
            getchar();
        }
    }

    return 0;
}

// Print menu options
void print_menu()
{
    printf("1. About Our Airline\n");
    printf("2. Book A Flight\n");
    printf("3. View Your Booking\n");
    printf("4. Cancel Your Booking\n");
    printf("5. Display Available Flights\n");
    printf("6. View All Booked Flights\n");
    printf("7. Exit\n\n");
}

int get_input()
{
    int num;
    scanf("%d", &num);
    getchar(); // clear leftover newline
    return num;
}

void convert_to_lowercase(char str[])
{
    for (int i = 0; str[i]; ++i)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

void aboutAirline()
{
    printf("\n--------------------------------------------------\n");
    printf("               ABOUT THE AIRLINE                 \n");
    printf("--------------------------------------------------\n");
    printf("Airline Name        : Emirates Airline\n");
    printf("Airline Code        : EA\n");
    printf("Founded Year        : 2025\n");
    printf("Headquarters        : Karachi, Pakistan\n");
    printf("Main Hub            : Jinnah International Airport (KHI)\n");
    printf("Destinations Served : Over 50 Domestic & International\n");
    printf("Fleet Size          : Around 30 aircraft\n");
    printf("Slogan              : 'FLY BETTER'\n");
    printf("--------------------------------------------------\n");
    printf("Press Enter to return to the main menu...");
    getchar();
}

void book_flight()
{
    printf("\n------------- Book A Flight -------------\n\n");
    printf("Welcome To The Flight Booking Section\n");
    printf("You Can Add A New Booking And Generate Your Ticket.\n\n");

    add_booking();
    printf("\nFlight Booking Completed Successfully.\n");
    printf("Press Enter to return to the main menu...");
    getchar();
}

void add_booking()
{
    struct booking newbooking;

    printf("------------- Add Booking -------------\n\n");

    int choice;
    int valid_choice = 0;

    display_flight();

    // Loop until a valid flight number is entered
    while (!valid_choice)
    {
        printf("\nEnter the Number of Flight You Want To Book: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number between 1-6.\n");
            while (getchar() != '\n')
                ; // clear input buffer
            continue;
        }
        getchar(); // remove leftover newline

        switch (choice)
        {
        case 1:
            strcpy(newbooking.flight_name, "EK201 - Dubai to London");
            valid_choice = 1;
            break;
        case 2:
            strcpy(newbooking.flight_name, "EL101 - Karachi to Dubai");
            valid_choice = 1;
            break;
        case 3:
            strcpy(newbooking.flight_name, "LH505 - Singapore to America");
            valid_choice = 1;
            break;
        case 4:
            strcpy(newbooking.flight_name, "MH727 - Doha to New York");
            valid_choice = 1;
            break;
        case 5:
            strcpy(newbooking.flight_name, "E8202 - London to Delhi");
            valid_choice = 1;
            break;
        case 6:
            strcpy(newbooking.flight_name, "FE506 - Islamabad to Germany");
            valid_choice = 1;
            break;
        default:
            printf("Invalid flight number! Please choose between 1-6.\n");
        }
    }

    // Passenger name
    printf("Enter Passenger Name: ");
    fgets(newbooking.passenger_name, sizeof(newbooking.passenger_name), stdin);
    trim(newbooking.passenger_name); // remove extra spaces

    // to block numbers and special characters in name
    for (int i = 0; newbooking.passenger_name[i] != '\0'; i++)
    {

        char c = newbooking.passenger_name[i];

        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ')))
        {
            printf("Name Cannot Contain Special Characters Or Number!\nPlease Enter Again:");
            fgets(newbooking.passenger_name, sizeof(newbooking.passenger_name), stdin);
            trim(newbooking.passenger_name);
            i=-1; // restart checking from beginning
        }
    }

    // Date input
    while (1)
    {
        printf("Enter Date (DD/MM/YYYY): ");
        fgets(newbooking.date, sizeof(newbooking.date), stdin);
        trim(newbooking.date); // remove spaces/newlines

        int day, month, year;
        if (sscanf(newbooking.date, "%d/%d/%d", &day, &month, &year) != 3)
        {
            printf("Invalid Date Format! Use DD/MM/YYYY\n");
            continue;
        }
        // validates date
        if (day < 1 || day > 31 || month < 1 || month > 12)
        {
            printf("Invalid Day or Month! Day must be 1-31, Month 1-12\n");
            continue;
        }

        //  validate year
        if (year < 2025 || year > 2100)
        {
            printf("Invalid Year! Year must be 2025-2100\n");
            continue;
        }

        break;
    }

    // Seat class
    while (1)
    {
        printf("Enter Seat Class (Economy/Business/First Class): ");
        fgets(newbooking.seat_class, sizeof(newbooking.seat_class), stdin);
        trim(newbooking.seat_class);

        char temp[15];
        strcpy(temp, newbooking.seat_class);
        convert_to_lowercase(temp);

        // validates seat class
        if (strcmp(temp, "economy") == 0 || strcmp(temp, "business") == 0 || strcmp(temp, "first class") == 0)
            break;

        printf("Invalid Seat Class! Please Enter Business, Economy, or First Class.\n");
    }

    generate_id(newbooking.user_id); // generates unique user id

    printf("\n------- Booking Summary --------\n");
    printf("User ID        : %s\n", newbooking.user_id);
    printf("Flight Name    : %s\n", newbooking.flight_name);
    printf("Passenger Name : %s\n", newbooking.passenger_name);
    printf("Date           : %s\n", newbooking.date);
    printf("Seat Class     : %s\n", newbooking.seat_class);

    perform_booking(newbooking);
    printf("Booking Successfully Added!\n");

    generate_ticket(newbooking);
}

void generate_ticket(struct booking b)
{
    printf("\n----------------------------------------\n");
    printf("           AIRLINE TICKET               \n");
    printf("----------------------------------------\n");
    printf("User ID        : %s\n", b.user_id);
    printf("Flight Name    : %s\n", b.flight_name);
    printf("Passenger Name : %s\n", b.passenger_name);
    printf("Date           : %s\n", b.date);
    printf("Seat Class     : %s\n", b.seat_class);
    printf("Status         : Confirmed\n");
    printf("----------------------------------------\n");
    printf("Have A Safe Journey!\n");

    FILE *fp = fopen("ticket.txt", "a");
    if (fp != NULL)
    {
        fprintf(fp, "----------------------------------------\n");
        fprintf(fp, "           AIRLINE TICKET               \n");
        fprintf(fp, "----------------------------------------\n");
        fprintf(fp, "User ID        : %s\n", b.user_id);
        fprintf(fp, "Flight Name    : %s\n", b.flight_name);
        fprintf(fp, "Passenger Name : %s\n", b.passenger_name);
        fprintf(fp, "Date           : %s\n", b.date);
        fprintf(fp, "Seat Class     : %s\n", b.seat_class);
        fprintf(fp, "Status         : Confirmed\n");
        fprintf(fp, "----------------------------------------\n\n");
        fclose(fp);
    }
}

void perform_booking(struct booking record)
{
    FILE *my_file = fopen("flight_booking.txt", "a");
    if (my_file == NULL)
    {
        printf("\nError: Cannot Perform Booking!\n");
        return;
    }

    fprintf(my_file, "%s, %s, %s, %s, %s\n",
            record.user_id,
            record.passenger_name,
            record.flight_name,
            record.date,
            record.seat_class);

    fclose(my_file);
}

// generates a unique user id for ticket
void generate_id(char id[])
{
    do
    {
        int num = rand() % 9000 + 1000;
        sprintf(id, "USR%d", num);
    } while (id_exists(id));
}

// Checks if the generated user id is unique or not
int id_exists(char id[])
{
    FILE *file = fopen("flight_booking.txt", "r");
    if (!file)
        return 0; // If the file does not exist then the id is unique

    char line[200];
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, id))
        {
            fclose(file);
            return 1; // already exists
        }
    }
    fclose(file);
    return 0; // unique
}

void check_booking()
{
    printf("\n------------- View Your Booking -------------\n\n");

    FILE *file = fopen("flight_booking.txt", "r");
    if (file == NULL)
    {
        printf("No booking records found yet!\n");
        printf("Press Enter to return to the main menu...");
        getchar();
        return;
    }

    char search_id[20];
    char search_name[50];
    char line[300];
    int found = 0;

    printf("Enter User ID: ");
    fgets(search_id, sizeof(search_id), stdin);
    search_id[strcspn(search_id, "\n")] = 0;

    printf("Enter Passenger Name: ");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = 0;

    // Convert name to lowercase for case-insensitive matching
    char lower_search_name[50];
    strcpy(lower_search_name, search_name);
    convert_to_lowercase(lower_search_name);

    while (fgets(line, sizeof(line), file))
    {

        // Make a copy of line to check name in lowercase
        char lower_line[300];
        strcpy(lower_line, line);
        convert_to_lowercase(lower_line);

        // Check IF BOTH ID and name match
        if (strstr(line, search_id) && strstr(lower_line, lower_search_name))
        {
            printf("\nBooking Found!\n");
            printf("----------------------------------------\n");
            printf("%s", line);
            printf("Status : Confirmed\n");
            printf("----------------------------------------\n");
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nNo booking found matching BOTH User ID '%s' AND Name '%s'\n",
               search_id, search_name);
    }

    printf("Press Enter to return to the main menu...");
    getchar();
}

void cancel_booking()
{
    FILE *f = fopen("flight_booking.txt", "r");
    if (f == NULL)
    {
        printf("No bookings found!\n");
        printf("Press Enter to return...");
        getchar();
        return;
    }

    char search_id[20], search_name[50];
    char line[300];
    int found = 0;

    printf("Enter User ID to cancel: ");
    fgets(search_id, sizeof(search_id), stdin);
    trim(search_id); // Trim spaces and newlines

    printf("Enter Passenger Name to confirm: ");
    fgets(search_name, sizeof(search_name), stdin);
    trim(search_name); // Trim spaces and newlines

    // Lowercase name for comparison
    char lower_search_name[50];
    strcpy(lower_search_name, search_name);
    convert_to_lowercase(lower_search_name);

    FILE *temp = fopen("temp.txt", "w");

    while (fgets(line, sizeof(line), f))
    {
        char line_copy[300];
        strcpy(line_copy, line);
        trim(line_copy);

        char lower_line[300];
        strcpy(lower_line, line_copy);
        convert_to_lowercase(lower_line);

        int id_match = strstr(line_copy, search_id) != NULL;
        int name_match = strstr(lower_line, lower_search_name) != NULL;

        if (id_match && name_match)
        {
            found = 1; // Skip writing to delete
            continue;
        }

        fputs(line, temp); // Write other lines
    }

    fclose(f);
    fclose(temp);

    remove("flight_booking.txt");
    rename("temp.txt", "flight_booking.txt");

    if (found)
    {
        printf("\nBooking successfully cancelled.\n");
        printf("User ID : %s\n", search_id);
        printf("Name    : %s\n", search_name);
    }
    else
    {
        printf("\nNo booking found matching BOTH:\n");
        printf("User ID : %s\n", search_id);
        printf("Name    : %s\n", search_name);
    }

    printf("Press Enter to return...");
    getchar();
}

void display_flight()
{
    printf("\n--- AVAILABLE FLIGHTS ---\n");
    printf("No.\tFlight Name\tRoute\t\t\tTime\n");
    printf("-----------------------------------------------------------\n");
    printf("1.\tEK201\t\tDubai - London\t\t10:00 AM\n");
    printf("2.\tEL101\t\tKarachi - Dubai\t\t08:00 AM\n");
    printf("3.\tLH505\t\tSingapore - America\t09:45 PM\n");
    printf("4.\tMH727\t\tDoha - New York\t\t03:00 PM\n");
    printf("5.\tE8202\t\tLondon - Delhi\t\t07:20 AM\n");
    printf("6.\tFE506\t\tIslamabad - Germany\t04:45 PM\n");
    printf("-----------------------------------------------------------\n");
}

// Show all bookings in the file
void view_all_bookings()
{
    FILE *f = fopen("flight_booking.txt", "r");
    if (f == NULL)
    {
        printf("\nNo bookings available!\n");
        printf("Press Enter to return...");
        getchar();
        return;
    }

    char line[300];
    int count = 0;

    printf("\n================= ALL BOOKED FLIGHTS =================\n");
    printf("No.\tUser ID\t\tPassenger Name\tFlight\t\tDate\t\tSeat Class\n");
    printf("--------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), f))
    {
        count++;
        printf("%d.\t%s", count, line); // line already has commas separating fields
    }

    if (count == 0)
    {
        printf("No bookings yet!\n");
    }

    fclose(f);
    printf("--------------------------------------------------------------------------\n");
    printf("Press Enter to return...");
    getchar();
}

void trim(char *str)
{
    // Remove trailing spaces/newlines first
    int len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\n' || str[len - 1] == '\r'))
    {
        str[len - 1] = '\0';
        len--;
    }

    // Remove leading spaces by shifting the string
    int start = 0;
    while (str[start] == ' ')
        start++;

    if (start > 0)
    {
        int i = 0;
        while (str[start + i] != '\0')
        {
            str[i] = str[start + i];
            i++;
        }
        str[i] = '\0';
    }
}
