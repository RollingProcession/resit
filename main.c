#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "user.h"

int main( int argc, char **argv )
{
	BookList *book_all;
	book_all = (BookList *)malloc(sizeof(BookList));
	book_all->list = (Book *)malloc(sizeof(Book));

	UserList *user_all;
	user_all = (UserList *)malloc(sizeof(UserList));
	user_all->list = (User *)malloc(sizeof(User));

	FILE *fp;

	fp = fopen("book.txt", "r");
	if( fp == NULL) {
		printf("\nError, BOOK FILE does not exist.\n");
		exit(0);
	}
	load_books(fp, book_all);
	fclose(fp);

	fp = fopen("user.txt", "r");
	if( fp == NULL) {
		printf("\nError, USER FILE does not exist.\n");
		exit(0);
	}
	load_users(fp, user_all);
	fclose(fp);



	int Judgement_condition = 1;
	int option;
	while( Judgement_condition ){
		printf("-----------------------------------");
		printf("\n Please choose an option: \n");
		printf("\n (1) Register an account \n");
		printf("\n (2) Login \n");
		printf("\n (3) Search for books \n");
		printf("\n (4) Display all books \n");
		printf("\n (5) Quit \n");
		printf("\n Please enter the Option: \n");
		option = optionChoice();

		if( option == 1 ) {
			reg(user_all);
		}
		else if( option == 2 ) {
			char *name;
			name = (char*)malloc(sizeof(char));
			strcpy(name, login(user_all));
			if(name == NULL){
				//TODO
			}
			else if(strcmp(name, "librarian") == 0){
				librarianCLI(book_all);
			}
			else if(name){
				userCLI(book_all, name);
			}
		}
		else if( option == 3 ) {
			printf("\nLogging search menu...\n");
			searchCLI(book_all);
		}
		else if( option == 4 ) {
			display_all(book_all);
		}
		else if( option == 5 ) {
			Judgement_condition = 0;
			printf("\nThank you for using the library system!\n");
		}
		else
			printf("\nSorry, the option you entered was invalid, please try again.\n");
	}

	free(book_all);
	free(user_all);

	return 0;
}
