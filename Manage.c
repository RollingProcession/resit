#define _CRT_SECURE_NO_WARNINGS
#include"book_management.h"
#include"User_management.h"
#include<stdlib.h>
#include<string.h>
void login_menu();//��¼�˵�
void manage_menu();//����Ա�˵�
void user_menu();//�û��˵�
int login_action();//��¼����
void action_manage();//����Ա����
void action_user();//�û�����
int main() {
	
	createUserList();
	createBookList();
	int cur_user_index;
	while (1)
	{
		cur_user_index = login_action();
		if (strcmp(getName(cur_user_index),"root") == 0)//����ǹ���Ա
		{
			action_manage();//����Ա����
		}
		else
		{
			action_user();//�û�����
		}
	}
	return 0;
}
void login_menu()
{
	system("cls");
	printf("ͼ�����ϵͳ\n");
	printf("1:�û�ע��\n");
	printf("2:�û���¼\n");
	printf("0:�˳���ǰϵͳ\n");
	printf("����������ѡ��:\n");
}
int login_action()//��¼����
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
			printf("��л����ʹ�ã�\n");
			exit(0);
		default:
			printf("������������\n");
			break;
		}
		system("pause");
	}
}
void manage_menu()//����Ա�˵�
{
	system("cls");
	printf("ͼ�����ϵͳ\n");
	printf("1:���ͼ��\n");
	printf("2:ɾ��ͼ��\n");
	printf("3:��ʾ����ͼ��\n");
	printf("4:���ճ�������ʾͼ��\n");
	printf("5:���ձ�����ʾͼ��\n");
	printf("6:����������ʾͼ��\n");
	printf("0:������һ��\n");
	printf("����������ѡ��:\n");
}
void action_manage()//����Ա����
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
			printf("������һ����ݣ�");
			scanf("%d", &year);
			showBookListByBookList(find_book_by_year(year));
		}
		break;
		case 5:
		{
			char title[256];
			printf("������һ�����⣺");
			scanf("%s", title);
			showBookListByBookList(find_book_by_title(title));
		}
		break;
		case 6:
		{
			char author[1024];
			printf("������һ������������");
			getchar();
			fgets(author, 1024, stdin);
			author[strlen(author) - 1] = '\0';
			showBookListByBookList(find_book_by_author(author));
		}
		break;
		case 0:
			return;
		default:
			printf("������������\n");
			break;
		}
		system("pause");
	}
}
void user_menu()//�û��˵�
{
	system("cls");
	printf("ͼ�����ϵͳ\n");
	printf("1:����\n");
	printf("2:����\n");
	printf("3:��ʾ����ͼ��\n");
	printf("4:���ճ�������ʾͼ��\n");
	printf("5:���ձ�����ʾͼ��\n");
	printf("6:����������ʾͼ��\n");
	printf("0:������һ��\n");
	printf("����������ѡ��:\n");
}
void action_user()//�û�����
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
			printf("������һ����ݣ�");
			scanf("%d", &year);
			showBookListByBookList(find_book_by_year(year));
		}
		break;
		case 5:
		{
			char title[256];
			printf("������һ�����⣺");
			scanf("%s", title);
			showBookListByBookList(find_book_by_title(title));
		}
		break;
		case 6:
		{
			char author[1024];
			printf("������һ������������");
			getchar();
			fgets(author, 1024, stdin);
			author[strlen(author) - 1] = '\0';
			showBookListByBookList(find_book_by_author(author));
		}
		break;
		case 0:
			return;
		default:
			printf("������������\n");
			break;
		}
		system("pause");
	}
}
