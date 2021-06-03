# REGEXP_SUBSTR
function ```REGEXP_SUBSTR(String, pattern, position, occurrence, modifier)```
- string:需要进行正则处理的字符串
- pattern：进行匹配的正则表达式
- position：起始位置，从字符串的第几个字符开始正则表达式匹配（默认为1） 注意：字符串最初的位置是1而不是0
- occurrence：获取第几个分割出来的组（分割后最初的字符串会按分割的顺序排列成组）
- modifier：模式（‘i’不区分大小写进行检索；‘c’区分大小写进行检索。默认为’c’）针对的是正则表达式里字符大小写的匹配  

``` SELECT REGEXP_SUBSTR(‘11a22A33a’,’[^A]+’,1,1,‘i’) AS STR FROM DUAL; ```  
> 配置不区分大小写， 从句首开始匹配不为字母a的对象， 结果为 : 11
