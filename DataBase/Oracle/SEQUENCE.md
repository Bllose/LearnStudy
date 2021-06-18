# 查询
``` SQL  
select * from dba_sequences where sequence_owner='sequenceOwner';
```

# 修改  
### 修改当前值  
1. 删除队列，然后新建相同队列，且开始于我们需要修改的值。
2. 修改增量，然后获取下一个值，然后将增量改回到原值。  

通过修改增量的方法:
``` SQL
-- 先计算当前队列值与目标值之间的差距， 获取并替换下方 increaseNumber
alter sequence sequenceName increment by increaseNumber nocache;
select sequenceName.nextval from dual;
alter sequence sequenceName increment by 1 nocache; 
```

通过重新建立队列的方法：
``` SQL
drop sequence sequenceName;
CREATE SEQUENCE  sequenceName  MINVALUE minNumber MAXVALUE maxNumber INCREMENT BY 1 START WITH currNumber NOCACHE  NOORDER  NOCYCLE;
```
