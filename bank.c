#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    int accNumber;
    char name[50];
    float balance;
} Account;

Account accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Function to log transactions
void logTransaction(int accNo, char name[], const char* type, float amount) {
    FILE *fp = fopen("transactions.txt", "a");
    if (fp == NULL) {
        printf("Unable to open transaction log file.\n");
        return;
    }
    fprintf(fp, "Account: %d | Name: %s | Type: %s | Amount: %.2f\n", accNo, name, type, amount);
    fclose(fp);
}


// Create a new account
void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Account limit reached.\n");
        return;
    }
    Account *a = &accounts[accountCount++];
    printf("Enter account number: ");
    scanf("%d", &a->accNumber);
    printf("Enter account holder name: ");
    scanf("%s", a->name);
    a->balance = 0.0f;
    printf("Account created successfully!\n");
}

// Deposit amount
void deposit() {
    int num;
    float amt;
    printf("Enter account number: ");
    scanf("%d", &num);
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accNumber == num) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amt);
            accounts[i].balance += amt;
            logTransaction(accounts[i].accNumber, accounts[i].name, "Deposit", amt);
            printf("Deposit successful. New Balance: ₹%.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Account not found!\n");
}

// Withdraw amount
void withdrawMoney() {
    int num;
    float amt;
    printf("Enter account number: ");
    scanf("%d", &num);
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accNumber == num) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amt);
            if (accounts[i].balance >= amt) {
                accounts[i].balance -= amt;
                logTransaction(accounts[i].accNumber, accounts[i].name, "Withdraw", amt);
                printf("Withdrawal successful. New Balance: ₹%.2f\n", accounts[i].balance);
            } else {
                printf("Insufficient balance!\n");
            }
            return;
        }
    }
    printf("Account not found!\n");
}

// Check balance
void checkBalance() {
    int num;
    printf("Enter account number: ");
    scanf("%d", &num);
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accNumber == num) {
            printf("Account Holder: %s\nBalance: ₹%.2f\n", accounts[i].name, accounts[i].balance);
            return;
        }
    }
    printf("Account not found!\n");
}

// View transaction history
void viewTransactionHistory() {
    char line[200];
    FILE *fp = fopen("transactions.txt", "r");
    if (fp == NULL) {
        printf("No transaction history found.\n");
        return;
    }
    printf("\n--- Transaction History ---\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

// Main menu
int main() {
    int choice;
    do {
        printf("\n=== Bank Management System ===\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Check Balance\n");
        printf("5. View Transaction History\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: viewTransactionHistory(); break;
            case 6: printf("Thank you for using the Bank Management System!\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}
