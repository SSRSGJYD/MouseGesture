#pragma once

#include "global.h"

void OneKeyAction(BYTE key, DWORD dwFlags);
void TwoKeysAction(BYTE key1, DWORD dwFlags1, BYTE key2, DWORD dwFlags2);

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
