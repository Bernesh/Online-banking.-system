#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 10

struct Account {
    char username[50];
    char password[50];
    double balance;
};

struct Account accounts[MAX_ACCOUNTS];
int numAccounts = 0;

void createAccount() {
    if (numAccounts < MAX_ACCOUNTS) {
        struct Account newAccount;

        printf("Enter username: ");
        scanf("%s", newAccount.username);

        printf("Enter password: ");
        scanf("%s", newAccount.password);

        newAccount.balance = 0.0;

        accounts[numAccounts] = newAccount;
        numAccounts++;

        printf("Account created successfully!\n");
    } else {
        printf("Cannot create more accounts. Limit reached.\n");
    }
}

int login() {
    char inputUsername[50];
    char inputPassword[50];

    printf("Enter username: ");
    scanf("%s", inputUsername);

    printf("Enter password: ");
    scanf("%s", inputPassword);

    for (int i = 0; i < numAccounts; i++) {
        if (strcmp(inputUsername, accounts[i].username) == 0 && strcmp(inputPassword, accounts[i].password) == 0) {
            return i; // Return the index of the logged-in account
        }
    }

    return -1; // Login failed
}

void displayMenu() {
    printf("\n1. View Balance\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. Logout\n");
}

void viewBalance(struct Account* account) {
    printf("\nBalance: $%.2f\n", account->balance);
}

void deposit(struct Account* account, double amount) {
    account->balance += amount;
    printf("\nDeposit successful. New balance: $%.2f\n", account->balance);
}

void withdraw(struct Account* account, double amount) {
    if (amount > account->balance) {
        printf("\nInsufficient funds\n");
    } else {
        account->balance -= amount;
        printf("\nWithdrawal successful. New balance: $%.2f\n", account->balance);
    }
}

int main() {
    int loggedInIndex = -1;

    while (1) {
        if (loggedInIndex == -1) {
            int choice;
            printf("\n1. Create Account\n");
            printf("2. Login\n");
            printf("3. Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    loggedInIndex = login();
                    if (loggedInIndex == -1) {
                        printf("Login failed. Invalid credentials.\n");
                    } else {
                        printf("Login successful!\n");
                    }
                    break;
                case 3:
                    printf("Goodbye!\n");
                    exit(0);
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } else {
            int choice;
            displayMenu();
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    viewBalance(&accounts[loggedInIndex]);
                    break;
                case 2: {
                    double amount;
                    printf("Enter deposit amount: $");
                    scanf("%lf", &amount);
                    deposit(&accounts[loggedInIndex], amount);
                    break;
                }
                case 3: {
                    double amount;
                    printf("Enter withdrawal amount: $");
                    scanf("%lf", &amount);
                    withdraw(&accounts[loggedInIndex], amount);
                    break;
                }
                case 4:
                    printf("Logout successful. Goodbye!\n");
                    loggedInIndex = -1;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }

    return 0;
}