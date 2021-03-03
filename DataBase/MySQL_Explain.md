# explain 

- id : 表执行顺序
> id 从大到小按顺序执行， 相同ID从上到下执行
- table : 查询所关联的表
- type : 最重要字段之一， 使用的查询类型
  - system,const : 可以将查询的变量转化为常量， 比如 id=1; id为主键或唯一键
  - eq_ref : 访问索引，返回某单一行的数据。 （通常在联接时出现， 查询使用的索引为主键或唯一主键）
  - ref : 访问索引，返回某个值的数据。（可以返回多条）通常使用 ```=``` 时发生
  - range ： 这个连接类型使用索引返回的一个范围中的行， 比如使用 ```>``` 或 ```<``` 查找东西， 并且该字段上建有索引时发生。（不一定好于 index）
  - index ： 以索引的顺序进行全表扫描， 优点是 不用排序， 缺点是还要全表扫描
  - ALL : 全表扫描， 应尽量避免
- possible_keys : 显示可能应用在这张表中的索引。 如果为空， 则说明没有可应用的索引
- key : 实际使用的索引。 如果为NULL， 则没有使用索引。
- key_len : 索引长度， 足够精确的前提下， 越短越好
- ref : 显示索引的哪一列被使用了
- rows : MySQL认为必须检索的用来返回请求数据的行数
- Extra : MySQL解析的额外信息
  - using index : 只用到索引， 可以避免访问表， 性能很高
  - using where : 使用 ```where``` 来过滤数据，并不是所有```where clause```都显示```using where```。 比如```=```的方式
  - using tmporary : 使用临时表处理
  - using filesort : 用到额外的排序。此时mysql会根据联接类型浏览所有符合条件的记录，并保存排序关键字和行指针，然后排序关键字并按顺序检索行。(**当使用order by v1,而没用到索引时,就会使用额外的排序**)。
  - range checked for eache record(index map:N) : 没有好的索引可以使用
  - Using index for group-by : 表明可以在索引中找到分组所需的所有数据， 不需要查询实际的表


``` SQL
SELECT t.*
FROM (select t.rule_id                                       as ruleId,
             t.product_line                                  as productLineCode,
             productLine.Product_Name_Cn                     as productLineName,
             t.product_family                                as productFamilyCode,
             productFamily.Product_Name_Cn                   as productFamilyName,
             t.product_model                                    productModelCode,
             productModel.Offering_Name                      as productModelName,
             t.return_type                                   as returnType,
             t.start_days                                    as startDays,
             t.end_days                                      as endDays,
             t.create_by                                     as createBy,
             t.remark                                        as remarks,
             t.valid_start_time                              as validStartTime,
             t.valid_end_time                                as validEndTime,
             t.cust_code                                     as customerCode,
             cut.customer_name                               as customerName,
             date_format(t.create_time, '%Y-%m-%d %H:%i:%S') as createTime
      from ASC_PRODUCT_AUTH_RULE_T t
               left join mv_item_product_v productModel on t.product_model = productModel.offering_code
               left join asc_customer_t cut on t.cust_code = cut.customer_bg_code,
           item_product_t productLine,
           item_product_t productFamily
      where t.enable_flag = 'Y'
        and t.product_line = productLine.Product_Code
        and t.product_family = productFamily.Product_Code
        and cut.enable_flag = 'Y'
        and t.rule_type = '10'
      order by t.rule_id desc) t
limit 0,10;
```  
| id | select_type | table | partitions | type | possible_keys | key | key_len | ref | rows | filtered | Extra |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | 
 | 1 | SIMPLE | cut |  | ALL |  |  |  |  | 8 | 12.5 | Using where; Using temporary; Using filesort | 
 | 1 | SIMPLE | t |  | ALL |  |  |  |  | 476 | 0.21 | Using where; Using join buffer (Block Nested Loop) | 
 | 1 | SIMPLE | productLine |  | ALL |  |  |  |  | 5694 | 10 | Using where; Using join buffer (Block Nested Loop) | 
 | 1 | SIMPLE | productFamily |  | ALL |  |  |  |  | 5694 | 10 | Using where; Using join buffer (Block Nested Loop) | 
 | 1 | SIMPLE | lv0 |  | ALL |  |  |  |  | 5694 | 100 | Using where | 
 | 1 | SIMPLE | lv1 |  | ref | ITEM_PRODUCT_T_N2 | ITEM_PRODUCT_T_N2 | 6 | tbsdasc.lv0.product_pc_id | 5 | 100 | Using where | 
 | 1 | SIMPLE | lv2 |  | ref | ITEM_PRODUCT_T_N2 | ITEM_PRODUCT_T_N2 | 6 | tbsdasc.lv1.product_pc_id | 5 | 100 | Using index | 
 | 1 | SIMPLE | lv3 |  | ref | ITEM_PRODUCT_T_N2 | ITEM_PRODUCT_T_N2 | 6 | tbsdasc.lv2.product_pc_id | 5 | 100 | Using index | 
 | 1 | SIMPLE | lv4 |  | ref | ITEM_PRODUCT_T_N2 | ITEM_PRODUCT_T_N2 | 6 | tbsdasc.lv3.product_pc_id | 5 | 100 | Using where | 
 | 1 | SIMPLE | link |  | ALL |  |  |  |  | 66185 | 100 | Using where | 
 | 1 | SIMPLE | offering |  | eq_ref | "PRIMARY | ITEM_OFFERING_T_N1" | PRIMARY | 5 | tbsdasc.link.offering_id | 1 | 100 | Using where |   
 
 ``` SQL
 select `lv0`.`product_code`       AS `lv0_no`,
       `lv0`.`product_name_cn`    AS `lv0_cn`,
       `lv0`.`product_category`   AS `lv0_category`,
       `lv1`.`product_code`       AS `lv1_no`,
       `lv1`.`product_name_cn`    AS `lv1_cn`,
       `lv1`.`product_name_en`    AS `lv1_en`,
       `lv1`.`product_category`   AS `lv1_category`,
       `lv2`.`product_code`       AS `lv2_no`,
       `lv2`.`product_name_cn`    AS `lv2_cn`,
       `lv2`.`product_name_en`    AS `lv2_en`,
       `lv2`.`product_category`   AS `lv2_category`,
       `lv3`.`product_code`       AS `lv3_no`,
       `lv3`.`product_name_cn`    AS `lv3_cn`,
       `lv3`.`product_name_en`    AS `lv3_en`,
       `lv3`.`product_category`   AS `lv3_category`,
       `lv4`.`product_code`       AS `lv4_no`,
       `lv4`.`product_name_cn`    AS `lv4_cn`,
       `lv4`.`product_name_en`    AS `lv4_en`,
       `lv4`.`product_category`   AS `lv4_category`,
       `link`.`offering_id`       AS `offering_id`,
       `link`.`status`            AS `status`,
       `offering`.`offering_code` AS `offering_code`,
       `offering`.`offering_name` AS `offering_name`,
       `offering`.`desc_cn`       AS `OFFER_DESC_CN`,
       `offering`.`desc_en`       AS `OFFER_DESC_EN`,
       `offering`.`brand`         AS `brand`
from `tbsdasc`.`item_product_t` `lv0`
         left join `tbsdasc`.`item_product_t` `lv1` on `lv0`.`product_pc_id` = `lv1`.`product_parent_id`
         left join `tbsdasc`.`item_product_t` `lv2` on `lv1`.`product_pc_id` = `lv2`.`product_parent_id`
         left join `tbsdasc`.`item_product_t` `lv3` on `lv2`.`product_pc_id` = `lv3`.`product_parent_id`
         left join `tbsdasc`.`item_product_t` `lv4` on `lv3`.`product_pc_id` = `lv4`.`product_parent_id`
         left join `tbsdasc`.`item_product_offering_t` `link` on `lv4`.`product_pc_id` = `link`.`product_pc_id`
         left join `tbsdasc`.`item_offering_t` `offering` on `link`.`offering_id` = `offering`.`offering_id`
where `lv0`.`product_code` = 'PDCG901161'
  and `lv1`.`product_category` = '402-00025349'
  and `lv1`.`product_status` = 1
  and `lv4`.`product_status` = 1
  and `link`.`status` = 1;
 ```  
| id | select_type | table | partitions | type | possible_keys | key | key_len | ref | rows | filtered | Extra |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | 
 | 1 | SIMPLE | lv4 |  | ALL | "{2}" |  |  |  | 5694 | 10 | Using where | 
 | 1 | SIMPLE | lv3 |  | eq_ref | "{2}" | PRIMARY | 5 | tbsdasc.lv4.product_parent_id | 1 | 100 |  | 
 | 1 | SIMPLE | lv2 |  | eq_ref | "{2}" | PRIMARY | 5 | tbsdasc.lv3.product_parent_id | 1 | 100 |  | 
 | 1 | SIMPLE | lv1 |  | eq_ref | "{2}" | PRIMARY | 5 | tbsdasc.lv2.product_parent_id | 1 | 5 | Using where | 
 | 1 | SIMPLE | lv0 |  | eq_ref | "{1}" | PRIMARY | 5 | tbsdasc.lv1.product_parent_id | 1 | 10 | Using where | 
 | 1 | SIMPLE | link |  | ALL |  |  |  |  | 66185 | 1 | Using where; Using join buffer (Block Nested Loop) | 
 | 1 | SIMPLE | offering |  | eq_ref | "PRIMARY | ITEM_OFFERING_T_N1" | PRIMARY | 5 | tbsdasc.link.offering_id | 1 | 100 |  | 


通过建立索引：
``` create index product_pc_id_index on item_product_offering_t(product_pc_id); ```
与上下表建立字段的索引对，从而优化搜索  
| id | select_type | table | partitions | type | possible_keys | key | key_len | ref | rows | filtered | Extra |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | 
 | 1 | SIMPLE | lv4 |  | ALL | "{2}" |  |  |  | 5694 | 10 | Using where | 
 | 1 | SIMPLE | lv3 |  | eq_ref | "{2}" | PRIMARY | 5 | tbsdasc.lv4.product_parent_id | 1 | 100 |  | 
 | 1 | SIMPLE | lv2 |  | eq_ref | "{2}" | PRIMARY | 5 | tbsdasc.lv3.product_parent_id | 1 | 100 |  | 
 | 1 | SIMPLE | lv1 |  | eq_ref | "{2}" | PRIMARY | 5 | tbsdasc.lv2.product_parent_id | 1 | 5 | Using where | 
 | 1 | SIMPLE | lv0 |  | eq_ref | "{1}" | PRIMARY | 5 | tbsdasc.lv1.product_parent_id | 1 | 10 | Using where | 
 | 1 | SIMPLE | link |  | ref | product_pc_id_index | product_pc_id_index | 6 | tbsdasc.lv4.product_pc_id | 15 | 10 | Using where | 
 | 1 | SIMPLE | offering |  | eq_ref | "PRIMARY | ITEM_OFFERING_T_N1" | PRIMARY | 5 | tbsdasc.link.offering_id | 1 | 100 |  | 
