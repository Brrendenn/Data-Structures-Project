  # 📚 Boogle: Slang Word Dictionary using Trie in C

This project is a console-based application built in C using the **Trie data structure** to store, search, and manage **slang words** and their **descriptions**. It simulates a mini dictionary where users can:

- Add new slang terms,
- Search for specific slang words,
- View all slang starting with a specific prefix, and
- Display all stored slang terms.

---

## 🚀 Features

- 📥 Insert a new slang word with a description
- 🔍 Search for a specific slang word and view its meaning
- 🔤 Search and display all slang words that start with a given **prefix**
- 📜 Display all slang words in alphabetical order
- ❌ Input validation to ensure words and descriptions meet certain rules

---

## 🛠️ Built With

- **C Language**
- **Trie (Prefix Tree)** data structure
- Standard C Libraries:
  - `stdio.h` – Input/output
  - `stdlib.h` – Memory allocation
  - `string.h` – String manipulation

---

## 🧠 How It Works

### 🌳 Trie Structure
Each node in the Trie contains:
- A `character`
- A flag `Word` that marks the end of a valid word
- A pointer `desc` to store the description of the slang
- An array of 128 child pointers to support ASCII characters

### 📝 Functionalities
- `insertWord()`: Inserts a word and its description into the Trie.
- `printTrie()`: Recursively prints all stored words using DFS.
- `searchPrefix()`: Finds and displays all words with a given prefix.
- `exists()`: Checks if a specific word exists and displays its description.
- `haveSpace()`: Utility to check for spaces in input strings.
- `wordCount()`: Counts the number of words in a string (used for validating descriptions).

---

## 📋 Sample Menu

============Boogle=============

1. Release a new slang word
2. Search a slang word
3. View all slang words starting with a certain prefix word
4. View all slang words
5. Exit
Choose an option:
