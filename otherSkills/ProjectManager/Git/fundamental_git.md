# git config -e  
```  vim
[core]
        repositoryformatversion = 0
        filemode = false
        bare = false
        logallrefupdates = true
        ignorecase = true
[remote "origin"]
        url = https://codehub-dg-g.huawei.com/CBGIT-Service/CCPD-2B/ASC.git
        fetch = +refs/heads/*:refs/remotes/origin/*
[branch "Br_bugfix_ASC_20210201"]
        remote = origin
        merge = refs/heads/Br_bugfix_ASC_20210201
[gui]
        wmstate = zoomed
        geometry = 841x483+518+257 261 218

```

# git remote  
``` git remote add -f bllose https://github.com/simpleOrg/simpleApp.git ```  
定义一个远程仓库， 如上定以后， 使用命令  
``` git push bllose ```  
则将推送到定义的地址  

# git push  
``` git push <远程主机名> <本地分支名>:<远程分支名> ```
