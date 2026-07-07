#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accno;
    float balance;
    char name[100];
    char status[20];
};

// CREATE ACCOUNT
void createAccount() {
    FILE *fp = fopen("Accounts.txt", "a");
    struct Account a;

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Account No, Balance, Name, Status:\n");
    scanf("%d %f %s %s", &a.accno, &a.balance, a.name, a.status);

    fprintf(fp, "%d %.2f %s %s\n", a.accno, a.balance, a.name, a.status);

    printf("Account created successfully!\n");
    fclose(fp);
}

// CHECK STATUS
void checkStatus() {
    FILE *fp = fopen("Accounts.txt", "r");
    struct Account a;
    int acc, found = 0;

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &acc);

    while (fscanf(fp, "%d %f %s %s", &a.accno, &a.balance, a.name, a.status) != EOF) {
        if (a.accno == acc) {
            printf("Status: %s\n", a.status);
            found = 1;
            break;
        }
    }

    if (!found) printf("Account not found!\n");

    fclose(fp);
}

// DEPOSIT
void deposit() {
    FILE *fp = fopen("Accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Account a;
    int acc, found = 0;
    float amount;

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &acc);

    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    while (fscanf(fp, "%d %f %s %s", &a.accno, &a.balance, a.name, a.status) != EOF) {
        if (a.accno == acc) {
            a.balance += amount;
            found = 1;
        }
        fprintf(temp, "%d %.2f %s %s\n", a.accno, a.balance, a.name, a.status);
    }

    fclose(fp);
    fclose(temp);

    remove("Accounts.txt");
    rename("temp.txt", "Accounts.txt");

    if (found)
        printf("Amount deposited successfully!\n");
    else
        printf("Account not found!\n");
}

// WITHDRAW
void withdraw() {
    FILE *fp = fopen("Accounts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct Account a;
    int acc, found = 0;
    float amount;

    if (fp == NULL || temp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &acc);

    printf("Enter withdrawal amount: ");
    scanf("%f", &amount);

    while (fscanf(fp, "%d %f %s %s", &a.accno, &a.balance, a.name, a.status) != EOF) {
        if (a.accno == acc) {
            found = 1;
            if (a.balance >= amount) {
                a.balance -= amount;
            } else {
                printf("Insufficient balance!\n");
            }
        }
        fprintf(temp, "%d %.2f %s %s\n", a.accno, a.balance, a.name, a.status);
    }

    fclose(fp);
    fclose(temp);

    remove("Accounts.txt");
    rename("temp.txt", "Accounts.txt");

    if (found)
        printf("Transaction completed!\n");
    else
        printf("Account not found!\n");
}

// CHECK BALANCE
void checkBalance() {
    FILE *fp = fopen("Accounts.txt", "r");
    struct Account a;
    int acc, found = 0;

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &acc);

    while (fscanf(fp, "%d %f %s %s", &a.accno, &a.balance, a.name, a.status) != EOF) {
        if (a.accno == acc) {
            printf("Balance: %.2f\n", a.balance);
            found = 1;
            break;
        }
    }

    if (!found) printf("Account not found!\n");

    fclose(fp);
}

// MAIN FUNCTION
int main() {
    int choice;

    while (1) {
        printf("\n--- BANK MANAGEMENT SYSTEM ---\n");
        printf("1. Create Account\n");
        printf("2. Check Status\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Check Balance\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: checkStatus(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: checkBalance(); break;
            case 6:
                printf("Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}
