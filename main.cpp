#include <iostream>
#include <cassert>

using namespace std;

#include "R_Tree.h"

int main() {
    R_Tree *s=newTree();
    Data *data= newData(38.90259,117.01317,"123");
    insert(s,data);
    printf("%lf",s->root->dataList[0]->x);
    return 0;
}
