.386
model .flat,STDCALL

INCLUDE C:\masm32\include\kernel32.inc
INCLUDE C:\masm32\include\user32.inc
INCLUDE C:\masm32\include\shell32.inc
INCLUDE C:\masm32\include\msvcrt.inc
INCLUDE action.inc

INCLUDELIB C:\masm32\lib\kernel32.lib
INCLUDELIB C:\masm32\lib\user32.lib
INCLUDELIB C:\masm32\lib\shell32.lib
INCLUDELIB C:\masm32\lib\msvcrt.lib

.data
arg_ControlPanel_1 BYTE "control",0
arg_TaskManager_1 BYTE "open",0
arg_TaskManager_2 BYTE "taskmgr",0
arg_TaskManager_3 BYTE "",0
arg_NotePad_1 BYTE "notepad",0
arg_Calculator_1 BYTE "calc",0
arg_WebSearchText_1 BYTE "%s%s",0
arg_WebSearchText_2 BYTE "https://www.baidu.com/s?wd=",0
arg_WebSearchText_3 BYTE "open",0
arg_WebSearchText_4 BYTE 0
arg_WebSearchText_url BYTE 0

.code
; ==========================================================
OneKeyAction PROC STDCALL
    key:BYTE, 
    dwFlags:DWORD
; requires: key to invoke and dwFlags
;===========================================================
    invoke keybd_event, key, 0, dwFlags, 0
	invoke keybd_event, key, 0, dwFlags| KEYEVENTF_KEYUP, 0
    ret
OneKeyAction ENDP


; ==========================================================
TwoKeysAction PROC STDCALL
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
    ret
TwoKeysAction ENDP 


; ==========================================================
copy PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_CONTROL, 0, 0x43, 0
    ret
copy ENDP


; ==========================================================
paste PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_CONTROL, 0, 0x56, 0
    ret
paste ENDP


; ==========================================================
Win PROC STDCALL
; requires: none
; ==========================================================
    invoke OneKeyAction, VK_LWIN, 0
    ret
Win ENDP


; ==========================================================
AltTab PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_MENU, 0, VK_TAB, 0
    ret
AltTab ENDP


; ==========================================================
WinTab PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, VK_TAB, 0
    ret
WinTab ENDP


; ==========================================================
WinD PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, 0x44, 0
    ret
WinD ENDP


; ==========================================================
WinUp PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, VK_UP, 0
    ret
WinUp ENDP


; ==========================================================
WinDown PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, VK_DOWN, 0
    ret
WinDown ENDP


; ==========================================================
WinLeft PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, VK_LEFT, 0
    ret
WinLeft ENDP


; ==========================================================
WinRight PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_LWIN, 0, VK_RIGHT, 0
    ret
WinRight ENDP


; ==========================================================
AltLeft PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_MENU, 0, VK_LEFT, 0
    ret
AltLeft ENDP


; ==========================================================
AltRight PROC STDCALL
; requires: none
; ==========================================================
    invoke TwoKeysAction, VK_MENU, 0, VK_RIGHT, 0
    ret
AltRight ENDP


; ==========================================================
mute PROC STDCALL
; requires: hgWnd:HWND
; ==========================================================
    invoke SendMessage, hgWnd, WM_APPCOMMAND, 0x200eb0, APPCOMMAND_VOLUME_MUTE * 0x10000
    ret
mute ENDP


; ==========================================================
soundUp PROC STDCALL
; requires: hgWnd:HWND
; ==========================================================
    invoke SendMessage, hgWnd, WM_APPCOMMAND, 0x30292, APPCOMMAND_VOLUME_UP * 0x10000
    ret
soundUp ENDP


; ==========================================================
soundDown PROC STDCALL
; requires: hgWnd:HWND
; ==========================================================
    invoke SendMessage, hgWnd, WM_APPCOMMAND, 0x30292, APPCOMMAND_VOLUME_DOWN * 0x10000
    ret
soundDown ENDP

; ==========================================================
ControlPanel PROC STDCALL
; requires: none
; ==========================================================
    invoke WinExec, offset arg_ControlPanel_1, SW_HIDE
    ret
ControlPanel ENDP


; ==========================================================
TaskManager PROC STDCALL
; requires: none
; ==========================================================
    invoke ShellExecuteA, 0, offset arg_TaskManager_1, offset arg_TaskManager_2, offset arg_TaskManager_3, offset arg_TaskManager_3, SW_SHOW
    ret
TaskManager ENDP


; ==========================================================
NotePad PROC STDCALL
; requires: none
; ==========================================================
    invoke WinExec, offset arg_NotePad_1, SW_HIDE
    ret
NotePad ENDP


; ==========================================================
Calculator PROC STDCALL
; requires: none
; ==========================================================
    invoke WinExec, offset arg_Calculator_1, SW_HIDE
    ret
Calculator ENDP


; ==========================================================
WebSearchText PROC STDCALL,
    text:PTR BYTE
    LOCAL sz:DWORD
; requires: none
; ==========================================================
    invoke crt_strlen, text
    mov sz, eax 
    invoke crt_sprintf, offset arg_WebSearchText_url, offset arg_WebSearchText_1, offset arg_WebSearchText_2, text
    invoke ShellExecuteA, 0, offset arg_WebSearchText_3, offset arg_WebSearchText_url, offset arg_WebSearchText_4, offset arg_WebSearchText_4, SW_SHOW
    ret
WebSearchText ENDP


; ==========================================================
WebSearchAuto PROC STDCALL
    LOCAL hMem:DWORD, lpStr:PTR BYTE
; requires: none
; ==========================================================
    invoke copy
    invoke OpenClipboard,0
    .IF eax != 0
        invoke GetClipboardData,CF_TEXT
        mov hMem,eax
        .IF hMem != 0
            invoke GlobalLock, hMem
            mov lpStr,eax
            .IF lpStr != 0
                invoke WebSearchText,lpStr
                invoke GlobalUnlock,hMem
                invoke EmptyClipboard
            .ENDIF
        .ENDIF
        invoke CloseClipboard
    .ENDIF
    ret
WebSearchAuto ENDP


