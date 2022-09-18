

import cs50

change = cs50.get_float("Change owed: ")

coins = 0
if (change / 0.25 >= 1):
    coins += int(change / 0.25)
    change = round(change % 0.25,2)

if (change / 0.10 >= 1):
    coins += int(change / 0.10)
    change = round(change % 0.10,2)

if (change / 0.05 >= 1):
    coins += int(change / 0.05)
    change = round(change % 0.05,2)

coins += int(change / 0.01)

print(coins)