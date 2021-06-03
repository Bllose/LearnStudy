# SUBSTRING_INDEX 字符串子串截取
``` substring_index(str,delim,count) ```  
- str 被截取字符串
- delim 分隔符
- count 计数
  - 如果是正数，则从左到右计数
  - 如果是负数，则从右向左计数  

比如：
``` SELECT SUBSTRING_INDEX('12,3,13', ',', 2) as result; ```  
| result |
| --- |
| 12,3 |  

``` SELECT SUBSTRING_INDEX('12,3', ',', -1) as result; ```  
| result |
| --- |
| 3 |  

相当于执行下面语句, 即获取中间某次匹配的方法
``` SELECT SUBSTRING_INDEX(SUBSTRING_INDEX('12,3,13', ',', 2), ',', -1) as result; ```
