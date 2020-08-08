def count_letters(content):

    global letters

    for i in range(len(content)):
        if ((content[i] >= 'a' and content[i] <= 'z') or (content[i] >= 'A' and content[i] <= 'Z')):
            letters += 1

    print(letters)


def count_words(content):

    global words

    for j in range(len(content)):
        if (content[j] == ' '):
            words += 1

    print(words)


def count_sentences(content):

    global sentences

    for k in range(len(content)):
        if (content[k] == '.' or content[k] == '!' or content[k] == '?'):
            sentences += 1

    print(sentences)


def formula():

    global letters
    global words
    global sentences

    L = (letters / words) * 100

    print(L)

    S = (sentences / words) * 100

    print(S)

    index = ((0.0588 * L) - (0.296 * S) - 15.8)

    index = round(index)

    if index > 16:
        print("Grade 16+")
    if index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


text = input("Text: ")

letters = 0
words = 1
sentences = 0

count_letters(text)
count_words(text)
count_sentences(text)
formula()
