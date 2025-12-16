#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH_AUTHOR_NAME 60
#define MAX_LENGTH_BOOK_HEADER 60
#define MAX_LENGTH_BOOK_CATEGORY 60

struct Book {
    char author_name[MAX_LENGTH_AUTHOR_NAME];
    char header[MAX_LENGTH_AUTHOR_NAME];
    unsigned short year;
    unsigned long long price;
    char category[MAX_LENGTH_BOOK_CATEGORY];
} book777;

void print_book(struct Book* book) {
    printf("Author: %s\n", book->author_name);
    printf("Header: %s\n", book->header);
    printf("Yeader: %d\n", book->year);
    printf("Price: %d\n", book->price);
    printf("Category: %s\n", book->category);
}

void fill(struct Book* book, char author[], char header[], int year, int price, char category[]) {
    book->year = year;
    book->price = price;
    if (sizeof(author) >= MAX_LENGTH_AUTHOR_NAME || sizeof(header) >= MAX_LENGTH_BOOK_HEADER || sizeof(category) >= MAX_LENGTH_BOOK_CATEGORY) {
        printf("Size error!\n");
    } else {
        for (int i = 0; author[i] != '\0'; i++) book->author_name[i] = author[i];
        for (int i = 0; header[i] != '\0'; i++) book->header[i] = header[i];
        for (int i = 0; category[i] != '\0'; i++) book->category[i] = category[i];
    }
}

int main() {
    // 4а, 4б, 4г
    struct Book book1 = {"Pushkin", "Evegen Onegen", 1825, 352, "Golden Century"};
    struct Book book2;

    char author[] = "Tolstory";
    char header[] = "War and peace";
    int year = 1888;
    int price = 500;
    char category[] = "Bronze Century";
    fill(&book2, author, header, year, price, category);
    print_book(&book2);

    // 4в
    static struct Book book3;
    struct Book* p_book4 = (struct Book*) malloc(sizeof(struct Book));
    return 0;
}