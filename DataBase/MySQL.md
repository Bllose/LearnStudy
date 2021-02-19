# 基础
## Function
- 查看  
``` show function status; ```


## Procedure
- 查看  
``` show procedure status; ```



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
