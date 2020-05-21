from cs50 import get_string
import re

# GET INPUT
input = get_string("Text: ")
#DEBUG# print(f"input is {input}")
    

# FIND W, TOTAL NO OF WORDS IN TEXT | sentence will not start or end with a space; a sentence will not have multiple spaces in a row.
words = 0
# default delimiter for .split = any whitespace
for i in input.split():
    words += 1
#DEBUG# print(f"words is {words}")


# FIND L, AVG NO OF LETTERS PER 100 WORDS IN TEXT | LETTERS = A-Za-z
letters = 0
for char in input:
    if (char.isalpha()):
        letters += 1
L = letters / words * 100;
#DEBUG# print(f"letters is {letters}")print(f"L is {L}")


# FIND S, AVG NO OF SENTENCES PER 100 WORDS IN TEXT | SENTENCE END = . ! ?
sentEnd = re.compile('[.!?]')
# re.findall returns a list(array) of strings that match the regex
sentences = len(sentEnd.findall(input))
S = sentences / words * 100;
#DEBUG# print(f"sentences is {sentences}")print(f"S is {S}")


# FIND INDEX
index = 0.0588 * L - 0.296 * S - 15.8
#DEBUG# print(f"index is {index}");
    
    
# PRINT GRADE LEVEL
if (index < 1):
    print("Before Grade 1")
elif (index >= 16):
    print("Grade 16+")
else:
    print(f"Grade {round(index)}");
