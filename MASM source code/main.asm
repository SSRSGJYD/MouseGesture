.386
.model flat,stdcall
option casemap:none

include         windows.inc
include         gdi32.inc
includelib      gdi32.lib
include         user32.inc
includelib      user32.lib
include         kernel32.inc
includelib      kernel32.lib
include         msvcrt.inc
includelib      msvcrt.lib
include         action.inc
includelib      action.lib

.data
saveButton      DWORD   ?
hgWindow        DWORD   ?
hDesktop        DWORD   ?
keyHook         DWORD   ?
mouseHook       DWORD   ?

clickTestText   BYTE    'Time0', 0
ListItem        BYTE    256 dup(?)
MsgTitle        BYTE    100 dup(?)
MsgText         BYTE    200 dup(?)
itemSelected    BYTE    "Selected operation No.%d for gesture No.%d", 0
selectedDetail  BYTE    "已变更操作“%s”为执行“%s”", 0

operationIndexes    DWORD   0, 1, 2, 3, 4, 5, 6, 7

; action list
ActionList      DWORD   OFFSET NotePad, OFFSET Calculator
; end of action list

.const

numGestures     =       8
numOperations   =       21

Planets00       BYTE    '复制', 0
Planets01       BYTE    '粘贴', 0
Planets02       BYTE    '开始', 0
Planets03       BYTE    '切换任务', 0
Planets04       BYTE    '查看任务', 0
Planets05       BYTE    '桌面', 0
Planets06       BYTE    '最大化/上半屏', 0
Planets07       BYTE    '最小化/下半屏', 0
Planets08       BYTE    '左半屏', 0
Planets09       BYTE    '右半屏', 0
Planets10       BYTE    '后退', 0
Planets11       BYTE    '前进', 0
Planets12       BYTE    '静音', 0
Planets13       BYTE    '增大音量', 0
Planets14       BYTE    '减小音量', 0
Planets15       BYTE    '控制面板', 0
Planets16       BYTE    '任务管理器', 0
Planets17       BYTE    '记事本', 0
Planets18       BYTE    '计算器', 0
Planets19       BYTE    '默认浏览器中搜索', 0
Planets20       BYTE    '默认浏览器中搜索2', 0

Planets         DWORD   Planets00, Planets01, Planets02, Planets03, Planets04,
                        Planets05, Planets06, Planets07, Planets08, Planets09,
                        Planets10, Planets11, Planets12, Planets13, Planets14,
                        Planets15, Planets16, Planets17, Planets18, Planets19,
                        Planets20

GestureNames00  BYTE    '左划', 0
GestureNames01  BYTE    '右划', 0
GestureNames02  BYTE    '上划', 0
GestureNames03  BYTE    '下划', 0
GestureNames04  BYTE    '左-下', 0
GestureNames05  BYTE    '左-上', 0
GestureNames06  BYTE    '右-下', 0
GestureNames07  BYTE    '右-上', 0

GestureNames    DWORD   GestureNames00, GestureNames01, GestureNames02, GestureNames03, GestureNames04,
                        GestureNames05, GestureNames06, GestureNames07

errorInfoText   BYTE    '窗口注册失败！', 0
errorInfoText2  BYTE    '窗口创建失败！', 0
errorInfoTitle  BYTE    '错误', 0

comboHMenuBase  =       5000
staticTypeName  BYTE    'STATIC', 0
comboTypeName   BYTE    'COMBOBOX', 0
comboBaseXPos   =       100
comboBaseYPos   =       35
comboWidth      =       160
comboHeight     =       20 * numOperations
settingAdder    =       30

windowClassName BYTE    'myWindowClass', 0
windowName      BYTE    'MouseGesture', 0
windowWidth     =       comboBaseXPos + comboWidth + 80
windowHeight    =       comboBaseYPos + settingAdder * numGestures + 120

buttonTypeName  BYTE    'BUTTON', 0
buttonText      BYTE    '保存', 0
buttonWidth     =       80
buttonHeight    =       25
buttonPosX      =       windowWidth - buttonWidth - 80
buttonPosY      =       windowHeight - buttonHeight - 75
buttonHMenu     =       8

nullText        BYTE    0

.code

_ProcWinMain    proc    uses ebx edx, hWnd, uMsg, wParam, lParam
                local   wmId: WORD
                local   wmEvent: WORD
                lea     eax, wParam
                mov     bx, WORD PTR[eax]
                mov     wmId, bx
                mov     bx, WORD PTR[eax + 2]
                mov     wmEvent, bx
                mov     eax, uMsg
                .if     eax == WM_CLOSE
                        invoke     DestroyWindow,hWnd
                .elseif eax == WM_DESTROY
                        invoke     PostQuitMessage,NULL
                .else
                        .if     eax == WM_COMMAND
                                .if     wmId == buttonHMenu && wmEvent == BN_CLICKED
                                        mov     al, clickTestText[4]
                                        inc     al
                                        .if     al > '9'
                                                mov     al, '0'
                                        .endif
                                        mov     clickTestText[4], al
                                        invoke  SetWindowText, saveButton, OFFSET clickTestText;
                                        mov     eax, 0
                                        ret
                                .elseif wmId >= comboHMenuBase && wmId < comboHMenuBase + numGestures && wmEvent == CBN_SELCHANGE
                                        invoke  SendMessage, lParam, CB_GETCURSEL, 0, 0
                                        mov     ebx, eax
                                        push    ebx
                                        movzx   eax, wmId
                                        sub     eax, comboHMenuBase
                                        push    eax
                                        invoke  crt_sprintf, OFFSET MsgTitle, OFFSET itemSelected, ebx, ax
                                        pop     eax
                                        pop     ebx
                                        mov     edx, 4
                                        mul     edx
                                        push    eax
                                        add     eax, OFFSET operationIndexes
                                        mov     [eax], ebx
                                        invoke  SendMessage, lParam, CB_GETLBTEXT, ebx, OFFSET ListItem
                                        pop     eax
                                        invoke  crt_sprintf, OFFSET MsgText, OFFSET selectedDetail, GestureNames[eax], OFFSET ListItem
                                        invoke  MessageBox, hWnd, OFFSET MsgText, OFFSET MsgTitle, MB_OK
                                        mov     eax, 0
                                        ret
                                .endif
                        .endif
                        invoke  DefWindowProc,hWnd,uMsg,wParam,lParam
                        ret
                .endif
                mov     eax, 0
                ret

_ProcWinMain    endp

; hook.cpp
MouseProc       proc    nCode: DWORD, wParam: DWORD, lParam: DWORD

                .if     nCode >= 0
                        mov     al, clickTestText[4]
                        inc     al
                        .if     al > '9'
                                mov     al, '0'
                        .endif
                        mov     clickTestText[4], al
                        invoke  SetWindowText, saveButton, OFFSET clickTestText;
                        mov     eax, 0
                .endif
                invoke  CallNextHookEx, keyHook, nCode, wParam, lParam
                mov     eax, 0
                ret
MouseProc       endp
; end of hook.cpp part

_WinMain        proc    uses ebx esi
                local   hInstance: DWORD
                local   hWinMain: DWORD
                local   wc: WNDCLASSEX
                local   Msg: MSG
                local   hWndComboBox: DWORD

                call    ActionList[4]

                invoke  GetModuleHandle,NULL
                mov     hInstance,eax
                invoke  RtlZeroMemory,addr wc, sizeof wc

                invoke  GetDesktopWindow
                mov     hDesktop, eax

                mov     wc.cbSize, sizeof WNDCLASSEX
                mov     wc.style, 0
                mov     wc.lpfnWndProc, offset _ProcWinMain
                mov     wc.cbClsExtra, 0
                mov     wc.cbWndExtra, 0
                push    hInstance
                pop     wc.hInstance
                invoke  LoadIcon, NULL, IDI_APPLICATION
                mov     wc.hIcon, eax
                invoke  LoadCursor,0,IDC_ARROW
                mov     wc.hCursor,eax
                mov     wc.hbrBackground,COLOR_WINDOW + 1
                mov     wc.lpszMenuName, NULL
                mov     wc.lpszClassName, offset windowClassName
                invoke  LoadIcon, NULL, IDI_APPLICATION
                mov     wc.hIconSm, eax

                invoke  RegisterClassEx, addr wc
                .if     eax == 0
                        mov     ebx, MB_ICONEXCLAMATION
                        or      ebx, MB_OK
                        invoke  MessageBox, NULL, OFFSET errorInfoText, OFFSET errorInfoTitle, ebx
                        mov     eax, 0
                        ret
                .endif

                invoke  CreateWindowEx, WS_EX_CLIENTEDGE, offset windowClassName, offset windowName, WS_OVERLAPPEDWINDOW, \
                            CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, NULL, NULL, hInstance, NULL
                mov     hWinMain, eax

                .if     eax == NULL
                        mov     ebx, MB_ICONEXCLAMATION
                        or      ebx, MB_OK
                        invoke  MessageBox, NULL, OFFSET errorInfoText2, OFFSET errorInfoTitle, ebx
                        mov     eax, 0
                        ret
                .endif

                push    hWinMain
                pop     hgWindow

                invoke  ShowWindow, hWinMain, SW_SHOWNORMAL
                invoke  UpdateWindow,hWinMain

                mov     ebx, WS_CHILD
                or      ebx, WS_VISIBLE
                invoke  CreateWindowEx, 0, offset buttonTypeName, offset buttonText, ebx, buttonPosX, buttonPosY, buttonWidth, buttonHeight, hWinMain, buttonHMenu, hInstance, 0
                mov     saveButton, eax

                ; set mouse hook
                invoke  SetWindowsHookEx, WH_MOUSE_LL, MouseProc, hInstance, 0
                mov     mouseHook, eax

                mov     ecx, numGestures
                mov     esi, 0
                mov     edx, comboBaseYPos
                mov     edi, comboHMenuBase
                CREATEITEMS:
                        push    ecx
                        push    esi
                        mov     ebx, CBS_DROPDOWNLIST
                        or      ebx, CBS_HASSTRINGS
                        or      ebx, WS_CHILD
                        or      ebx, WS_OVERLAPPED
                        or      ebx, WS_VISIBLE
                        push    edx
                        invoke  CreateWindowEx, 0, OFFSET comboTypeName, OFFSET nullText, ebx,
                                    comboBaseXPos, edx, comboWidth, comboHeight, hWinMain, edi, hInstance, NULL
                        mov     hWndComboBox, eax

                        mov     ebx, WS_CHILD
                        or      ebx, WS_VISIBLE
                        mov     eax, esi
                        mov     ecx, 4
                        mul     ecx
                        mov     eax, GestureNames[eax]
                        pop     edx
                        add     edx, 5
                        push    edx
                        invoke  CreateWindowEx, 0, OFFSET staticTypeName, eax, ebx, comboBaseXPos - 60, edx, 50, 20, hWinMain, NULL, hInstance, NULL
                        inc     edi

                        mov     ecx, numOperations
                        mov     esi, 0
                        OperationsListSet:
                                push    ecx
                                mov     ebx, Planets[esi]
                                mov     edx, OFFSET ListItem
                                CopyStr:
                                        mov     al, [ebx]
                                        mov     [edx], al
                                        inc     ebx
                                        inc     edx
                                        cmp     al, 0
                                        jne     CopyStr
                                ; Add string to combobox.
                                invoke  SendMessage, hWndComboBox, CB_ADDSTRING, 0, OFFSET ListItem
                                pop     ecx
                                add     esi, 4
                                loop    OperationsListSet

                        ; Send the CB_SETCURSEL message to display an initial item 
                        ;  in the selection field  
                        pop     edx
                        pop     esi
                        push    esi
                        push    edx
                        mov     eax, esi
                        mov     ebx, 4
                        mul     ebx
                        invoke  SendMessage, hWndComboBox, CB_SETCURSEL, operationIndexes[eax], 0

                        pop     edx
                        add     edx, settingAdder - 5
                        pop     esi
                        inc     esi
                        pop     ecx
                        dec     ecx
                        jne     CREATEITEMS

                .while TRUE
                        invoke      GetMessage, addr Msg, NULL, 0, 0
                        .break      .if eax == 0
                        invoke      TranslateMessage, addr Msg
                        invoke      DispatchMessage, addr Msg
                .endw
                ret
_WinMain        endp

start:
                call    _WinMain
                invoke  ExitProcess, NULL
                end     start