#include <stdio.h>

int main() {
    char response;
    printf("Do you FW Skibidi Toilet? (Y/N) ");
    scanf(" %c", &response);

    if (response == 'Y' || response == 'y') {
        printf("LETS GOOOOOOO\n");
    } else if (response == 'N' || response == 'n') {
        printf("KYS DICKHEAD!\n");
    } else {
        printf("Invalid response.\n");
    } printf("Press Enter to exit.");
    getchar();
    getchar();

    return 0;
}
