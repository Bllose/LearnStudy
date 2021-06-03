# REGEXP_SUBSTR 通过正则表达式获取匹配的字符串子串
function ```REGEXP_SUBSTR(String, pattern, position, occurrence, modifier)```
- string:需要进行正则处理的字符串
- pattern：进行匹配的正则表达式
- position：起始位置，从字符串的第几个字符开始正则表达式匹配（默认为1） 注意：字符串最初的位置是1而不是0
- occurrence：获取第几个分割出来的组（分割后最初的字符串会按分割的顺序排列成组）
- modifier：模式（‘i’不区分大小写进行检索；‘c’区分大小写进行检索。默认为’c’）针对的是正则表达式里字符大小写的匹配  

``` SELECT REGEXP_SUBSTR(‘11a22A33a’,’[^A]+’,1,1,‘i’) AS STR FROM DUAL; ```  
> 配置不区分大小写， 从句首开始匹配不为字母a的对象， 结果为 : 11


# REGEXP_COUNT 通过正则表达式获取子串的匹配次数
```REGEXP_COUNT ( source_char, pattern [, position [, match_param]])```  
- source_char 被匹配字符串
- pattern 子串的正则表达式
- position 匹配的起始位置
- 匹配规则
  - ‘i’ 用于不区分大小写的匹配
  - ‘c’ 用于区分大小写的匹配
  - ‘n’ 允许句点(.)作为通配符去匹配换行符。如果省略该参数，则句点将不匹配换行符
  - ‘m’ 将源串视为多行。即Oracle 将^和$分别看作源串中任意位置任何行的开始和结束，而不是仅仅看作整个源串的开始或结束。如果省略该参数，则Oracle将源串看作一行。
  - ‘x’ 忽略空格字符。默认情况下，空格字符与自身相匹配。
