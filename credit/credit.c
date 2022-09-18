
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long card = get_long("Card number: ");
    long user_card = card;

    int card_digits = 1;
    long card_count = user_card;

    while (card_count / 10 > 0)
    {
        card_digits += 1;
        card_count = card_count / 10;
    }

    int arr[card_digits];

    for (int i = 0; i < card_digits; i++)
    {
        arr[i] = user_card % 10;
        user_card = user_card / 10;
    }

    int sum1 = 0;
    int sum2 = 0;

    for (int i = 0; i < card_digits; i++)
    {
        if (i % 2 == 1)
        {
            if (arr[i] * 2 >= 10)
            {
                sum1 += (arr[i] * 2) % 10;
                sum1 += (arr[i] * 2) / 10;
            }
            else
            {
                sum1 += arr[i] * 2;
            }
        }
        else
        {
            sum2 += arr[i];
        }
    }

    if ((sum1 + sum2) % 10 == 0)
    {
        printf("Card is legit :)\n");
    }
    else
    {
        printf("INVALID CARD\n");
    }

    if (card_digits == 15)
    {
        if (arr[14] == 3 && (arr[13] == 4 || arr[13] == 7))
        {
            printf("American Express\n");
        }
        else
        {
            printf("INVALID CARD\n");
        }
    }
    else if (card_digits == 16)
    {
        if (arr[15] == 5 && (arr[14] == 1 || arr[14] == 2 || arr[14] == 3 || arr[14] == 4 || arr[14] == 5))
        {
            printf("Mastercard\n");
        }
        else if (arr[15] == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID CARD\n");
        }
    }
    else if (card_digits == 13)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID CARD\n");
    }
}