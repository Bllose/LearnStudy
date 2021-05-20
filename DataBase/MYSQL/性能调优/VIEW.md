
视图实际是一个自身不存储数据的虚拟数据表。  
实际上这个虚拟表的数据来自于访问视图下SQL所查询到的结果。  
视图(view)和数据表(table)在MySQL中共享命名空间。然而处理二者的方式不同。 例如：视图没有触发器， 也无法使用```DROP TABLE```命令移除视图。

![merge&](https://p3-juejin.byteimg.com/tos-cn-i-k3u1fbpfcp/3e6489640e404c0eb5ff558a17bd713e~tplv-k3u1fbpfcp-zoom-1.image)
