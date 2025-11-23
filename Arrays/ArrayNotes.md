# ARRAYS
--------

1) An array is a collection of elements of the same data type, stored in continuous memory.

2) *Declaring an Array* 
    int arr[5];

    *Initializing an Array*
    int arr[5] = {1, 2, 3, 4, 5};

    int arr[5] = {10, 20};
    Rest becomes 0 → {10, 20, 0, 0, 0}

    int arr[] = {4, 5, 6};

4) *Accessing Elements (Indexing)*
Index starts from 0.

cout << arr[0]; 
cout << arr[4]; 

5) *Taking Input in an Array*
int arr[5];
for(int i = 0; i < 5; i++) {
    cin >> arr[i];
}

6) *Printing an Array*
for(int i = 0; i < 5; i++) {
    cout << arr[i] << " ";
}

7) *Size of Array*
int n = sizeof(arr) / sizeof(arr[0]);

sizeof(arr) → total bytes
sizeof(arr[0]) → bytes of 1 element

8) *Out-of-Bounds Access (Important)*

int arr[5];
arr[10] = 50;   // ERROR → accessing invalid memory

Always keep index in valid range
0 to n-1.

9) *Arrays are fixed size*
Once created, you cannot change the size:

int arr[5];
arr = new int[10];  // not allowed

**For dynamic size, use vector**

------------
10) 2D ARRAY
------------
A 2D array is an array of arrays.
Think of it like a matrix or a table with rows and columns.

*Example*: a 3×4 matrix (3 rows, 4 columns).

(i) Declaring a 2D Array
------------------------
int arr[3][4];

(ii) Initializing a 2D Array
----------------------------
int arr[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
*OR*
int arr[2][3] = {1, 2, 3, 4, 5, 6};

(iii) Accessing Elements
------------------------
arr[row][column]

*EXAMPLE*: cout << arr[1][2];  // row 1, column 2 (0-based)

(iv) Taking Input in a 2D Array
-------------------------------
int arr[3][3];

for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
        cin >> arr[i][j];
    }
}

(v) Printing a 2D Array
-----------------------
for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
        cout << arr[i][j] << " ";
    }
    cout << endl;
}

(vi) Memory Layout (**Important Concept**)
------------------------------------------
A 2D array is stored in row-major order:

*Example*:
int arr[2][3] = {
    {1,2,3},
    {4,5,6}
};

Memory is like:
1 2 3 4 5 6 -> Rows placed one after another.

(vii) Number of Elements in 2D Array
------------------------------------
rows × columns
int arr[5][7]; -> Total elements = 5 × 7 = 35