#include <iostream>
#include <cassert>

using namespace std;

#include "R_Tree.h"

int main() {
    R_Tree *s=newTree();
    insert(s,newData(39.14413,117.21738,"天津站"));
    insert(s,newData(39.14415,117.22033,"裕阳花园"));
    insert(s,newData(39.14547,117.21867,"城市之光"));
    insert(s,newData(39.14618,117.21387,"月光园"));
    insert(s,newData(39.14041,117.21925,"汇和家园"));
    insert(s,newData(39.14073,117.21287,"龙门大厦"));
    insert(s,newData(39.14288,117.21037,"天津行车公寓"));



    showAll(s);
    printf("\n");

    DataList *dataList=newDataList();
    Data *d=newData(39.14050,117.20529, nullptr);
    geoRadius(dataList,s,d->x,d->y,1000);
    show(dataList);


    _free(s);
    return 0;
}
