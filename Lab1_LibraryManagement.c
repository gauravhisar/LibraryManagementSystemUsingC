#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include"Libfunc.h" //Self-made Header File Containing all the Functions that I used in this Project

void main()
{
    struct node* root = NULL;
    static char* fname = "LibRec.txt"; //storing filename
    root = store_data(fname,root);

    root = implement_Library(root);// Lets Start Managing our Library

    //All the changes made in our library will be stored again in our file
    FILE* fpt = fopen(fname,"w");
    char res[10];
    sprintf(res, "%d", Entries);
    fputs(res, fpt);
    putc('\n', fpt);
    fputs("sNo;courseId;BookId;BookName;Author;totalcopies;copiesAvailable;rollno;issuedate;",fpt);
    fclose(fpt);
    writeRecords(fname, root);
}


/*

addbook()
{
    if newbook then search that book by its bookname and author in your library if that book already exists then increase the number of copies otherwise enter all its details and make a new entry,

    else if returning an existing book then enter its BookId and rollno and show fine imposed on that rollno, then remove the rollno and remove the issuedate corresponding to the student who issued the book
}*/
