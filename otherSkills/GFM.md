
# [GitHub Flavored Markdown Spec](https://github.github.com/gfm/)
- MATH 相关内容
> [How to show math equations in general github's markdown](https://stackoverflow.com/questions/11256433/how-to-show-math-equations-in-general-githubs-markdownnot-githubs-blog)  
[github markup issue](https://github.com/github/markup/issues/897)  

    1. Script+MathJax 解决方案
    > MathJax 是一个用于数学公式展示的JavaScrip引擎  
    ``` <script src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML" type="text/javascript"></script> ```
    ``` JavaScrip
    <script type="text/x-mathjax-config">
    MathJax.Hub.Config({
      tex2jax: {
        inlineMath: [ ['$','$'], ["\\(","\\)"] ],
        processEscapes: true
      }
    });
    </script>  
    ```
  
    2. 外部网站
    ```<img src="http://chart.googleapis.com/chart?cht=tx&chl= 在此插入Latex公式" style="border:none;">```
    样例:  
    <img src="http://chart.googleapis.com/chart?cht=tx&chl=\Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}" style="border:none;">  

    ```<img src="http://www.forkosh.com/mathtex.cgi? 在此处插入Latex公式">```
    样例:  
    <img src="http://www.forkosh.com/mathtex.cgi? \Large x=\frac{-b\pm\sqrt{b^2-4ac}}{2a}">
