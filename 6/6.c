#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH_AUTHOR_NAME 60
#define MAX_LENGTH_BOOK_TITLE 60
#define MAX_LENGTH_BOOK_CATEGORY 60
#define MAX_TOTAL_LENGTH (MAX_LENGTH_AUTHOR_NAME+MAX_LENGTH_BOOK_TITLE+MAX_LENGTH_BOOK_CATEGORY+32)

int library_max_size = 5;
int library_size = 0;

struct Book {
    char author_name[MAX_LENGTH_AUTHOR_NAME];
    char title[MAX_LENGTH_BOOK_TITLE];
    int year;
    int price;
    // char category[MAX_LENGTH_BOOK_CATEGORY];
};

struct Book* library;


// case 1: Just printing all book titles
void print_library() {
    if (library_size == 0) {
        printf("There are no books in library\n");
        return;
    }

    for (int i = 0; i < library_size; i++) {
        printf("Book %d:\n", i+1);
        printf("Author name: %s\n", library[i].author_name);
        printf("Book title: %s\n", library[i].title);
        printf("Year published: %d\n", library[i].year);
        printf("Book price: %d\n", library[i].price);
        printf("\n");
    }
}

// Input for author name, title and catergory
void handle_input_strings(const int LIMIT, char strng[]) {
    for (int i = 0; i < LIMIT; i++) {
        char ch; scanf("%c", &ch);
        if (ch == '\n') {
            strng[i] = '\0';
            break;
        } else strng[i] = ch;
    }
}


void check_library_size() {
    if (library_size >= library_max_size) {
        library_max_size *= 2;
        library = realloc(library, sizeof(struct Book) * library_max_size);
    }
}

// case 2: Input (scanf_s) new book
void scan_new_book() {
    check_library_size();

    printf_s("Write author name\n");
    handle_input_strings(MAX_LENGTH_AUTHOR_NAME, library[library_size].author_name);
    printf_s("Write title\n");
    handle_input_strings(MAX_LENGTH_BOOK_TITLE, library[library_size].title);
    printf("Write year\n");
    scanf_s("%d", &library[library_size].year);
    printf("Write price\n");
    scanf_s("%d", &library[library_size].price);
    library_size++;
}

// Compare strings function from previous labs
int compare_strings(void* str1, void* str2) {
    char* char_str1 = (char*) str1;
    char* char_str2 = (char*) str2;
    int i = 0;
    char end = '\0';
    while (char_str1[i] != end && char_str2[i] != end) {
        if (char_str1[i] < char_str2[i]) return 1;
        else if (char_str1[i] > char_str2[i]) return -1;
        i++;
    }
    if (char_str1[i] == end && char_str2[i] == end) return 0;
    if (char_str2[i] == end) return -1;
    if (char_str1[i] == end) return 1;
    
    return 1;
}

// We return the index in library(array of struct Book)
// otherwise, -1(if title not founded)
int find_book_in_library(char book_title[]) {
    int string_compare_result = -1;
    for (int i = 0; i < library_size; i++) {
        string_compare_result = compare_strings(library[i].title, book_title);
        if (string_compare_result == 0) {
            return i;
        }
    }

    return -1;
}

// Just swap to field(for example titles)
void swap_books_fields(char array1[], char array2[], int limit) {
    for (int i = 0; i < limit; i++) {
        array1[i] = array2[i];
        if (array1[i] == '\0') break;
    }
}

// case 3: Delete book from library
// Actually, we just replace the last 
// book fields to book, which we want to delete and then decresse
// library_size by one
void delete_book() {
    if (library_size == 0) {
        printf("There are no books in library\n");
        return;
    }

    printf("Write book's title\n");
    char book_title[MAX_LENGTH_BOOK_TITLE];
    handle_input_strings(MAX_LENGTH_BOOK_TITLE, book_title);

    int index_book_to_delete = find_book_in_library(book_title);
    if (index_book_to_delete == -1) printf("Title book not founded!\n");
    else {
        if (library_size != 1) {
            swap_books_fields(library[index_book_to_delete].author_name, library[library_size-1].author_name, MAX_LENGTH_AUTHOR_NAME);
            swap_books_fields(library[index_book_to_delete].title, library[library_size-1].title, MAX_LENGTH_BOOK_TITLE);
            library[index_book_to_delete].price = library[library_size-1].price;
            library[index_book_to_delete].year = library[library_size-1].price;
        }

        library_size--;
    }

}

// case 4: Saving all library books to file
void write_library_to_drive() {
    FILE *fptr;
    fptr = fopen("library_output.txt", "w");

    for (int i = 0; i < library_size; i++) {
        fprintf(fptr, "%s\n%s\n%d\n%d\n", library[i].author_name, library[i].title, library[i].year, library[i].price);
    }
    fclose(fptr);
}  

void write_to_library_field(int start, int end, char buff[], char field[]) {
    for (int i = start; i < end; i++) {
        field[i] = buff[i];
    }

    field[end] = '\0';
}

void change_last_char_to_null_char(char buff[]) {
    int i = 0;
    while (buff[i] != '\n') i++;
    buff[i] = '\0';
}

// case 5: get books from file(library_input.txt) to ram
void write_from_drive_to_library() {
    FILE *fptr;
    fptr = fopen("library_input.txt", "r");

    int library_size_copy = library_size;
    for (int i = library_size_copy; !feof(fptr); i++) {
        fgets(library[i].author_name, MAX_LENGTH_AUTHOR_NAME, fptr);
        change_last_char_to_null_char(library[i].author_name);
        fgets(library[i].title, MAX_LENGTH_BOOK_TITLE, fptr);
        change_last_char_to_null_char(library[i].title);
        fscanf(fptr, "%d\n", &library[i].year);
        fscanf(fptr, "%d\n", &library[i].price);

        library_size++;
        check_library_size();
    }
    
    fclose(fptr);
}


int check_menu_input(int action, int handle_input_error) {
    if (handle_input_error == 0 || action < 1 || action > 6) {
        printf("There is input mistake\n");
        return 0;
    } else return 1;
}

void print_menu_actions() {
    printf("1 - Print library titles\n");
    printf("2 - Scan new book\n");
    printf("3 - Delete book\n");
    printf("4 - Write library to drive\n");
    printf("5 - Write from file\n");
    printf("6 - Exit\n");
}

// Menu actions with our library
void menu() {
    print_menu_actions();
    int action;
    int handle_input_error = scanf_s("%d", &action);
    
    int check_menu_result = check_menu_input(action, handle_input_error);
    if (check_menu_result == 0) return menu();

    char ch; scanf("%c", &ch); // Last useless charachter '\n'
    switch (action) {
        case 1:
            print_library();
            break;
        case 2:
            scan_new_book();
            break;
        case 3:
            delete_book();
            break;
        case 4:
            write_library_to_drive();
            break;
        case 5:
            write_from_drive_to_library();
            break;
        case 6:
            return;
        default:
            printf("switch error???67\n");
            break;
    }

    return menu();
}

void preparing_library() {
    library = (struct Book*) malloc(sizeof(struct Book) * library_max_size);
}

int main() {
    preparing_library();
    menu();

    return 0;
}
