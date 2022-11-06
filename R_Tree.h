//
// Created by lyq on 2022/11/4.
//

#ifndef R_TREE_R_TREE_H
#define R_TREE_R_TREE_H


#include <malloc.h>
#include <string.h>
#include <math.h>

/***

R树一定要满足一下要求：

1．根节点若非叶子节点，则至少有两个子节点；

2．每个非根叶节点和非叶节点包含的实体个数均介于m和M之间；

3．所有叶子节点在同一层次；

 其中m表示拥有子节点的下限，目的是为了提高磁盘利用率，提高搜索效率。如果m=1，所有节点都只有一个子节点，那树就退化为了普通链表。
 当节点的子节点数量少于m时，则会删除该节点，把该节点的子节点分配到其他节点中；
 M表示拥有子节点的上限，因为一般情况下，出于减少磁盘IO和批量刷盘的目的，我们一个节点对应了磁盘中一个或若干页。
 当节点的子节点数量大于M时，则会分裂该节点，把子节点分配到两个新的节点中。一般情况下m=1/2M。

 */


#define M 3
#define m ceil(M/2.0)
#define EARTH_RADIUS 6378137        //地球半径，单位m
#define PI 3.1415926

typedef enum {
    NODE=1,
    DATANODE=2
}NodeType;


typedef struct {
    double x;       //纬度
    double y;       //经度
}Matrix;


typedef struct Data{
    Matrix *matrix;
    char *data;
}Data;


typedef struct Node {
    int count;
    NodeType type;
    Matrix place[2];
    struct Node *parent;
    struct Node *nodeList[M];
    struct Node *ptr[M+1];
    Data *dataList[M];
}Node;


typedef struct R_Tree{
    Node *root;
};


R_Tree *newTree();
Node *newNode();
Matrix *newMatrix(double x0,double y0);
Data *newData(double x0,double y0,char *d);
Data *newData(Matrix *s,char *d);

void check(Node *root);
int insert(R_Tree *root,int key,char *data);
int _free_tree(Node *root);
int deleteNode(R_Tree *root,int key);
Node *get(R_Tree *root,int key);
void showAll(Node *root);




R_Tree *newTree(){
    R_Tree *s=(R_Tree *) malloc(sizeof (R_Tree));
    memset(s,0,sizeof (s));
    memset(s->root,0,sizeof (s->root));
    return s;
}



Node *newNode(){
    Node *s=(Node *) malloc(sizeof (Node));
    memset(s,0,sizeof (s));
    memset(s->ptr,0,sizeof (s->ptr));
    memset(s->dataList,0,sizeof (s->dataList));
    memset(s->nodeList,0,sizeof (s->nodeList));
    s->parent=NULL;
    s->type=NODE;
    return s;
}


Matrix *newMatrix(double x0,double y0){
    Matrix *s=(Matrix *) malloc(sizeof (Matrix));
    s->x=x0;
    s->y=y0;
    return s;
}



Data *newData(double x0,double y0,char *d){
    Matrix *s=(Matrix *) malloc(sizeof (Matrix));
    s->x=x0;
    s->y=y0;
    Data *data=(Data *) malloc(sizeof (Data));
    data->matrix=s;
    data->data=d;
    return data;
}



Data *newData(Matrix *s,char *d){
    Data *data=(Data *) malloc(sizeof (Data));
    data->matrix=s;
    data->data=d;
    return data;
}



/**
 * 转化为弧度(rad)
 */
double rad(double d)
{
    return d * PI / 180.0;
}



/**
 * 计算两点间距离
 */
double getDistance(Matrix a,Matrix b){
    double radLat1 = rad(a.x);
    double radLat2 = rad(b.x);
    double x = radLat1 - radLat2;
    double y = rad(a.y) - rad(b.y);
    double s = 2 * asin(sqrt(pow(sin( x / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(y / 2), 2)));
    s = s * EARTH_RADIUS;
    s = round(s * 10000) / 10000;
    return s;
}



#endif //R_TREE_R_TREE_H
