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

    std::string query;
    int flag, t;

    mysql_init (&mysql);
    if (!mysql_real_connect
            (&mysql, "localhost", "root", "leacock", "MyTest", 0, NULL, 0))
    {
        printf ("Failed to connect to Mysql!\n");
        return 0;
    }
    else
    {
        printf ("Connected MySQL successfully!\n");
        query = "DESCRIBE People_Info;";
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

        res = mysql_store_result (&mysql); // 获取结果集
        unsigned int num_columns  = mysql_field_count(&mysql); // 结果集中 列数
        unsigned int num_rows = res->row_count; // 结果集中 行数
        printf ("num_columns = %d\n", num_columns);
        printf ("num_rows = %d\n", num_rows);
        row = mysql_fetch_row(res); // 检索结果集的下一行 每行有 num_columns 列
        std::string result;
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
        mysql_close (&mysql);
        return 0;
    }
}
