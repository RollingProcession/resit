#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "user.h"

Book* read()		
{
	FILE *fp;
    Book book1;
	Book *p=NULL,*tail=NULL,*head=NULL;
	fp=fopen("libraries.txt","r");
	if(!fp)
	{
		printf("cannot open file\n");
		exit(0);
	}
	while(fscanf(fp,"%s%s%s%s%s%d%f",book1.id,book1.title,book1.authors,book1.year,book1.copies)!=EOF)//??????????????? 
	{  
		p=(Book*)malloc(sizeof(Book));
		p->Book=book1;						
		if(head==NULL)
			head=p;
		if(tail!=NULL)
			tail->next=p;
		tail=p;
		tail->next=NULL;
	}
	fclose(fp);
	return head;
}

void menu()
{
	system("cls");
	printf("*----------------------Library management system---------------------------*\n");
	printf("*--------------------------------------------------------------------------*\n");
	printf("*                            The login options                             *\n");
	printf("*                1.administrator                  2.user                   *\n");
	printf("*--------------------------------------------------------------------------*\n");
	printf("\n");
}

void menu1()
{
	system("cls");
	printf("*-------------------Library management system------------------------------*\n");
	printf("*                                                                          *\n");
	printf("*-------------------Administrator Function List----------------------------*\n");
	printf("*                                                                          *\n");
	printf("*-------------------1. Input books-----------------------------------------*\n");
    printf("*-------------------2. Add book--------------------------------------------*\n");
    printf("*-------------------3. According to the book-------------------------------*\n");
	printf("*-------------------4. Modify the book information-------------------------*\n");
    printf("*-------------------5. Find books------------------------------------------*\n");
    printf("*-------------------6. Delete books----------------------------------------*\n");
	printf("*-------------------7.Browse the books-------------------------------------*\n");
    printf("*-------------------8. Order of books--------------------------------------*\n");
    printf("*-------------------9. Insert the book-------------------------------------*\n");
	printf("*--------------------------------------------------------------------------*\n");
	printf("\n");
}

void backmenu1()
{
	FILE *fp;
	int n=1;
	while(n!=0)
	{
		system("cls");
		menu1();// In this loop, the menu continues to be displayed after each function is executed
		printf("Please select the above functions and press 0 to exit the system\n");
		printf("\n");
		scanf("%d",&n); 
		fp=fopen("libraries.txt","r");	
		if((n>=3&&n<=9)&&(fp==NULL||fgetc(fp)==EOF))// When there is no file or the content of the file is blank, select not (input add display) function 
		{
			printf("If there are no books, the administrator is advised to input the book information first\n");
			system("pause");
		}	
		else
		{
			switch(n)
			{
				case 1:enter();break;
				case 2:add();break;	
				case 3:display1();break;
				case 4:change();break;
				case 5:find();break;
				case 6:delete();break;
				case 7:browser();break;
				case 8:sort();break; 
				case 9:insert();break;
			}
		}
		fclose(fp);			
	}
	printf("\n");
	if(n==0)
		printf("You have successfully logged out of the library management system£¡\n");
 } 

void backmenu2()
{
	FILE *fp;
	int n=1;
	while(n!=0)
	{
		system("cls");
		menu2();
		printf("Please select the above functions and press 0 to exit the system\n");
		scanf("%d",&n);
		fp=fopen("libraries.txt","r");
		if((fp==NULL||fgetc(fp)==EOF))// When there is no file or the file content is blank
		{
			printf("There are no books in the library, please wait patiently.\n");
			system("pause");
			
		}	
		else
		{
			switch(n)
			{
				case 1:lendbook();break;
				case 2:find();break;
				case 3:returnbook();break;
				case 4:browser();break; 
			}
		}
		fclose(fp);
	}
	if(n==0)
	{
		printf("You have successfully logged out of the library management system\n");
		system("pause");
	}
}

int main()
{
	char Option;
	menu();
	printf("Enter M for the administrator and U for the user,ÍË³öÇë°´0\n");
	scanf("%c",&Option);
	while(Option!='0')// when the output is not an exit key 
	{
		if(Option=='M')
		{
			backmenu1();// Enter the manager function 
			break;
		}
		else
			if(Option=='U')
			{
				backmenu2();// Enter the user function
				break;
			}
			else
			{
				printf("Input error Please try again!\n");
				scanf("%c",&Option);
			}
			scanf("%c",&Option);
	}
	if(Option=='0')
		printf("You have successfully logged out of the library management system!\n");
	return 0;
}
