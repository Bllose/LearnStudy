
视图实际是一个自身不存储数据的虚拟数据表。  
实际上这个虚拟表的数据来自于访问视图下SQL所查询到的结果。  
视图(view)和数据表(table)在MySQL中共享命名空间。然而处理二者的方式不同。 例如：视图没有触发器， 也无法使用```DROP TABLE```命令移除视图。

在MySQL中使用两种算法， 称之为MERGE和TEMPTABLE， 尽可能使用MERGE算法。
![merge&temp](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/3e6489640e404c0eb5ff558a17bd713e~tplv-k3u1fbpfcp-zoom-1.image)
  
当视图中有 GROUP BY, DISTINCT, 聚合函数, UNION, 子查询 或其他数据表之间不是一对一的关系时， MySQL会使用TEMPTABLE算法。
当使用```explain```语句， ```select_type```中有**DERIVED**的话， 则表示使用了TEMPTABLE算法。  

如果隐藏的衍生表需要很高的代价产生， EXPLAIN就会变得性能很低并且执行很慢， 因为它需要实际执行和构建衍生表。  

这些算法在生成视图的时候已经确认， 不会因为不同的查询条件而改变。


# 直接优化视图难度大， 使用变通的办法实现  

通过创建表， 通过procedure插入或更新数据， 使用Event作为定时触发。  
``` CREATE TABLE table_name (...);```  
``` SQL
CREATE PROCEDURE procedure_name()
BEGIN
  sql_statement; 
END;
```  
``` SQL 
CREATE EVENT event_name ON SCHEDULE every 1 day DO sql_statement;
