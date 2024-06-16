#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

char text[MAX] = "";
char clipboard[MAX] = "";

void display() {
    printf("Current Text:\n%s\n", text);
}

void copy(int start, int length) {
    strncpy(clipboard, text + start, length);
    clipboard[length] = '\0';
    printf("Copied: %s\n", clipboard);
}

void cut(int start, int length) {
    copy(start, length);
    int textLen = strlen(text);
    memmove(text + start, text + start + length, textLen - start - length + 1);
    printf("Cut: %s\n", clipboard);
}

void paste(int start) {
    char newText[MAX] = "";
    strncpy(newText, text, start);
    newText[start] = '\0';
    strcat(newText, clipboard);
    strcat(newText, text + start);
    strcpy(text, newText);
    printf("Pasted: %s\n", clipboard);
}

int main() {
    int choice, start, length;

    while (1) {
        printf("\nText Editor\n");
        printf("1. Display Text\n");
        printf("2. Copy\n");
        printf("3. Cut\n");
        printf("4. Paste\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display();
                break;
           



 case 2:
                printf("Enter start position and length to copy: ");
                scanf("%d %d", &start, &length);
                copy(start, length);
                break;
            case 3:
                printf("Enter start position and length to cut: ");
                scanf("%d %d", &start, &length);
                cut(start, length);
                break;
            case 4:
                printf("Enter start position to paste: ");
                scanf("%d", &start);
                paste(start);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
