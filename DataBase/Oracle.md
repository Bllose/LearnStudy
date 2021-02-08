# 高级方法
- ROW_NUMBER() OVER([PARTITION BY value_expression, ... [n]] ORDER_BY_CLAUSE )
```PARTITION BY value_expression```
> 将```FROM```子句生成的结果集划入应用了ROW_NUMBER函数的分区。其中```value_expression```指定对结果集进行分区所依据的列，若未指定，则此函数将视所有行为单个组。
```ORDER_BY_CLAUSE```子句可确定特定分区中的行分配唯一的 **ROW_NUMBER** 的顺序。
