#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Member
{
    char name[50];
    float hours;
    float savings;
};

int main()
{
    int choice;
    float withdraw;
    float hoursAdded;
    float hoursUsed;
    float goal = 0.0f;
    char line[100];
    FILE *fp;

    struct Member user;

    user.hours = 0.0f;
    user.savings = 0.0f;

    printf("Enter Name: \n");
    scanf("%49s", user.name);

    printf("Welcome To The Neighborhood Time Bank\n");

    while (1)
    {
        printf("\n--- Main Menu ---\n");
        printf("1. Check Account Balance\n");
        printf("2. Deposit Service Hours\n");
        printf("3. Use Service Hours\n");
        printf("4. Savings & Budget Goal\n");
        printf("5. View Member Directory & Transactions\n");
        printf("6. Withdraw From Savings\n");
        printf("7. Exit\n");

        printf("Enter Choice: \n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("\nMember Name: %s\n", user.name);
                printf("Hours Available: %.2f\n", user.hours);
                printf("Savings: %.2f\n", user.savings);
                break;

            case 2:
                printf("Enter Hours Earned: ");
                scanf("%f", &hoursAdded);

                if (hoursAdded > 0)
                {
                    user.hours += hoursAdded;
                    user.savings += hoursAdded;

                    fp = fopen("transactions.txt", "a");
                    if (fp != NULL)
                    {
                        fprintf(fp, "%s deposited %.2f service hours\n", user.name, hoursAdded);
                        fclose(fp);
                    }

                    printf("Hours Added Successfully!\n");
                }
                else
                {
                    printf("Invalid Hours.\n");
                }
                break;

            case 3:
                printf("Enter Hours To Use: ");
                scanf("%f", &hoursUsed);

                if (hoursUsed > 0 && hoursUsed <= user.hours)
                {
                    user.hours -= hoursUsed;

                    fp = fopen("transactions.txt", "a");
                    if (fp != NULL)
                    {
                        fprintf(fp, "%s used %.2f service hours\n", user.name, hoursUsed);
                        fclose(fp);
                    }

                    printf("Hours Used Successfully!\n");
                }
                else
                {
                    printf("Not Enough Hours Available.\n");
                }
                break;

            case 4:
                printf("Current Savings: %.2f Hours\n", user.savings);
                printf("Enter a Savings Goal (in hours): ");
                scanf("%f", &goal);

                if (goal <= 0)
                {
                    printf("Invalid goal amount.\n");
                }
                else if (user.savings >= goal)
                {
                    printf("Congratulations! You have reached your goal of %.2f hours!\n", goal);
                }
                else
                {
                    printf("You need %.2f more hours to reach your goal of %.2f hours.\n",
                           goal - user.savings, goal);
                }
                break;

            case 5:
                fp = fopen("transactions.txt", "r");

                if (fp == NULL)
                {
                    printf("No transactions recorded yet.\n");
                }
                else
                {
                    printf("\n--- Member Directory & Transaction History ---\n");
                    while (fgets(line, sizeof(line), fp) != NULL)
                    {
                        printf("%s", line);
                    }
                    fclose(fp);
                }
                break;

            case 6:
                printf("Enter Hours To Withdraw From Savings: ");
                scanf("%f", &withdraw);

                if (withdraw > 0 && withdraw <= user.savings)
                {
                    user.savings -= withdraw;

                    fp = fopen("transactions.txt", "a");
                    if (fp != NULL)
                    {
                        fprintf(fp, "%s withdrew %.2f hours from savings\n", user.name, withdraw);
                        fclose(fp);
                    }

                    printf("Withdrawal Successful! Remaining Savings: %.2f Hours\n", user.savings);
                }
                else
                {
                    printf("Insufficient Savings or Invalid Amount.\n");
                }
                break;

            case 7:
                printf("Exiting. Thank you for using the Neighborhood Time Bank!\n");
                return 0;

            default:
                printf("Invalid choice. Please enter a number from 1 to 7.\n");
                break;
        }
    }

    return 0;
}