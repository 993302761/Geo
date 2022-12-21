#include <iostream>
#include <cassert>
#include <mysql/mysql.h>


using namespace std;

#include "R_Tree.h"


int main() {
    R_Tree *s=newTree();
    update_data(s);

    showAll(s);
    printf("\n");

//    DataList *dataList=newDataList();
//    Data *d=newData(39.14050,117.20529, nullptr);
//    geoRadius(dataList,s,d->x,d->y,1000);
//    show(dataList);


    _free(s);

}
