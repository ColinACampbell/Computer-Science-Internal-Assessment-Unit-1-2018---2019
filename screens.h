#include "utils.h"
#define NEWLINE "\n"

extern FILE *ptr;

int menu()
{
    int option = 0;

    printf("Please chose the number that corresponds with the actions you will like to commit :");
    printf(NEWLINE);
    printf("1) Add a class.");
    printf(NEWLINE);
    printf("2) Remove a class");
    printf(NEWLINE);
    printf("3) Get a class report");
    printf(NEWLINE);
    printf("4) Manage class");
    printf(NEWLINE);
    printf("5) Undecided");
    printf(NEWLINE);

    flushBuffer();// flush out the buffer so it wont overflow fresh values
    printf("What do wish to do : ");
    scanf("%d",&option);

    return option;
}

void addClass()
{
    char cName[40]; // class name
    char tName[40]; // teacher's name
    char tPass[40]; // teacher's password

    printf(NEWLINE);
    printf("|\t|\t|\t|\t Add Class \t|\t|\t|\t|");
    printf(NEWLINE);

    printf("Please enter the class's name : ");
    flushBuffer();
    gets(cName);

    printf("Please enter username : ");
    flushBuffer();
    gets(tName);

    printf("Please enter password for the class : ");
    flushBuffer();
    gets(tPass);

    createClass(cName,tName,tPass);
}

void removeClass()
{
    char className[40];
    char tUsername[40];
    char tPassword[40];
    // TODO finish up this method
    printf("Please enter the name of the class you'd like to  delete : ");
    flushBuffer();
    gets(className);

    strcat(className,".txt");
    // open file to read line by line
    FILE *fp; // fp : file pointer
    fp = fopen(className,"r");
    if (!fp)
    {
        printf("Class %s, not found",className);
        fclose(fp);
        return; // exit the function if fp is null
    }

    printf("Please enter username : ");
    flushBuffer();
    gets(tUsername);

    printf("Please enter password for class : ");
    flushBuffer();
    gets(tPassword);


    if (fp)
    {
        char readUsername[40];
        char readPassword[40];
        fscanf(fp,"%s\t%s",readUsername,readPassword);
        fclose(fp); // close the pointer to the file so, the file can be deleted safely
        if (strcmp(readPassword,tPassword) == 0 &&  // strcmp, or string compare, returns 0 if both strings are equal to each other
            strcmp(readUsername,tUsername) == 0)
        {
            int status = remove(className);
            printf("Status : %d",status);
        } else
            printf("User name and/or password is incorrect");
    } else
    {
        printf("File %s, not found\n",className);
    }

}

void getClassRpt()
{
    char tUsername[40];
    char tPassword[40];
    char className[40];

    printf(NEWLINE);
    printf("|\t|\t|\t|\t Class Report \t|\t|\t|\t|");
    printf(NEWLINE);
    printf(NEWLINE);

    printf("Please enter class you'd like to get report from : ");
    flushBuffer();
    gets(className);

    strcat(className,".txt");
    FILE *fp = fopen(className,"r");

    printf("Please enter usename : ");
    flushBuffer();
    gets(tUsername);

    printf("Please enter password : ");
    flushBuffer();
    gets(tPassword);

    bool isLogged = loginTeacher(tUsername,tPassword,fp);

    struct Student students[100];

    if (isLogged)
    {
        // read scan student information to the file
        int x = 0;
        int i = 0;

        char heighestAverageStudent[40];
        int heighestAverage = 0;

        char heighestEngStudent[40];
        int heighestEng = 0;

        char heighestPhysEdStudent[40];
        int heighestPhyEd = 0;

        char heighestMathStudent[40];
        int heighestMath = 0;

        char heighestInteSciStudent[40];
        int heighestInteSci = 0;

        while (x != EOF)
        {
            struct Student student;
            x = fscanf(fp,"%s\t%d\t%d\t%d\t%d\n",student.fullName,&student.mathGrade,&student.engGrade,&student.phyEdGrade,&student.inteSciGrade);
            //printf("Name : %s, i = %d\n",student.fullName,i);

            strcpy(students[i].fullName,student.fullName);
            students[i].mathGrade = student.mathGrade;
            students[i].engGrade = student.engGrade;
            students[i].phyEdGrade = student.phyEdGrade;
            students[i].inteSciGrade = student.inteSciGrade;

            // calculate the heighest scores
            if (students[i].mathGrade > heighestMath)
            {
                heighestMath = students[i].mathGrade;
                strcpy(heighestMathStudent,students[i].fullName);
            }

            if (students[i].engGrade > heighestEng)
            {
                heighestEng = students[i].engGrade;
                strcpy(heighestEngStudent,students[i].fullName);
            }

            if (students[i].phyEdGrade > heighestPhyEd)
            {
                heighestPhyEd = students[i].phyEdGrade;
                strcpy(heighestPhysEdStudent,students[i].fullName);
            }

            if (students[i].inteSciGrade > heighestInteSci)
            {
                heighestInteSci = students[i].inteSciGrade;
                strcpy(heighestInteSciStudent,students[i].fullName);
            }

            i++;
        }

        i = i-1;
        int j = 0;
        printf("\nStudent Name/Math Average Grade/English Average Grade/Integrated Science Average Grade/Physical Education Average Grade/Overall Average\n");
        while ( j < i)
        {
            int averageGrade = (students[j].mathGrade + students[j].engGrade + students[j].inteSciGrade + students[j].phyEdGrade)/4;
            printf("%s\t %d \t %d \t %d\t %d\t %d\n",students[j].fullName,students[j].mathGrade,students[j].engGrade,students[j].inteSciGrade,students[j].phyEdGrade,averageGrade);
            j++;
        }

        printf("\nHeighest average in mathematics %d, %s\n",heighestMath,heighestMathStudent);
        printf("Heighest average in english %d, %s\n",heighestEng,heighestEngStudent);
        printf("Heighest average in integrated science %d, %s\n",heighestInteSci,heighestInteSciStudent);
        printf("Heighest average in physical education %d, %s\n",heighestPhyEd,heighestPhysEdStudent);

    }

}

void mngClass()
{
    int option = 0;

    printf(NEWLINE);
    printf("|\t|\t|\t|\t Manage Class \t|\t|\t|\t|");
    printf(NEWLINE);
    printf(NEWLINE);

    printf("Please chose the number that corresponds with the actions you will like to commit :");
    printf(NEWLINE);
    printf(NEWLINE);

    printf("1) Add Students to a class.");
    printf(NEWLINE);

    printf("2) Remove Student from a class.");
    printf(NEWLINE);

    printf("\nWhat would like to do : ");
    scanf("%d",&option);

    if (option == 1)
        addStudents_Abstract(); // subscreen
    else if(option == 2)
        removeStudent(); // subscreen
    else
    {
        printf("The value you entered is not recognised");
        printf(NEWLINE);
        return;
    }
}


