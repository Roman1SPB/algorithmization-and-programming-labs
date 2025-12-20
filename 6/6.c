#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_BOOK_AUTHOR 60
#define MAX_LENGTH_BOOK_TITLE 60
#define MAX_LENGTH_BOOK_CATEGORY 60
#define TOTAL_BOOK_ATTRIBUTES_LENGTH (MAX_LENGTH_BOOK_AUTHOR+MAX_LENGTH_BOOK_TITLE+MAX_LENGTH_BOOK_CATEGORY+32)

int library_max_size = 5;
int library_size = 0;

struct Book {
    char author[MAX_LENGTH_BOOK_AUTHOR];
    char title[MAX_LENGTH_BOOK_TITLE];
    int year;
    int price;
    char category[MAX_LENGTH_BOOK_CATEGORY];
};

struct Book* library;

int check_input(int choice, int handle_input_error, int range_from, int range_to) {
    if (handle_input_error == 0 || choice < range_from || choice > range_to) {
        printf("There is input mistake\n");
        fflush(stdin);
        return 0;
    } else return 1;
}
// case 1: Just printing all book titles
void print_library() {
    if (library_size == 0) {
        printf("There are no books in library\n");
        return;
    }

    for (int i = 0; i < library_size; i++) {
        printf("Book %d:\n", i+1);
        printf("Book author: %s\n", library[i].author);
        printf("Book title: %s\n", library[i].title);
        printf("Book category: %s\n", library[i].category);
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

    printf_s("Write author\n");
    handle_input_strings(MAX_LENGTH_BOOK_AUTHOR, library[library_size].author);
    printf_s("Write title\n");
    handle_input_strings(MAX_LENGTH_BOOK_TITLE, library[library_size].title);
    printf_s("Write category\n");
    handle_input_strings(MAX_LENGTH_BOOK_CATEGORY, library[library_size].category);
    printf("Write year\n");
    int check_input1_error = scanf_s("%d", &library[library_size].year);
    printf("Write price\n");
    int check_input2_error = scanf_s("%d", &library[library_size].price);

    int check_input1_result = check_input(library[library_size].year, check_input1_error, -10000, 10000);
    int check_input2_result = check_input(library[library_size].year, check_input2_error, -10000, 10000);
    if (check_input1_result == 0 || check_input2_result == 0) return scan_new_book();
    else library_size++;
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
        if (library_size != 1) library[index_book_to_delete] = library[library_size-1];
        printf("Book successfully deleted!\n");
        library_size--;
    }

}

// case 4: Saving all library books to file
void write_library_to_drive() {
    FILE *fptr;
    fptr = fopen("library_output.txt", "w");

    for (int i = 0; i < library_size; i++) {
        fprintf(fptr, "%s\n%s\n%s\n%d\n%d\n", library[i].author, library[i].title, library[i].category, library[i].year, library[i].price);
    }
    fclose(fptr);
    printf("Library successfully saved to 'library_output.txt' file\n");
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

// case 5: get books from file(library_input.txt) to library
void write_from_drive_to_library() {
    FILE *fptr;
    fptr = fopen("library_input.txt", "r");
    if (fptr == NULL) {
        printf("You should create file 'library_input.txt' and place books there\n");
        return;
    }

    int library_size_copy = library_size;
    for (int i = library_size_copy; !feof(fptr); i++) {
        fgets(library[i].author, MAX_LENGTH_BOOK_AUTHOR, fptr);
        change_last_char_to_null_char(library[i].author);
        fgets(library[i].title, MAX_LENGTH_BOOK_TITLE, fptr);
        change_last_char_to_null_char(library[i].title);
        fgets(library[i].category, MAX_LENGTH_BOOK_CATEGORY, fptr);
        change_last_char_to_null_char(library[i].title);
        fscanf(fptr, "%d\n", &library[i].year);
        fscanf(fptr, "%d\n", &library[i].price);

        library_size++;
        check_library_size();
    }
    
    fclose(fptr);
}

void print_menu_actions() {
    printf("1 - Print library titles\n");
    printf("2 - Scan new book\n");
    printf("3 - Delete book\n");
    printf("4 - Write library to drive\n");
    printf("5 - Write from file\n");
    printf("6 - Sort library\n");
    printf("7 - Exit\n");
}

void swap_books(struct Book* book1, struct Book* book2) {
    struct Book temp = *book1;
    *book1 = *book2;
    *book2 = temp;
}

short cmp_author(struct Book* book1, struct Book* book2) {
    int cmp_result = compare_strings(book1->author, book2->author);
    return (cmp_result == 1) ? 0 : 1;
}
short cmp_title(struct Book* book1, struct Book* book2) {
    int cmp_result = compare_strings(book1->title, book2->title);
    return (cmp_result == 1) ? 0 : 1;
}

short cmp_price(struct Book* book1, struct Book* book2) {
    return (book1->price < book2->price) ? 0 : 1;
}

short cmp_year(struct Book* book1, struct Book* book2) {
    return (book1->year <= book2->year) ? 0 : 1;
}

short cmp_category(struct Book* book1, struct Book* book2) {
    int cmp_result = compare_strings(book1->category, book2->category);
    return (cmp_result == 1) ? 0 : 1;
}

void print_criteria() {
    printf("1 - Sort by author\n");
    printf("2 - Sort by title\n");
    printf("3 - Sort by catergory\n");
    printf("3 - Sort by year\n");
    printf("4 - Sort by price\n\n");
    
    printf("1 - Increase order\n");
    printf("2 - Decrease order\n");
}

void sort_books(short (*cmp)(struct Book* book1, struct Book* book2), int order) {
    // order: 1 - increae, 2 - decrease 
    for (int i = 0; i < library_size; i++) {
        struct Book* criteria_book = &library[i];
        for (int j = i + 1; j < library_size; j++) {
            short cmp_result = cmp(&library[j], criteria_book);
            if (cmp_result == 0 && order == 1) criteria_book = &library[j];
            if (cmp_result == 1 && order == 2) criteria_book = &library[j];
        }
        
        swap_books(&library[i], criteria_book);
    }
}

void sort_criteria() {
    print_criteria();
    int criteria, order;
    int handle_input1_error = scanf("%d", &criteria);
    int handle_input2_error = scanf("%d", &order);
    int check_input1_result = check_input(criteria, handle_input1_error, 1, 5);
    int check_input2_result = check_input(order, handle_input2_error, 1, 2);
    if (check_input1_result == 0 || check_input2_result == 0) return sort_criteria();

    switch (criteria) {
        case 1:
            sort_books(cmp_author, order);
            break;
        case 2:
            sort_books(cmp_title, order);
            break;
        case 3:
            sort_books(cmp_category, order);
            break;
        case 4:
            sort_books(cmp_year, order);
            break;
        case 5:
            sort_books(cmp_price, order);
            break;
        default:
            printf("switch error???76\n");
            break;
    }
} 

// Menu actions with our library
void menu() {
    print_menu_actions();
    int action;
    int handle_input_error = scanf_s("%d", &action);
    
    int check_menu_result = check_input(action, handle_input_error, 1, 7);
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
            sort_criteria();
            break;
        case 7:
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