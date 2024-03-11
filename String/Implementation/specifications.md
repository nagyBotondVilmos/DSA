# Author
Nagy Botond-Vilmos

# Description
This file contains the specifications of my implementation of the string data structure in C++.

# Specifications
Character strings are arrays of characters that allow storing a sequence of characters in a single array.

# Properties

- Homogeneous
- O(n * m) time complexity, where n is the length of the source text and m is the length of the pattern being searched for
- Able to store character strings consisting of any characters
- Dynamic size, can be both increased and decreased
- The name of the data structure in the program: "str_bm"
- Data members:
    - Variable of type char* data containing the actual data
    - int len storing the length of the character string

# Operations

- `Creation`:
1. Empty:
Preconditions: -
Postconditions: An empty character string is created
2. With assignment:
Preconditions: Specify the content of the character string as const char* or as type str_bm
Postconditions: The character string is created with the specified data

- `Release`:
Frees the memory allocated by the data structure, if it exists

- `get_data`:
Returns the content of the character string in a variable of type const char*
Preconditions: -
Postconditions: -

- `strlen`:
Returns the length of a character string provided as a parameter of type const char*

- `bad_char`:
Initializes a 256-length vector based on the given pattern following the bad character rule
Example: pattern = "apple", then bc['a'] = 3, bc['p'] = 1, bc['l'] = 2

- `&operator[]`:
Returns the element at the given index
Preconditions: The given index is valid
Postconditions: Returns the character at the given index

- `&operator=`:
Preconditions: The parameter must be of the same type
Postconditions: Changes the value of a character string to another

- `operator+`:
Preconditions: The parameter must be of the same type
Postconditions: Returns the concatenated value of 2 character strings

- `&operator+=`:
Preconditions: The parameter must be of the same type
Postconditions: Appends the content of the parameter to the character string

- `to_lower`:
Converts uppercase letters to lowercase in the character string
Preconditions: -
Postconditions: -

- `to_upper`:
Converts lowercase letters to uppercase in the character string
Preconditions: -
Postconditions: -

- `&operator>>`:
Reads from the specified stream until whitespace
Preconditions: -
Postconditions: -

- `&operator<<`:
Writes the character string to the specified stream
Preconditions: -
Postconditions: -

- `substr`:
Returns a substring of the character string
Preconditions: Specify 2 valid indices (an interval)
Postconditions: Returns the specified part of the character string

- `insert`:
Inserts another character string into the character string
Preconditions: The position is valid
Postconditions: Inserts the specified character string at the given position

- `replace`:
Replaces a specified part in the character string
Preconditions: The specified index is valid
Postconditions: Replaces the part at the specified position

- `reverse`:
Returns the reverse of the character string
Preconditions: -
Postconditions: -

- `length`:
Returns the length of the character string in an int variable
Preconditions: -
Postconditions: -

- `find_from`:
Finds all occurrences of the pattern provided as a parameter and stores them in a vector
If no occurrence is found, the vector remains empty
Preconditions: -
Postconditions: -

- `find_from_see_steps`:
Same as the previous one, but variables' values can be tracked in the terminal

- `find_from_naive`:
Naive version of the character string search implemented above

- `read_from`:
Reads from a file
Preconditions: The file parameter is of type const char* and the file exists
Postconditions: Successful reading

- `get_line`:
Reads until a newline character from the specified stream
Preconditions: -
Postconditions: Successful reading

[Back](../readme.md)