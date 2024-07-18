#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[200];
    char phone[20];
    int age;
    char place_of_birth[200];
    char account_type[200];
    float Balance;
} Client;

void Making_account(const char* name) {
    Client take_information;
    FILE* fp = fopen(name, "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Enter your ID: ");
    scanf("%d", &take_information.id);

    printf("Enter your age: ");
    scanf("%d", &take_information.age);
    getchar(); 

    printf("Enter your name: ");
    fgets(take_information.name, sizeof(take_information.name), stdin);
    take_information.name[strcspn(take_information.name, "\n")] = '\0'; 
    
    printf("Enter your phone number: ");
    fgets(take_information.phone, sizeof(take_information.phone), stdin);
    take_information.phone[strcspn(take_information.phone, "\n")] = '\0'; 

    printf("Enter place of birth: ");
    fgets(take_information.place_of_birth, sizeof(take_information.place_of_birth), stdin);
    take_information.place_of_birth[strcspn(take_information.place_of_birth, "\n")] = '\0'; 

    printf("Enter your account type: ");
    fgets(take_information.account_type, sizeof(take_information.account_type), stdin);
    take_information.account_type[strcspn(take_information.account_type, "\n")] = '\0'; 
    take_information.Balance=0.00,
    fprintf(fp, "ID: %d\n", take_information.id);
    fprintf(fp, "Name: %s\n", take_information.name);
    fprintf(fp, "Phone: %s\n", take_information.phone);
    fprintf(fp, "Age: %d\n", take_information.age);
    fprintf(fp, "Place of Birth: %s\n", take_information.place_of_birth);
    fprintf(fp, "Account Type: %s\n", take_information.account_type);
    fprintf(fp, "The balance: %s\n", take_information.Balance);

    fclose(fp);
    printf("Account information saved successfully.\n");
}

void account_details(const char* name) {
    char display[200];
    FILE* fp = fopen(name, "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (fgets(display, sizeof(display), fp) != NULL) {
        printf("%s", display);
    }

    fclose(fp);
}

void Correction_of_account_information(const char* name) {
    char line_deletes[100];
    char buffer[100];
    char option;

    printf("How can we help you?\nA - Delete\nB - Add\n");
    option = getchar();
    getchar();  

    if (option == 'a' || option == 'A') {
        printf("Please enter the information to delete:\n");
        fgets(line_deletes, sizeof(line_deletes), stdin);
        line_deletes[strcspn(line_deletes, "\n")] = '\0';

        FILE *fp = fopen(name, "r");
        if (fp == NULL) {
            printf("Error opening file.\n");
            return;
        }

        FILE *tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            printf("Could not open temporary file.\n");
            fclose(fp);
            return;
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            if (strstr(buffer, line_deletes) == NULL) {
                fputs(buffer, tempFile);
            }
        }

        fclose(fp);
        fclose(tempFile);

        remove(name);
        rename("temp.txt", name);

        printf("Information deleted successfully.\n");

    } else if (option == 'b' || option == 'B') {
        char add_information[100];

        printf("Enter the information you want to add:\n");
        fgets(add_information, sizeof(add_information), stdin);
        add_information[strcspn(add_information, "\n")] = '\0';

        FILE *fp = fopen(name, "a");
        if (fp == NULL) {
            printf("Error opening file.\n");
            return;
        }

        fprintf(fp, "%s\n", add_information);
        fclose(fp);

        printf("Information added successfully.\n");

    } else {
        printf("Invalid option selected.\n");
    }
}
void service(char* name){
     Client balanc;
    float add_balance;
    char option;
    printf("How we can help you\nA-Withdraw balance\nB-Deposit balance\n:");
    scanf("%c",&option);
    if(option == 'a'|| option == 'A'){
        printf("Enter the amount of the withdrawal balance");
        scanf("%f",&add_balance);
        FILE *fp = fopen(name, "a");
        if (fp == NULL) {
            printf("Error opening file.\n");
            return;
        }
        fprintf(fp, "-%f\n", add_balance);
        fclose(fp);
  
    }else if(option == 'b'|| option == 'B'){
        printf("Enter the value of the added balance");
        scanf("%f",&add_balance);
        FILE *fp = fopen(name, "a");
        if (fp == NULL) {
            printf("Error opening file.\n");
            return;
        }
        fprintf(fp, "+%f\n", add_balance);
        fclose(fp);

    }


}

int main() {
    char name[50];
    char option;

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0'; 

    printf("Welcome %s to our BOA. How can we help you?\nA - Make a new account\nB - See account details\nC - Correct account information\nD - Service\n", name);
    option = getchar();
    getchar();

    if (option == 'a' || option == 'A') {
        Making_account(name);
    } else if (option == 'b' || option == 'B') {
        account_details(name);
    } else if (option == 'c' || option == 'C') {
        Correction_of_account_information(name);
    } 
     else if (option == 'D' || option == 'd') {
        service(name);
    }else {
        printf("Invalid option selected.\n");
    }

    return 0;
}

