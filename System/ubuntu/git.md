# GITHUB上无法clone
## GnuTLS recv error (-110): The TLS connection was non-properly terminated.  
[参考网址](https://blog.frytea.com/archives/421/)  
大致原因与错误的代理有关。  
我没有使用代理， 直接关闭所有代理即可  
``` 
git config --global --unset http.proxy
git config --global --unset https.proxy
git clone https://github.com/Chia-Network/chia-blockchain.git
正克隆到 'chia-blockchain'...
remote: Enumerating objects: 42426, done.
remote: Counting objects: 100% (3354/3354), done.
remote: Compressing objects: 100% (1368/1368), done.
remote: Total 42426 (delta 2535), reused 2625 (delta 1970), pack-reused 39072
接收对象中: 100% (42426/42426), 19.95 MiB | 66.00 KiB/s, 完成.
处理 delta 中: 100% (32415/32415), 完成.
```
