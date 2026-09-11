// stl.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <vector>

void stl_sort(List &l, bool numeric) {
    std::vector<Node*> nodes;

    for (Node* current = l.head; current != nullptr; current = current->next) {
        nodes.push_back(current);
    }


    std::sort(nodes.begin(), nodes.end(), \
    [numeric](Node* a, Node* b) {return a->number < b->number;});

    nodes[nodes.size() - 1]->next = nullptr;
    l.head = nodes.front();

    for (int i = 0; i < nodes.size() - 1; i++) {
        nodes[i]->next = nodes[i + 1];
    }

}
