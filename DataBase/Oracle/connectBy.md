# CONNECT BY  


``` select level from dual connect by level < 3 ```  
| LEVEL |  
| --- |  
| 1 |  
| 2 |  

``` ORACLE  
-- d 表示一个星期中的第几天
-- iw 表示一年中的第几周
SELECT
    SYSDATE - ( to_number(TO_CHAR(SYSDATE - 1, 'd')) - 1 ) - ( ROWNUM - 1 ) * 7 AS startdate,
    SYSDATE + ( 7 - to_number(TO_CHAR(SYSDATE - 1, 'd')) ) - ( ROWNUM - 1 ) * 7 AS enddate,
    to_number(TO_CHAR(SYSDATE, 'iw')) - ROWNUM + 1 AS weekindex
FROM
    dual
CONNECT BY
    ROWNUM <= 12;
```  

| STARTDATE | ENDDATE | WEEKINDEX |  
| --- | --- | --- |
| 12-4月-21 | 18-4月-21 | 15 |
| 05-4月-21 | 11-4月-21 | 14 |
| 29-3月-21 | 04-4月-21 | 13 |
| 22-3月-21 | 28-3月-21 | 12 |
| 15-3月-21 | 21-3月-21 | 11 |
| 08-3月-21 | 14-3月-21 | 10 |
| 01-3月-21 | 07-3月-21 | 9 |
| 22-2月-21 | 28-2月-21 | 8 |
| 15-2月-21 | 21-2月-21 | 7 |
| 08-2月-21 | 14-2月-21 | 6 |
| 01-2月-21 | 07-2月-21 | 5 |
| 25-1月-21 | 31-1月-21 | 4 |
  
  
  
### TABLE( CAST( MULTISET() )  AS sys.odcinumberlist)   

