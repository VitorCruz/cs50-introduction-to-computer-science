

import cs50
import string

text = cs50.get_string("Text: ")

letters = 0
words = 1
sentences = 0

for i in text:
    if i == ' ':
        words += 1
    if i in ['.', '!','?']:
        sentences += 1
    if i.lower() in string.ascii_lowercase:
        letters += 1

score = int(round((0.0588 * (letters/words) * 100) - (0.296 * (sentences/words) * 100) - 15.8,0))

print("Grade 16+") if score >= 16 else print("Before Grade 1") if score <= 1 else print("Grade "+str(score))

