``` SQL
explain
select th.IDEAL_NO                               as     idealNo,
       th.ideal_head_id                          as     idealHeadId,
       tar.cust_name                             as     custName,
       th.apply_no                               as     applyNo,
       th.ststus                                 AS     status,
       th.business_flow                                 businessFlow,
       tar.model_code                                   modelCode,
       date_format(th.CREATE_TIME, '%Y-%m-%d %H:%i:%S') createTime
from asc_ideal_head_t th,
     asc_return_apply_t tar
where tar.apply_no = th.apply_no
  and tar.apply_status != '5';
```  
| id | select\_type | table | partitions | type | possible\_keys | key | key\_len | ref | rows | filtered | Extra |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | SIMPLE | th | NULL | ALL | IDEAL\_HEAD\_ID\_N1 | NULL | NULL | NULL | 185050 | 100 | Using where |
| 1 | SIMPLE | tar | NULL | ref | ASC\_RETURN\_APPLY\_N1 | ASC\_RETURN\_APPLY\_N1 | 203 | tbsdasc.th.apply\_no | 1 | 100 | Using index condition; Using where |  
  
  
``` SQL
explain
select th.IDEAL_NO                               as     idealNo,
       th.ideal_head_id                          as     idealHeadId,
       tar.cust_name                             as     custName,
       th.apply_no                               as     applyNo,
       th.ststus                                 AS     status,
       th.business_flow                                 businessFlow,
       tar.model_code                                   modelCode,
       date_format(th.CREATE_TIME, '%Y-%m-%d %H:%i:%S') createTime,
       (select COUNT(ti.device_id)
        from tbsdrtc.rtc_check_result_t ti
        where ti.rto_no = th.transport_order_no) as     totalCount
from asc_ideal_head_t th,
     asc_return_apply_t tar
where tar.apply_no = th.apply_no
  and tar.apply_status != '5';
```  
| id | select\_type | table | partitions | type | possible\_keys | key | key\_len | ref | rows | filtered | Extra |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | PRIMARY | th | NULL | ALL | IDEAL\_HEAD\_ID\_N1 | NULL | NULL | NULL | 185050 | 100 | Using where |
| 1 | PRIMARY | tar | NULL | ref | ASC\_RETURN\_APPLY\_N1 | ASC\_RETURN\_APPLY\_N1 | 203 | tbsdasc.th.apply\_no | 1 | 100 | Using index condition; Using where |
| 2 | DEPENDENT SUBQUERY | ti | NULL | ref | RTC\_CHECK\_RESULT\_N1 | RTC\_CHECK\_RESULT\_N1 | 803 | tbsdasc.th.transport\_order\_no | 1 | 100 | Using index condition |


``` SQL
explain
select th.IDEAL_NO                               as     idealNo,
       th.ideal_head_id                          as     idealHeadId,
       tar.cust_name                             as     custName,
       th.apply_no                               as     applyNo,
       th.ststus                                 AS     status,
       th.business_flow                                 businessFlow,
       tar.model_code                                   modelCode,
       date_format(th.CREATE_TIME, '%Y-%m-%d %H:%i:%S') createTime,
       (select COUNT(ti.device_id)
        from tbsdrtc.rtc_check_result_t ti
        where ti.rto_no = th.transport_order_no) as     totalCount,
       (SELECT count(tag.device_id)
        FROM asc_guest_association_t tag,
             asc_ideal_ordet_t tio
        where th.ideal_head_id = tio.ideal_head_id
          and tag.enable_flag = 'Y'
          and tio.order_id = tag.order_id)       as     completeCount
from asc_ideal_head_t th,
     asc_return_apply_t tar
where tar.apply_no = th.apply_no
  and tar.apply_status != '5';
```  
| id | select\_type | table | partitions | type | possible\_keys | key | key\_len | ref | rows | filtered | Extra |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 1 | PRIMARY | th | NULL | ALL | IDEAL\_HEAD\_ID\_N1 | NULL | NULL | NULL | 185050 | 100 | Using where |
| 1 | PRIMARY | tar | NULL | ref | ASC\_RETURN\_APPLY\_N1 | ASC\_RETURN\_APPLY\_N1 | 203 | tbsdasc.th.apply\_no | 1 | 100 | Using index condition; Using where |
| 3 | DEPENDENT SUBQUERY | tag | NULL | ref | ASC\_GUEST\_ASSOCIATION\_N1,ASC\_GUEST\_ASSOCIATION\_N5 | ASC\_GUEST\_ASSOCIATION\_N5 | 7 | const | 465224 | 100 | Using where |
| 3 | DEPENDENT SUBQUERY | tio | NULL | eq\_ref | PRIMARY,ASC\_IDEAL\_ORDET\_N1 | PRIMARY | 9 | tbsdasc.tag.order\_id | 1 | 10 | Using where |
| 2 | DEPENDENT SUBQUERY | ti | NULL | ref | RTC\_CHECK\_RESULT\_N1 | RTC\_CHECK\_RESULT\_N1 | 803 | tbsdasc.th.transport\_order\_no | 1 | 100 | Using index condition |
