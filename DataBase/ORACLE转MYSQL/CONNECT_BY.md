# connect by  
## ORACLE
``` SELECT level FROM dual CONNECT BY LEVEL <= 5; ```  
| level |  
| --- |
| 1 |
| 2 |
| 3 |
| 4 |
| 5 |  

``` select regexp_replace('PUNISHMENT,WARNING', '[^,]+') as result from dual; ```  
| RESULT |
| --- |
| , |  

REGEXP_REPLACE 官方说明  
![regexp_replace](https://img-blog.csdnimg.cn/20190102102806583.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl80Mzc2NzAwMg==,size_16,color_FFFFFF,t_70)


``` ORACLE  
SELECT
    CAST(MULTISET(
        SELECT
            level
        FROM
            dual
        CONNECT BY
            level <= length(regexp_replace('PUNISHMENT,WARNING', '[^,]+')) + 1
    ) AS sys.odcinumberlist) AS odcinumberlist
FROM
    dual;
```  
| ODCINUMBERLIST |  
| --- |   
| SYS.ODCINUMBERLIST(1, 2) |    

``` ORACLE  
SELECT
    *
FROM
    TABLE ( CAST(MULTISET(
        SELECT
            level
        FROM
            dual
        CONNECT BY
            level <= length(regexp_replace('PUNISHMENT,WARNING', '[^,]+')) + 1
    ) AS sys.odcinumberlist) ) commas;
```   
| COLUMN_VALUE |  
| --- |
| 1 |
| 2 |  

## MYSQL  
``` MYSQL
SELECT SUBSTRING_INDEX(SUBSTRING_INDEX('12,3,13', ',', help_topic_id + 1), ',', -1) AS num
FROM mysql.help_topic
WHERE help_topic_id < LENGTH('12,3,13') - LENGTH(REPLACE('12,3,13', ',', '')) + 1;
```
| num |
| --- |
| 12 |
| 3 |
| 13 |
> 本质上来说， 就是利用表```mysql.help_topic```下的```help_topic_id```列。  
> 而该列本质上就是一个从0开始的递增队列。   

使用自定义表代替其功能:
``` SQL
-- ----------------------------
-- Table structure for help_topic_t
-- ----------------------------
DROP TABLE IF EXISTS `help_topic_t`;
CREATE TABLE `help_topic_t`  (
  `help_topic_id` int(11) NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '特殊功能支援表' ROW_FORMAT = DYNAMIC;
-- initialization
insert into help_topic_t values (0),(1),(2),(3),(4),(5),(6),(7),(8),(9),(10),(11),(12),(13),(14),(15),(16),(17),(18),(19),(20),(21),(22),(23),(24),(25),(26),(27),(28),(29),(30),(31),(32),(33),(34),(35),(36),(37),(38),(39),(40),(41),(42),(43),(44),(45),(46),(47),(48),(49),(50),(51),(52),(53),(54),(55),(56),(57),(58),(59),(60),(61),(62),(63),(64),(65),(66),(67),(68),(69),(70),(71),(72),(73),(74),(75),(76),(77),(78),(79),(80),(81),(82),(83),(84),(85),(86),(87),(88),(89),(90),(91),(92),(93),(94),(95),(96),(97),(98),(99),(100),(101),(102),(103),(104),(105),(106),(107),(108),(109),(110),(111),(112),(113),(114),(115),(116),(117),(118),(119),(120),(121),(122),(123),(124),(125),(126),(127),(128),(129),(130),(131),(132),(133),(134),(135),(136),(137),(138),(139),(140),(141),(142),(143),(144),(145),(146),(147),(148),(149),(150),(151),(152),(153),(154),(155),(156),(157),(158),(159),(160),(161),(162),(163),(164),(165),(166),(167),(168),(169),(170),(171),(172),(173),(174),(175),(176),(177),(178),(179),(180),(181),(182),(183),(184),(185),(186),(187),(188),(189),(190),(191),(192),(193),(194),(195),(196),(197),(198),(199),(200),(201),(202),(203),(204),(205),(206),(207),(208),(209),(210),(211),(212),(213),(214),(215),(216),(217),(218),(219);
```
