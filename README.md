## MouseGesture

#### 文件说明：

GUI部分文件说明：

+ main.cpp: windows程序入口
+ hook.h, hook.cpp: 实现了对鼠标、键盘的hook，可以获取鼠标位置、按键状态、键盘按键状态
+ global.h： 声明全局变量



功能API部分文件说明：

+ action.h, action.cpp: C语言实现的模拟按键、命令的实现
+ action.asm, action.lib: masm源代码
+ action.obj: 目标文件
+ action.lib: 生成的静态库



#### 功能API：

```assembly
copy PROTO STDCALL
paste PROTO STDCALL
Win PROTO STDCALL
AltTab PROTO STDCALL ;切换任务
WinTab PROTO STDCALL ;查看任务
WinD PROTO STDCALL ;桌面
WinUp PROTO STDCALL ;最大化；上半屏
WinDown PROTO STDCALL ;最小化；下半屏
WinLeft PROTO STDCALL ;左半屏
WinRight PROTO STDCALL ;右半屏
AltLeft PROTO STDCALL ;后退
AltRight PROTO STDCALL ;前进
mute PROTO STDCALL, ;静音
    hgWnd:DWORD
soundUp PROTO STDCALL, ;增大音量
    hgWnd:DWORD
soundDown PROTO STDCALL, ;减小音量
    hgWnd:DWORD

ControlPanel PROTO STDCALL ;控制面板
TaskManager PROTO STDCALL ;任务管理器
NotePad PROTO STDCALL ;记事本
Calculator PROTO STDCALL ;计算器
WebSearchText PROTO STDCALL, ;在默认浏览器中搜索
   text:PTR BYTE
WebSearchAuto PROTO STDCALL ;在默认浏览器中搜索
```

使用方法：

```assembly
INCLUDE action.inc
INCLUDELIB action.lib
```

