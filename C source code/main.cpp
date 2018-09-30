#include "hook.h"

HWND hgWnd;
HHOOK key_hook, mouse_hook;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	hgWnd = hwnd;

	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	char text[30];

	// 设置注册窗口结构体
	wc.cbSize = sizeof(WNDCLASSEX);              // 注册窗口结构体的大小
	wc.style = 0;                               // 窗口的样式
	wc.lpfnWndProc = WndProc;                         // 指向窗口处理过程的函数指针
	wc.cbClsExtra = 0;                               // 指定紧跟在窗口类结构后的附加字节数
	wc.cbWndExtra = 0;                               // 指定紧跟在窗口事例后的附加字节数
	wc.hInstance = hInstance;                       // 本模块的实例句柄
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 图标的句柄
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);     // 光标的句柄
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);        // 背景画刷的句柄
	wc.lpszMenuName = NULL;                            // 指向菜单的指针
	wc.lpszClassName = L"myWindowClass";                     // 指向类名称的指针
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // 和窗口类关联的小图标

												  // 2. 使用【窗口结构体】注册窗口
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("窗口注册失败！"), TEXT("错误"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// 创建窗口
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,       // 窗口的扩展风格
		L"myWindowClass",            // 指向注册类名的指针
		TEXT("MouseGesture"),       // 指向窗口名称的指针
		WS_OVERLAPPEDWINDOW,    // 窗口风格
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 500, // 窗口的 x,y 坐标以及宽高
		NULL,                   // 父窗口的句柄
		NULL,                   // 菜单的句柄
		hInstance,              // 应用程序实例的句柄
		NULL                    // 指向窗口的创建数据
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("窗口创建失败"), TEXT("错误"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// 显示窗口
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// 设置键盘全局监听
	key_hook = SetWindowsHookEx(
		WH_KEYBOARD_LL, // 监听类型【键盘】
		KeyboardProc,   // 处理函数
		hInstance,      // 当前实例句柄
		0               // 监听窗口句柄(NULL为全局监听)
	);

	// 设置鼠标全局监听
	mouse_hook = SetWindowsHookEx(
		WH_MOUSE_LL, // 监听类型【键盘】
		MouseProc,   // 处理函数
		hInstance,      // 当前实例句柄
		0               // 监听窗口句柄(NULL为全局监听)
	);


	// 消息循环
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}