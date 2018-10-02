## MouseGesture

#### 文件说明：

GUI部分文件说明：

+ main.cpp: windows程序入口
+ hook.h, hook.cpp: 实现了对鼠标、键盘的hook，可以获取鼠标位置、按键状态、键盘按键状态
+ global.h： 声明全局变量



#### 接口：

```cpp
void copy();
void paste();
void Win();
void AltTab(); //切换任务
void WinTab(); //查看任务
void WinD(); //桌面
void WinUp(); //最大化；上半屏
void WinDown(); //最小化；下半屏
void WinLeft(); //左半屏
void WinRight(); //右半屏

//控制面板
void ControlPanel();
//任务管理器
void TaskManager();
//记事本
void NotePad();
//计算器
void Calculator();
//在默认浏览器中搜索
void WebSearch(const char* text);
```

