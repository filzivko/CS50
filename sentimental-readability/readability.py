# TODO
# Import cs50 for get_string function
import cs50

text = cs50.get_string("Text:")

# Initial variables
spacecount = 0
sentencecount = 0
sentenceendings = ".?!"
alphabet = "qwertyuiopasdfghjklzxcvbnm"
lettercount = 0

# Loop through the string and count the letters, spaces and letter endings
for i in range(len(text)):
    if text[i].isspace():
        spacecount += 1
    if text[i] in sentenceendings:
        sentencecount += 1
    if text[i].lower() in alphabet:
        lettercount += 1

wordcount = spacecount+1

# Letters per 100 words
L = lettercount/wordcount*100
# Sentences per 100 words
S = sentencecount/wordcount*100

# Determine the Coleman-Liau index
index = 0.0588 * L - 0.296 * S - 15.8

# Print functions
if index < 1:
    print("Before Grade 1")
if index >= 16:
    print("Grade 16+")
else:
    print("Grade ", round(index))
