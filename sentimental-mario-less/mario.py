
from cs50 import get_int

while True:
    height = get_int("Height: ")
    if(height >= 1 and height <= 8):
        break
    print("Height must be an integer between 1 and 8")

for i in range(height):
    spaces = height - 1 - i
    squares = i + 1
    print(spaces * ' ', squares * '#')



