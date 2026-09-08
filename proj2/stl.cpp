// stl.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
// we included 
#include <vector>
#include <string>

void stl_sort(List &l, bool numeric) {
    std::vector<Node*> vN;
    std::vector<int> vi;
    Node *temp;
    for(int i = 0; i < size; i++) {
        temp = l -> head; 
        vN.push_back(temp); 
        vi.push_back(temp->number);
        head = head->next;
        
    }
    std::sort(vN);
    std::cout << 
}

