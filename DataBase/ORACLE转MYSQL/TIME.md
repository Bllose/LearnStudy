# Time  

作为限制参数， 约束Date类型字段时， 如果是VARCHAR类型， ORACLE和MYSQL都能自动转化为时间类型进行判断  

``` SQL
-- ORACLE  
select to_char(to_date('2021-02-25 05:05:05', 'yyyy-MM-dd HH24:Mi:ss') + 8/24 , 'yyyy-MM-dd HH24:Mi:ss') from dual;
```
相当于  
``` SQL  
-- MYSQL  
select date_format(date_add(str_to_date('2021-02-25 05:05:05' ,'%Y-%m-%d %H:%i:%s'), interval 8 hour),'%Y-%m-%d %H:%i:%s');
```
> Oracle 的 DATE 值可以直接与 INTEGER 进行计算， 单位为天。 如果需要进行小时计算， 通过除以24实现。  
> MySQL 的 DATE 值进行计算通过 date_add() 函数进行.  
>> DATE_ADD(date, INTERVAL expr type)  
>> | Type Enum |  
>> | --- |
>> |  MICROSECOND  |
>> |  SECOND  |
>> |  MINUTE  |
>> |  HOUR  |
>> |  DAY  |
>> |  WEEK  |
>> |  MONTH  |
>> |  QUARTER  |
>> |  YEAR  |
>> |  SECOND_MICROSECOND  |
>> |  MINUTE_MICROSECOND  |
>> |  MINUTE_SECOND  |
>> |  HOUR_MICROSECOND  |
>> |  HOUR_SECOND  |
>> |  HOUR_MINUTE  |
>> |  DAY_MICROSECOND  |
>> |  DAY_SECOND  |
>> |  DAY_MINUTE  |
>> |  DAY_HOUR  |
>> |  YEAR_MONTH  |
