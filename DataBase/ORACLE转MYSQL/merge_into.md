# merge into
- ORACLE
``` SQL
MERGE INTO table_name alias1
USING (table | view | sub_query) alias2
ON (join condition)
WHEN MATCHED THEN
  UPDATE table_name SET col1 = col_val1, col2 = col2_val
WHEN NOT MATCHED THEN
  INSERT (column_list) VALUES (column_values);
```
> 对于MYSQL中提供的方法: ON DUPLICATE KEY UPDATE; REPLACE INTO.  
相对于```MERGE INTO```缺陷在于缺少```ON (join condition)```. 即MYSQL只能通过唯一主键或唯一索引判断哪些数据是重复的。  
[MySQL supports the use of ```INSERT ... ON DUPLICATE KEY UPDATE``` syntax which can be used to achieve a similar effect with the limitation that the join between target and source has to be made only on **PRIMARY KEY** or **UNIQUE** constraints, which is not required in the ANSI/ISO standard. It also supports ```REPLACE INTO``` syntax, which first attempts an insert, and if that fails, deletes the row, if exists, and then inserts the new one.](https://stackoverflow.com/questions/42663074/is-merge-statement-available-in-mysql)

- MYSQL
``` SQL
REPLACE INTO table_name(column_list) VALUES (values);  
REPLACE INTO table_name(column_list) SELECT column_list [FROM table_name [WHERE ]];  
INSERT INTO table_name(column_list) SELECT column_list FROM table_name_new ON DUPLICATE KEY UPDATE column_1 = value_1, column_2 = value_2 ...;
```  
> ```REPLACE INTO```语法相对简洁，无需多余指定，除了主键和唯一索引，其他字段都用于更新。  
```ON DUPLICATE KEY UPDATE```需要额外指定更新字段。可以更精确控制需要更新的字段。

### 解决方案
- 通过建立主键或唯一索引
- 通过代码辅助完成
> 收件将整个列表进行查询操作，返回所有存在的**关键字**，然后将所有得到的关键字进行更新操作。  
而不存在的关键字进行插入操作
- 通过存储过程与游标
