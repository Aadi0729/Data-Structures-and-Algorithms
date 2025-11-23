# STRINGS
---------

1) A string in C++ is a sequence of characters.
2) We use the string class from: #include <string>
(or <bits/stdc++.h> includes it automatically)

3) *Declaring and Initializing Strings*
---------------------------------------
string s = "Hello";
string name;
name = "Aditya";

4) *Taking Input*
-----------------
- Single word (no spaces)
  cin >> s;

Input: Hello (YES)
Input: Hello World (NO) **only Hello stored**.

- Full line (with spaces)
  getline(cin, s);
  
Input: Hello World (YES) **entire line stored.**

5) *Length of String*
---------------------
cout << s.length();
cout << s.size();   // same

6) *Accessing Characters (Indexing)*
string s = "Hello";
cout << s[0];  // H
cout << s[4];  // o

7) *Modifying Characters*
-------------------------
s[0] = 'Y';   // Now "Yello"

8) *Adding / Appending Strings*
-------------------------------
string a = "Hello";
string b = "World";

string c = a + " " + b;   // Hello World

OR

a += " Everyone";         // a becomes Hello Everyone

9) **Useful Functions**
-----------------------
Function	                      Purpose
--------                      ----------------
s.length()	                  length of string
s.empty()	                  check if empty
s.clear()	                  empty the string
s.push_back('a')	          add char at end
s.pop_back()	              remove last char
s.substr(pos, len)	          substring
s.find("abc")	              find substring

10) *Convert Between String & Number*
------------------------------------
**string → int**
int x = stoi("1234");

**int → string**
string s = to_string(5678);

11) *Looping Through a String*
-----------------------------
- Using index
-------------
for(int i = 0; i < s.length(); i++)
    cout << s[i];

- Using for-each
----------------
for(char c : s)
    cout << c;