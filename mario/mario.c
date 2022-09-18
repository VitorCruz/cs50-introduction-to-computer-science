
#include <cs50.h>
#include <stdio.h>

// INSERT MORE COMMENTS HERE :)

int main(void)
{
    int x = 0;

    while (x <= 0 || x > 8)
    {
        x = get_int("Height: ");
    }

    string espace = " ";
    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= x * 2 + 2 ; j++)
        {
            if (j >= x - i + 1 && j <= x)
            {
                printf("#");
            }
            else if (j > x + 2 && j <= x + 2 + i)
            {
                printf("#");
            }
            else
            {
                printf("%s", espace);
            }
        }
        printf("\n");
    }
}

/*

*/