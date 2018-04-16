#include <iostream>

using namespace std;

float readingToVolt (int reading, float aref) {
	return ((aref * reading) / 1024);
}

long distance (float volt) {
	long rv = (269.77 / volt) - 24.973;
	if (rv < 0) {
		rv = 0;
	} else if (rv > 800) {
		rv = 800;
	}
	return rv;
}

int main () {

    float aref = 3.5;
    cout << "{" << "\n";
    for (int i = 0; i < 1023; i++) {
        cout << distance(readingToVolt(i, aref)) << ",\t";
        if ((i+1)%8 == 0) {
            cout << "\n";
        }
    }
    cout << distance(readingToVolt(1023, aref)) << "\n};";

    return 0;
}
