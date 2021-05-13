**查看C盘空间大小**
``` wmic LogicalDisk where "Caption='C:'" get FreeSpace,Size /value ```
