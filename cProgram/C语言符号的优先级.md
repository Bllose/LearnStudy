# C语言包含十五个优先级

## 十五优先级
- 强制转换 ()
- (数组)下标 []
- 成员 ->与.
``` C
float result = same_counter*1.00/(tar_one.wide * tar_one.length);
printf("相似度为： %d%%", (int)(result*100));
```
> 如上所示 ``` (int)(result*100) ``` 如果结果为 87, 那么如果写成``` (int) result*100 ``` 结果将会是 0

