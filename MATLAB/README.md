## MacOS 系统下优雅的编写 Matlab

> Author: Jeason

##### 工具：octave

​	[Octave](http://wiki.octave.org/GNU_Octave_Wiki) 是一个旨在提供与Matlab语法兼容的开放源代码科学计算及数值分析的工具；它提供了方便的互动命令列接口来解决线性与非线性的数值运算问题，并可将计算结果可视化，与高价的商业软体MATLAB语法几乎兼容

##### 如何安装

1.  个人推荐使用 HomeBrew 安装。如果电脑里有 HomeBrew 跳过这里。

    如果没有，打开终端，执行:

    ```bash
    /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
    ```

    没报错，就安装完了。

2.  打开终端，依次执行下面命令：

    ```bash
    brew tap homebrew/science
    brew update && brew upgrade
    brew install octave
    ```

    如果没报错就 ok 了。

3.  配置环境变量。

    打开终端，如果用 bash，则执行 `vi ~/.bash_profile` ,如果用 zsh 执行 `vi ~/.zshrc` ，然后添加一行：

    ```bash
    export FONTCONFIG_PATH=/opt/X11/lib/X11/fontconfig
    ```
    
    保存退出，然后再执行 `vi /usr/local/share/octave/site/m/startup/octaverc` 添加一行`setenv('GNUTERM','x11')` ，保存退出。

4.  安装和配置完成。

##### 如何使用

打开终端，执行`octave` 则打开`octave-gui`

执行 `octave-cli` 则为命令行交互模式。

##### 如何添加工作空间-path

 - 在你项目文件下输入 `pwd` 查看路径，如：`/Users/Jeason/Documents/ToDos/DataStructureHomework/MATLAB`
 - 输入 octave-cli 进入命令行模式，输入 `addpath('/Users/Jeason/Documents/ToDos/DataStructureHomework/MATLAB')` 添加 path
 - 在 octave-cli 模式下输入 `path` 查看是否添加成功
 - 在 octave-cli 模式下输入 `savepath` 保存修改的 `path`
 - 注意：function 命名要与文件名一致

##### 如何使用 VSCode 编写 Matlab

 - 首先你得有 `VSCode`，电脑里安装并配置好了 `octave` 及 `ocatve-cli`
 - 安装插件 `Shift + cmd + p` 输入 `ext insatll Matlab` 稍等片刻，安装完成代码提示
 - `` ctrl + ` `` 调出内置终端，开始使用