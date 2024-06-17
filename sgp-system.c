#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define TRUE 1
#define TEMP_PERCENT 0.10
#define MID_PERCENT 0.30
#define FINAL_PERCENT 0.40
#define HOMEWORK_PERCENT 0.20

struct student {
    char id[10]; /*學號 */
    char name[10]; /*姓名 */
    double temp_score; /*平時考 */
    double homework_score; /*作業 */
    double mid_score; /*期中考分數 */
    double final_score; /*期末考分數 */
    struct student *next;
};

struct student *head, *prev, *current, *ptrnew;
FILE *fptr;
char fname[20];

void insert();
void del();
void query();
void modify();
void display();
double calaverage(struct student *);
void flushBuffer();
void rank();

int main() /**** Main function ****/
{
    char ch;
    head = (struct student *) malloc(sizeof(struct student));
    head->next = NULL;
    while (TRUE) {
        printf("\n*****************************************");
        printf("\n* Type 'i' to enter new student's data  *");
        printf("\n*      'd' to delete one student's data *");
        printf("\n*      'q' to query one student's data  *");
        printf("\n*      'm' to modify one student's data *");
        printf("\n*      'l' to list all students' data   *");
        printf("\n*      'e' to exit program and save     *");
        printf("\n*****************************************");
        printf("\nPlease enter your choice : ");

        ch = tolower(getche());
        switch (ch) {
            case 'i':
                insert();
                break;
            case 'd':
                del();
                break;
            case 'q':
                query();
                break;
            case 'm':
                modify();
                break;
            case 'l':
                display();
                break;
            case 'e':
                exit(0);
            default:
                printf("\nPlease select one choice !\n");
        }
    }
    system("PAUSE");
    return 0;
} /* End of main function */

 /**** Insert function ****/
void insert()
{
    ptrnew = (struct student *) malloc(sizeof(struct student));

    printf("\nEnter ID            : ");
    scanf("%s", ptrnew->id);
    printf("Enter Name          : ");
    scanf("%s", ptrnew->name);
    printf("Enter Temp Score    : ");
    scanf("%lf", &ptrnew->temp_score);
    printf("Enter Homework Score: ");
    scanf("%lf", &ptrnew->homework_score);
    printf("Enter Mid Score     : ");
    scanf("%lf", &ptrnew->mid_score);
    printf("Enter Final Score   : ");
    scanf("%lf", &ptrnew->final_score);

    /* insert algorithm */
    ptrnew->next = head->next;
    head->next = ptrnew;
    flushBuffer();
} /* End of function insert */


/**** Del function ****/
void del()
{
    char id[10];
    double average;
    printf("\nWhich student ID do you want to delete ? ");
    scanf("%s", id);
    prev = head;
    current = head->next;
    while (current != NULL && strcmp(current->id, id) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        printf("Data not found\n");
        return;
    }
    printf("\n\n學號       姓名        平時考    作業    期中考    期末考    平均分數");
    printf("\n-------------------------------------------------------------------------\n");
    printf("%-10s", current->id);
    printf(" %-10s", current->name);
    printf("  %-6.1f", current->temp_score);
    printf("    %-6.1f", current->homework_score);
    printf("  %-6.1f", current->mid_score);
    printf("    %-6.1f", current->final_score);
    average = calaverage(current);
    printf("    %-6.1f\n", average);
    printf("\nAre you sure to delete this record ? (Y/N) : ");
    flushBuffer(); // To clear the buffer before reading input
    if (toupper(getche()) == 'Y') {
        prev->next = current->next;
        free(current);
        printf("\nRecord deleted.\n");
    } else
        printf("\nRecord not deleted.\n");
} /* End of function del */

/**** Query function ****/
void query()
{
    char id[10];
    double average;
    printf("\nWhich student ID do you want to query  ? ");
    scanf("%s", id);
    current = head->next;
    while (current != NULL && strcmp(current->id, id))
        current = current->next;
    if (current == NULL) {
        printf("Data is not found\n");
        return;
    }
    printf("\n\n學號       姓名        平時考    作業    期中考    期末考    平均分數");
    printf("\n-------------------------------------------------------------------------\n");
    printf("%-10s", current->id);
    printf(" %-10s", current->name);
    printf("  %-6.1f", current->temp_score);
    printf("    %-6.1f", current->homework_score);
    printf("  %-6.1f", current->mid_score);
    printf("    %-6.1f", current->final_score);
    average = calaverage(current);
    printf("    %-6.1f\n", average);
} /* End of function query */


/**** Modify function ****/
void modify()
{
    char id[10];
    printf("\nWhich student ID do you want to modify ? ");
    scanf("%s", id);
    current = head->next;
    while (current != NULL && strcmp(current->id, id))
        current = current->next;
    if (current == NULL) {
        printf("Data is not found\n");
        return;
    }
    /* input new data */
    printf("\nEnter ID            : ");
    scanf("%s", current->id);
    printf("Enter Name          : ");
    scanf("%s", current->name);
    printf("Enter Temp Score    : ");
    scanf("%lf", &current->temp_score);
    printf("Enter Homework Score: ");
    scanf("%lf", &current->homework_score);
    printf("Enter Mid Score     : ");
    scanf("%lf", &current->mid_score);
    printf("Enter Final Score   : ");
    scanf("%lf", &current->final_score);
    flushBuffer(); // To clear the buffer after reading inputs
} /* End of function modify */


/**** Display function ****/
void display()
{
    double average;
    if (head->next == NULL)
        printf("\n list is empty\n");
    else {
        // Display rankings
        printf("\n\n排名   學號       姓名        平時考    作業    期中考    期末考    平均分數");
        printf("\n-------------------------------------------------------------------------\n");
        rank();
        current = head->next;
        int rank = 1;
        while (current != NULL) {
            printf(" %-6d", rank++);
            printf("%-10s", current->id);
            printf(" %-10s", current->name);
            printf("  %-6.1f", current->temp_score);
            printf("    %-6.1f", current->homework_score);
            printf("  %-6.1f", current->mid_score);
            printf("    %-6.1f", current->final_score);
            average = calaverage(current);
            printf("    %-6.1f\n", average);
            current = current->next;
        }
    }
} /* End of function display */

/**** Calaverage function ****/
double calaverage(struct student *current)
{
    double avg;
    avg = current->temp_score * TEMP_PERCENT +
          current->homework_score * HOMEWORK_PERCENT +
          current->mid_score * MID_PERCENT +
          current->final_score * FINAL_PERCENT;
    return avg;
} /* End of function calaverage */

/**** function function ****/
void flushBuffer()
{
    while (getchar() != '\n')
        continue;
} /* End of function flushBuffer */

/**** Rank function ****/
void rank()
{
    if (head->next == NULL) return;

    struct student *sorted = NULL;
    struct student *current = head->next;
    struct student *next;

    while (current != NULL) {
        next = current->next;
        if (sorted == NULL || calaverage(current) > calaverage(sorted)) {
            current->next = sorted;
            sorted = current;
        } else {
            struct student *tmp = sorted;
            while (tmp->next != NULL && calaverage(current) <= calaverage(tmp->next)) {
                tmp = tmp->next;
            }
            current->next = tmp->next;
            tmp->next = current;
        }
        current = next;
    }

    head->next = sorted;
} /* End of function rank */
