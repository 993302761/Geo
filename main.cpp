#include <iostream>
#include <cassert>

using namespace std;

#include "R_Tree.h"

int main() {
    R_Tree *s=newTree();

    for (int i = 1; i <=18; ++i) {
        insert(s,newData(i,117.01317,"123"));
    }


    showAll(s);
    return 0;
}
