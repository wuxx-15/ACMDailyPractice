#在macOS上使用带ASAN,UBSAN的GCC<br>
1.卸载现有 GCC 并从源码重新编译<br>
```
brew uninstall gcc
brew edit gcc
```
2.在打开的 Formula 文件中，找到 args 参数列表，加入 --enable-libsanitizer<br>
3.执行安装：<br>
```
brew install gcc --build-from-source
```

#附录：使终端经过clash-verge代理<br>
##第一步：获取 Clash Verge 的代理端口打开 Clash Verge 软件。<br>
在左侧或设置中查看 "Mixed Port"（混合端口） 或 "HTTP Port" 的数值。通常默认是 7890 或 7897。(以下以7897为例)<br>
##第二步：在终端注入代理环境变量
在终端中执行以下命令（请将下面的 7897 替换为你实际看到的端口号）：
```
export http_proxy=http://127.0.0.1:7897
export https_proxy=http://127.0.0.1:7897
export ALL_PROXY=socks5://127.0.0.1:7897
```
##第三步：验证代理是否成功
在同一个终端窗口中，运行以下命令测试网络：
```
curl -I https://google.com
```
##第四步：直接本地编译安装 GCC
直接通过之前下载并修改好的本地 gcc.rb 文件开始编译了。请在 gcc.rb 所在的目录下执行：
```
brew install --build-from-source ./gcc.rb
```