#include "action.h"
#include "stdio.h"

int KEYDOWNTIME = 100;

void OneKeyAction(BYTE key, DWORD dwFlags)
{
	keybd_event(key, 0, dwFlags, 0);
	keybd_event(key, 0, dwFlags| KEYEVENTF_KEYUP, 0);
}

void TwoKeysAction(BYTE key1, DWORD dwFlags1, BYTE key2, DWORD dwFlags2)
{
	keybd_event(key1, 0, dwFlags1, 0);
	keybd_event(key2, 0, dwFlags2, 0);
	Sleep(KEYDOWNTIME);
	keybd_event(key1, 0, dwFlags1 | KEYEVENTF_KEYUP, 0);
	keybd_event(key2, 0, dwFlags2 | KEYEVENTF_KEYUP, 0);
}

//ctrl + c
void copy()
{
	TwoKeysAction(VK_CONTROL, 0, 0x43, 0);
}

//ctrl + v
void paste()
{
	TwoKeysAction(VK_CONTROL, 0, 0x56, 0);
}

//Win
void Win()
{
	OneKeyAction(VK_LWIN, 0);
}

//Alt+Tab
void AltTab()
{
	TwoKeysAction(VK_MENU, 0, VK_TAB, 0);
}

//Win+Tab
void WinTab()
{
	TwoKeysAction(VK_LWIN, 0, VK_TAB, 0);
}

//Win+D
void WinD()
{
	TwoKeysAction(VK_LWIN, 0, 0x44, 0);
}

//Win+Up
void WinUp()
{
	TwoKeysAction(VK_LWIN, 0,VK_UP, 0);
}

//Win+Down
void WinDown()
{
	TwoKeysAction(VK_LWIN, 0, VK_DOWN, 0);
}

//Win+Left
void WinLeft()
{
	TwoKeysAction(VK_LWIN, 0, VK_LEFT, 0);
}

//Win+Down
void WinRight()
{
	TwoKeysAction(VK_LWIN, 0, VK_RIGHT, 0);
}

//Alt+Left
void AltLeft()
{
	TwoKeysAction(VK_MENU, 0, VK_LEFT, 0);
}

//Alt+Right
void AltRight()
{
	TwoKeysAction(VK_MENU, 0, VK_RIGHT, 0);
}

//静音
void mute()
{
	SendMessage(hgWnd, WM_APPCOMMAND, 0x200eb0, APPCOMMAND_VOLUME_MUTE * 0x10000);
}

//增大音量
void soundUp()
{
	SendMessage(hgWnd, WM_APPCOMMAND, 0x30292, APPCOMMAND_VOLUME_UP * 0x10000);
}

//减小音量
void soundDown()
{
	SendMessage(hgWnd, WM_APPCOMMAND, 0x30292, APPCOMMAND_VOLUME_DOWN * 0x10000);
}

//控制面板
void ControlPanel()
{
	WinExec("control", SW_HIDE);
}

//任务管理器
void TaskManager()
{
	ShellExecuteA(NULL, "open", "taskmgr", "", "", SW_SHOW);
}

//记事本
void NotePad()
{
	WinExec("notepad", SW_HIDE);
}

//计算器
void Calculator()
{
	WinExec("calc", SW_HIDE);
}

//在默认浏览器中搜索
void WebSearchText(const char* text)
{
	int size = strlen(text);
	char* url = (char*)malloc(size + 50);
	sprintf_s(url, size+50,"%s%s", "https://www.baidu.com/s?wd=",text);
	ShellExecuteA(NULL, "open", url,"", "", SW_SHOW);
	free(url);
}

//在默认浏览器中搜索
void WebSearchAuto()
{
	copy();
	if (OpenClipboard(NULL))
	{
		//获得剪贴板数据
		HGLOBAL hMem = GetClipboardData(CF_TEXT);
		if (NULL != hMem)
		{
			char* lpStr = (char*)::GlobalLock(hMem);
			if (NULL != lpStr)
			{
				WebSearchText(lpStr);
				GlobalUnlock(hMem);
				EmptyClipboard();
			}
		}
		CloseClipboard();
	}
}