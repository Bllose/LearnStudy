# CONNECT BY  

**TABLE( CAST( MULTISET() )  AS sys.odcinumberlist)**  

``` select level from dual connect by level < 3 ```  
| LEVEL |  
| --- |  
| 1 |  
| 2 |  

