**查看C盘空间大小**  
``` wmic LogicalDisk where "Caption='C:'" get FreeSpace,Size /value ```  

**查看当前时间**  
``` echo %date% %time%  ```  

**记录硬盘使用情况**  
```
@echo off  
set n = 0  
:begin

set /a n+=1
if %n%==1000 exit

echo %date% %time% >> D:\temp\record\disk_record.log
wmic LogicalDisk where "Caption='C:'" get FreeSpace,Size /value >> D:\temp\record\disk_record.log
echo record the disk information : %n%
choice /T 600 /d y /n > nul

goto begin
```
