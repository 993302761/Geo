#include <iostream>
using namespace std;

#include "R_Tree.h"

int main() {
    Matrix a{38.86324,117.08319};
    Matrix b{38.84896,117.11161};
    cout<<getDistance(a,b);
    return 0;
}
