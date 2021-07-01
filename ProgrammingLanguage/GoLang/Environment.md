# GOROOT & GOPATH

# GOMOD & GOPATH
``` GO111MODULE = on ```  
当开启 MOD 模式时， 在项目目录下首先初始化：
``` 
>go mod init main.go 
go: creating new go.mod: module main.go
go: to add module requirements and sums:
        go mod tidy
```  
尝试运行:
```
>go run main.go
main.go:4:2: no required module provides package github.com/gin-gonic/gin; to add it:
        go get github.com/gin-gonic/gin
```  

根据提示， 获取对应依赖：
```
>go get github.com/gin-gonic/gin
go: downloading github.com/gin-gonic/gin v1.3.0
go: downloading github.com/gin-gonic/gin v1.7.2
go: downloading github.com/gin-contrib/sse v0.1.0
go: downloading github.com/mattn/go-isatty v0.0.12
go: downloading github.com/json-iterator/go v1.1.9
go: downloading github.com/golang/protobuf v1.3.3
go: downloading github.com/ugorji/go v1.1.7
go: downloading gopkg.in/yaml.v2 v2.2.8
go: downloading github.com/go-playground/validator/v10 v10.4.1
go: downloading github.com/ugorji/go/codec v1.1.7
go: downloading golang.org/x/sys v0.0.0-20200116001909-b77594299b42
go: downloading github.com/modern-go/concurrent v0.0.0-20180228061459-e0a39a4cb421
go: downloading github.com/modern-go/reflect2 v0.0.0-20180701023420-4b7aa43c6742
go: downloading github.com/go-playground/universal-translator v0.17.0
go: downloading github.com/leodido/go-urn v1.2.0
go: downloading golang.org/x/crypto v0.0.0-20200622213623-75b288015ac9
go: downloading github.com/go-playground/locales v0.13.0
go get: added github.com/gin-gonic/gin v1.7.2
```     

再次执行：  
```
>go run main.go
[GIN-debug] [WARNING] Creating an Engine instance with the Logger and Recovery middleware already attached.

[GIN-debug] [WARNING] Running in "debug" mode. Switch to "release" mode in production.
 - using env:   export GIN_MODE=release
 - using code:  gin.SetMode(gin.ReleaseMode)

[GIN-debug] GET    /ping                     --> main.main.func1 (3 handlers)
[GIN-debug] Environment variable PORT is undefined. Using port :8080 by default
[GIN-debug] Listening and serving HTTP on :8080

```  

进入 GOPATH 目录， 观察刚才下载的依赖包：
```  
>cd D:\workplace\goWorkPlace\pkg\mod
>ls
cache  github.com  golang.org  gopkg.in
```


