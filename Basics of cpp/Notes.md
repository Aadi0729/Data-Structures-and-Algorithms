# SHORTCUT HEADER
-----------------
#include <bits/stdc++.h> is just a *shortcut header* that includes *almost every standard C++ library* in one line.

# User Input/Output
-------------------
*cin* → Standard input (keyboard)
*cout* → Standard output (screen)

They are part of the iostream library:

#include <iostream>
using namespace std;

# Data Type
-----------
✅ 1. What are Data Types?

Data types tell the compiler what kind of data a variable will store and how much memory it needs.

🧱 2. *Basic Built-in Data Types in C++*
🔸 i. Integer Types
Type	              Size	                          Range
int	                 4 bytes	         –2,147,483,648 to 2,147,483,647
long long	         8 bytes	                 very large (~9e18)
short	             2 bytes	                 –32,768 to 32,767
unsigned int	     4 bytes	                 0 to 4,294,967,295
unsigned long long	 8 bytes	                   0 to 1.8e19

Why use long long?
DSA problems often have values up to 10^12 or 10^18.


🔸 ii. Floating Point Types
Type	              Size	              Precision
float	             4 bytes	      6 decimal digits
double	             8 bytes	      15 decimal digits
long double	        10–16 bytes	      highest precision

🔸 iii. Character Type
Type	 Size	      Example
char	1 byte	   'a', 'Z', '3'

🔸 iv. Boolean
Type	    Value
bool	true or false

# Quick Visual Memory Map
-------------------------
char         ─ 1 byte
int          ───── 4 bytes
float        ───── 4 bytes
double       ───────────── 8 bytes
long long    ───────────── 8 bytes

-----------------------------------------------------------
➤ If your calculations can cross 2×10⁹ → use *long long*.
Not the input size, but the result of operations.

int -> -10^9 to 10^9
long -> -10^12 t0 10^12
long long -> -10^18 to 10^18
-----------------------------------------------------------

🔸 v. string

✅ What getline() Does ?

*getline()* reads a whole line from input (including spaces) until it hits a newline character (\n).

*Without cin.ignore()*, getline() will immediately read the leftover newline from the previous input, so you will NOT get a chance to type the string.

🔸 vi. char


# If-else statement
# Switch statement

# FOR-LOOP
# WHILE LOOP
# DO-WHILE LOOP