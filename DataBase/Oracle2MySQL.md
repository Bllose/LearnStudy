# 非对应性转化
## merge into
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


## ROW_NUMBER() OVER() 
- ORACLE
``` ORACLE
SELECT
	ct.check_no,
	adt.device_id,
	ct.logistics_no,
	row_number() over ( PARTITION BY adt.device_id ORDER BY ct.create_time DESC ) rn
FROM
	asc_check_t ct
	INNER JOIN asc_check_detail_t adt ON adt.check_id = ct.check_id;
```  
- MYSQL
``` MYSQL
SELECT a.device_id,
       a.check_no,
       a.logistics_no,
       IF
           (
                   @objno = a.device_id
                   OR (@objno IS NULL AND a.device_id IS NULL),
                   @rank := @rank + 1,
                   @rank := 1
           )                 AS rn,
       @objno := a.device_id as compare
FROM (SELECT ct.check_no,
             adt.device_id,
             ct.logistics_no
      FROM asc_check_t ct
               INNER JOIN asc_check_detail_t adt ON adt.check_id = ct.check_id
      order by adt.device_id, ct.create_time desc
     ) a,
     (SELECT @rownum := 0, @objno := NULL, @rank := 0) b;
```  

>    首先 **MYSQL** 需要分为两个部分来完成该功能。
>>1. 通过子查询，将数据源数据集中起来，功能相当于完成了 **ORACLE** 将 ``` FROM ``` 数据源导入ROW_NUMBER()集合。  
  2. 通过变量 ``` @rank ``` 匹配关键字 ***device_id*** ,计数得到结果，从而达到 ``` OVER() ``` 的效果。  
> 变更诀窍
> ``` PARTITION BY expression ORDER BY expression ```通过**MYSQL**中子查询的``` ORDER BY ```实现  

<font color=#008000>**MYSQL**子查询中变量```@objno```，其赋值动作```@objno := a.device_id as compare```一定要在```IF```语句之后才能生效，这是什么原因?</font>
