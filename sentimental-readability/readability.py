# TODO
from cs50 import get_string


# GET TEXT FROM USER
text = get_string("Text: ")

# COUNT LETTERS
letters = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w",
           "x", "y", "z"]

letter_count = 0
for x in text:
    if x.lower() in letters:
        letter_count += 1

sentence_chars = ['.', '!', '?']

# COUNT WORDS
word_count = 0
for index, x in enumerate(text):
    if x == ' ':
        word_count += 1
if word_count > 1:
    word_count += 1


# SENTENCES (Ignoring some point false detection issues as instructed)
sentence_count = 0

for x in text:
    if x in sentence_chars:
        sentence_count += 1


# CALCULATE Coleman-Liau index

# L is the average number of letters per 100 words in the text, and
L = 100 * letter_count / word_count

# S is the average number of sentences per 100 words in the text
S = 100 * sentence_count / word_count

coleman_liau_index = 0.0588 * L - 0.296 * S - 15.8

grade = round(coleman_liau_index)

# print(letter_count, " letters")
# print(word_count, " words")
# print(sentence_count, "sentences")
# print("index", grade)

# GIVE RESULT

if grade < 1:
    print("Before Grade 1")
elif grade >= 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")