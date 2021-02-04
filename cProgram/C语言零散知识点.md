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


## [宏](#宏)

- 在程序编译时，将先由预处理程序进行宏代替。即将程序中出现宏名的位置，原封不动地变为宏表达式  
``` C
#define M n*n+3*n

int main(){
    int sum = 3*M + 4*M + 5*M;
    printf("%d", sum);
}
```  
编译后，程序实际得到的式子为：
``` C
    int sum = 3*n*n+3*n + 4*n*n+3*n + 5*n*n+3*n;
```


[宏](@宏) : Macro  
> 广大 : a single instruction given to a computer that produces a set of instructions for the computer to perform a particular piece of work.  

Macro-  
large; relating to the whole of something, rather than its parts.  
macroscopic(= large enough to be seen by the human eye)  
macroeconomics(= the study of financial systems at a national level)
