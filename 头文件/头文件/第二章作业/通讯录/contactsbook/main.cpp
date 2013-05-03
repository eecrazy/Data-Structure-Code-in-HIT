/*
 * File:   main.cpp
 * Author: admin
 *
 * Created on 2010年12月19日, 下午2:20
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
struct record
{
char name[20];
char street[20];
char city[20];
char code[20];
char state[20];
}student[500];
struct slnode
{
 record date;
 struct slnode *next;
 struct slnode *prior;
};
typedef  slnode * linklist;
linklist l;
int num=0;
FILE *fp;
void mainmenu();
void searchmenu();
void enter();
void search();
void display();
void load();
void save();
void delet();
void listinsert();
void initlist();
  int main()
{
 initlist();
 load();
 listinsert();
 while (1)
  mainmenu();
}
void load()
{
 if((fp=fopen("student.bin","rb"))==NULL)
 {
  printf("\n\t\tthe contacts file doesn't exist");
  if ((fp=fopen("student","wb"))==NULL)
  {
   printf("\n\t\tfail to establish");
   exit(0);
  }
  else
{
printf("\n\t\tthe contacts file has already established");
printf("\n\t\tpress any key to enter the main menu");
getch();
return;
}
exit(0);
}
fseek(fp,0,2);
if (ftell(fp)>0)
{
rewind(fp);
for (num=0;!feof(fp) && fread(&student[num],sizeof(struct record),1,fp);num++);
printf("\n\t\tthe import of file is complete");
printf("\n\t\tpress any key to return the main menu");
getch();
return;
}
printf("\n\t\tthe import of file is complete");
printf("\n\t\tno record in the contacts file");
printf("\n\t\tpress any key to return the main menu");
getch();
return;
}
void mainmenu()//主菜单
{
 char choic;
 system("cls");
 printf("\n\t\t***************welcome to the contacts system***************");
 printf("\n\t\t******************1-add new record ******************");
 printf("\n\t\t******************2-find a contacts ****************");
 printf("\n\t\t******************3-delete a contact ***************");
 printf("\n\t\t******************4-save and quit  *****************");
    printf("\n\t\t******************5-quit without save  ***************");
    printf("\n\t\t************************************************");
 printf("\n\t\tplease choose");
 choic=getch();
 switch (choic)
 {
 case '1':enter();break;
 case '2':searchmenu();break;
 case '3':delet();break;
 case '4':save();break;
 case '5':exit(0);
 default:mainmenu();
 }
}
void searchmenu()//查询菜单
{
 char choic;
 system("cls");
 printf("\n\t\t******************* search the menu *******************");
 printf("\n\t\t**************** 1-show all ********************");
 printf("\n\t\t**************** 2-search by name ******************");
 printf("\n\t\t**************** 3-return the main menu ******************");
 printf("\n\t\t************************************************");
 printf("\n\t\tplease choose：");
 choic=getch();
 switch (choic)
 {
 case '1':display();break;
 case '2':search();break;
 case '3':mainmenu();break;
 }
}
void enter()//添加纪录
{
 printf("\n\t\t**************** please input students' information ****************\n");
 printf("\n\t\tname:");
 scanf("%s",&student[num].name);
 printf("\n\t\tstreet:");
 scanf("%s",&student[num].street);
 printf("\n\t\tcity:");
 scanf("%s",&student[num].city);
 printf("\n\t\tcode；");
 scanf("%s",&student[num].code);
 printf("\n\t\tstate:");
 scanf("%s",&student[num].state);
 num++;
 printf("\n\t\tcontinue to add?(Y/N):");
 if (getch()=='y')
  enter();
 return;
}
void display()//显示所有
{
 int i;
 system("cls");
 if(num!=0)
 {
  printf("\n\t\t***************the following is all the information od the contacts************");
  for (i=0;i<num;i++)
  {
   printf("\n\t\tname: %s",student[i].name);
   printf("\n\t\tstreet: %s",student[i].street);
   printf("\n\t\tcity: %s",student[i].city);
   printf("\n\t\tcode: %s",student[i].code);
   printf("\n\t\tstate: %s",student[i].state);
   printf("\t\t");
   if (i+1<num)
   {
    printf("\n\t\t__________________________");
    system("pause");
   }
  }
  printf("\n\t\t************************************************");
 }
 else
  printf("\n\t\tno record in the contacts");
 printf("\n\t\tpress any key to return the menu");
 getch();
 return;
}
void save()//写入文件
{
int i;
if ((fp=fopen("student","wb"))==NULL)
{
printf("\n\t\tfail to open the file");
}
for (i=0;i<num;i++)
{
if (fwrite(&student[i],sizeof(struct record),1,fp)!=1)
{
printf("\n\t\tfile error!\n");
}
}
fclose(fp);
printf("\n\t\thas saved the contacts file");
printf("\n\t\tpress any key to exist the program\n\t\t");
exit(0);

}
void listinsert()//增加一个结点
{
 linklist s,p=l;
 for(int i=0;i<num;i++)
 {
  s=new slnode;
        strcpy(s->date.name,student[i].name);
        strcpy(s->date.city,student[i].city);
        strcpy(s->date.street,student[i].street);
        strcpy(s->date.code,student[i].code);
        strcpy(s->date.state,student[i].state);
     s->prior=p->prior;
     s->next=p;
     p->prior->next=s;
     p->prior=s;
  p=p->next;
 }
}
void initlist()
{
 l=new slnode;
 l->next=l;
 l->prior=l;
}
void search()
{
 int j=0,a=0;
 linklist p=l;
 printf("\n\t\t***************** search by name *******************");
 char name[20];
 printf("\n\t\tplease enter the name:");
 scanf("%s",name);
    for(int i=a;i<num;i++,p=p->next)
 {
  if(strcmp(name,p->next->date.name)==0)
  {
          printf("the information found:");
    printf("\n");
    printf("name:");
    printf("%s",p->next->date.name);
    printf("\n");
          printf("city:");
    printf("%s",p->next->date.city);
    printf("\n");
          printf("state:");
    printf("%s",p->next->date.state);
    printf("\n");
       printf("street:");
    printf("%s",p->next->date.street);
    printf("\n");
          printf("code:");
    printf("%s",p->next->date.code);
    j++;
  }
  if(j==0)
   printf("\t\tthe person doesn't exist in the contacts!");
  if ((i+1)<num)
  {
   printf("\n\t\tcontinue to search information by the same name?(y/n)");
   if (getch()=='y')
   {

    a=i;
    continue;
   }
   else
    return;
  }
  else
  {
   printf("\n\t\tpress any key to return the main menu");
   getch();
   return;
  }
  }

}
void delet()
{
 int a=0;
    int findmark=0;
    int j;
    int deletemark=0;
    int i;
    char name[20];
    printf("\n\t\tplease enter the student's name that will be deleted");
    scanf("%s",name);
 for (i=a;i<num;i++)
 {
  if (strcmp(student[i].name,name)==NULL)
  {
   printf("\n\t\tthe will-be-deleted-student's informatin is below:");
   findmark++;
   printf("\n\t\t_________________________________");
   printf("\n\t\tname: %s",student[i].name);
   printf("\n\t\tstreet: %s",student[i].street);
   printf("\n\t\tcity: %s",student[i].city);
            printf("\n\t\tcode: %s",student[i].code);
            printf("\n\t\tstate:  %s",student[i].state);
            printf("\n\t\t__________________________________");
            printf("\n\t\tdelete?(y/n)");
   if (getch()=='y')
   {
    for (j=i;j<num-1;j++)
     student[j]=student[j+1];
    num--;
    deletemark++;
    printf("\n\t\tsuccessfully deleted");
    if((i+1)<num)
    {
     printf("\n\t\tcontinue to delete student's information with the same name?(y/n)");
     if (getch()=='y')
     {
      a=i;
      continue;
     }
    }
    printf("\n\t\tcontinue to delete?(y/n)");
    if (getch()=='y')
     delet();
    return;
   }

if((i+1)<num)
   {
    printf("\n\t\tcontinue to delete student's information with the same name?(y/n)");
    if (getch()=='y')
    {
     a=i;
     continue;
    }
   }
  }
  else
   continue;
 }
 if ((deletemark==0)&&(findmark==0))
 {

  printf("\n\t\tno record of the student");
  return;
 }
 else
  if (findmark!=0)
  {
   printf("\n\t\tno same name information");
   printf("\n\t\tno record of the student");
   return;
  }
  }


