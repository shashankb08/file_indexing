#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct stud
{
int stud_no;
char stud_name[20];
float stud_percentage;
}s;


void main()
{
FILE *fp;
char *fname,ch='y';
int n=0,x=0;;
printf("enter the no of student records\n");
scanf("%d",&x);
fp=fopen("record.txt","a");
if(fp==NULL)
{
printf("\n unable to open");
exit(0);
}
for(int i=0;i<x;i++)
{
printf("\n enter student number");
scanf("%d",&s.stud_no);
printf("\n enter student name:\t");
scanf("%s",s.stud_name);
printf("\n enter percentage");
scanf("%f",&s.stud_percentage);
fprintf(fp,"%d %s %f\n",s.stud_no,s.stud_name,s.stud_percentage);
//fwrite(&s,sizeof(s),1,fp);  
n++;
fflush(stdin);
}
}
