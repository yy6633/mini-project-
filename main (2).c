#include<stdio.h>
#include<stdlib.h>
typedef struct flight
{
int f_no,price;
char dest[100];
}f;
typedef struct book
{
char name[100],address[1000],ph;
int age,price,mobile_no;
}b;
void add_flight()
{
f *add;
int i,n;
FILE *fp;
fp=fopen("Add.txt","w");
printf("                       How many Flights you want to add:");
scanf("%d",&n);
add=(f *)calloc(n,sizeof(f));
for(i=0;i<n;i++)
{
printf("                         Enter the details of flight %d\n",i+1);
printf("                         Enter the Flight number:");
scanf("%d",&add[i].f_no);
printf("                         Enter the Destination of the Flight:");
scanf(" %[^\n]",add[i].dest);
printf("                         Enter the Price:");
scanf("%d",&add[i].price);
fwrite(&add[i],sizeof(f),1,fp);
}
printf("\n");
fclose(fp);
}
void delete_flight()
{ 
FILE *fp,*fp1;
int f_no,found=1;
f add;
fp=fopen("Add.txt","r");
fp1=fopen("df.txt","w");
printf("                         Enter the Flight Number to delete:");
scanf("%d",&f_no);
rewind(fp);
while(fread(&add,sizeof(f),1,fp))
{
if(f_no==add.f_no)
{
found=0;
continue;
}
else
{
//add=(f *)calloc(1,sizeof(f));
fwrite(&add,sizeof(f),1,fp1);
}
}
fclose(fp);
fclose(fp1);
if(found==1)
{
printf("                         No flight found with the given flight number.\n");
}
else
{
fp=fopen("df.txt","r");
fp1=fopen("Add.txt","w");
while(fread(&add,sizeof(f),1,fp))
{
fwrite(&add,sizeof(f),1,fp1);
}
printf("                         Flight deleted successfully.");
}

printf("\n");
fclose(fp);
fclose(fp1);
}
void book_tickets()
{
f add;
b *book;
int price,f_no,n,i;
FILE *fp1,*fp;
fp =fopen("Add.txt","r");
fp1=fopen("book.txt","a");
printf("                       -----------------------------------------------\n");
printf("                         F_NO \t DESTINATION \t\t PRICE \n");
printf("                       -----------------------------------------------\n");
while(fread(&add,sizeof(f),1,fp))
{
printf("                         %d \t %s \t\t %d \n",add.f_no,add.dest,add.price);
}
printf("                       ------------------------------------------------\n ");
printf("                       Enter the Flight Number:");
scanf("%d",&f_no);
printf("How many Tickets you want to book:");
scanf("%d",&n);
book=(b *)calloc(n,sizeof(b));
rewind(fp);
while(fread(&add,sizeof(f),1,fp))
{
    if(f_no==add.f_no)
    {
    	for(i=0;i<n;i++)
    	{
        	char name[100],address[1000],ph;
        	int age,mobile_no,price;
        	printf("                         Enter \n                         Name:");
        	scanf(" %[^\n]",book[i].name);
        	printf("                         AGE:");
        	scanf("%d",&book[i].age);
        	printf("                         MOBILE NUMBER:");
        	scanf("%d",&book[i].mobile_no);
        	printf("                         ADDRESS:");
       		scanf(" %[^\n]",book[i].address);
        	printf("                         Are you physically handicapped(y/n):");
        	scanf(" %c",&book[i].ph);
        	printf("\n");
        	price=add.price;
        	printf("                         The price for your ticket is: %d\n",price);
    		if(book[i].age<=18)
        	{
        		book[i].price=price-price*0.1;
        		printf("                         You are eligible for a concessionn of 10 percent of your price.\n");
        		printf("                         The price after the eligible concession is: %d\n",book[i].price);
}
else if(book[i].age>60)
{
book[i].price=price-price*0.05;
printf("                         You are eligible for a concessionn of 5 percent of your price.\n");
        		printf("                         The price after the eligible concession is: %d\n",book[i].price);
}
else if(book[i].ph=='y' || book[i].ph=='Y')
{
book[i].price=price-price*0.15;
printf("                         You are eligible for a concessionn of 15 percent of your price.\n");
        		printf("                         The price after the eligible concession is: %d\n",book[i].price);
}
printf("\n");
fwrite(&book[i],sizeof(b),1,fp1);
}
break;
    }
}
printf("\n");
fclose(fp);
}
void cancel_tickets()
{
FILE *fp,*fp1;
b book;
f add;
int mobile_no,found=0,i;
fp=fopen("book.txt","r");
fp1=fopen("del.txt","w");
printf("                         Enter the mobile number used to book the ticket:");
scanf("%d",&mobile_no);
rewind(fp);
while(fread(&book,sizeof(b),1,fp))
{
if(mobile_no==book.mobile_no)
{
found=1;
continue;
}
else
{
//book=(b *)calloc(1,sizeof(b));
fwrite(&book,sizeof(b),1,fp1);
}
}
fclose(fp);
fclose(fp1);
if(found==1)
{
fp=fopen("del.txt","r");
fp1=fopen("book.txt","w");
while(fread(&add,sizeof(f),1,fp))
{
fwrite(&add,sizeof(f),1,fp1);
}
printf("                         Ticket cancelled successfully.\n");
}
else
printf("                         No ticket found with given mobile number.\n");
printf("\n");
fclose(fp);
fclose(fp1);
}
void main()
{
int n,e,u;
printf("***  AIRLINES RESERVATION  ***\n");
while(1)
{
printf("                       1.EMPLOYEE\n");
printf("                       2.USER\n");
printf("                       0.EXIT\n");
printf("                       Enter your choice:");
scanf("%d",&n);
printf("\n");
if(n==1)
{
printf("                       1.ADD FLIGHT\n");
printf("                       2.DELETE FLIGHT\n");
printf("                       Enter your choice:");
scanf("%d",&e);
printf("\n");
switch(e)
{
case 1:
add_flight();
break;
case 2:
delete_flight();
break;
default:
printf("                       Enter the correct choice\n");
}
}
else if(n==2)
{
printf("                       1.BOOK TICKETS\n");
printf("                       2.CANCEL TICKETS\n");
printf("                       Enter your coice:");
scanf("%d",&u);
printf("\n");
switch(u)
{
case 1:
book_tickets();
break;
case 2:
cancel_tickets();
break;
default:
printf("                       Enter correct choice\n");
}
}
else if(n==0)
exit(0);
else
printf("                       Enter correct choice\n");
}
}
