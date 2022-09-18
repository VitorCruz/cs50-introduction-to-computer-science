
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string key = argv[1];
    int count_key = strlen(key);
    char key_lower[count_key];
    int key_location[count_key];

    string plaintext = get_string("Plaintext: ");
    int count_text = strlen(plaintext);
    char cipherkey[count_text];

    if (argc == 1)
    {
        printf("DIGITAR SENHA");
        return 1;
    }
    if (argc > 2)
    {
        printf("TOO MUCH INFO");
        return 1;
    }

    for (int i = 0; i < count_key; i++)
    {
        if (key[i] < 65 || key[i] > 122 || (key[i] > 90 && key[i] < 97))
        {
            printf("KEY CONTAINS A NOT ALFABETIC CHARACTER");
            return 1;
        }
    }
    // FALTA IMPLEMENTAR O APENAS LETRAS DIFERENTES
    if (count_key != 26)
    {
        printf("CHAVE INCORRETA! NECESSÁRIO TER 26 CARACTERES E APENAS 1 CORRESPONDÊNCIA POR LETRA");
        return 1;
    }

    for (int i = 0; i < count_key; i++)
    {
       key_lower[i] = tolower(key[i]);
    }

    // THE SUM OF ALL LETTERS IN THE KEY - 97 MUST BE 325 IF THEY ARE UNIQUE
    int sum_letters = 0;
    for (int i = 0; i < count_key; i++)
    {
       sum_letters += key_lower[i] - 97;
    }

    if (sum_letters != 325)
    {
        printf("KEY MUST HAVE UNIQUE LETTERS\n");
        return 1;
    }

    for (int i = 0; i < count_key; i++)
    {
       key_location[i] = (int) key_lower[i] - (97 + i);
    }

    for (int i = 0; i < count_text; i++)
    {
       if (plaintext[i] >= 65 && plaintext[i] <= 90)
       {
            int loc = plaintext[i] - 65;
            cipherkey[i] = plaintext[i] + key_location[loc];
       }
       else if (plaintext[i] >= 97 && plaintext[i] <= 122)
       {
            int loc = plaintext[i] - 97;
            cipherkey[i] = plaintext[i] + key_location[loc];
       }
       else
       {
            cipherkey[i] = plaintext[i];
       }
    }

    printf("Ciphertext: ");
    for (int i = 0; i < count_text; i++)
    {
        printf("%c", cipherkey[i]);
    }
    printf("\n");

    return 0;
}