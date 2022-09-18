
#include <cs50.h>
#include <stdio.h>

int main(void) {
    int x = 0;

    while (x <= 0 || x > 8) {
    x = get_int("Height: ");
    }

    string space = " ";
    for (int i = 1; i <= x; i++){

        for (int j = 1; j <= x; j++){
        if (j >= x - i + 1) {
            printf("#");
        }
        else {
            printf("%s", space);
        }
        }
        printf("\n");
   }
}
