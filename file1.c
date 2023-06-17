#include <stdio.h>
#include <string.h>

void removeBetweenTs(char* str) {
    char* start = strchr(str, 't');
    char* end = strrchr(str, 't');

    if (start && end && end > start) {
        size_t length = strlen(end + 1) + 1;
        memmove(start + 1, end + 1, length);
    }
}

int main() {
    char str[] = "Lorem ipsum salutiiiiiiiiiiiiitoi dolor sit amet, consectetur adipiscing elit.";

    printf("Avant suppression : %s\n", str);

    removeBetweenTs(str);

    printf("Après suppression : %s\n", str);

    return 0;
}








