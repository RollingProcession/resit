#ifndef USER_GUARD__H 
#define USER_GUARD__H
#include <stdio.h>
typedef struct _User {
	char name[50];//姓名
	char uName[20];//用户名
	char passWord[20];//密码
	struct _User* next; //pointer to the next User element
}User;

typedef struct _UserList {
	User* list; // pointer to a list of struct _User.
	unsigned int length; // number of elements in the (_User*) List 
}UserList;
int login();
int regist();
int read(FILE* file);
int save(FILE* file);
void createUserList();
int isManager(int uIndex);
void borrow_book();
void return_book();
char* getName(int index);
#endif