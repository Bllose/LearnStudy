# 非对应性转化
## merge into
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
``` SQL
INSERT INTO table_name(column_list) SELECT column_list FROM table_name_new ON DUPLICATE KEY UPDATE 
```
