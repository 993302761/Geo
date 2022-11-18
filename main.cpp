#include <iostream>
#include <cassert>

using namespace std;

#include "R_Tree.h"

int main() {
    R_Tree *s=newTree();
    Data *d=newData(38.90005,117.08917,"123");

    insert(s,newData(38.90001,117.01317,"123"));
    insert(s,newData(38.90000,117.77917,"123"));
    insert(s,newData(38.90002,117.01817,"123"));
    insert(s,newData(38.90003,117.08917,"123"));
    insert(s,newData(38.90004,117.08917,"123"));
    insert(s,d);

    showAll(s);
    return 0;
}
