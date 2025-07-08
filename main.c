#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

// Saare colours jo use honge
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

// Member ka structure
struct Member {
    char name[20];
    int batchNo;
    int rollNo;
};
//Society ka structure
struct Society {
    char society_name[20];
    int num_members;
    char society_field[10]; 
    struct Member members[100];
};
//Booking ka structure
struct Booking {
    char society_name[50];
    char venue[50];
    char date[15];         
    char startTime[6];      
    char endTime[6];        
};

// Venues jo book ho sakte hain
const char *venues[] = {
    "Auditorium", "Conference Hall", "Basketball Court", 
    "Badminton Court", "Sports Room", "A1", "B9", "C16", "D27", "E32"
};
const char* feilds[] = {
    "CS", "DS", "AI", "SE", "CY", "BA", "FT", "EE", "SP", "GL"
};
const int num_venues = 10;
// const int num_feilds = 10;

// saare use hone wale function
int society_check(const char *society_name) {
    struct Society society;
    FILE *file = fopen("societies.dat", "rb");
    if (!file) {
        return 0;
    }

    while (fread(&society, sizeof(struct Society), 1, file)) {
        if (strcmp(society.society_name, society_name) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0; 
}
void loader();
void exiting();
void add_new_society();
void one_society_data();
void delete_member();
void add_new_member();
void deleteSociety();
void delay(int milliseconds);
void clearScreen() {
        system("cls"); 
}
void all_society_data();
void suggest();
// Yeh yahn isliye rakha kyu keh neeche error de rha hai
int booking_check(const char *venue, const char *date, const char *startTime, const char *endTime) {
    struct Booking booking;
    FILE *file = fopen("bookings.dat", "rb");
    if (!file) {
        return 1; 
    }

    while (fread(&booking, sizeof(struct Booking), 1, file)) {
        if (strcmp(booking.venue, venue) == 0 && strcmp(booking.date, date) == 0) {
            // Phele booking check karne ki condition
            if ((strcmp(startTime, booking.endTime) < 0) && (strcmp(endTime, booking.startTime) > 0)) {
                fclose(file);
                return false; 
            }
        }
    }

    fclose(file);
    return true;
}
void addBooking();
void cancelBooking();
void viewAllBookings();
int time_check(const char *time);
int venu_check(const char *venue);
int feild_check(const char* feild);


int main() {
    int choice;
    int milliseconds = 900;
    while (1) {
        
        printf(GREEN "\n--- Society Management System ---\n" RESET);
        printf("1. Enter new societies and members data\n");
        printf("2. Delete Society\n");
        printf("3. View members of a specific society\n");
        printf("4. View Names of All Societies\n");
        printf("5. Suggest Societies based on field\n");
        printf("6. Delete a member from a society\n");
        printf("7. Add a new member to an existing society\n");
        printf("8. Book a Venue\n");
        printf("9. Cancel Booking\n");
        printf("10.View All Bookings\n");
        printf("11. Exit\n");
        printf(YELLOW "Enter your choice: " RESET);
        scanf("%d", &choice);
        clearScreen();
        switch (choice) {
            case 1:
                loader();
                add_new_society();
                break;
            case 2:
                loader();
                deleteSociety();
                break;
            case 3:
                loader();
                one_society_data();
                break;
            case 4:
                loader();
                all_society_data();
                
                break;
            case 5:
                loader();
                suggest();
                break;
            case 6:
                loader();
                delete_member();
                break;
            case 7:
                loader();
                add_new_member();
                break;
            case 8:
                loader();
                addBooking();
                break;
            case 9:
                loader();
                cancelBooking();
                break;
            case 10:
                loader();
                viewAllBookings();
                break;
            case 11:
                exiting();
                exit(0);
            default:
                printf(RED "Invalid choice! Please try again.\n" RESET);
        }
    }
    return 0;
}

void loader(){
    printf("\n");
    for (int i = 0; i < 10; i++)
    {
        printf(BLUE"."RESET);
        delay(50);
    }
    printf(BLUE"L"RESET);
    delay(50);
    printf(BLUE"O"RESET);
    delay(50);
    printf(BLUE"A"RESET);
    delay(50);
    printf(BLUE"D"RESET);
    delay(50);
    printf(BLUE"I"RESET);
    delay(50);
    printf(BLUE"N"RESET);
    delay(50);
    printf(BLUE"G"RESET);
    delay(50);
    for (int i = 0; i < 10; i++)
    {
        printf(BLUE"."RESET);
        delay(50);
    }
}
void exiting(){
    printf("\n");
    for (int i = 0; i < 10; i++)
    {
        printf(RED"."RESET);
        delay(50);
    }
    printf(RED"E"RESET);
    delay(50);
    printf(RED"X"RESET);
    delay(50);
    printf(RED"I"RESET);
    delay(50);
    printf(RED"T"RESET);
    delay(50);
    printf(RED"I"RESET);
    delay(50);
    printf(RED"N"RESET);
    delay(50);
    printf(RED"G"RESET);
    delay(50);
    for (int i = 0; i < 10; i++)
    {
        printf(RED"."RESET);
        delay(50);
    }
}
void delay(int milliseconds) {
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * CLOCKS_PER_SEC / 1000);

}
int feild_check(const char* feild){
    for (int i = 0; i < 10; i++) {
        if (strcmp(feild, feilds[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
// Saari society ke naam dekhne ke liye function
void all_society_data() {
    struct Society society;
    FILE *file = fopen("societies.dat", "rb");
    if (!file) {
        printf(RED "Error opening file for reading!\n" RESET);
        return;
    }

    while (fread(&society, sizeof(struct Society), 1, file)) {
        printf(GREEN "\nSociety: %s\n" RESET, society.society_name);
        printf("Number of Members: %d\n", society.num_members);
        printf("Relevant Field: %s\n", society.society_field);
    }

    fclose(file);
}

void add_new_society() {
    struct Society society;
    FILE *file = fopen("societies.dat", "ab");
    if (!file) {
        printf(RED "Error opening file for writing!\n" RESET);
        return;
    }

    printf(YELLOW "\nEnter Society Name: " RESET);
    scanf(" %[^\n]", society.society_name);
    for (int i = 0; i < strlen(society.society_name); i++) {
        if (!isalpha(society.society_name[i]) && society.society_name[i] != ' ') {
            printf(RED"Invalid Name!Name only have letters\n"RESET);
            return; 
        }
    }
    if (society_check(society.society_name)) {
        printf(RED "A society with this name already exists!\n" RESET);
        fclose(file);
        return;
    }

    printf(YELLOW "Enter relevant field (CS, DS, AI, SE, CY, BA, FT, EE, SP, GL): " RESET);
    scanf(" %[^\n]", society.society_field);
    if (!(feild_check(society.society_field))) {
        printf(RED "Invalid Feild! Please choose from the list above.\n" RESET);
        return;
    }

    // printf(YELLOW "Enter number of members: " RESET);
    // scanf("%d", &society.num_members);
    do {
        printf(YELLOW "Enter number of members (1-100): " RESET);
        if (scanf("%d", &society.num_members) != 1) {
            printf(RED "Invalid input! Please enter an integer.\n" RESET);
            while (getchar() != '\n'); // Clear the input buffer
            return;
        }
        if (society.num_members < 1 || society.num_members > 100) {
            printf(RED "Number of members must be between 1 and 100.\n" RESET);
        }
    } while (society.num_members < 1 || society.num_members > 100);
    
    for (int i = 0; i < society.num_members; i++) {
        printf(BLUE "\nMember %d:\n" RESET, i + 1);
        printf(YELLOW "  Name: " RESET);
        scanf(" %[^\n]", society.members[i].name);
        for (int j = 0; j < strlen(society.members[i].name); j++) {
            if (!isalpha(society.members[i].name[j]) && society.members[i].name[j] != ' ') {
                printf(RED"Invalid Name!Name only have letters\n"RESET);
                return; 
            }
        }
        printf(YELLOW "  Batch Number: " RESET);
        scanf("%d", &society.members[i].batchNo);
        printf(YELLOW "  Roll Number: " RESET);
        scanf("%d", &society.members[i].rollNo);
    }

    fwrite(&society, sizeof(struct Society), 1, file);
    printf(GREEN "\nData written successfully.\n" RESET);
    fclose(file);
}


// phele se mojood society ko delete karne ka function
void deleteSociety() {
    struct Society society;
    char *name = (char *)malloc(20 * sizeof(char));
    if (name==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    
    int found = 0;

    FILE *file = fopen("societies.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (!file || !tempFile) {
        printf(RED "Error opening files!\n" RESET);
        return;
    }

    printf(YELLOW "\nEnter the Society Name to delete: " RESET);
    scanf(" %[^\n]", name);

    while (fread(&society, sizeof(struct Society), 1, file)) {
        if (strcmp(society.society_name, name) != 0) {
            fwrite(&society, sizeof(struct Society), 1, tempFile);
        } else {
            found = 1; 
        }
    }

    if (found) {
        printf(GREEN "Society deleted successfully!\n" RESET);
    } else {
        printf(RED "Society not found.\n" RESET);
    }

    fclose(file);
    fclose(tempFile);
    remove("societies.dat");
    rename("temp.dat", "societies.dat");
    free(name);
}
// sirf kisi ek society ki details display karne ka function
void one_society_data() {
    struct Society society;
    char *name = (char *)malloc(20 * sizeof(char));
    if (name==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    FILE *file = fopen("societies.dat", "rb");
    if (!file) {
        printf(RED "Error opening file for reading!\n" RESET);
        return;
    }

    printf(YELLOW "\nEnter the Society Name to search: " RESET);
    scanf(" %[^\n]", name);

    int found = 0;
    while (fread(&society, sizeof(struct Society), 1, file)) {
        if (strcmp(society.society_name, name) == 0) {
            found = 1;
            printf(GREEN "\nSociety: %s\n" RESET, society.society_name);
            printf(GREEN "Number of Members: %d\n" RESET, society.num_members);
            printf(GREEN "Relevant Field: %s\n" RESET, society.society_field);
            for (int i = 0; i < society.num_members; i++) {
                printf(BLUE "\n  Member %d:\n" RESET, i + 1);
                printf("    Name: %s\n", society.members[i].name);
                printf("    Batch Number: %d\n", society.members[i].batchNo);
                printf("    Roll Number: %d\n", society.members[i].rollNo);
            }
        }
    }
    if (!found) {
        printf(RED "Society not found.\n" RESET);
    }
    fclose(file);
    free(name);
}
// Society suggest karne ke liye function
void suggest() {
    char *field = (char *)malloc(20 * sizeof(char));
    if (field==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    struct Society society;
    int found = 0;

    printf(YELLOW "\nEnter your field (CS, DS, AI, SE, CY, BA, FT, EE, SP, GL): " RESET);
    scanf(" %[^\n]", field);

    FILE *file = fopen("societies.dat", "rb");
    if (!file) {
        printf(RED "Error opening file for reading!\n" RESET);
        return;
    }

    printf(GREEN "\nSuggested Societies for %s:\n" RESET, field);
    while (fread(&society, sizeof(struct Society), 1, file)) {
        if (strcmp(society.society_field, field) == 0) {
            found = 1;
            printf("  - %s\n", society.society_name);
        }
    }

    if (!found) {
        printf(RED "No societies found for the field '%s'.\n" RESET, field);
    }

    fclose(file);
    free(field);
}
// phele se mojood society mai new member add karne ka function
void add_new_member() {
    struct Society society;
    char *name = (char *)malloc(20 * sizeof(char));
    if (name==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    int found = 0;
    FILE *file = fopen("societies.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (!file || !tempFile) {
        printf(RED "Error opening files!\n" RESET);
        return;
    }

    printf(YELLOW "\nEnter the Society Name to add a new member: " RESET);
    scanf(" %[^\n]",name);

    while (fread(&society, sizeof(struct Society), 1, file)) {
        if (strcmp(society.society_name, name) == 0) {
            found = 1;
            if (society.num_members < 100) {
                printf(YELLOW "Adding new member details:\n" RESET);
                printf(YELLOW "  Name: " RESET);
                scanf(" %[^\n]", society.members[society.num_members].name);
                for (int j = 0; j < strlen(society.members[society.num_members].name); j++) {
                    if (!isalpha(society.members[society.num_members].name[j]) && society.members[society.num_members].name[j] != ' ') {
                        printf(RED"Invalid Name!Name only have letters\n"RESET);
                        return; 
                    }
                }
                printf(YELLOW "  Batch Number: " RESET);
                scanf("%d", &society.members[society.num_members].batchNo);
                if (!(society.members[society.num_members].batchNo>= 20 && society.members[society.num_members].batchNo <= 24)) {
                    printf("\tInvalid batch no! Please enter a batch number between 20 and 24 only!\n");
                   return;
                }
                printf(YELLOW "  Roll Number: " RESET);
                scanf("%d", &society.members[society.num_members].rollNo);
                if (!(society.members[society.num_members].rollNo>1000 && society.members[society.num_members].rollNo<9999))
                {
                    printf("\tInvalid Roll no\n");
                    return;
                }
                society.num_members++;
                printf(GREEN "New member added successfully!\n" RESET);
            } else {
                printf(RED "Maximum member limit reached.\n" RESET);
            }
        }
        fwrite(&society, sizeof(struct Society), 1, tempFile);
    }

    if (!found) {
        printf(RED "Society not found.\n" RESET);
    }

    fclose(file);
    fclose(tempFile);
    remove("societies.dat");
    rename("temp.dat", "societies.dat");
    free(name);
}
// kisi existiing member ko delte karne ka function
void delete_member() {
    struct Society society;
    char *name = (char *)malloc(20 * sizeof(char));
    if (name==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    int rollNumberToDelete;
    int found = 0, memberFound = 0;
    FILE *file, *tempFile;

    file = fopen("societies.dat", "rb");
    tempFile = fopen("temp.dat", "wb");
    if (file == NULL || tempFile == NULL) {
        printf(RED "Error opening file!\n" RESET);
        return;
    }

    printf(YELLOW "\nEnter the Society Name to delete a member from: " RESET);
    scanf(" %[^\n]", name);

    while (fread(&society, sizeof(struct Society), 1, file)) {
        if (strcmp(society.society_name, name) == 0) {
            found = 1;
            printf(YELLOW "Enter the Roll Number of the member to delete: " RESET);
            scanf("%d", &rollNumberToDelete);

            // member uske roll no ke basis par delete hoga
            for (int i = 0; i < society.num_members; i++) {
                if (society.members[i].rollNo == rollNumberToDelete) {
                    memberFound = 1;
                    for (int j = i; j < society.num_members - 1; j++) {
                        society.members[j] = society.members[j + 1];
                    }
                    society.num_members--;
                    printf(GREEN "Member with Roll Number %d has been deleted.\n" RESET, rollNumberToDelete);
                    break;
                }
            }
        }

        fwrite(&society, sizeof(struct Society), 1, tempFile);
    }

    if (!found) {
        printf(RED "Society '%s' not found.\n" RESET, name);
    } else if (!memberFound) {
        printf(RED "Member with Roll Number %d not found.\n" RESET, rollNumberToDelete);
    }

    fclose(file);
    fclose(tempFile);

    remove("societies.dat");
    rename("temp.dat", "societies.dat");
    free(name);
}

// venue mojood hai yah nhi wo check karne ka function
int venu_check(const char *venue) {
    for (int i = 0; i < num_venues; i++) {
        if (strcmp(venue, venues[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int time_check(const char *time) {
    if (strlen(time) != 5 || time[2] != ':') {
        return 0;
    }
    int hour = (time[0] - '0') * 10 + (time[1] - '0');
    int minute = (time[3] - '0') * 10 + (time[4] - '0');
    return (hour >= 0 && hour < 24 && minute >= 0 && minute < 60);
}

// Booking ke liye function
void addBooking() {
    struct Booking booking;
    struct Society society;
    int societyExists = 0;
    char *venue = (char *)malloc(15 * sizeof(char));
    if (venue==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    FILE *societyFile = fopen("societies.dat", "rb");
    FILE *bookingFile = fopen("bookings.dat", "ab");
    if (!societyFile || bookingFile==NULL) {
        printf(RED "Error opening file\n" RESET);
        return;
    }
    printf(GREEN "\nAvailable Venues:\n" RESET);
    for (int i = 0; i < num_venues; i++) {
        printf("  - %s\n", venues[i]);
    }

    printf(YELLOW "\nEnter Society Name: " RESET);
    scanf(" %[^\n]", booking.society_name);

    while (fread(&society, sizeof(struct Society), 1, societyFile)) {
        if (strcmp(society.society_name, booking.society_name) == 0) {
            societyExists = 1;
            break;
        }
    }
    fclose(societyFile);

    if (!societyExists) {
        printf(RED "The society '%s' does not exist. Booking cannot be made.\n" RESET, booking.society_name);
        fclose(bookingFile);
        return;
    }

    printf(YELLOW "Enter Venue: " RESET);
    scanf(" %[^\n]", venue);

    if (!venu_check(venue)) {
        printf(RED "Invalid venue! Please choose from the list above.\n" RESET);
        fclose(bookingFile);
        return;
    }
    if ((strcmp(venue, "Basketball Court") == 0 || strcmp(venue, "Badminton Court") == 0 || strcmp(venue, "Sports Room") == 0) && strcmp(society.society_name, "Sportics") != 0) {
        printf(RED "You must be part of the 'Sportics' society to book the %s.\n" RESET, venue);
        return;
    }
    strcpy(booking.venue,venue);
    printf(YELLOW "Enter Date (YYYY-MM-DD): " RESET);
    scanf("%s", booking.date);

    printf(YELLOW "Enter Start Time (HH:MM): " RESET);
    scanf("%s", booking.startTime);

    if (!time_check(booking.startTime)) {
        printf(RED "Invalid start time format! Please use HH:MM (24-hour clock).\n" RESET);
        fclose(bookingFile);
        return;
    }

    printf(YELLOW "Enter End Time (HH:MM): " RESET);
    scanf("%s", booking.endTime);

    if (!time_check(booking.endTime)) {
        printf(RED "Invalid end time format! Please use HH:MM (24-hour clock).\n" RESET);
        fclose(bookingFile);
        return;
    }

    if (strcmp(booking.startTime, booking.endTime) >= 0) {
        printf(RED "End time must be later than start time.\n" RESET);
        fclose(bookingFile);
        return;
    }

    if (!booking_check(booking.venue, booking.date, booking.startTime, booking.endTime)) {
        printf(RED "This venue is already booked for the given date and time range.\n" RESET);
        fclose(bookingFile);
        return;
    }

    fwrite(&booking, sizeof(struct Booking), 1, bookingFile);
    printf(GREEN "Booking added successfully!\n" RESET);

    fclose(bookingFile);
    free(venue);
}

// Bookin cancel karne ka function
void cancelBooking() {
    struct Booking booking;
    char society_name[50];
    char *venue = (char *)malloc(15 * sizeof(char));
    char *date = (char *)malloc(11 * sizeof(char));
    char *start_time = (char *)malloc(6 * sizeof(char));
    if (venue==NULL || date==NULL || start_time==NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
    int found = 0;

    FILE *file = fopen("bookings.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (file==NULL || tempFile==NULL) {
        printf(RED "Error opening files\n" RESET);
        return;
    }

    printf(YELLOW "\nEnter Society Name: " RESET);
    scanf(" %[^\n]", society_name);

    printf(YELLOW "Enter Venue: " RESET);
    scanf(" %[^\n]", venue);

    printf(YELLOW "Enter Date (YYYY-MM-DD): " RESET);
    scanf("%s", date);

    printf(YELLOW "Enter Start Time (HH:MM): " RESET);
    scanf("%s", start_time);

    while (fread(&booking, sizeof(struct Booking), 1, file)) {
        
        if (strcmp(booking.society_name, society_name) == 0 &&
            strcmp(booking.venue, venue) == 0 &&
            strcmp(booking.date, date) == 0 &&
            strcmp(booking.startTime, start_time) == 0) {
            found = 1; 
            printf(GREEN "Booking canceled successfully!\n" RESET);
        } else {
            fwrite(&booking, sizeof(struct Booking), 1, tempFile);  
        }
    }

    if (!found) {
        printf(RED "No matching Booking.\n" RESET);
    }

    fclose(file);
    fclose(tempFile);

    remove("bookings.dat");
    rename("temp.dat", "bookings.dat");
}

// Booking view karne ka function
void viewAllBookings() {
    struct Booking booking;
    FILE *file = fopen("bookings.dat", "rb");
    if (!file) {
        printf(RED "No bookings found.\n" RESET);
        return;
    }

    printf(GREEN "\n--- All Bookings ---\n" RESET);
    while (fread(&booking, sizeof(struct Booking), 1, file)) {
        printf(YELLOW "\nSociety Name: %s\n" RESET, booking.society_name);
        printf("Venue: %s\n", booking.venue);
        printf("Date: %s\n", booking.date);
        printf("Time: %s - %s\n", booking.startTime,booking.endTime);
    }

    fclose(file);
}