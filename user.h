#include <stdio.h>

typedef struct _User {
	    char *username;
        char *password;
		struct _User *next; //pointer to the next book element
}User;

typedef struct _UserList {
	 User* list; // pointer to a list of struct Book.
	 unsigned int length; // number of elements in the (Book*) List 
}UserList;