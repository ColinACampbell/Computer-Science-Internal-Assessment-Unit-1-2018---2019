#include <string.h>
#include <stdbool.h>
#include "models.h"
#define NEWLINE "\n"

// contains subscreens and functions used for 'dirty' work

void addStudents(FILE *);

// short hand code to flush buffer
void flushBuffer()
{
    fflush(stdin);
}

// method used to create class file

// return the pointer so it can be used by other methods
void createClass(char cName[60], char tName[40],char tPass[40])
{
    FILE *ptr;

    /**strcat(location,cName); // concatenate the string path to the file name
    strcat(location,".txt");
    strcpy(path,location);**/

    char *fileExtension = ".txt";

    strcat(cName,fileExtension);
    ptr = fopen(cName,"w");

    // Error handling
    if (ptr)
    {
        fprintf(ptr,"%s\t%s\n",tName,tPass); // put the user name and password at top of the file
        addStudents(ptr);
        printf("\nClass Created successfully");
        fclose(ptr);
    } else
    {
        printf(NEWLINE);
        perror("Error");
        printf(NEWLINE);
        exit(1);
    }
}

bool loginTeacher(char tName[40],char tPass[40],FILE *fp)
{
    // copied from removeClass function
    if (fp)
    {
        char readUsername[40];
        char readPassword[40];
        fscanf(fp,"%s\t%s\n",readUsername,readPassword);
        //fclose(fp); // close the pointer to the file so, the file can be deleted safely
        if (strcmp(readPassword,tPass) == 0 &&  // strcmp, or string compare, returns 0 if both strings are equal to each other
            strcmp(readUsername,tName) == 0)
        {
            return true;
        } else
        {
            printf("User name and/or password is incorrect");
            return false;
        }
    } else
    {
        return false;
    }
}

// Subscreen
void addStudents(FILE *fp)
{
    int size = 0;
    flushBuffer();
    printf("Please enter the amount of students that are in the class :");
    scanf("%d",&size);
    struct Student students[size];

    // Read students' information into an array
    for (int i = 0; i < size; i++)
    {
        int x = i + 1;
        printf("\nPlease enter student %d full name : ",x);
        flushBuffer();
        gets(students[i].fullName);

        printf("Please enter student %d Mathematics average grade : ",x);
        flushBuffer();
        scanf("%d",&students[i].mathGrade);

        printf("Please enter student %d English average grade : ",x);
        flushBuffer();
        scanf("%d",&students[i].engGrade);

        printf("Please enter student %d Physical Education average grade : ",x);
        flushBuffer();
        scanf("%d",&students[i].phyEdGrade);

        printf("Please enter student %d Integrated Science average grade : ",x);
        flushBuffer();
        scanf("%d",&students[i].inteSciGrade);
    }

    for ( int i = 0; i < size; i++)
    {
        fprintf(fp,"%s\t%d\t%d\t%d\t%d\n",students[i].fullName,students[i].mathGrade,students[i].engGrade,students[i].phyEdGrade,students[i].inteSciGrade);
    }
}

void addStudent()
{
    char tUsername[40];
    char tPass[40];
    char className[40];

    printf("\nPlease enter the class you'd like to add the student to : ");
    flushBuffer();
    gets(className);

    strcat(className,".txt"); // add .txt to the file extension
    FILE *fp = fopen(className,"r");

    printf("Please enter username : ");
    flushBuffer();
    gets(tUsername);

    printf("Please enter password : ");
    flushBuffer();
    gets(tPass);

    bool isLogged = loginTeacher(tUsername,tPass,fp);

    fp = fopen(className,"a"); // open the file again, it was closed in loginTeacher

    if (isLogged)
    {
        struct Student student;
        printf("\nPlease enter student full name : ");
        flushBuffer();
        gets(student.fullName);

        printf("Please enter student Mathematics average grade : ");
        flushBuffer();
        scanf("%d",&student.mathGrade);

        printf("Please enter student English average grade : ");
        flushBuffer();
        scanf("%d",&student.engGrade);

        printf("Please enter student Physical Education average grade : ");
        flushBuffer();
        scanf("%d",&student.phyEdGrade);

        printf("Please enter student Integrated Science average grade : ");
        flushBuffer();
        scanf("%d",&student.inteSciGrade);
        fprintf(fp,"%s\t%d\t%d\t%d\t%d\n",student.fullName,student.mathGrade,student.engGrade,student.phyEdGrade,student.inteSciGrade);
        fclose(fp);

        printf("Student added successfully\n");
    }
}

void removeStudent()
{
    char tUsername[40];
    char tPass[40];
    char className[40];
    char studentName[40];

    printf("\nPlease enter the class you'd like to add the student to : ");
    flushBuffer();
    gets(className);

    strcat(className,".txt"); // add .txt to the file extension
    FILE *fp = fopen(className,"r");

    printf("Please enter username : ");
    flushBuffer();
    gets(tUsername);

    printf("Please enter password : ");
    flushBuffer();
    gets(tPass);

    printf("Please enter student that you'd like to remove : ");
    flushBuffer();
    gets(studentName);

    struct Student students[100];

    bool isLogged = loginTeacher(tUsername,tPass,fp);

    if (isLogged)
    {
        int x = 1;
        int i = 0;

        struct Student student;

        while (x != EOF)
        {
            x = fscanf(fp,"%s\t%d\t%d\t%d\t%d\n",student.fullName,&student.mathGrade,&student.engGrade,&student.phyEdGrade,&student.inteSciGrade);
            printf("Name : %s, i = %d\n",student.fullName,i);

            strcpy(students[i].fullName,student.fullName);
            students[i].mathGrade = student.mathGrade;
            students[i].engGrade = student.engGrade;
            students[i].phyEdGrade = student.phyEdGrade;
            students[i].inteSciGrade = student.inteSciGrade;
            i++;
        }

        // close the pointer and remove the class
        fclose(fp);
        remove(className);
        int j = i;

        FILE *ptr = fopen(className,"w");
        fprintf(ptr,"%s\t%s\n",tUsername,tPass);

        int length = sizeof(students) / sizeof(students[0]);
        printf("\n j : %d",j);

        for (int i = 0; i < length; i++)
        {
            if ( strcmp(studentName,students[i].fullName) == 0)
                continue;
            else if ( i == j)
                break;

            fprintf(ptr,"%s\t%d\t%d\t%d\t%d\n",students[i].fullName,students[i].mathGrade,students[i].engGrade,students[i].phyEdGrade,students[i].inteSciGrade);
        }

    }
}
