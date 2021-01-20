//
// Created by cWX921932 on 2021/1/19.
//
// n! 的最后一位非0的数
#include <stdio.h>

void process_factorial(int n){
    if(n > 10000 || n < 1) return; // 将作用范围控制在 1~10000

    int result = 1;

    for (; n > 0 ; n --){
        result *= n;
        while(!(result%10)){
            result /= 10;
        }
        if(result > 100){
            result = result % 100;
        }
    }

    printf("%d\n", result%10);

}


void factorial_processor(){
    process_factorial(100);
}
