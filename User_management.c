#define _CRT_SECURE_NO_WARNINGS
#include"User_management.h"
#include"book_management.h"
#include<string.h>
#include<stdlib.h>
UserList uList;

int save(FILE* file)
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
int read(FILE* file)
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
void createUserList()
{
	FILE* file=fopen("userAndPassword.txt","r");
	uList.list = (User*)malloc(sizeof(User));
	uList.list->next = NULL;
	uList.length = 0;
	read(file);
}
int login()
{
	User u;
	unsigned int i;
	User* p;

	while (1)
	{
		printf("�������û���:");
		scanf("%s", u.uName);
		if (strlen(u.uName) > 18)
		{
			printf("�û������ȴ���18������������!\n");
		}
		else
			break;
		while (getchar() != '\n')
			;
	}
	while (1)
	{
		printf("����������:");
		scanf("%s", u.passWord);
		if (strlen(u.passWord) > 18)
		{
			printf("���볤�ȴ���18������������!\n");
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
				printf("��¼�ɹ���\n");
				return i;//���ص�ǰ��¼�û����±�
			}
			else	
			{
				printf("�������󣡵�¼ʧ�ܣ�\n");
				return -1;
			}
		}
		p = p->next;
	}
	printf("��ǰ�û�δע�ᣡ\n");
	return -1;
}
int regist()
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
		printf("�������û���:");
		scanf("%s", u->uName);
		if (strlen(u->uName) > 18)
		{
			printf("�û������ȴ���18������������!\n");
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
			printf("����������:");
			scanf("%s", u->passWord);
			if (strlen(u->passWord) > 18)
			{
				printf("���볤�ȴ���18������������!\n");
			}
			else
				break;
			while (getchar() != '\n')
				;
		}
		printf("��ȷ������:");
		scanf("%s", password2);
		if (strcmp(password2, u->passWord) != 0)
		{
			printf("�������벻һ�£����������룡\n");
		}
		else
			break;
	}
	for (i = 0, p = uList.list->next; i < uList.length; i++) {
		if (strcmp(p->uName, u->uName) == 0)
		{
			printf("�û����Ѵ��ڣ�ע��ʧ�ܣ�\n");
			free(u);
			return -1;
		}
		p = p->next;
	}
	printf("������������");
	scanf("%s", u->name);
	u->next = uList.list->next;
	uList.list->next = u;
	uList.length++;
	printf("ע��ɹ���\n");
	file = fopen("userAndPassword.txt", "w");
	save(file);
	return 1;
}
int isManager(int uIndex)
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
void borrow_book()
{
	Book*b=getBookPointById();
	int cnt;
	printf("��������Ҫ���ĵı���:");
	scanf("%d", &cnt);
	if (cnt > b->copies)
	{
		printf("��治�㣬����ʧ�ܣ�\n");
	}
	else
	{
		b->copies -= cnt;
		printf("���ĳɹ���\n");
	}
}
void return_book()
{
	Book* b = getBookPointById();
	int cnt;
	printf("��������Ҫ�黹�ı���:");
	scanf("%d", &cnt);
	b->copies += cnt;
	printf("�黹�ɹ���\n");
}
char* getName(int index)
{
	User* p = uList.list->next;
	int i;
	for (i = 0; i < index; i++)
	{
		p = p->next;
	}
	return p->uName;
}