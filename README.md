Write a function that returns a line read from a
# get_next_line with LinkedList

A function that returns a line read from a file descriptor.

Repeated calls of get_next_line() function will let you read the text file pointed to by the file descriptor, one line at a time.

I used Linked List so that you don't need to specify buffer size when you read from file discriptor.

## Usage
```
$ gcc -c get_next_line.c
$ gcc -o <your c file> get_next_line.o
```
