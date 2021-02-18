# [Can't connect to HTTPS URL because the SSL module is not available #8273](https://github.com/conda/conda/issues/8273)

copy the following files  
> libcrypto-1_1-x64.*  
libssl-1_1-x64.*  

from D:\Anaconda3\Library\bin to D:\Anaconda3\DLLs.


# [ImportError: DLL load failed while importing error](https://blog.csdn.net/GUET_DM_LQ/article/details/106669205)

anaconda 安装 jupyter 后尝试启动 notebook 时出现异常。  
```
D:\etc\Python\Anaconda3\Scripts>jupyter notebook
_cffi_ext.c
D:\etc\Python\Anaconda3\lib\site-packages\zmq\backend\cffi\__pycache__\_cffi_ext.c(268): fatal error C1083: 无法打开包括文件: “zmq.h”: No such file or directory
Traceback (most recent call last):
  File "D:\etc\Python\Anaconda3\Scripts\jupyter-notebook-script.py", line 6, in <module>
    from notebook.notebookapp import main
  File "D:\etc\Python\Anaconda3\lib\site-packages\notebook\notebookapp.py", line 51, in <module>
    from zmq.eventloop import ioloop
  File "D:\etc\Python\Anaconda3\lib\site-packages\zmq\__init__.py", line 50, in <module>
    from zmq import backend
  File "D:\etc\Python\Anaconda3\lib\site-packages\zmq\backend\__init__.py", line 40, in <module>
    reraise(*exc_info)
  File "D:\etc\Python\Anaconda3\lib\site-packages\zmq\utils\sixcerpt.py", line 34, in reraise
    raise value
  File "D:\etc\Python\Anaconda3\lib\site-packages\zmq\backend\__init__.py", line 27, in <module>
    _ns = select_backend(first)
  File "D:\etc\Python\Anaconda3\lib\site-packages\zmq\backend\select.py", line 28, in select_backend
    mod = __import__(name, fromlist=public_api)
  File "D:\etc\Python\Anaconda3\lib\site-packages\zmq\backend\cython\__init__.py", line 6, in <module>
    from . import (constants, error, message, context,
ImportError: DLL load failed while importing error: 找不到指定的模块。
```  

使用**activate**指令将Python3重新激活环境  
```
D:\etc\Python\Anaconda3\Scripts>activate D:\etc\Python\Anaconda3  

(base) D:\etc\Python\Anaconda3\Scripts>python -m ipykernel install --user
Installed kernelspec python3 in C:\Users\Bllose\AppData\Roaming\jupyter\kernels\python3
```  

