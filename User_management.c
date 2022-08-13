#define _CRT_SECURE_NO_WARNINGS
#include"User_management.h"
#include"book_management.h"
#include<string.h>
#include<stdlib.h>
UserList uList;

int save(FILE* file)//Store information
{
	User* p;
	unsigned int i;
	if (uList.length == 0)
	{
		uList.list->next = (User*)malloc(sizeof(User));
		strcpy(uList.list->next->uName, "root");
		strcpy(uList.list->next->passWord, "root");
		strcpy(uList.list->next->name, "root");
		uList.list->next->next = NULL;
		uList.length = 1;
	}
	for (i = 0, p = uList.list->next; i < uList.length; i++) {
		fprintf(file, "%s\t%s\t%s\n", p->uName, p->passWord, p->name);
		p = p->next;
	}
	fclose(file);
	return 1;
}

int read(FILE* file)//Reading User Information
{
	User* p;
	if (!file)
	{
		file = fopen("userAndPassword.txt", "w");
		save(file);
		return -1;
	}
	while (!feof(file))
	{
		p = (User*)malloc(sizeof(User));
		fscanf(file, "%s", p->uName);
		if (feof(file))
		{
			free(p);
			break;
		}
		fscanf(file, "%s%s", p->passWord, p->name);
		p->next = uList.list->next;
		uList.list->next = p;
		uList.length++;
	}
	fclose(file);
	return 1;
}

void createUserList()//create a new list
{
	FILE* file=fopen("userAndPassword.txt","r");
	uList.list = (User*)malloc(sizeof(User));
	uList.list->next = NULL;
	uList.length = 0;
	read(file);
}

int login()//log in
{
	User u;
	unsigned int i;
	User* p;

	while (1)
	{
		printf("Please enter a user name:");
		scanf("%s", u.uName);
		if (strlen(u.uName) > 18)
		{
			printf("username contains more than 18 characters, enter a new username!\n");
		}
		else
			break;
		while (getchar() != '\n')
			;
	}
	while (1)
	{
		printf("Please enter your password:");
		scanf("%s", u.passWord);
		if (strlen(u.passWord) > 18)
		{
			printf("The password contains more than 18 characters. Enter a new password!\n");
		}
		else
			break;
		while (getchar() != '\n')
			;
	}

	for (i = 0, p= uList.list->next; i < uList.length; i++) {
		if (strcmp(p->uName, u.uName) == 0)
		{
			if (strcmp(p->passWord, u.passWord) == 0)
			{
				printf("Login successful!\n");
				return i;// Returns the subscript of the currently logged in user
			}
			else	
			{
				printf("Wrong password! Login failed!\n");
				return -1;
			}
		}
		p = p->next;
	}
	printf("The current user is not registered!\n");
	return -1;
}

int regist()//registered
{
	User* u;
	FILE* file;
	char password2[20];
	unsigned int i;
	User* p;

	u = (User*)malloc(sizeof(User));
	u->next = NULL;
	while (1)
	{
		printf("Please enter a user name:");
		scanf("%s", u->uName);
		if (strlen(u->uName) > 18)
		{
			printf("username contains more than 18 characters, enter a new username!\n");
		}
		else
			break;
		while (getchar() != '\n')
			;
	}
	//getchar();
	//fgets(u->uName, sizeof(u->uName), stdin);
	//u->uName[strlen(u->uName) - 1] = '\n';
	while (1)
	{

		while (1)
		{
			printf("Please enter your password:");
			scanf("%s", u->passWord);
			if (strlen(u->passWord) > 18)
			{
				printf("The password contains more than 18 characters. Enter a new password!\n");
			}
			else
				break;
			while (getchar() != '\n')
				;
		}
		printf("Please confirm the password.:");
		scanf("%s", password2);
		if (strcmp(password2, u->passWord) != 0)
		{
			printf("The two passwords do not match! Please re-enter!\n");
		}
		else
			break;
	}
	for (i = 0, p = uList.list->next; i < uList.length; i++) {
		if (strcmp(p->uName, u->uName) == 0)
		{
			printf("The user name already exists! Registration failed!\n");
			free(u);
			return -1;
		}
		p = p->next;
	}
	printf("Please enter your name:");
	scanf("%s", u->name);
	u->next = uList.list->next;
	uList.list->next = u;
	uList.length++;
	printf("Registered successfully!\n");
	file = fopen("userAndPassword.txt", "w");
	save(file);
	return 1;
}

int isManager(int uIndex)//Administrator Login
{
	int i;
	User* p;
	for (i = 0, p = uList.list->next; i < uIndex; i++) {
		p = p->next;
	}
	if (strcmp("root", p->uName) == 0)
		return 1;
	return 0;
}

void borrow_book()//borrow book
{
	Book*b=getBookPointById();
	int cnt;
	printf("Please enter the number of copies you want to borrow:");
	scanf("%d", &cnt);
	if (cnt > b->copies)
	{
		printf("Loan failed due to insufficient stock!\n");
	}
	else
	{
		b->copies -= cnt;//Quantity in stock reduced by one
		printf("Borrowing successful!\n");
	}
}

void return_book()//return book
{
	Book* b = getBookPointById();
	int cnt;
	printf("Please enter the number of copies you want to return:");
	scanf("%d", &cnt);
	b->copies += cnt;
	printf("Return the success!\n");
}

char* getName(int index)//Obtaining a User Name
{
	User* p = uList.list->next;
	int i;
	for (i = 0; i < index; i++)
	{
		p = p->next;
	}
	return p->uName;
}