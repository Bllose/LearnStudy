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

1、查看内存占用情况
``` wmic OS get FreePhysicalMemory ```

2、查看系统内存总数
``` wmic ComputerSystem get TotalPhysicalMemory ```

3、查看CPU占用情况
``` wmic cpu get loadpercentage ```


实际应用，做个监测cpu占用的bat，后期加上日期，加上ping计时输出到txt就可作为监控日志了
``` @for /f "skip=1" %p in ('wmic cpu get loadpercentage') do @echo %p% ```
