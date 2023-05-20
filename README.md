# WebClientREST

## Overview

There is a separate entity for each functionality:

### Client

Stores the **host IP** and **port**, the **socket file descriptor**, a message
corresponding to the **server's response** (error or success messages), the
**session cookie** and **authorization token**.

### Command

Stores all **parameters of a command**.

### Cookie

Stores the **cookie** as *separate fields*.

### Server Interaction

Stores the **client request**, **server response** and the **JSON payload**
obtained from the response.


## Helper files

The files `buffer.*`, `helpers.*` and `requests.*` are slight modifications of
the files provided in lab 9.

The files `serialize.*` serialize user input in JSON format using `parson`.
This is done only for POST and DELETE requests (for GET requests there is no
user input that needs to be serialized).


## Testing

The code can be tested using the make rule `make run_tests` or
`make run_tests_valgrind`. The test file does not contain tests for the
`get_books` and `get_book` commands as these did not generate a valid response
in this testing mode. These commands do work when tested manually.
