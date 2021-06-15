# information_schema
``` SQL 
SELECT * FROM information_schema.INNODB_TRX; 
```  

``` SQL  
select l.requesting_trx_id,
       t1.trx_state           trx_state_req,
       t1.trx_started         trx_started_req,
       t1.trx_wait_started    trx_wait_started_req,
       t1.trx_mysql_thread_id trx_mysql_thread_id_req,
       t1.trx_query           trx_query_req,
       l.blocking_trx_id,
       t2.trx_state           trx_state_blk,
       t2.trx_started         trx_started_blk,
       t2.trx_wait_started    trx_wait_started_blk,
       t2.trx_mysql_thread_id trx_mysql_thread_id_blk,
       t2.trx_query           trx_query_blk
from information_schema.INNODB_LOCK_WAITS l,
     information_schema.INNODB_TRX t1,
     information_schema.INNODB_TRX t2
where l.requesting_trx_id = t1.trx_id
  and l.blocking_trx_id = t2.trx_id;
```  


# processlist  
``` SQL
show full processlist; 
```


