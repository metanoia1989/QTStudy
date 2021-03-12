# 解锁不能复制的PDF文件
```sh
# 创建虚拟环境
$ virtualenv venv
# 安装依赖
$ pip install -r requirement.txt
# 打包，需要自行修改 tcl 和 tk 的目录
$ pyinstaller.exe  -D -w --icon=pdfunlock.ico  
    --add-data D:\Program\Python37\tcl\tcl8.6;tcl\tcl8.6  
    --add-data D:\Program\Python37\tcl\tk8.6;tk\tk8.6  
    pdfunlock.py
```