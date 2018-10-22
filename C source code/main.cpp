#include "hook.h"

HWND saveButton, hgWindow;
HHOOK keyHook, mouseHook;

TCHAR clickTestText[6] = TEXT("Time0");
TCHAR ListItem[256];

const int numGestures = 8;
const int numOperations = 21;
int operationIndexes[numGestures] = { 0, 1, 2, 3, 4, 5, 6, 7 };

const TCHAR Planets[numOperations][10] = {
    TEXT("复制"), TEXT("粘贴"), TEXT("开始"), TEXT("切换任务"),
    TEXT("查看任务"), TEXT("桌面"), TEXT("最大化/上半屏"), TEXT("最小化/下半屏"),
    TEXT("左半屏"), TEXT("右半屏"), TEXT("后退"), TEXT("前进"), TEXT("静音"),
    TEXT("增大音量"), TEXT("减小音量"), TEXT("控制面板"), TEXT("任务管理器"),
    TEXT("记事本"), TEXT("计算器"), TEXT("默认浏览器中搜索"), TEXT("默认浏览器中搜索2")
};

const TCHAR GestureNames[numGestures][10] = {
    TEXT("左划"), TEXT("右划"), TEXT("上划"), TEXT("下划"), TEXT("左-下"), TEXT("左-上"), TEXT("右-下"), TEXT("右-上")
};

const TCHAR errorInfoText[] = TEXT("窗口注册失败！");
const TCHAR errorInfoText2[] = TEXT("窗口创建失败！");
const TCHAR errorInfoTitle[] = TEXT("错误");

const int comboHMenuBase = 5000;
const TCHAR staticTypeName[8] = TEXT("STATIC");
const TCHAR comboTypeName[9] = TEXT("COMBOBOX");
const int comboBaseXPos = 100;
const int comboBaseYPos = 35;
const int comboWidth = 160;
const int comboHeight = 20 * numOperations;
const int settingAdder = 30;

const TCHAR windowClassName[14] = TEXT("myWindowClass");
const TCHAR windowName[13] = TEXT("MouseGesture");
const int windowWidth = comboBaseXPos + comboWidth + 80;
const int windowHeight = comboBaseYPos + settingAdder * numGestures + 120;

const TCHAR buttonTypeName[7] = TEXT("BUTTON");
const TCHAR buttonText[3] = TEXT("保存");
const int buttonWidth = 80;
const int buttonHeight = 25;
const int buttonPosX = windowWidth - buttonWidth - 80;
const int buttonPosY = windowHeight - buttonHeight - 75;
const HMENU buttonHMenu = (HMENU)8;

const TCHAR nullText[1] = TEXT("");

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int wmId = LOWORD(wParam);
    int wmEvent = HIWORD(wParam);
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
        if (wmId == int(buttonHMenu) && wmEvent == BN_CLICKED) {
            clickTestText[4] = L'0' + (clickTestText[4] - L'0' + 1) % 10;
            SetWindowText(saveButton, clickTestText);
            break;
        }
        else if (wmId >= comboHMenuBase && wmId < comboHMenuBase + numGestures && wmEvent == CBN_SELCHANGE)
        {
            int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
            SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT, (WPARAM)ItemIndex, (LPARAM)ListItem);
            MessageBox(hWnd, (LPCWSTR)ListItem, TEXT("Item Selected"), MB_OK);
            break;
        }
        // Here don't write break on purpose!
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hWinMain;
    MSG Msg;
    HWND hWndComboBox;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = windowClassName;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, errorInfoText, errorInfoTitle, MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hWinMain = CreateWindowEx(WS_EX_CLIENTEDGE, windowClassName, windowName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);

    if (hWinMain == NULL)
    {
        MessageBox(NULL, errorInfoText2, errorInfoTitle, MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hgWindow = hWinMain;

    ShowWindow(hWinMain, nCmdShow);
    UpdateWindow(hWinMain);

    //// 下面一行代码创建输入框
    //CreateWindowEx(0, L"EDIT", 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 40, 400, 50, 18, hwnd, 0, hInstance, 0);

    saveButton = CreateWindowEx(0, buttonTypeName, buttonText, WS_CHILD | WS_VISIBLE, buttonPosX, buttonPosY, buttonWidth, buttonHeight, hWinMain, buttonHMenu, hInstance, NULL);

    //// 设置键盘全局监听
    //key_hook = SetWindowsHookEx(
    //	WH_KEYBOARD_LL, // 监听类型【键盘】
    //	KeyboardProc,   // 处理函数
    //	hInstance,      // 当前实例句柄
    //	0               // 监听窗口句柄(NULL为全局监听)
    //);

    //// 设置鼠标全局监听
    //mouse_hook = SetWindowsHookEx(
    //	WH_MOUSE_LL, // 监听类型【鼠标】
    //	MouseProc,   // 处理函数
    //	hInstance,      // 当前实例句柄
    //	0               // 监听窗口句柄(NULL为全局监听)
    //);

    for (int i = 0; i < numGestures; i++) {
        hWndComboBox = CreateWindowEx(0, comboTypeName, nullText, CBS_DROPDOWNLIST | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,
            comboBaseXPos, comboBaseYPos + i * settingAdder, comboWidth, comboHeight, hWinMain, (HMENU)(comboHMenuBase + i), hInstance, NULL);

        CreateWindowEx(0, staticTypeName, GestureNames[i], WS_CHILD | WS_VISIBLE, comboBaseXPos - 60, comboBaseYPos + 5 + i * settingAdder, 50, 20, hWinMain, NULL, hInstance, NULL);

        int  k = 0;

        memset(&ListItem, 0, sizeof(ListItem));
        for (k = 0; k < numOperations; k++)
        {
            wcscpy_s(ListItem, sizeof(ListItem) / sizeof(TCHAR), (TCHAR*)Planets[k]);

            // Add string to combobox.
            SendMessage(hWndComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)ListItem);
        }

        // Send the CB_SETCURSEL message to display an initial item 
        //  in the selection field  
        SendMessage(hWndComboBox, CB_SETCURSEL, (WPARAM)(operationIndexes[i]), (LPARAM)0);
    }

    while (GetMessage(&Msg, NULL, 0, 0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return 0;
}