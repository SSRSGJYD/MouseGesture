include C:\masm32\include\kernel32.inc
include C:\masm32\include\user32.inc
include C:\masm32\include\windows.inc

includelib C:\masm32\lib\kernel32.lib
includelib C:\masm32\lib\user32.lib
includelib C:\masm32\lib\windows.lib

include action.inc


; ==========================================================
OneKeyAction PROC
    key:BYTE, 
    dwFlags:DWORD
; requires: key to invoke and dwFlags
;===========================================================
    invoke keybd_event, key, 0, dwFlags, 0
	invoke keybd_event, key, 0, dwFlags| KEYEVENTF_KEYUP, 0
OneKeyAction ENDP


; ==========================================================
TwoKeysAction PROTO
    key1:BYTE, 
    dwFlags1:DWORD,
    key2:BYTE, 
    dwFlags2:DWORD
; requires: two keys key1 and key2 and their dwFlags
; ==========================================================
    invoke keybd_event, key1, 0, dwFlags1, 0
    invoke keybd_event, key2, 0, dwFlags2, 0
    invoke Sleep, KEYDOWNTIME
    invoke keybd_event, key1, 0, dwFlags1| KEYEVENTF_KEYUP, 0
	invoke keybd_event, key2, 0, dwFlags2| KEYEVENTF_KEYUP, 0
TwoKeysAction ENDP 


; ==========================================================
copy PROC
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_CONTROL, 0, 0x43, 0
copy ENDP


; ==========================================================
paste PROC
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_CONTROL, 0, 0x56, 0
paste ENDP


; ==========================================================
Win PROC
; requires: none
; ==========================================================
    invoke OneKeyAction, VK_LWIN, 0
Win ENDP


; ==========================================================
AltTab PROC
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_MENU, 0, VK_TAB, 0
AltTab ENDP


; ==========================================================
WinTab PROC
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, VK_TAB, 0
WinTab ENDP


; ==========================================================
WinD PROC
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, 0x44, 0
WinD ENDP


; ==========================================================
WinUp PROC
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, VK_UP, 0
WinUp ENDP


; ==========================================================
WinDown PROC
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, VK_DOWN, 0
WinDown ENDP


; ==========================================================
WinLeft PROC
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, VK_LEFT, 0
WinLeft ENDP


; ==========================================================
WinRight PROC
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, VK_RIGHT, 0
WinRight ENDP


; ==========================================================
ControlPanel PROC
; requires: none
; ==========================================================
    arg1 BYTE "control",0
    invoke WinExec, offset arg1, SW_HIDE
ControlPanel ENDP


; ==========================================================
TaskManager PROC
; requires: none
; ==========================================================
    arg1 BYTE "open",0
    arg2 BYTE "taskmgr",0
    arg3 BYTE "",0
    invoke ShellExecuteA, 0, offset arg1, offset arg2, offset arg3, offset arg3, SW_SHOW
TaskManager ENDP


; ==========================================================
NotePad PROC
; requires: none
; ==========================================================
    arg1 BYTE "notepad",0
    invoke WinExec, offset arg1, SW_HIDE
NotePad ENDP


; ==========================================================
Calculator PROC
; requires: none
; ==========================================================
    arg1 BYTE "calc",0
    invoke WinExec, offset arg1, SW_HIDE
Calculator ENDP