# 查询于锁有关的线程信息
``` SQL
show full PROCESSLIST;
select * from information_schema.INNODB_LOCKS;
select * from information_schema.innodb_lock_waits;
```  

# 指定锁类型的查询语句  
排他锁:写锁:X锁  
``` SQL
select * from tableName where columnName = searchValue for update;
```
该语句可以保证查询到的值为最后更新的值， 但如果有update语句没有提交，将要等待。  

共享锁:读锁:S锁
``` SQL
select * from tableName where columnName = searchValue LOCK IN SHARE MODE;
```
该语句如果有update语句没有提交， 也时需要等待的， 最终会查询到update之后的结果。  

``` SQL
select * from tableName where columnName = searchValue;
```  
普通的查询语句， 不会收到update的锁影响， 会查出脏数据。
