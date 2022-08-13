#define _CRT_SECURE_NO_WARNINGS
#include"book_management.h"
BookList bookList;
#include<stdlib.h>
#include<string.h>
int store_books(FILE* file)//store book
{
	Book* p = bookList.list->next;
	while (p)
	{
		fprintf(file,"%d\n", p->id);
		fprintf(file, "%s\n", p->title);
		fprintf(file, "%d%s",strlen(p->authors), p->authors);
		fprintf(file, "%d\n", p->year);
		fprintf(file, "%d\n", p->copies);
		p = p->next;
	}
	fclose(file);
	return 1;
}

int load_books(FILE* file)//load book
{
	if (!file)
		return -1;
	Book* p;
	while (!feof(file))
	{
		p = (Book*)malloc(sizeof(Book));
		p->title= (char*)malloc(sizeof(char) * 256);
		p->authors = (char*)malloc(sizeof(char) * 1024);
		fscanf(file, "%d", &p->id);
		if (feof(file))
		{
			free(p);
			break;
		}
		fscanf(file, "%s", p->title);
		int len;
		fscanf(file, "%d", &len);
		//printf("%d", len);
		int i;
		for (i= 0; i < len; i++)
		{
			p->authors[i]=fgetc(file);
			//printf("|%c|", p->authors[i]);
			//system("pause");
		}
		p->authors[i] = '\0';
		fscanf(file, "%d", &p->year);
		//printf("%d\n", p->year);
		fscanf(file, "%d", &p->copies);
		//printf("%d\n", p->copies);
		p->next = bookList.list->next;
		bookList.list->next = p;
		bookList.length++;
	}
	fclose(file);
	return 1;
}

void createBookList()//Create a new list
{
	FILE* file = fopen("books.txt", "r");
	bookList.list = (Book*)malloc(sizeof(Book));
	bookList.list->next = NULL;
	bookList.length = 0;
	load_books(file);
}

void showAllBook()//print booklist
{
	Book*p= bookList.list->next;
	int i;
	if (p == NULL)
	{
		printf("No book!\n");
		return;
	}
	printf("Book ID\t\tBook title\t\tauthors\t\tyear\t\tnumber of copies the library has\n");
	while (p)
	{
		printf("%d\t\t",p->id); 
		printf("%s\t\t",p->title); 
		printf("[");
		for (i = 0; i < strlen(p->authors); i++)
		{
			if (p->authors[i] == '\n')
			{
				printf("]");
				if(i!= strlen(p->authors)-1)
					printf("[");
			}
			else
			printf("%c", p->authors[i]);
		}
		printf("\t\t%d\t\t\t",p->year);
		printf("%d\n",p->copies);
		p = p->next;
	}
	printf("\n");
}

int add_book(Book book)//add book
{
	Book *b=(Book*)malloc(sizeof(Book));
	*b = book;
	b->next=bookList.list->next;
	bookList.list->next = b;
	bookList.length++;
	store_books(fopen("books.txt", "w"));
	printf("Add success!\n");
	return 1;
}

int remove_book(Book book)//remove book
{
	Book* p = bookList.list;
	while (p->next)
	{
		if (book.id == p->next->id)
		{
			Book* p2 = p->next;
			p->next = p2->next;
			free(p2);
			printf("Delete the success!\n");
			bookList.length--;
			store_books(fopen("books.txt", "w"));
			return 1;
		}
		p = p->next;
	}
	printf("Delete failed!\n");
	return -1;
}

//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title(const char* title)
{
	BookList newBookList;
	newBookList.list = (Book*)malloc(sizeof(Book));
	newBookList.list->next = NULL;
	newBookList.length = 0;
	Book* p = bookList.list->next;
	while (p)
	{
		if (strcmp(p->title,title)==0)
		{
			Book* p2 = (Book*)malloc(sizeof(Book));
			*p2 = *p;
			p2->title = (char*)malloc(sizeof(p->title));
			strcpy(p2->title, p->title);
			p2->authors = (char*)malloc(sizeof(p->authors));
			strcpy(p2->authors, p->authors);
			p2->next = newBookList.list->next;
			newBookList.list->next = p2;
			newBookList.length++;
		}
		p = p->next;
	}
	return newBookList;
}

int theBookIsHaveTheAuthor(char* authors, const char* author)//Identify and obtain a title
{
	char* p;
	p = strtok(authors, "\n");
	while (p)
	{
		if (strcmp(p, author)==0)
		{
			return 1;
		}
		p = strtok(NULL, "\n");
	}
	return 0;
}

//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author(const char* author)
{
	BookList newBookList;
	newBookList.list = (Book*)malloc(sizeof(Book));
	newBookList.list->next = NULL;
	newBookList.length = 0;
	Book* p = bookList.list->next;
	while (p)
	{
		char* pauthor = (char*)malloc(strlen(p->authors) + 1);
		strcpy(pauthor, p->authors);
		if (theBookIsHaveTheAuthor(pauthor,author))
		{
			Book* p2 = (Book*)malloc(sizeof(Book));
			*p2 = *p;
			p2->title = (char*)malloc(strlen(p->title)+1);
			strcpy(p2->title, p->title);
			p2->authors = (char*)malloc(strlen(p->authors) + 1);
			strcpy(p2->authors, p->authors);
			p2->next = newBookList.list->next;
			newBookList.list->next = p2;
			newBookList.length++;
		}
		p = p->next;
	}
	return newBookList;
}

//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the 
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_year(unsigned int year)
{
	BookList newBookList;
	newBookList.list = (Book*)malloc(sizeof(Book));
	newBookList.list->next = NULL;
	newBookList.length = 0;
	Book* p = bookList.list->next;
	while (p)
	{
		if (p->year == year)
		{
			Book *p2= (Book*)malloc(sizeof(Book));
			*p2 = *p;
			p2->next=newBookList.list->next;
			newBookList.list->next = p2;
			newBookList.length++;
		}
		p = p->next;
	}
	return newBookList;
}

void showBookListByBookList(BookList bL)//print the booklist
{
	Book* p = bL.list->next;
	if (p == NULL)
	{
		printf("No book!\n");
		return;
	}
	printf("----------------------------------------------\n");
	while (p)
	{
		printf("****************************\n");
		printf("Book ID:%d\n", p->id);
		printf("Book title:%s\n", p->title);
		if(p->authors[strlen(p->authors)-1]=='\n')
			printf("authors:\n%s", p->authors);
		else
			printf("authors:\n%s\n", p->authors);
		printf("year of publication:%d\n", p->year);
		printf("number of copies the library has:%d\n", p->copies);
		p = p->next;
		printf("****************************\n");
	}
	printf("----------------------------------------------\n");
}

Book getBookById()//Access book id
{
	Book b;
	printf("please enter Book ID:");
	scanf("%d", &b.id);
	return b;
}

Book* getBookPointById()//Look up books by isBN number
{
	Book b=getBookById();
	Book* p = bookList.list->next;
	while (p)
	{
		if (p->id == b.id)
		{
			return p;
		}
		p = p->next;
	}
	return NULL;
}

Book inputBook()//Store books
{
	Book b;
	printf("please enter Book ID:");
	scanf("%d", &b.id);
	printf("please enter book title:");
	b.title = (char*)malloc(sizeof(char) * 256);
	scanf("%s", b.title);
	printf("please enter author number:");
	int cnt;
	int i;
	scanf("%d", &cnt);
	getchar();
	char name[256];
	b.authors = (char*)malloc(sizeof(char) * 1024);
	b.authors[0] = '\0';
	for (i = 1; i <= cnt; i++)
	{
		printf("please enter number %d author name:", i);
		fgets(name, 256, stdin);
		strcat(b.authors, name);
	}
	printf("please enter year of publication:");
	scanf("%d", &b.year);
	printf("please enter number of copies the library has:");
	scanf("%d", &b.copies);
	return b;
}