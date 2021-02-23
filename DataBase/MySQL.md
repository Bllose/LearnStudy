# 基础
## Function
- 查看  
``` show function status; ```


## Procedure
- 查看  
``` show procedure status; ```


## Table
- 删除主键  
``` ALTER TABLE table_name DROP PRIMARY KEY; ```



# 权限控制
> ``` GRANT 权限 ON 数据库对象 TO 用户 ```

## 视图
1. ``` GRANT create view ON database_name.'*' TO user_name@'%'; ```
2. ``` GRANT show view ON database_name.'*' TO user_name@'%'; ```

## 异常信息
### [42000][1133] Can't find any matching row in the user table
本质上是由于语句执行过程中无法找到匹配的角色信息， 而该角色信息保存在  
``` SELECT Host, User from mysql.user; ```  
例如， 在该条语句中``` GRANT CREATE VIEW ON abc.* TO ABC@'%'; ```出现异常。
是因为__user__表中的用户为  

 Host | User 
 ---- | ----
 % | abc  
 
 修改命令为``` GRANT CREATE VIEW ON abc.* TO abc@'%'; ```执行正常。


# 运维  
- 查看执行进程  
``` SQL
SHOW PROCESSLIST;
```
| Id | User | Host | db | Command | Time | State | Info |  
| --- | --- | --- | --- | --- | --- | --- | --- |
| 1664720 | user_name | 10.244.217.140:38938 | db_name | Sleep | 92 | "" |  |
| 1664904 | user_name | 10.244.217.140:43470 | db_name | Sleep | 3 | "" |  |
| 1664936 | user_name | 10.244.217.140:44550 | db_name | Sleep | 450 | "" |  |
| 1664991 | user_name | 10.242.118.143:59626 | db_name | Query | 292 | updating | /* ApplicationName=DataGrip 2020.1 */ UPDATE db_name.table_name t SET t.store_type = '7' WHER |
| 1664992 | user_name | 10.244.217.140:45684 | db_name | Sleep | 270 | "" |  |
| 1664993 | user_name | 10.244.217.140:45686 | db_name | Sleep | 270 | "" |  |
| 1664994 | user_name | 10.244.217.140:45688 | db_name | Sleep | 270 | "" |  |
| 1664995 | user_name | 10.244.217.140:45690 | db_name | Sleep | 270 | "" |  |
| 1664996 | user_name | 10.244.217.140:45692 | db_name | Sleep | 270 | "" |  |
| 1664997 | user_name | 10.244.217.140:45694 | db_name | Sleep | 270 | "" |  |
| 1664998 | user_name | 10.244.217.140:45696 | db_name | Sleep | 270 | "" |  |
| 1665023 | user_name | 10.242.118.143:59726 | db_name | Query | 191 | updating | /* ApplicationName=DataGrip 2020.1 */ UPDATE db_name.table_name t SET t.store_type = '7' WHER |
| 1665065 | user_name | 10.242.118.143:59964 | db_name | Query | 0 | starting | /* ApplicationName=DataGrip 2020.1 */ SHOW PROCESSLIST |

