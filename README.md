# Parking Pass system project

Description
-------------------
1. Reference docs: https://docs.google.com/document/d/1D59fzwRLq1DTPpcYgdn-EVpa_uCQtdYn3rj3zrN0__0

2. DB folder is not included in the git repo

3. Project Structure:
    - build directory (gitignored)
    - db directory (gitignored)
        - admin.txt
        - application.txt
        - transaction.txt
        - user.txt
        - analytics.txt
    - checkPass.cpp
    - parkingPass.cpp
    - README.md
    - TODO.md
    - txtDB.cpp

4. Libraries to be compiled

    - When compiling, run this command
        ```
        g++ .\targetFile.cpp .\build\lib1.o .\build\lib2.o -o .\build\executable.exe
        ```

    - txtDB.cpp
        ```
        g++ -c .\txtDB.cpp -o .\build\txtDB.o
        ```

### parkingPass.cpp
----------------
Description: This shall be the main program for the MPKJ Monthly Car Parking PAss Management System for UTAR Students.

### checkPass.cpp
-----------
Description: This shall be the program for officers to check the parking pass of vehichals.

### txtDB.cpp
-----

There are five text files maanged with different formats

1. admin.txt

- Admin name 8 letters
- Admin password 8 letters

2. user.txt

- Username 20 letters
- User password 8 letters

3. application.txt

- Username 20 letters
- Pass aplication 6 numbers
- Car plate 10 letters
- Status 3 letters

4. analytics.txt

- Month 6 letters
- New Users 3 letters
- New Applicants 3 letters
- Extensions 3 letters
- Parking Pass price 5 letters
- Income 8 letters

5. transaction.txt

- Username 20 letter
- Type (INC/ RFD) 3 letters
- Amount 5 letters