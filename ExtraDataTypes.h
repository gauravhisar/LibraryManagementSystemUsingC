//This header file is used in Libfunc.h header file

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

int Entries;
struct book_instance
{
    int sNo;
    char courseId[10];
    int BookId;
    char BookName[50];
    char Author[100];
    int totalcopies;
    int copiesAvailable;
    int rollno[30];
    int issuedate[30][3];  //3 col each for date month_number year
};

struct node  ///Node of a Binary Search Tree with key as Author, Searching will be fast when searched by author name
{
    struct book_instance data;
    struct node* left;
    struct node* right;
};
