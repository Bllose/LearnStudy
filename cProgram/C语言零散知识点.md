# 编码硬规则
## 方法

- 方法定义
> 方法的定义不允许嵌套。编译过程报错：Function definition is not allowed here。   
但实践证明：GNU gdb (GDB) 8.1 允许函数定义嵌套；同时网友反映：TMD-GCC 4.9.2 64-bit Release 同样允许函数定义嵌套。

``` C
void fun() {

    int fun_inner(int a, int b) { //Function definition is not allowed here.
        return a - b;
    }

    printf("result = %d\n", fun_inner(5, 67));
}
```


## 宏[^1]

- 宏 注释 规则

*[宏] : macro  
a single instruction given to a computer that produces a set of instructions for the computer to perform a particular piece of work.

*[注释]：注释内容

[^1]: macro
