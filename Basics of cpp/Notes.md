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

----------------------------------------------------------------------------

# Functions

1. **What is a Function?**

A function is a block of code that performs a specific task.

It helps in:
- reusing code
- reducing repetition
- making code clean & organized
- breaking problems into smaller parts

2. **Types of Functions**

**Built-in Functions**
Given by C++ library
Examples: sqrt(), max(), min(), sort()

**User-defined Functions**
Functions we create.

3. **How to Create a Function**

returnType functionName(parameters) 
{
    // code
}

4. **Calling a Function**

functionName();

This executes the function.

5. **Function with Parameters**

void sayHi(string name) 
{
    cout << "Hi " << name;
}

sayHi("Aditya"); -> Call

6. **Function with Return Value**

int add(int a, int b) 
{
    return a + b;
}

Call: int sum = add(10, 20);


7. **Why Functions are Important in DSA**
reuse logic (sum, max, reverse array, etc.)
divide complex problems
make recursive functions
make sorting, searching functions
increase code readability

Functions are the foundation for recursion, which is key in:
- Trees
- Backtracking
- Dynamic programming

8. **Function Parameters: Pass by Value vs Pass by Reference**

✔ **Pass by Value (Copy)**

Changes do NOT affect original value.

void change(int a) 
{
    a = 10;
}

Call:

int x = 5;
change(x);
cout << x;  // still 5

✔ **Pass by Reference**

Changes DO affect original value.

void change(int &a) 
{
    a = 10;
}

Call:

int x = 5;
change(x);
cout << x;  // now 10

Used a lot in arrays & recursion.


9. **Function Overloading**

Same function name, different parameters.

int add(int a, int b) 
{
    return a + b; 
}

double add(double a, double b) { return a + b; }

10. **Default Arguments**
int mul(int a, int b = 2) 
{
    return a * b;
}

mul(5);     // uses b = 2
mul(5, 10); // uses b = 10

11. **Inline Functions**

Used to reduce function call overhead.

inline int square(int x) 
{
    return x * x;
}

12. **Function Prototypes (Declaration)**

If function is written after main():

int add(int a, int b);  // prototype

int main() 
{
    cout << add(2, 3);
}

int add(int a, int b) 
{ 
    return a + b; 
}

Not required if function is written above main.

13. **Functions and Arrays**

When passing an array to a function:

void printArray(int arr[], int n) 
{
    for(int i=0; i<n; i++) cout << arr[i] << " ";
}

Arrays are always passed by reference (address is passed), so changes inside function affect the array.

14. **Recursion (Functions calling themselves)**

Foundation of:
- Backtracking
- Tree problems
- DP
- Divide & Conquer

Example:

int factorial(int n) 
{
    if(n == 0) return 1;
    return n * factorial(n - 1);
}

15. **Return Types**
Type	                        Means
void	                   returns nothing
int	                       returns integer
bool	                   returns true/false
string	                   returns string
custom struct/class	       returns custom object