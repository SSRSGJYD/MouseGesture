#include "hook.h"

const int GESTURE_UP = 0;
const int GESTURE_DOWN = 1;
const int GESTURE_LEFT = 2;
const int GESTURE_RIGHT = 3;
const int GESTURE_UPLEFT = 4;
const int GESTURE_DOWNLEFT = 5;
const int GESTURE_UPRIGHT = 6;
const int GESTURE_DOWNRIGHT = 7;

int tracking = false;
int tracks[100];
int trackNum = 0;
int lastTrack = -1;
int lastX = 0;
int lastY = 0;
int oldX = -1;
int oldY = -1;

int judgeTrack(int xDiff, int yDiff)
{
    int xChange = xDiff > 0 ? xDiff : -xDiff;
    int yChange = yDiff > 0 ? yDiff : -yDiff;
    if (yChange < 2 * xChange && xChange < 2 * yChange)
    {
        if (xDiff > 0 && yDiff > 0)
        {
            return GESTURE_DOWNRIGHT;
        }
        if (xDiff > 0 && yDiff < 0)
        {
            return GESTURE_UPRIGHT;
        }
        if (xDiff < 0 && yDiff > 0)
        {
            return GESTURE_DOWNLEFT;
        }
        else
        {
            return GESTURE_UPLEFT;
        }
    }
    else if (xChange >= 2 * yChange)
    {
        if (xDiff > 0)
        {
            return GESTURE_RIGHT;
        }
        else
            return GESTURE_LEFT;
    }
    else
    {
        if (yDiff > 0)
        {
            return GESTURE_DOWN;
        }
        else
            return GESTURE_UP;
    }
    return -1;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    MOUSEHOOKSTRUCT* p = (MOUSEHOOKSTRUCT*)lParam;
    const wchar_t *info = NULL;
    wchar_t text[50], data[20];

    PAINTSTRUCT ps;
    HDC hdc;

    if (nCode >= 0)
    {
        if (wParam == WM_LBUTTONDOWN)
        {
            info = L"鼠标左键按下";
            tracking = true;
        }
        else if (wParam == WM_LBUTTONUP)
        {
            info = L"鼠标左键抬起";
            tracking = false;
            trackNum = 0;
        }
        else if (wParam == WM_RBUTTONDOWN)
        {
            info = L"鼠标右键按下";
            tracking = true;
        }
        else if (wParam == WM_RBUTTONUP)
        {
            info = L"鼠标右键抬起";
            tracking = false;
            trackNum = 0;
        }

        ZeroMemory(text, sizeof(text));
        ZeroMemory(data, sizeof(data));
        int x = p->pt.x;
        int y = p->pt.y;

        wsprintf(text, L"%s", info);
        wsprintf(data, L"位置：x=%d,y=%d", x, y);
        if (tracking && trackNum != -1)
        {
            // paint mouse trace
            if (oldX != -1)
            {
                HDC hDC = GetDC(hDesktop);
                HPEN hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 255));
                HGDIOBJ hPenOld = SelectObject(hDC, hPen);
                MoveToEx(hDC, oldX, oldY, NULL);
                LineTo(hDC, x, y);
                DeleteObject(hPen);
                ReleaseDC(hDesktop, hDC);
            }

            if ((x - lastX)*(x - lastX) + (y - lastY)*(y - lastY) > 10000)
            {
                int track = judgeTrack(x - lastX, y - lastY);
                if (track != lastTrack)
                {
                    tracks[trackNum] = track;
                    lastTrack = track;
                    trackNum++;
                    if (trackNum > 3)
                    {
                        trackNum = -1; // no action
                        lastTrack = -1;
                    }
                }
                lastX = x;
                lastY = y;
            }
        }
        oldX = x;
        oldY = y;
        wsprintf(text, L"%d", lastTrack);
        hdc = GetDC(hgWindow);
        InvalidateRect(hgWindow, NULL, true);
        UpdateWindow(hgWindow);
        TextOut(hdc, 10, 10, text, wcslen(text));
        TextOut(hdc, 10, 30, data, wcslen(data));
        ReleaseDC(hgWindow, hdc);
    }

    return CallNextHookEx(keyHook, nCode, wParam, lParam);
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
	const wchar_t *info = NULL;
	wchar_t text[50], data[20];

	PAINTSTRUCT ps;
	HDC hdc;

	if (nCode >= 0)
	{
		if (wParam == WM_KEYDOWN)      info = L"普通按鍵抬起";
		else if (wParam == WM_KEYUP)        info = L"普通按鍵按下";
		else if (wParam == WM_SYSKEYDOWN)   info = L"系統按鍵抬起";
		else if (wParam == WM_SYSKEYUP)     info = L"系統按鍵按下";

		ZeroMemory(text, sizeof(text));
		ZeroMemory(data, sizeof(data));
        //p->scanCode
		wsprintf(text, L"%s - 键盘码 [%04d], 扫描码 [%04d]  ", info, p->vkCode, p->scanCode);
		wsprintf(data, L"按键码目测为： %c  ", p->vkCode);

		hdc = GetDC(hgWindow);
		TextOut(hdc, 10, 50, text, wcslen(text));
		TextOut(hdc, 10, 70, data, wcslen(data));
		ReleaseDC(hgWindow, hdc);
	}

	return CallNextHookEx(keyHook, nCode, wParam, lParam);
}