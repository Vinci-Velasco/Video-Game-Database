CMPT 135 Assignment 5
=====================

Names of Team Members
---------------------

1. Vinci Velasco, vvv@sfu.ca, 301430456


Instructions for Compiling and Running
--------------------------------------

- Type "make" in the shell to compile everything. 
  Once done, type "./main_test" to run the program


Limitations
-----------

- Did not end up using ncurses for menus


Known Bugs
----------

- If the shell/command line is not full screen, the spacing of displaying records is messy. This is because the columns
  use a lot of width which only works if fullscreen

- When adding records/finding/deleting records, whenever inputting a number for year_published or metacritic_score, if 
  user types numbers first tfollowed by characters (i.e 2002sdjfkjsk) it still reads the initial numbers (2002). 
  However, it never accepts invalid data into the fields

-  When adding a new record and inputting a string field, if user puts "***" anywhere in the string, it will be read as
   a comma. This was done to avoid confusion if the user typed any commas in their string, as database.txt is structured
   using commas and "***" is not a common string to input.


Extra Features
--------------

- Included automated tests that use their own test database called test_database.txt.
  The reason for the test database is so that whenever tests are run, they never interfere
  with the main database