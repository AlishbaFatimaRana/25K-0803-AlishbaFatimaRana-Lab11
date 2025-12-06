#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRANSACTIONS 100

typedef struct {
    char type[20];        
    float amount;
    char date[20];         
} Transaction;

typedef struct {
    int accountNumber;
    char name[50];
    char accountType[20];
    float balance;

    float interestRate;
    float minBalance;

    char creationDate[20];
    char lastTransactionDate[20];

    Transaction history[MAX_TRANSACTIONS];
    int transactionCount;

} BankAccount;

void getCurrentDate(char *buffer) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(buffer, 20, "%d-%m-%Y", tm);
}

BankAccount createAccount() {
    BankAccount acc;

    printf("Enter account number: ");
    scanf("%d", &acc.accountNumber);

    printf("Enter name: ");
    scanf("%s", acc.name);

    printf("Select account type (Savings/Current/Fixed): ");
    scanf("%s", acc.accountType);

    if (strcmp(acc.accountType, "Savings") == 0) {
        acc.minBalance = 1000;
        acc.interestRate = 4;
    }
    else if (strcmp(acc.accountType, "Current") == 0) {
        acc.minBalance = 5000;
        acc.interestRate = 0;
    }
    else {
        acc.minBalance = 10000;
        acc.interestRate = 7;
    }

    printf("Enter initial deposit: ");
    scanf("%f", &acc.balance);

    if (acc.balance < acc.minBalance) {
        printf(" ERROR: Below minimum balance requirement!\n");
        exit(0);
    }

    getCurrentDate(acc.creationDate);
    strcpy(acc.lastTransactionDate, acc.creationDate);

    acc.transactionCount = 0;

    return acc;
}

void addTransaction(BankAccount *acc, char *type, float amount) {
    Transaction *t = &acc->history[acc->transactionCount++];

    strcpy(t->type, type);
    t->amount = amount;

    getCurrentDate(t->date);
    strcpy(acc->lastTransactionDate, t->date);
}

void deposit(BankAccount *acc) {
    float amt;
    printf("Enter deposit amount: ");
    scanf("%f", &amt);

    acc->balance += amt;
    addTransaction(acc, "Deposit", amt);

    printf("Deposit successful.\n");
}

void withdraw(BankAccount *acc) {
    float amt;
    printf("Enter withdrawal amount: ");
    scanf("%f", &amt);

    if (acc->balance - amt < acc->minBalance) {
        printf(" ERROR: Cannot go below minimum balance!\n");
        return;
    }

    acc->balance -= amt;
    addTransaction(acc, "Withdrawal", amt);

    printf("Withdrawal successful.\n");
}

void showAccount(BankAccount acc) {
    printf("\n--- ACCOUNT DETAILS ---\n");
    printf("Account Number: %d\n", acc.accountNumber);
    printf("Name: %s\n", acc.name);
    printf("Type: %s\n", acc.accountType);
    printf("Balance: %.2f\n", acc.balance);
    printf("Interest Rate: %.1f%%\n", acc.interestRate);
    printf("Created On: %s\n", acc.creationDate);
    printf("Last Transaction: %s\n", acc.lastTransactionDate);

    printf("\n--- TRANSACTION HISTORY ---\n");
    for (int i = 0; i < acc.transactionCount; i++) {
        printf("%s: %.2f on %s\n",
               acc.history[i].type,
               acc.history[i].amount,
               acc.history[i].date);
    }
}

int main() {
    BankAccount acc = createAccount();
    int choice;

    do {
        printf("\n1. Deposit\n2. Withdraw\n3. Show Details\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: deposit(&acc); break;
            case 2: withdraw(&acc); break;
            case 3: showAccount(acc); break;
            case 4: break;
        }

    } while (choice != 4);

    return 0;
}
