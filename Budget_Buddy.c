#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_FILE "users.txt"
#define EXPENSE_FILE "expenses.txt"

struct User
{
    char username[30];
    char password[30];
};

struct Expense
{
    char username[30];
    char category[30];
    char description[100];
    float amount;
};

void register_user()
{
    struct User u;
    FILE *fp;

    fp = fopen(USER_FILE, "a");

    printf("Enter Username: ");
    scanf("%s", u.username);

    printf("Enter Password: ");
    scanf("%s", u.password);

    fprintf(fp, "%s %s\n", u.username, u.password);

    fclose(fp);

    printf("User Registered Successfully\n");
}

int login(char username[])
{
    struct User u;
    char user[30], pass[30];
    FILE *fp;

    printf("Username: ");
    scanf("%s", user);

    printf("Password: ");
    scanf("%s", pass);

    fp = fopen(USER_FILE, "r");

    while (fscanf(fp, "%s %s", u.username, u.password) != EOF)
    {
        if (strcmp(user, u.username) == 0 &&
            strcmp(pass, u.password) == 0)
        {
            strcpy(username, user);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void add_expense(char username[])
{
    struct Expense e;
    FILE *fp;

    fp = fopen(EXPENSE_FILE, "a");

    strcpy(e.username, username);

    printf("Enter Category (Food/Travel/Bills/Shopping): ");
    scanf("%s", e.category);

    printf("Enter Description: ");
    scanf(" %[^\n]", e.description);

    printf("Enter Amount: ");
    scanf("%f", &e.amount);

    fprintf(fp, "%s %s %s %.2f\n",
            e.username,
            e.category,
            e.description,
            e.amount);

    fclose(fp);

    printf("Expense Added\n");
}

void view_my_expenses(char username[])
{
    struct Expense e;
    FILE *fp;
    float total = 0;

    fp = fopen(EXPENSE_FILE, "r");

    printf("\nYour Expenses\n");

    while (fscanf(fp, "%s %s %s %f",
                  e.username,
                  e.category,
                  e.description,
                  &e.amount) != EOF)
    {
        if (strcmp(e.username, username) == 0)
        {
            printf("%s | %s | %.2f\n",
                   e.category,
                   e.description,
                   e.amount);

            total += e.amount;
        }
    }

    printf("Total = %.2f\n", total);

    fclose(fp);
}

void family_report()
{
    struct Expense e;
    FILE *fp;
    float total = 0;

    fp = fopen(EXPENSE_FILE, "r");

    printf("\nFamily Expenses\n");

    while (fscanf(fp, "%s %s %s %f",
                  e.username,
                  e.category,
                  e.description,
                  &e.amount) != EOF)
    {
        printf("%s | %s | %s | %.2f\n",
               e.username,
               e.category,
               e.description,
               e.amount);

        total += e.amount;
    }

    printf("Total Family Expense = %.2f\n", total);

    fclose(fp);
}

void category_report()
{
    struct Expense e;
    FILE *fp;

    float food = 0, travel = 0, bills = 0, shopping = 0;

    fp = fopen(EXPENSE_FILE, "r");

    while (fscanf(fp, "%s %s %s %f",
                  e.username,
                  e.category,
                  e.description,
                  &e.amount) != EOF)
    {
        if (strcmp(e.category, "Food") == 0)
            food += e.amount;

        else if (strcmp(e.category, "Travel") == 0)
            travel += e.amount;

        else if (strcmp(e.category, "Bills") == 0)
            bills += e.amount;

        else if (strcmp(e.category, "Shopping") == 0)
            shopping += e.amount;
    }

    fclose(fp);

    printf("\nCategory Report\n");
    printf("Food = %.2f\n", food);
    printf("Travel = %.2f\n", travel);
    printf("Bills = %.2f\n", bills);
    printf("Shopping = %.2f\n", shopping);
}

void user_menu(char username[])
{
    int choice;

    while (1)
    {
        printf("\nWelcome %s\n", username);

        printf("1 Add Expense\n");
        printf("2 View My Expenses\n");
        printf("3 Logout\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            add_expense(username);

        else if (choice == 2)
            view_my_expenses(username);

        else if (choice == 3)
            return;

        else
            printf("Invalid Choice\n");
    }
}

int main()
{
    int choice;
    char username[30];

    while (1)
    {
        printf("\n====== BUDGET BUDDY ======\n");

        printf("1 Register\n");
        printf("2 Login\n");
        printf("3 Family Report\n");
        printf("4 Category Report\n");
        printf("5 Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            register_user();
            break;

        case 2:
            if (login(username))
            {
                printf("Login Successful\n");
                user_menu(username);
            }
            else
            {
                printf("Invalid Login\n");
            }
            break;

        case 3:
            family_report();
            break;

        case 4:
            category_report();
            break;

        case 5:
            exit(0);

        default:
            printf("Invalid Choice\n");
        }
    }

    return 0;
}
