/*** 	This program uses assert() in checking
	whether a certain value is observed.
	This is a way to make sure if your have
	correct values for your variables.
***/

// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WHO_LEN 15
#define WHAT_LEN 20
#define WHEN_LEN 14
#define WHERE_LEN 20
#define MAX_REC 10

// The record type
typedef struct {
    char who[WHO_LEN];
    char what[WHAT_LEN];
    char when[WHEN_LEN];
    char where[WHERE_LEN];
}Record;

/** These are the function prototypes **/

void ReadFromFile (Record *, int *, char *);
int menu(void);
void EnterRecord (Record *, int *);
void ViewDay (Record [], int);
void ViewWeek (Record *, int);
void Modify (Record *, int);
void Delete (Record *, int *);
void Search (Record *, int);
void Quit (Record *, int, char *);

// Start of a main program
int main (void)
{
    Record AppBook[MAX_REC];
    int quit = 0, choice, count=0;
    char fileName[WHO_LEN];

    ReadFromFile (AppBook, &count, fileName);
    printf("%d records read from file\n", count);

    while (! quit) {
        choice = menu();  // get a choice
        switch (choice) { // process according to the choice
            case 1: EnterRecord(AppBook, &count);
                    break;
            case 2: ViewDay(AppBook, count);
                    break;
            case 3: ViewWeek(AppBook, count);
                    break;
            case 4: Modify(AppBook, count);
                    break;
            case 5: Delete(AppBook, &count);
                    break;
            case 6: Search(AppBook, count);
                    break;
            case 9: Quit(AppBook, count, fileName);
                    quit = 1;
                    break;
            default: printf("Please enter a choice 1-6 or 9 to quit\n");
        }
    }
}

void ReadFromFile (Record * Book, int * count, char buff[])
{
    FILE * filePointer;
    int i;

    printf("ReadFromFile -- ask the file name from user");
    printf(" and process the file\n");
    printf(" count is %d\n", * count);

    printf("Please enter a file name to open/save: ");
    scanf("%s", buff);

    printf("Opening file: %s ....\n", buff);
    if( (filePointer = fopen(buff,"r")) == NULL)
        return;
    else
        while (fgets(Book[*count].who, WHO_LEN, filePointer) != NULL) {
            Book[*count].who[strlen(Book[*count].who)-1] = '\0';
            fgets(Book[*count].what, WHAT_LEN, filePointer);
            Book[*count].what[strlen(Book[*count].what)-1] = '\0';
            fgets(Book[*count].when, WHEN_LEN, filePointer);
            Book[*count].when[strlen(Book[*count].when)-1] = '\0';
            fgets(Book[*count].where, WHERE_LEN, filePointer);
            Book[*count].where[strlen(Book[*count].where)-1] = '\0';
            (* count) ++ ;
        }
    assert(*count < MAX_REC); // to check if count is within the size

// echo print
    for (i = 0 ; i < *count ; ++i) {
        printf("Who: %s\n", Book[i].who);
        printf("What: %s\n", Book[i].what);
        printf("When: %s\n", Book[i].when);
        printf("Where: %s\n", Book[i].where);
    }
}

int menu(void)
{
    int pick;

    printf("***************************************\n");
    printf("*      Appointment Book Services      *\n");
    printf("*      -------------------------      *\n");
    printf("*   1. Enter Record       4. Modify   *\n");
    printf("*   2. View Day           5. Delete   *\n");
    printf("*   3. View Week          6. Search   *\n");
    printf("*   9. Quit                           *\n");
    printf("***************************************\n");
    printf("\nPlease enter a choice:");

    scanf("%d", &pick); // get a choice from the user
    getchar();

    return pick; // pass the value back
}

void EnterRecord (Record Book[], int * count)
{
    int i;  // for proof printing only;

    (*count) ++ ;
    printf("%d",*count);

    printf("\nEnterRecord -- to enter the who/what/when/where\n");
    printf("Please enter WHOM you have an appointment with: ");
    gets(Book[*count].who);
    printf("Please enter WHAT the event is: ");
    gets(Book[*count].what);
    printf("Please enter WHEN (yyyymmddhhmm): ");
    gets(Book[*count].when);
    printf("Please enter WHERE you have an appointment at: ");
    gets(Book[*count].where);

    printf("%d",*count);

// to check if count is within the size
    assert(*count < MAX_REC);
//check if who is within the size
    assert(strlen(Book[*count-1].who) <= WHO_LEN);
//check if what is within the size
    assert(strlen(Book[*count-1].what) <= WHAT_LEN);
//check if when is within the size
    assert(strlen(Book[*count-1].when) <= WHEN_LEN);
//check if where is within the size
    assert(strlen(Book[*count-1].where) <= WHERE_LEN);

// these lines below are for testing only
    for (i = 0 ; i < *count ; ++i) {
        printf("Who: %s\n", Book[i].who);
        printf("What: %s\n", Book[i].what);
        printf("When: %s\n", Book[i].when);
        printf("Where: %s\n", Book[i].where);
     }

}

void ViewDay (Record Book[], int count)
{
    char date[WHEN_LEN];
    int i = 0;

    printf("\nViewDay -- to show the appointments of a given day\n");
    printf("Please enter the day (yyyymmdd) to view: ");
    scanf ("%s", date);

    while (i<count && (strncmp(date, Book[i].when,strlen(date)) != 0))
        ++ i;

    if (i < count) {
        printf("Who: %s\n", Book[i].who);
        printf("What: %s\n", Book[i].what);
        printf("When: %s\n", Book[i].when);
        printf("Where: %s\n", Book[i].where);
    }

    return ;
}

void ViewWeek (Record Book [], int count)
{
    printf("\nViewWeek -- to show the appintments of a given week\n");
}

void Modify (Record Book [], int count)
{
    printf("\nModify -- to modify a record\n");
}

void Delete (Record Book [], int * count)
{
    printf("\nDelete --  to delete a record\n");
}

void Search (Record Book [], int count)
{
    printf("\nSearch --- to search a record by one of when/what/who/where\n");
}

void Quit (Record Book [], int count, char fileName[])
{
    int i;
    FILE * fp;

    printf("\nQuit --- It saves the current records ");
    printf("to the file and terminates the program.\n");

    printf("Saving to file: %s ... \n", fileName);
    fp = fopen ( fileName, "w");
    for (i = 0; i<count; ++i)
        fprintf(fp, "%s\n%s\n%s\n%s\n", Book[i].who,
                                        Book[i].what,
                                        Book[i].when,
                                        Book[i].where );
}

