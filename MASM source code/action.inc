KEYDOWNTIME = 100

OneKeyAction PROTO,  ; simulate one key down and up
    key:BYTE, 
    dwFlags:DWORD

TwoKeysAction PROTO,  ; simulate two keys down and up
    key1:BYTE, 
    dwFlags1:DWORD,
    key2:BYTE, 
    dwFlags2:DWORD

copy PROTO
paste PROTO
Win PROTO
AltTab PROTO ;切换任务
WinTab PROTO ;查看任务
WinD PROTO ;桌面
WinUp PROTO ;最大化；上半屏
WinDown PROTO ;最小化；下半屏
WinLeft PROTO ;左半屏
WinRight PROTO ;右半屏

ControlPanel PROTO ; 控制面板
TaskManager PROTO ;任务管理器
NotePad PROTO ;记事本
Calculator PROTO ;计算器
;WebSearch PROTO,  ;在默认浏览器中搜索
;    text:BYTE