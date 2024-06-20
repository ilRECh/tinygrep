# TINYGREP

## Description

A grep-like utility written in C++ that does a recursive search of a given query in all files in a directory. Behaves like a
```
grep -r '<pattern>' '<directory_or_file>'
```

## Tech stack
- C++11
- CMake
- Linux (debian based)

## Design
- Classes
    - [File](#File)
    - [Finder](#Finder)
    - [TinyGrep](#TinyGrep)

### File
Contains current file information. In Unix OS' "everything is a file", so this is a class, which abstracts this statement, and makes that it contains an "actual" file with contents.

### Finder
Contains searching functionality. Addresses the [File](#File) class for the file to search in.

### TinyGrep
The main class.

## Features
- Basic regex pattern is supported
- Recursive search in directories

## How to run

## Run tests

