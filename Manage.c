#define _CRT_SECURE_NO_WARNINGS
#include"book_management.h"
#include"User_management.h"
#include<stdlib.h>
#include<string.h>
void login_menu();//login menu
void manage_menu();//Administrator Menu
void user_menu();//user menu
int login_action();//log in
void action_manage();//management action
void action_user();//user action

int main() {
	
	createUserList();
	createBookList();
	int cur_user_index;
	while (1)
	{
		cur_user_index = login_action();
		if (strcmp(getName(cur_user_index),"root") == 0)//Judgment of identity
		{
			action_manage();
		}
		else
		{
			action_user();
		}
	}
	return 0;
}

void login_menu()//login menu
{
	system("cls");
	printf("Library management system\n");
	printf("1:User registration\n");
	printf("2:The user login\n");
	printf("0:Exiting the current System\n");
	printf("Please enter your selection:\n");
}

int login_action()//log in
{
	int ch;
	int ret;
	while (1)
	{
		login_menu();
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:regist();
			break;
		case 2:
		{
			if ((ret=login())!=-1)
			{
				return ret;
			}
		}
			break;
		case 0:
			printf("Thank you for your use!\n");
			exit(0);
		default:
			printf("Your input is incorrect!\n");
			break;
		}
		system("pause");
	}
}

void manage_menu()//Administrator Menu
{
	system("cls");
	printf("Library management system\n");
	printf("1:Add books\n");
	printf("2:Delete books\n");
	printf("3:Display all books\n");
	printf("4:Search for books by publication year\n");
	printf("5:Search for books by title\n");
	printf("6:Search for books by author\n");
	printf("0:Back to the previous level\n");
	printf("Please enter your selection:\n");
}

void action_manage()//management action
{
	int ch;
	while (1)
	{
		manage_menu();
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:add_book(inputBook());
			break;
		case 2:remove_book(getBookById());
			break;
		case 3:showAllBook();
			break;
		case 4:
		{
			int year;
			printf("Please enter a year:");
			scanf("%d", &year);
			showBookListByBookList(find_book_by_year(year));
		}
		break;
		case 5:
		{
			char title[256];
			printf("Please enter a title:");
			scanf("%s", title);
			showBookListByBookList(find_book_by_title(title));
		}
		break;
		case 6:
		{
			char author[1024];
			printf("Please enter author:");
			getchar();
			fgets(author, 1024, stdin);
			author[strlen(author) - 1] = '\0';
			showBookListByBookList(find_book_by_author(author));
		}
		break;
		case 0:
			return;
		default:
			printf("Your input is incorrect!\n");
			break;
		}
		system("pause");
	}
}

void user_menu()//user menu
{
	system("cls");
	printf("Library management system\n");
	printf("1:borrow book\n");
	printf("2:Return the book\n");
	printf("3:Display all books\n");
	printf("4:Search for books by publication year\n");
	printf("5:Search for books by title\n");
	printf("6:Search for books by author\n");
	printf("0:Back to the previous level\n");
	printf("Please enter your selection:\n");
}

void action_user()//user action
{
	int ch;
	while (1)
	{
		user_menu();
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:borrow_book();
			break;
		case 2:return_book();
			break;
		case 3:showAllBook();
			break;
		case 4:
		{
			int year;
			printf("Please enter a year:");
			scanf("%d", &year);
			showBookListByBookList(find_book_by_year(year));
		}
		break;
		case 5:
		{
			char title[256];
			printf("Please enter a title:");
			scanf("%s", title);
			showBookListByBookList(find_book_by_title(title));
		}
		break;
		case 6:
		{
			char author[1024];
			printf("Please enter author:");
			getchar();
			fgets(author, 1024, stdin);
			author[strlen(author) - 1] = '\0';
			showBookListByBookList(find_book_by_author(author));
		}
		break;
		case 0:
			return;
		default:
			printf("Your input is incorrect!\n");
			break;
		}
		system("pause");
	}
}
