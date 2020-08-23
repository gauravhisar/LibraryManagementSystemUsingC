#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
int today[3];//store today's date in dd/mm/yyyy format


void getDate(int today[]);
int calc_fine(int issueDate[]);
int getDifference(int d1[], int d2[]);
int count_leap(int year);
int isleap(int year);

void getDate(int today[])
{
    time_t lt;//lt means local time
    lt = time(NULL);//time_t time(time_t *timer)  //now lt stores the calendar time
    struct tm *d; //stores date and time as a collection of integers
    d = localtime(&lt);//date time stored in lt is stored in d(struct tm*)
    today[0] = d->tm_mday;
    today[1] = d->tm_mon + 1;
    today[2] = d->tm_year + 1900;
    //printf("today = %d/%d/%d",today[0],today[1],today[2]);

    //printf("%s",asctime(d));//asctime returns the string of calendar date and time and take parameter as struct tm*
}
int calc_fine(int issueDate[])
{
    getDate(today);
    int gap;
    gap = getDifference(issueDate, today);
    if(gap <= 15)
        return 0;
    else
        return gap-15;
}
int getDifference(int d1[], int d2[])
{
    int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int n1, n2;

    //count days before date d1
    n1 = 365*d1[2];
    for(int i=0;i<d1[1] - 1;i++)
    {
        n1 = n1 + monthDays[i];
    }
    n1 = n1 + d1[0];
    n1 = n1 + count_leap(d1[2]);
    if(d1[1] > 2 && isleap(d1[2]))// if the current year is leap and month is above february, then we must count the extra day in feburary
    {
        n1 = n1 + 1;
    }
    //count days before date d2
    n2 = 365*d2[2];
    for(int i=0;i<d2[1] - 1;i++)
    {
        n2 = n2 + monthDays[i];
    }
    n2 = n2 + d2[0];
    n2 = n2 + count_leap(d2[2]);
    if(d2[1] > 2 && isleap(d2[2]))// if the current year is leap and month is above february, then we must count the extra day in feburary
    {
        n2 = n2 + 1;
    }
    return n2 - n1;
}
int count_leap(int year) // count leap year up to the given year excluding current year
{
    int count=0;
    for(int i=1;i<year;i++)
    {
        if(isleap(i))
        {
            count++;
        }
    }
    return count;
}
int isleap(int year)
{
    // If a year is multiple of 400,
    // then it is a leap year
    if (year % 400 == 0)
        return 1;

    // Else If a year is muliplt of 100,
    // then it is not a leap year
    if (year % 100 == 0)
        return 0;

    // Else If a year is muliplt of 4,
    // then it is a leap year
    if (year % 4 == 0)
        return 1;
    return 0;
}
