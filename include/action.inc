KEYDOWNTIME = 100
SW_HIDE = 0
SW_SHOW = 5
CF_TEXT = 1

OneKeyAction PROTO STDCALL,  ; simulate one key down and up
    key:BYTE, 
    dwFlags:DWORD

TwoKeysAction PROTO STDCALL,  ; simulate two keys down and up
    key1:BYTE, 
    dwFlags1:DWORD,
    key2:BYTE, 
    dwFlags2:DWORD

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