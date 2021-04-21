# connect by  
## ORACLE
``` SELECT level FROM dual CONNECT BY LEVEL <= 5; ```  
| level |  
| --- |
| 1 |
| 2 |
| 3 |
| 4 |
| 5 |  

``` select regexp_replace('PUNISHMENT,WARNING', '[^,]+') as result from dual; ```  
| RESULT |
| --- |
| , |  

REGEXP_REPLACE 官方说明  
![regexp_replace](https://img-blog.csdnimg.cn/20190102102806583.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzc2NzAwMg==,size_16,color_FFFFFF,t_70)


``` ORACLE  
SELECT
    CAST(MULTISET(
        SELECT
            level
        FROM
            dual
        CONNECT BY
            level <= length(regexp_replace('PUNISHMENT,WARNING', '[^,]+')) + 1
    ) AS sys.odcinumberlist) AS odcinumberlist
FROM
    dual;
```  
| ODCINUMBERLIST |  
| --- |   
| SYS.ODCINUMBERLIST(1, 2) |    

``` ORACLE  
SELECT
    *
FROM
    TABLE ( CAST(MULTISET(
        SELECT
            level
        FROM
            dual
        CONNECT BY
            level <= length(regexp_replace('PUNISHMENT,WARNING', '[^,]+')) + 1
    ) AS sys.odcinumberlist) ) commas;
```   
| COLUMN_VALUE |  
| --- |
| 1 |
| 2 |  

## MYSQL  
``` MYSQL
SELECT SUBSTRING_INDEX(SUBSTRING_INDEX('12,3,13', ',', help_topic_id + 1), ',', -1) AS num
FROM mysql.help_topic
WHERE help_topic_id < LENGTH('12,3,13') - LENGTH(REPLACE('12,3,13', ',', '')) + 1;
```

