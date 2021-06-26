# curl  
``` sudo apt-get install curl ```  

## DownLoad a file from internet by curl  
``` curl –o [filename] [URL] ```  
``` curl -O [URL1] -O [URL2] ```  
PS: ``` curl -O https://raw.githubusercontent.com/getlantern/lantern-binaries/master/lantern-installer-64-bit.deb ```  
``` curl -k -O -L https://download.teamviewer.com/download/linux/teamviewer_amd64.deb ```
#### DownLoad from FTP Server
``` curl -u [ftp_user]:[ftp_passwd] -O [ftp_URL] ```  


# wGet
``` sudo apt-get install wget ```  
``` wget --no-check-certificate https://download.teamviewer.com/download/linux/teamviewer_amd64.deb ```
