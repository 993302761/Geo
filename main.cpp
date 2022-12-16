#include <iostream>
#include <cassert>
#include <mysql/mysql.h>


using namespace std;

#include "R_Tree.h"


int main() {
//    R_Tree *s=newTree();
//    insert(s,newData(39.14413,117.21738,"天津站"));
//    insert(s,newData(39.14415,117.22033,"裕阳花园"));
//    insert(s,newData(39.14547,117.21867,"城市之光"));
//    insert(s,newData(39.14618,117.21387,"月光园"));
//    insert(s,newData(39.14041,117.21925,"汇和家园"));
//    insert(s,newData(39.14073,117.21287,"龙门大厦"));
//    insert(s,newData(39.14288,117.21037,"天津行车公寓"));
//
//
//
//    showAll(s);
//    printf("\n");
//
//    DataList *dataList=newDataList();
//    Data *d=newData(39.14050,117.20529, nullptr);
//    geoRadius(dataList,s,d->x,d->y,1000);
//    show(dataList);
//
//
//    _free(s);


    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

    string query;
    int flag, t;

    /**
     分配或初始化与mysql_real_connect()相适应的MYSQL对象。
     如果mysql是NULL指针，该函数将分配、初始化、并返回新对象。
     否则，将初始化对象，并返回对象的地址。如果mysql_init()分配了新的对象，当调用mysql_close()来关闭连接时。将释放该对象。
     */
    mysql_init (&mysql);


    /**
     * mysql_real_connect()尝试与运行在主机上的MySQL数据库引擎建立连接。在你能够执行需要有效MySQL连接句柄结构的任何其他API函数之前，mysql_real_connect()必须成功完成。
     */
    if (!mysql_real_connect(&mysql, "localhost", "root", "001124", "Smart_parking_data", 0, NULL, 0))
    {
        printf ("Failed to connect to Mysql!\n");
        return 0;
    }
    else
    {
        printf ("Connected MySQL successfully!\n");
        query = "select parking_lot_name,latitude,longitude from Parking_lot_information";

        //设置编码格式utf8
        mysql_query(&mysql, "set names utf8");

        /**
         * 执行由query指向的SQL查询，它应该是一个length个字节的字符串。查询必须由一个单个的SQL语句组成。
         */
        flag = mysql_real_query (&mysql, query.c_str(), query.length());
        if (flag)
        {
            printf ("query failed !\n");
            return 0;
        }
        else
        {
            printf ("query success !\n");
        }

        /**
         * 对于成功检索了数据的每个查询（SELECT、SHOW、DESCRIBE、EXPLAIN、CHECK TABLE等），必须调用mysql_store_result()或mysql_use_result() 。
         * 对于其他查询，不需要调用mysql_store_result()或mysql_use_result()，但是如果在任何情况下均调用了mysql_store_result()，它也不会导致任何伤害或性能降低。
         * 通过检查mysql_store_result()是否返回0，可检测查询是否没有结果集
         * 查询未返回数据(例如，它是INSERT、UPDATE或DELETE)
         */
        res = mysql_store_result (&mysql); // 获取结果集
        if(res== nullptr)
        {
            printf("result null");
            return 0;
        }

        /**
         * 返回作用在连接上的最近查询的列数。该函数的正常使用是在mysql_store_result()返回NULL（因而没有结果集指针）时。
         * 在这种情况下，可调用mysql_field_count()来判定mysql_store_result()是否应生成非空结果。
         * 这样，客户端就能采取恰当的动作，而无需知道查询是否是SELECT（或类似SELECT的）语句。
         */
        unsigned int num_columns  = mysql_field_count(&mysql);
        unsigned int num_rows = res->row_count; // 结果集中 行数
        printf ("num_columns = %d\n", num_columns);
        printf ("num_rows = %d\n", num_rows);

        /**
         * 检索一个结果集合的下一行。当在mysql_store_result()之后使用时，如果没有更多的行可检索时，mysql_fetch_row()返回NULL。
         */
        row = mysql_fetch_row(res); // 检索结果集的下一行 每行有 num_columns 列
        string result;
        int index = 0;
        while (row)
        {
            printf ("%d\t", ++index);

            for (t = 0; t < num_columns; t++)
                printf ("%s\t", row[t]);
            printf ("\n");
            row = mysql_fetch_row(res);
        }
        printf ("index = %d\n", index);
        mysql_free_result(res);

        /**
          mysql_close() 关闭指定的连接标识所关联的到 MySQL 服务器的连接。如果没有指定 link_identifier，则关闭上一个打开的连接。
          通常不需要使用 mysql_close()，因为已打开的非持久连接会在脚本执行完毕后自动关闭。参见释放资源。
         */
        mysql_close (&mysql);

        return 0;
    }
}
