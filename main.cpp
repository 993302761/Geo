#include <iostream>
#include <cassert>

using namespace std;

#include "R_Tree.h"

int main() {
    R_Tree *s=newTree();
    Data *d=newData(8,117.01317,"123");
    for (int i = 1; i <=20; ++i) {
        insert(s,newData(i,117.01317,"123"));
    }
//    insert(s,d);

    showAll(s);
    geoRadius(s,2,117.01317,1000);
    _free(s);
    return 0;
}
