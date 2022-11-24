#include <iostream>
#include <cassert>

using namespace std;

#include "R_Tree.h"

int main() {
    R_Tree *s=newTree();
    Data *d=newData(8,117.01317,"123");
    for (int i = 1; i <=7; ++i) {
        insert(s,newData(i,117.01317,"123"));
    }
    insert(s,d);

    showAll(s);
    _free(s);
    return 0;
}
