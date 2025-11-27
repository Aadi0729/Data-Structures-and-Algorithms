#include <iostream>
using namespace std;

void printPattern1(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << "* ";
        }
        cout << endl;
    }
}

void printPattern2(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout << "* ";
        }
        cout << endl;
    }
}

void printPattern3(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout << j+1 << " ";
        }
        cout << endl;
    }
}

void printPattern4(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout << i+1 << " ";
        }
        cout << endl;
    }
}

void printPattern5(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
}

void printPattern6(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i; j++) {
            cout << j+1 << " ";
        }
        cout << endl;
    }
}

void printPattern7(int n) {
    for(int i=0; i<n; i++) {
        //Spaces
        for(int j=0; j<n-i-1; j++) {
            cout << " " << " ";
        }

        // Stars
        for(int k=0; k<(2*i)+1; k++) {
            cout << "* ";
        }
        cout << endl;
    }
}

void printPattern8(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<i; j++) {
            cout << " " << " ";
        }

        for(int k=0; k<(2*n)-(2*i+1); k++) {
            cout << "* ";
        }
        cout << endl;
    }
}

void printPattern9(int n) {
    for(int i=0; i<n; i++) {

        // Spaces
        for(int j=0; j<n-i-1; j++) {
            cout << " " << " ";
        }

        // Stars
        for(int k=0; k<(2*i)+1; k++) {
            cout << "* ";
        }
        cout << endl;
    }
    for(int i=0; i<n; i++) {

        // Spaces
        for(int j=0; j<i; j++) {
            cout << " " << " ";
        }

        // Stars
        for(int k=0; k<(2*n)-(2*i+1); k++) {
            cout << "* ";
        }
        cout << endl;
    }
}

void printPattern10(int n) {
    for(int i=0; i<(2*n)-1; i++) {
        if(i < 5) {
            for(int j=0; j<i+1; j++) {
                cout << "* ";
            }
            cout << endl;
        }
        else {
            for(int j=0; j<(2*n)-i-1; j++) {
                cout << "* ";
            }
            cout << endl;
        }
    }
}

void printPattern11(int n) {
    for(int i=0; i<n; i++) {

        // Numbers increasing
        for(int j=0; j<i+1; j++) {
            cout << j+1 << " ";
        }

        //Spaces
        for(int k=0; k<(2*n)-(2*i)-2; k++) {
            cout << " " << " ";
        }

        // Numbers in reverse
        for(int l=i+1; l>=1; l--) {
            cout << l << " ";
        }
        cout << endl;
    }
}

void printPattern12(int n) {

    int num = 1;
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout << num++ << " ";
        }
        cout << endl;
    }
}

void printPattern13(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout << char('A' + j) << " ";
        }
        cout << endl;
    }
}

void printPattern14(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout << char('A' + i) << " ";
        }
        cout << endl;
    }
}

void printPattern15(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<n-i-1; j++) {
            cout << " " << " ";
        }

        for(int k=0; k<i+1; k++) {
            cout << char('A' + k) << " ";
        }

        for(int l=i; l>=1; l--) {
            cout << char('A' + l - 1) << " ";
        }
        cout << endl;
    }
}

void printPattern16(int n) {
    for(int i=0; i<n; i++) {
        for(int j=0; j<i+1; j++) {
            cout << char('A' + (n-i-1)+j) << " ";
        }
        cout << endl;
    }
}
int main() {
    int n;
    cout << "Enter n: " << endl;
    cin >> n;

    printPattern1(n);
    printPattern2(n);
    printPattern3(n);
    printPattern4(n);
    printPattern5(n);
    printPattern6(n);
    printPattern7(n);
    printPattern8(n);
    printPattern9(n);
    printPattern10(n);
    printPattern11(n);
    printPattern12(n);
    printPattern13(n);
    printPattern14(n);
    printPattern15(n);
    printPattern16(n);

    return 0;
}