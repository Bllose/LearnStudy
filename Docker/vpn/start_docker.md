``` docker run -p 1635:1635 -p 1634:1634 -p 1633:1633 -p 443:443 -it ubuntu:latest /bin/sh  ```
> -p 1635/1634/1633 bee request  
> -p 443 curl openvpn  

``` docker run --network=host -v E:\docker_space:/share -it ubuntu:latest /bin/sh ```  
> -v \[宿主地址] : \[挂载地址]  
> --network=host
