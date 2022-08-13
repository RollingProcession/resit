#define _CRT_SECURE_NO_WARNINGS
#include"book_management.h"
#include"User_management.h"
#include<stdlib.h>
#include<string.h>
void login_menu();//登录菜单
void manage_menu();//管理员菜单
void user_menu();//用户菜单
int login_action();//登录操作
void action_manage();//管理员操作
void action_user();//用户操作
int main() {
	
	createUserList();
	createBookList();
	int cur_user_index;
	while (1)
	{
		cur_user_index = login_action();
		if (strcmp(getName(cur_user_index),"root") == 0)//如果是管理员
		{
			action_manage();//管理员操作
		}
		else
		{
			action_user();//用户操作
		}
	}
	return 0;
}
void login_menu()
{
	system("cls");
	printf("图书管理系统\n");
	printf("1:用户注册\n");
	printf("2:用户登录\n");
	printf("0:退出当前系统\n");
	printf("请输入您的选择:\n");
}
int login_action()//登录操作
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
			printf("感谢您的使用！\n");
			exit(0);
		default:
			printf("您的输入有误！\n");
			break;
		}
		system("pause");
	}
}
void manage_menu()//管理员菜单
{
	system("cls");
	printf("图书管理系统\n");
	printf("1:添加图书\n");
	printf("2:删除图书\n");
	printf("3:显示所有图书\n");
	printf("4:按照出版年显示图书\n");
	printf("5:按照标题显示图书\n");
	printf("6:按照作者显示图书\n");
	printf("0:返回上一级\n");
	printf("请输入您的选择:\n");
}
void action_manage()//管理员操作
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
			printf("请输入一个年份：");
			scanf("%d", &year);
			showBookListByBookList(find_book_by_year(year));
		}
		break;
		case 5:
		{
			char title[256];
			printf("请输入一个标题：");
			scanf("%s", title);
			showBookListByBookList(find_book_by_title(title));
		}
		break;
		case 6:
		{
			char author[1024];
			printf("请输入一个作者姓名：");
			getchar();
			fgets(author, 1024, stdin);
			author[strlen(author) - 1] = '\0';
			showBookListByBookList(find_book_by_author(author));
		}
		break;
		case 0:
			return;
		default:
			printf("您的输入有误！\n");
			break;
		}
		system("pause");
	}
}
void user_menu()//用户菜单
{
	system("cls");
	printf("图书管理系统\n");
	printf("1:借书\n");
	printf("2:还书\n");
	printf("3:显示所有图书\n");
	printf("4:按照出版年显示图书\n");
	printf("5:按照标题显示图书\n");
	printf("6:按照作者显示图书\n");
	printf("0:返回上一级\n");
	printf("请输入您的选择:\n");
}
void action_user()//用户操作
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
			printf("请输入一个年份：");
			scanf("%d", &year);
			showBookListByBookList(find_book_by_year(year));
		}
		break;
		case 5:
		{
			char title[256];
			printf("请输入一个标题：");
			scanf("%s", title);
			showBookListByBookList(find_book_by_title(title));
		}
		break;
		case 6:
		{
			char author[1024];
			printf("请输入一个作者姓名：");
			getchar();
			fgets(author, 1024, stdin);
			author[strlen(author) - 1] = '\0';
			showBookListByBookList(find_book_by_author(author));
		}
		break;
		case 0:
			return;
		default:
			printf("您的输入有误！\n");
			break;
		}
		system("pause");
	}
}
