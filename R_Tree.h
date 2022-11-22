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


#define M 4
#define EARTH_RADIUS 6378137        //地球半径，单位m
#define PI 3.1415926

typedef enum {
    NODE=1,             //普通节点
    DATANODE=2          //数据节点
}NodeType;



typedef struct Data{
    double x;       //纬度
    double y;       //经度
    char *data;
}Data;


typedef struct Node {
    int count;
    NodeType type;
    double x[2];
    double y[2];
    Node *parent;
    Node *nodeList[M+1];
    Data *dataList[M];
}Node;


typedef struct DataList{
    Data *data;
    DataList *next;
}DataList;


typedef struct R_Tree{
    Node *root;
}R_Tree;


R_Tree *newTree();
Node *newNode();
Data *newData(double x0,double y0,char *d);
DataList *newDataList();

double rad(double d);
double getDistance(Data a,Data b);


int check_dataNode(Node *node);
int check_Node(Node *node);

int insert(R_Tree *root,Data *data);
int merge_data(Node *root, Data *data);
int add_node(Node *root, Node *node);

int _free(R_Tree *root);
void delete_data(Node *node, Data *data, int s);
void replace_node(Node *node, Node *n1, Node *n2);
void delete_node(Node *node, double d);
void showAll(R_Tree *root);
DataList *geoRadius(R_Tree *root,double x,double y,int radius);



R_Tree *newTree(){
    R_Tree *s=(R_Tree *) malloc(sizeof (R_Tree));
    memset(s,0,sizeof (s));
    s->root=NULL;
    return s;
}



Node *newNode() {
    Node *s = (Node *) malloc(sizeof(Node));
    memset(s, 0, sizeof(s));
    memset(s->dataList, 0, sizeof(s->dataList));
    memset(s->nodeList, 0, sizeof(s->nodeList));
    s->parent = NULL;
    s->type = NODE;
    return s;
}





Data *newData(double x0,double y0,char *d){
    if (x0<0||x0>90||y0<0||y0>180){
        printf("经纬度数据错误");
        return NULL;
    }
    Data *data=(Data *) malloc(sizeof (Data));
    data->data=d;
    data->x=x0;
    data->y=y0;
    return data;
}


DataList *newDataListNode(Data *d){
    DataList *s=(DataList *) malloc(sizeof (DataList));
    s->data=d;
    s->next=NULL;
    return s;
}


/**
 * 转化为弧度(rad)
 */
double rad(double d)
{
    return d * PI / 180.0;
}




/**
 * 计算两坐标点间距离
 */
double getDistance(Data a,Data b){
    double radLat1 = rad(a.x);
    double radLat2 = rad(b.x);
    double x = radLat1 - radLat2;
    double y = rad(a.y) - rad(b.y);
    double s = 2 * asin(sqrt(pow(sin( x / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(y / 2), 2)));
    s = s * EARTH_RADIUS;
    s = round(s * 10000) / 10000;
    return s;
}


/**
 * 计算两纬度间距离
 * (纬度差0.008990=1000.762200米)
 */
double xSpace(double x0,double x1){
    return fabs(x0-x1)/0.008990*1000.762200;
}


/**
 * 计算两点经度间距离
 * (经度差0.011570=1000.684500米)
 */
double ySpace(double y0,double y1){
    return fabs(y0-y1)/0.011570*1000.684500;
}



/**
 * 获取坐标半径内的所有标记点
 * @param radius 半径
 * @return 标记点集合
 */
DataList *geoRadius(R_Tree *root,double x,double y,int radius){
    if (root==NULL||root->root==NULL){
        return NULL;
    }
    Node *node=root->root;

}

void show(Node *n){
    if (n==NULL){
        return;
    }
    int k=n->count;
    printf("%d :",n->type);
    for (int i = 0; i < k; ++i) {
        printf("%lf  ",n->x[i]);
    }
    printf("\n");

    for (int i = 0; i < M+1; ++i) {
        if (n->nodeList[i]==NULL){
            return;
        }
        show(n->nodeList[i]);
    }
}


/**
 * 遍历树
 */
void showAll(R_Tree *root){
    if (root==NULL){
        return;
    }
    show(root->root);
}







/**
 * 删除数据节点
 */
void delete_data(Node *node, Data *data, int s){
    int j=node->count;
    int i;
    for ( i = 0; i < j; ++i) {
        if (node->dataList[i]==data){
            if (s==1){
                free(data);
            }
            for (int k = i; k < M-1; ++k) {
                node->dataList[k]=node->dataList[k+1];
            }
            node->count--;
            break;
        }
    }

    assert(i<j);
}




void replace_node(Node *node, Node *n1, Node *n2){
    int i;
    for ( i = 0; i < M+1; ++i) {
        if (node->nodeList[i]==n1){
            node->nodeList[i]=n2;
            break;
        }
    }
}




void delete_node(Node *node, double d){
    int i;
    for ( i = 0; i < M; ++i) {
        if (node->x[i]==d){
            for (int k = i; k < M-1; ++k) {
                node->x[k]=node->x[k+1];
            }
            break;
        }
    }
}




int check_Node(Node *node){
    int j=node->count;
    if (j==M){
        //开始执行分裂操作
        Node *right=newNode();
        Node *left=newNode();
        left->type=right->type=node->type;

        for (int i = 0 , k=0,s=0; i < M+1; ++i) {
            if (i<M/2){
                left->nodeList[k]=node->nodeList[i];
                node->nodeList[i]=NULL;
                left->nodeList[k]->parent=left;
                k++;
            } else{
                right->nodeList[s]=node->nodeList[i];
                node->nodeList[i]=NULL;
                right->nodeList[s]->parent=right;
                s++;
            }
        }

        for (int i = 0 , k=0,s=0; i < j; ++i) {
            if (i<M/2-1){
                left->x[k++]=node->x[i];
                left->count++;
            } else if (i>M/2-1){
                right->x[s++]=node->x[i];
                right->count++;
            }
        }
        Node *parent=node->parent;
        if (parent==NULL){
            left->parent=right->parent=node;
            node->x[0]=node->x[M/2-1];
            for (int i = 1; i < M; ++i) {
                node->x[i]=0;
            }
            node->count=1;
            node->nodeList[0]=left;
            node->nodeList[1]=right;

        } else{
            left->parent=right->parent=parent;
            replace_node(parent,node,left);
            add_node(parent,right);
            free(node);
            check_Node(parent);
        }
    }
}




int check_dataNode(Node *node){
    int j=node->count;
    if (j==M){
        //开始执行分裂操作
        Node *right=newNode();
        Node *left=newNode();
        left->type=right->type=DATANODE;
        for (int i = j-1; i >= 0; --i) {
            if (i<M/2){
                merge_data(left, node->dataList[i]);
            } else{
                merge_data(right, node->dataList[i]);
            }
            node->dataList[i]=NULL;
            node->x[i]=0;
            node->count--;
        }

        if (node->parent!=NULL){
            Node *parent=node->parent;
            left->parent=right->parent=parent;
            replace_node(parent, node ,left);
            add_node(parent, right);
            free(node);
            check_Node(parent);
        } else{
            left->parent=right->parent=node;
            node->type=NODE;
            node->nodeList[0]=left;
            node->nodeList[1]=right;
            node->x[0]=right->x[0];
            node->count++;
        }

    }
}





int add_node(Node *root, Node *node){
    assert(root->type != DATANODE);
    assert(root->nodeList[M] == NULL);

    double x=node->x[0];

    int i=(root->count)++;
    for (int j = i-1; j >= 0; --j) {
        if (root->x[j]>x){
            root->x[j+1]=root->x[j];
            root->nodeList[j+2]=root->nodeList[j+1];
            i=j;
        } else{
            break;
        }
    }
    root->x[i]=node->x[0];
    if (root->nodeList[i]->x[0]>node->x[0]){
        root->nodeList[i+1]=root->nodeList[i];
        root->nodeList[i]=node;
    } else{
        root->nodeList[i+1]=node;
    }
}




int merge_data(Node *root, Data *data){
    assert(root->type == DATANODE);
    assert(root->dataList[M - 1] == NULL);

    //以x轴为排序标准
    int i=(root->count)++;
    root->dataList[i]=data;

//    for (int j = i-1; j >= 0; --j) {
//        if ((root->dataList[j]->x) > (root->dataList[i]->x)){
//            Data *p=root->dataList[j];
//            root->dataList[j]=root->dataList[i];
//            root->dataList[i]=p;
//            i=j;
//        } else{
//            break;
//        }
//    }

    if (root->x[0]>data->x){
        root->x[0]=data->x;
    } else if (root->x[1]<data->x){
        root->x[1]=data->x;
    }

    if (root->y[0]>data->y){
        root->y[0]=data->y;
    } else if (root->y[1]<data->y){
        root->y[1]=data->y;
    }

    return check_dataNode(root);
}




/**
 * 插入节点
 */
int insert(R_Tree *head,Data *data){
    Node *root;

    //树未初始化
    if (head==NULL){
        return 0;
    }

    //判断树是否为空树
    if (head->root==NULL){
        root=newNode();
        root->type=DATANODE;
        head->root=root;
    } else{
        root=head->root;
    }

    //找到x轴临近的叶子节点
    while (root->type!=DATANODE){
        int i;
        for ( i = 0; i < 2; ++i) {
            if (root->x[i]>data->x){
                root=root->nodeList[i];
                break;
            }
        }
        if (i==2){
            root=root->nodeList[i];
        }
    }

    //加入叶子节点中
    return merge_data(root, data);
}




int _free0(Node *node){
    if (node==NULL){
        return 0;
    }
    int s=node->count;
    if (node->type==NODE){
        for (int i = 0; i < s+1; ++i) {
            _free0(node->nodeList[i]);
        }
    } else{
        for (int i = 0; i < s; ++i) {
            free(node->dataList[i]);
        }
    }
    free(node);
    return 1;
}




/**
 * 释放树
 */
int _free(R_Tree *root){
    if (root==NULL){
        return 0;
    }
    return _free0(root->root);
}



#endif //R_TREE_R_TREE_H
