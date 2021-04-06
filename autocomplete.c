#include<stdio.h>
#include<string.h> 
#include<stdlib.h>
#include<dirent.h>

struct node *lists[128] = {NULL}; 
char dirpath[128];

struct node { 
    char file[128]; // string for file name 
    struct node *next;  
};

void insert(char file[]) { // create new node in alphabetically correct position in linked list 

    struct node *pointer = lists[file[0]]; // starting location for list 
    struct node *link = malloc(sizeof(struct node)); // node to be inserted 
    strcpy(link->file, file); 

    if (pointer == NULL || strcmp(pointer->file, file) > 0) { 
        // either first time a file has appeared with this first letter or file name belongs at the beginning of list 
        link->next = lists[file[0]];
        lists[file[0]] = link;  
        return;
    }    

    while (pointer->next != NULL && strcmp(pointer->next->file, file) < 0) 
        pointer = pointer->next; // find where file name belongs alphabetically 
    
    link->next = pointer->next;
    pointer->next = link; // insert new node 
}

int main() {

    DIR *dir;
    struct dirent *entry;

    printf("Enter a folder name: ");
    scanf("%s", dirpath); // get user input, trusting that they don't clobber something because I'm too lazy to stop them 

    dir = opendir(dirpath);

    while((entry = readdir(dir)) != NULL) 
        insert(entry->d_name); // read in file names 
    closedir(dir);

    char input[128];
    while (strcmp(input, "exit") != 0) {

        scanf("%s", input);
        printf("\n");

        struct node *temp = lists[input[0]]; // pointer to walk through linked list 
        
        while (temp != NULL) {
            if (strncmp(temp->file, input, strlen(input)) == 0) { // compare first n chars of input to file names, n being length of input
                printf("%s\n", temp->file);
            }
            temp = temp->next;
        }
        printf("\n");
    }
    return(0);
}
