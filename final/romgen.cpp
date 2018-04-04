#include <iostream>

using namespace std;

long distance (int reading, float aref) {
    long rv = 5 * ((34.796 * (255/(reading*aref))-5.1197)-10);
    if (rv < 0) {
        rv = 0;
    } else if (rv > 255) {
        rv = 255;
    }
    return rv;
}

int main () {

    float aref = 3.0;
    cout << "{";
    for (int i = 0; i < 255; i++) {
        cout << distance(i, aref) << ",\t";
        if ((i+1)%8 == 0) {
            cout << "\n";
        }
    }
    cout << distance(255, aref) << "}";

    return 0;
}