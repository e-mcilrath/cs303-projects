/*
Eric McIlrath. solution.cpp for challenge01. 
*/

#include <iomanip>
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::cin;
using std::cout; 
using std::endl;

int main(int argc, char *argv[]) {

    int size;
    int rot;
    char dir;
    vector<int> nums;
    int start;

    

    while (cin >> size >> rot >> dir){
        nums.resize(size);
        for (int i = 0; i < size; i++) {
            cin >> nums[i];
        }
        
        if (dir == 'L') {
            start = rot % size;
            for (int i = 0; i < size; i++) {
                if (i > 0) cout << " ";
                cout << nums[(i + start) % size];
            }
            cout << '\n';
        }

        else if (dir == 'R') {
            start = ((size - rot % size) % size);
            for (int i = 0; i < size; i++) {
                if (i > 0) cout << " ";
                cout << nums[(i + start) % size];
            }
            cout << '\n';

        }

    }

    return 0;
}

