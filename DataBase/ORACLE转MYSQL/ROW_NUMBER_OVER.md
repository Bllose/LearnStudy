- ORACLE
``` ORACLE
SELECT
	ct.check_no,
	adt.device_id,
	ct.logistics_no,
	row_number() over ( PARTITION BY adt.device_id ORDER BY ct.create_time DESC ) rn
FROM
	table_one ct
	INNER JOIN table_two adt ON adt.check_id = ct.check_id;
```   
以device_id作为集合， 按照create_time倒序进行排序 进行编号。

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
      FROM table_one ct
               INNER JOIN table_two adt ON adt.check_id = ct.check_id
      order by adt.device_id, ct.create_time desc
     ) a,
     (SELECT @rownum := 0, @objno := NULL, @rank := 0) b;
```  

>    首先 **MYSQL** 需要分为两个部分来完成该功能。
>> 1. 通过子查询，将数据源数据集中起来，功能相当于完成了 **ORACLE** 将 ``` FROM ``` 数据源导入ROW_NUMBER()集合。  
>> 2. 通过变量 ``` @rank ``` 匹配关键字 ***device_id*** ,计数得到结果，从而达到 ``` OVER() ``` 的效果。  


> 变更诀窍
>>``` PARTITION BY adt.device_id ORDER BY ct.create_time DESC ``` 中 ``` PARTITION BY ``` 并入子查询的``` GROUP BY ```, ``` ORDER BY ``` 并入子查询  	
>>
	 
> ``` PARTITION BY expression ORDER BY expression ```通过**MYSQL**中子查询的``` ORDER BY ```实现  

<font color=#008000>**MYSQL**子查询中变量```@objno```，其赋值动作```@objno := a.device_id as compare```一定要在```IF```语句之后才能生效，这是什么原因?</font>
