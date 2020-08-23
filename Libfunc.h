#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include"ExtraDataTypes.h"
#include"datetime.h"

//Primary Functions
struct node* store_data(char* fname,struct node*);
struct node* add_instanceData(struct node* root,struct book_instance temp);
struct node* implement_Library(struct node* root);
void writeRecords(char* fname , struct node* root);

//Main Useful Functions
struct node* addbook(struct node* root);
struct node* takebook(struct node* root);
struct node* searchBook(struct node* root);
struct node* searchBk(struct node* root, char author[], char bookname[]);
struct node* search_BookId(struct node* root, int BukId);
void display_records(struct node* root); //display all the books in the library
void display_details(struct node* root); // display details of a book passed as parameter
int TotalBooks(struct node* root);

//Auxiliary Functions
void getstring(char* str);
void resettoZero(int num[], int n);
int getInt(int num[], int n);//converts array of single digit numbers into an integer
void pop_array(int A[],int n, int i);
void popRow(int A[][3], int n, int i);



struct node* implement_Library(struct node* root)
{
    char* adminpass = "IAmAdmin";
    int admin = 1, action = 1;
    char pass[20];
    while(admin)
    {
        action = 1;
        printf("Press 1-administrator 2-otherwise 0-exit : ");
        fflush(stdin);
        scanf("%d",&admin);
        if(admin==1)//administrator
        {
            printf("Enter administrator password :");
            fflush(stdin);
            getstring(pass);
            if(strcmp(pass,adminpass)==0)
            {
                printf(" Admin Login Successful\n");
                while(action)
                {
                    int flag;
                    printf("1-addbook; 2-Takebook; 3-searchBook 4-dislplayRecords 5-TotalBooksInLibrary 0-exit: ");
                    fflush(stdin);
                    scanf("%d",&action);
                    switch(action)
                    {
                        case 1:
                            root = addbook(root);
                            break;
                        case 2:
                            root = takebook(root);
                            break;
                        case 3:
                            printf("Press 1-BookId search  2-Author/BookName Search: ");
                            fflush(stdin);
                            scanf("%d",&flag);
                            if(flag == 1)
                            {
                                int ID;
                                printf("Enter BookId: ");
                                fflush(stdin);
                                scanf("%d",&ID);
                                display_details(search_BookId(root, ID));
                            }
                            else
                            {
                                searchBook(root);
                            }
                            break;
                        case 4:
                            display_records(root);
                            break;
                        case 5:
                            printf("Total Books In the Library: %d\n",TotalBooks(root));
                            break;
                        default:
                            break;
                    }
                }
            }
            else
            {
                printf("Wrong Password! Please Try Again\n");
            }
        }
        else if(admin == 2)//student
        {
            action = 1;
            printf("Guest Login\n");
            while(action)
            {
                int flag;
                printf("Press 1-SearchBook 2-displayRecords 3-TotalBooksInLibrary  0-exit: ");
                fflush(stdin);
                scanf("%d",&action);
                switch(action)
                {
                    case 1:
                        printf("Press 1-BookId search  2-Author/BookName Search: ");
                        fflush(stdin);
                        scanf("%d",&flag);
                        if(flag == 1)
                        {
                            int ID;
                            printf("Enter BookId: ");
                            fflush(stdin);
                            scanf("%d",&ID);
                            display_details(search_BookId(root, ID));
                        }
                        else
                        {
                            searchBook(root);
                        }
                        break;
                    case 2:
                        display_records(root);
                        break;
                    case 3:
                        printf("Total Books Registered in the Library: %d\n",TotalBooks(root));
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return root;
}
void display_records(struct node* root)
{
    if(root!=NULL)
    {
        display_details(root);
        display_records(root->left);
        display_records(root->right);
    }
}
void display_details(struct node* root)
{
    if(root==NULL)
    {
        printf("Book Not Found!\n");
        return;
    }
    int t,a;
    t = root->data.totalcopies;
    a = root->data.copiesAvailable;
    printf("%d  %s  %d    %s   %s   TotalCopies=%d   CopiesAvailable=%d   ",root->data.sNo,root->data.courseId,root->data.BookId,root->data.BookName,root->data.Author,root->data.totalcopies,root->data.copiesAvailable);
    if(t-a!=0)
    {
        printf("StudentsWhoIssued-%d",root->data.rollno[0]);
        for(int j =1;j<t-a;j++)
        {
            printf(",%d",root->data.rollno[j]);
        }
        printf("  RespectiveIssueDate-%d/%d/%d",root->data.issuedate[0][0],root->data.issuedate[0][1],root->data.issuedate[0][2]);
        for(int j =1;j<t-a;j++)
        {
            printf(",%d",root->data.issuedate[j][0]);
            for(int k=1;k<3;k++)
            {
                printf("/%d",root->data.issuedate[j][k]);
            }
        }
    }
    printf("\n");
}
struct node* store_data(char* fname, struct node* root)
{
    FILE *fp;
    fp = fopen(fname, "r");
    struct book_instance temp;

    //first store number of entries
    int num[10];
    char ch = fgetc(fp);
    int i = 0,k,l;
    while(ch != '\t' && ch != '\n' && ch != ' ')
    {
        num[i] = ch - '0';
        i++;
        ch = fgetc(fp);
    }
    Entries = getInt(num,i);

     //parsing schema
    ch = fgetc(fp);
    while(ch!='\n')
    {
        ch = fgetc(fp);
    }

    //now store all the Entries
    while(ch != EOF)
    {
        temp.Author[0] = '\0';
        temp.BookName[0] ='\0';
        temp.courseId[0] = '\0';
        resettoZero(num, 10);
        int j = 0;

        //storing serial number
        ch = fgetc(fp);
        while(ch != ';')
        {
            num[j] = ch - '0';
            j++;
            ch = fgetc(fp);
        }
        temp.sNo = getInt(num,j);


        //storing course name
        ch = fgetc(fp);
        j = 0;
        while(ch!=';')
        {
            temp.courseId[j] = ch;
            j++;
            ch = fgetc(fp);
        }
        temp.courseId[j] = '\0';

        //storing BookId
        resettoZero(num, 10);
        ch = fgetc(fp);
        j=0;
        while(ch!=';')
        {
            num[j] = ch - '0';
            j++;
            ch = fgetc(fp);
        }
        temp.BookId = getInt(num,j);

        //storing BookName
        ch = fgetc(fp);
        j=0;
        while(ch!=';')
        {
            temp.BookName[j] = ch;
            j++;
            ch = fgetc(fp);
        }
        temp.BookName[j] = '\0';

        //storing AuthorName
        ch = fgetc(fp);
        j=0;
        while(ch!=';')
        {
            temp.Author[j] = ch;
            j++;
            ch = fgetc(fp);
        }
        temp.Author[j] = '\0';

        //storing TotalCopies
        resettoZero(num, 10);
        ch = fgetc(fp);
        j=0;
        while(ch!=';')
        {
            num[j] = ch - '0';
            j++;
            ch = fgetc(fp);
        }
        temp.totalcopies = getInt(num,j);

        //storing copiesAvailable
        resettoZero(num, 10);
        ch = fgetc(fp);
        j=0;
        while(ch!=';')
        {
            num[j] = ch - '0';
            j++;
            ch = fgetc(fp);
        }
        temp.copiesAvailable = getInt(num,j);

        //storing rollnos who issued the book
        ch = fgetc(fp);
        k=0;
        while(ch!=';')
        {
            j = 0;
            resettoZero(num, 10);
            while(ch != ',' && ch!=';')
            {
                num[j] = ch - '0';
                j++;
                ch = fgetc(fp);
            }
            temp.rollno[k] = getInt(num,j);
            k++;
            if(ch == ';')
                break;
            ch = fgetc(fp);
        }

        //storing date of issued book respective to each roll number
        ch = fgetc(fp);
        k=0;
        while(ch!=';')
        {
            l=0;
            while(ch != ',' && ch!=';')
            {
                j = 0;
                resettoZero(num, 10);
                while(ch!='/' && ch!=',' && ch!=';')
                {
                    num[j] = ch - '0';
                    j++;
                    ch = fgetc(fp);
                }
                temp.issuedate[k][l] = getInt(num,j);
                l++;
                if(ch == ',' || ch == ';')
                    break;
                ch = fgetc(fp);
            }
            k++;
            if(ch == ';')
                break;
            ch = fgetc(fp);
        }
        root = add_instanceData(root,temp);
        //printf("//%d//",root->data.BookId);
        ch = fgetc(fp);
    }
    fclose(fp);
    return root;
}
struct node* add_instanceData(struct node* root,struct book_instance temp)
{
    if(root==NULL)
    {
        root=(struct node*)malloc(sizeof(struct node));
        root->right=NULL;
        root->left=NULL;
        root->data = temp;
       // printf("//%d//",root->data.BookId);
        return root;
    }
    else
    {
        if(strcmp(temp.Author,(root->data).Author) > 0)
            root->right=add_instanceData(root->right,temp);
        else if(strcmp(temp.Author,(root->data).Author) < 0)
            root->left=add_instanceData(root->left, temp);
        else //When the authors are same..place books on the basis of bookname
        {
            if(strcmp(temp.BookName,(root->data).BookName) > 0)
                root->right=add_instanceData(root->right,temp);
            else if(strcmp(temp.BookName,(root->data).BookName) < 0)
                root->left=add_instanceData(root->left, temp);
        }
    }
    return root;
}
struct node* search_BookId(struct node* root, int BukId)
{
    if(root!= NULL)
    {
        struct node* temp;
        if(BukId == root->data.BookId)
        {
            return root;
        }
        temp = search_BookId(root->left, BukId);
        if(temp == NULL)
        {
            return search_BookId(root->right, BukId);
        }
        else
        {
            return temp;
        }
    }
    return NULL;
}

void writeRecords(char* fname , struct node* root)
{
    if(root!=NULL)
    {
        char res[15];
        FILE* fpt = fopen(fname,"a");
        putc('\n', fpt);
        sprintf(res, "%d" , root->data.sNo);//converts integer into a string and stores it into res
        fputs(res, fpt);
        fputc(';',fpt);
        fputs(root->data.courseId, fpt);
        fputc(';',fpt);
        sprintf(res, "%d", root->data.BookId);
        fputs(res, fpt);
        fputc(';',fpt);
        fputs(root->data.BookName, fpt);
        fputc(';',fpt);
        fputs(root->data.Author, fpt);
        fputc(';',fpt);
        int a,b;
        a = root->data.copiesAvailable;
        b = root->data.totalcopies;
        sprintf(res, "%d", b);
        fputs(res, fpt);
        fputc(';',fpt);
        sprintf(res, "%d", a);
        fputs(res, fpt);
        fputc(';',fpt);
        if(b - a)
        {
            sprintf(res, "%d", root->data.rollno[0]);
            fputs(res, fpt);
            for(int i=1;i<b-a;i++)
            {
                putc(',', fpt);
                sprintf(res, "%d", root->data.rollno[i]);
                fputs(res, fpt);
            }
        }
        putc(';',fpt);
        if(b - a)
        {
            for(int j=0;j<b-a;j++)
            {
                sprintf(res, "%d", root->data.issuedate[j][0]);
                if(strlen(res) == 1)//you need to add zero if date number is of single digit
                    putc('0',fpt);

                fputs(res, fpt);


                putc('/', fpt);
                sprintf(res, "%d", root->data.issuedate[j][1]);
                if(strlen(res) == 1)
                    putc('0',fpt);

                fputs(res, fpt);


                putc('/', fpt);
                sprintf(res, "%d", root->data.issuedate[j][2]);
                fputs(res, fpt);

                if(j!=b-a-1)
                {
                    putc(',', fpt);
                }
            }
        }
        putc(';',fpt);
        fclose(fpt);
        writeRecords(fname, root->left);
        writeRecords(fname, root->right);
    }
}
struct node* addbook(struct node* root)
{
    int act;
    int BukId;
    int roll;
    struct node* temp;
    printf("Press 1 -ifReturning_a_Book  2 -adding_New_Book: ");
    fflush(stdin);
    scanf("%d",&act);
    if(act == 1) //Returning of book
    {
        printf("Enter BookId : ");
        fflush(stdin);
        scanf("%d",&BukId);
        printf("Enter rollno of student who is returning the book : ");
        fflush(stdin);
        scanf("%d",&roll);
        temp = search_BookId(root, BukId);
        if(temp!= NULL)  //BookId found
        {
            int i;
            int n = temp->data.totalcopies-temp->data.copiesAvailable;
            for(i=0;i<n;i++) //finding rollno
            {
                if(temp->data.rollno[i] == roll)
                    break;
            }
            if(i<n)
            {
                printf("Fine Imposed on rollno %d = Rs. %d\n",roll,calc_fine(temp->data.issuedate[i]));
                pop_array(temp->data.rollno, n, i);
                popRow(temp->data.issuedate, n, i);
                temp->data.copiesAvailable ++;
            }
            else
            {
                printf("roll number not found in book issue list. Please Try Again\n");
            }

        }
        else //BookId not found
        {
            printf("Book corresponding to this Id is not in the Library. Please try Again\n");
        }


    }
    else if(act == 2) //addition of new book in the library
    {
        struct node* temp;
        char author[100];
        char bookname[50];
        printf("Enter Exact Author Name : ");
        fflush(stdin);
        getstring(author);
        printf("Enter Exact Book Name : ");
        fflush(stdin);
        getstring(bookname);
        temp = searchBk(root, author, bookname);
        int n = 1;//n is number of copies of the book you are submitting
        printf("Enter No. of Copies you are adding of this book: ");
        fflush(stdin);
        scanf("%d",&n);
        if(temp != NULL)  //book found therefore increase number of copies
        {
            temp->data.copiesAvailable += n;
            temp->data.totalcopies += n;
        }
        else //Book is not already available in library ..therefore we have to add this book
        {
            struct book_instance newbook;
            char course[10];
            int id;

            newbook.copiesAvailable = n;
            newbook.totalcopies = n;
            strcpy(newbook.Author,author);
            strcpy(newbook.BookName, bookname);
            printf("Enter Course corresponding to the Book : ");
            fflush(stdin);
            getstring(course);
            strcpy(newbook.courseId, course);
            Entries++;
            newbook.sNo = Entries;
            printf("Enter BookId: ");
            fflush(stdin);
            scanf("%d",&id);

            while(search_BookId(root, id) != NULL)
            {
                printf("This BookId ALready Exists! Enter Valid BookId: ");
                fflush(stdin);
                scanf("%d",&id);
            }
            newbook.BookId = id;

            add_instanceData(root, newbook);
        }
    }
    return root;
}
struct node* takebook(struct node* root)
{
    int action =1, roll;
    printf("Enter roll number of the student who is taking the book: ");
    fflush(stdin);
    scanf("%d",&roll);
    struct node* Found;
    printf("Which Book do you want to Issue?\n");
    printf("Press 1-for BookId Search 2-for Author and BookName Search: ");
    fflush(stdin);
    scanf("%d",&action);
    if(action == 2)
    {
        char author[100];
        char bookname[50];
        printf("Enter Exact Author Name : ");
        fflush(stdin);
        getstring(author);
        printf("Enter Exact Book Name : ");
        fflush(stdin);
        getstring(bookname);
        Found = searchBk(root, author, bookname);
    }
    else if(action == 1)
    {
        int id;
        printf("Enter BookId: ");
        fflush(stdin);
        scanf("%d",&id);
        Found = search_BookId(root, id);
    }
    else
    {
        printf("Invalid Input:: Try Again\n");
        return root;
    }

    if(Found!=NULL)
    {
        if(Found->data.copiesAvailable != 0)
        {
            int i,a,b;
            Found->data.copiesAvailable --;
            a = Found->data.copiesAvailable;
            b = Found->data.totalcopies;
            i = b - a - 1;
            Found->data.rollno[i] = roll;
            getDate(Found->data.issuedate[i]);
            printf("Book has been issued to rollno-%d\n",roll);
        }
        else
        {
            printf("Right Now, Book is not Available\n");
        }
    }
    else
    {
        printf("Book Not Found! Please Try Again\n");
    }
    return root;

}
struct node* searchBook(struct node* root)
{
    struct node* Found;
    char author[100];
    char bookname[50];
    printf("Enter Exact Author Name : ");
    fflush(stdin);
    getstring(author);
    printf("Enter Exact Book Name : ");
    fflush(stdin);
    getstring(bookname);
    Found =  searchBk(root, author, bookname);
    if(Found)
        display_details(Found);
    else
        printf("Book Not Found!\n");

    return Found;
}

struct node* searchBk(struct node* root, char author[], char bookname[])
{
    if(root!=NULL)
    {
        if(strcmp(author, root->data.Author) == 0)
        {
            if(strcmp(bookname,root->data.BookName) == 0)
            {
                return root;
            }
            else if(strcmp(bookname, root->data.BookName) >  0)
            {
                return searchBk(root->right,author,bookname);
            }
            else
            {
                return searchBk(root->left,author,bookname);
            }
        }
        else if(strcmp(author, root->data.Author) > 0)
        {
            return searchBk(root->right, author, bookname);
        }
        else
        {
            return searchBk(root->left, author, bookname);
        }
    }
    return root;
}
void pop_array(int A[],int n, int i)
{
    if(i<n)
    {
        int j = i + 1;
        for(;j<n;j++)
        {
            A[j-1] = A[j];
        }

    }
}
void popRow(int A[][3],int n, int i)
{
    if(i < n)
    {
        int x = i + 1;
        for(;x<n;x++)
        {
            for(int j=0;j<3;j++)
            {
                A[x - 1][j] = A[x][j];
            }
        }
    }
}
void getstring(char* str)
{
    int i=0;
    char c='a';
    while(1)
    {
        scanf("%c",&c);
        if(c=='\n')
        break;
        str[i]=c;
        i++;
    }
    str[i]='\0';

}
int getInt(int num[] , int n)
{
    int i;
    i = n-1;
    int p = 1;
    int sum = 0;
    for(;i>=0;i--)
    {
        sum = sum + num[i]*p;
        p = p*10;
    }
    return sum;
}
void resettoZero(int num[], int n)
{
    for(int i=0;i<n;i++)
    {
        num[i] = 0;
    }
}
int TotalBooks(struct node* root)
{
    if(root!=NULL)
    {
        return root->data.totalcopies + TotalBooks(root->left) + TotalBooks(root->right);
    }
    return 0;
}
