#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <conio.h>
#include "user.h"
pNode createList()
{
    pNode pHead = (pNode)malloc(sizeof(LNode));
    pHead->next=NULL;
    FILE *fp = fopen("USER.txt","r+");
    if(NULL == fp)
    {
        printf("FILE NOT FOUND");
        exit(-1);
    }
	
    pNode cur = pHead;
    while(1)
    {
        pNode temp = (pNode)malloc(sizeof(LNode));
        if(!temp)
            exit(-1);
            
        if(2!=fscanf(fp,"%s%s",temp->name,temp->pass))
        {
            free(temp);
            break;
        }
		
        cur->next=temp;

        cur = temp;

        cur->next = NULL;
    }
    return pHead;
}

//Log in
int login(pNode head)
{
    if(NULL==head->next)
    {
        printf("user list empty\n");
        getchar();
        return 0;
    }
    char name[10];
    char pass[10];
    printf("enter your name:");
    scanf("%s",name);
    printf("enter your password:");
    scanf("%s",pass);
    pNode temp = head->next;
    while(temp)
    {
        if(0==strcmp(temp->name,name) && 0==strcmp(temp->pass,pass))
        {
            printf("success");
            getchar();
            return 1;
        }
        temp = temp->next;
    }
    printf("user not found");
    getch();
}

void writeToFile(pNode head)
{
    FILE *fw = fopen("user.txt","a+");
    pNode temp=head->next;
    if(temp==NULL){
        return;
    }
    while(temp){
        fprintf(fw,temp->name);
        fprintf(fw,"\t");
        fprintf(fw,temp->pass);
        fprintf(fw,"\n");
        temp  = temp->next;
    }
}


//sign in
void registerUser(pNode head)
{
    char name[10];
    char pass[10];
    pNode temp = head->next;
    if(!temp)
    {
        temp = (pNode)malloc(sizeof(LNode));
        head->next = temp;
    }
    else
    {
        while(temp->next)
        {
            temp = temp->next;
        }
        pNode last = (pNode)malloc(sizeof(LNode));
        temp->next = last;
        temp = last;
    }
    int c=1;
    printf("enter your name:");
    scanf("%s",name);//Check whether the user name already exists
    if(0==strcmp(temp->name,name)){
        printf("The user name already exists!\n");
        while(c){
            if(0==strcmp(temp->name,name)){
                printf("enter your name again:\n");
                scanf("%s",name);
                c=1;
            }
            else{
                c=0;
                printf("The user name is available. Please enter the user name again!\n");
                scanf("%s",temp->name);
            }
        }
    }
    else{
        printf("The user name is available. Please enter the user name again!\n");
        scanf("%s",temp->name);
    }
    
    c=1;//Check whether the two passwords are the same
    while(c){
        printf("enter your password:");
        scanf("%s",temp->pass);
        printf("enter your password again:");
        scanf("%s",temp->pass2);
        if("pass==pass2"){
            printf("Successful registration!\n");
            c=0;
        }
        else{
            printf("The two passwords are different!\n");
            c=1;
        }
    }
    temp->next=NULL;
}

int menu2()//User Login Page
{
    int choice;
    printf("1.login\n");
    printf("2.register\n");
    printf("3.exit\n");
    printf("enter your choice:");
    scanf("%d",&choice);
    return choice;
}

int main()
{
    int choice;
    pNode head = createList();
    while(1)
    {
        choice = menu2();
        if(1==choice)
        {
            system("cls");
            if(login(head))
            {
                //这里写登陆成功的模块
            }
        }
        else if(2==choice)
        {
            system("cls");
            registerUser(head);
        }
        else if(3==choice)
        {
            writeToFile(head);//Save and exit
            return 0;
        }
        else{
            system("cls");
            printf("Invalid instruction, please enter again!\n");
            main();
        }
    }
}