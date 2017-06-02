# Single-player text-based Blackjack
======

## Section 1. Introduction
The executable can be run from command line. It is text-based but it uses unicode characters and ncurses library to delivered an improved visual output.

The size of the visual layout is fixed (it does not resize at the moment) and equal to 80x25 in characters. Please get sure your console windows is at least of that size to get a better experience.

## Section 2. Compile and Run
======

[Option 1]. Xcode project
A full xcode project is provided. This can be open, edited and tested.

[Option 2]. make
As an alternative, a Makefile is also given. Yu can use the following commands:
````
$ make build run
``` 

## Section 3. Usage
======
The user (player) can use the following keys when available:
H. Hit, get a new card
S. Stand, pass or end your hand
X. Quit game

When possible, the dealer will progressively play its hands, and after few instans the results will be displayed.

## Section 4. Unit tests
======
Few unit tests were added to check selected methods, you can run them by
```
$ make build test
```

## Section 5. Requirements
======
You need to have **ncurses** and **unicode** support. Please check that your console it is at least **80x25 characters
**.