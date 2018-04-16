#include <iostream>

using namespace std;

float readingToVolt (int reading, float aref) {
	  return ((aref * reading) / 255);
}

long distance (float volt) {
    long rv = (26.977 / volt) - 2.4973;
    if (rv < 0) {
        rv = 0;
    } else if (rv > 60) {
        rv = 61;
    }
    return rv;
}

int main () {

    float aref = 3.5;
    cout << "{";
    for (int i = 0; i < 255; i++) {
        cout << distance(readingToVolt(i, aref)) << ",\t";
        if ((i+1)%8 == 0) {
            cout << "\n";
        }
    }
    cout << distance(readingToVolt(255, aref)) << "}";

    return 0;
}
