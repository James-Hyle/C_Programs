#include <stdio.h>

int main(void) {

    printf("%f\n", 3.14159);
    printf("%c\n", 'G');
    printf("%d\n", 'G');
    printf("%s\n", "Hello, world!");
    printf("%.3f\n", 3.14159);
    printf("%+.5f\n", 3.14);
    printf("%x\n", 29);
    printf("%o\n", 29);
    printf("%d\t%d\n", 10, 20);
    printf("\a\a\a\a\n");
    printf("%d\b%d", 100, 7);

    return 0;
}
