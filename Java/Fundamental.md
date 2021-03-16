# Java 8 Stream  
Java 集合运算和表达的高阶抽象。 这种风格将要处理的元素集合看做一种流， 流在管道中传输， 并可以在管道的节点上进行处理， 比如筛选， 排序， 聚合等等。  
元素流在管道中经过中间操作(intermediate operation)的处理， 最后由最终操作(terminal operation)得到前面处理的结果。  

```
+--------------------+       +------+   +------+   +---+   +-------+
| stream of elements +-----> |filter+-> |sorted+-> |map+-> |collect|
+--------------------+       +------+   +------+   +---+   +-------+
```

## 生成流  
两种方式：  
- **stream()** 为集合创建串行流  
- **parallelStream()** 为集合创建并行流  

## Foreach  

## map
map方法用于映射每个元素所对应的结果
``` Java
List<TestVo> testList = new ArrayList<>();
testList.add(new TestVo(11, "Bllose"));
testList.add(new TestVo(22, "Rcedw"));
testList.add(new TestVo(33, "Again"));
testList.add(new TestVo(44, "Forever"));
testList.add(new TestVo(44, "Test"));

List<Integer> result = testList.stream().map(TestVo::getId).collect(Collectors.toList());
List<Integer> result_1 = testList.stream().map(TestVo::getId).distinct().collect(Collectors.toList());

System.out.println(result);
System.out.println(result_1);
```  
输出结果: 
```  
[11, 22, 33, 44, 44]
[11, 22, 33, 44]
```
