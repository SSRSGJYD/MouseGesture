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

	// ����ע�ᴰ�ڽṹ��
	wc.cbSize = sizeof(WNDCLASSEX);              // ע�ᴰ�ڽṹ��Ĵ�С
	wc.style = 0;                               // ���ڵ���ʽ
	wc.lpfnWndProc = WndProc;                         // ָ�򴰿ڴ�����̵ĺ���ָ��
	wc.cbClsExtra = 0;                               // ָ�������ڴ�����ṹ��ĸ����ֽ���
	wc.cbWndExtra = 0;                               // ָ�������ڴ���������ĸ����ֽ���
	wc.hInstance = hInstance;                       // ��ģ���ʵ�����
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); // ͼ��ľ��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);     // ���ľ��
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);        // ������ˢ�ľ��
	wc.lpszMenuName = NULL;                            // ָ��˵���ָ��
	wc.lpszClassName = L"myWindowClass";                     // ָ�������Ƶ�ָ��
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // �ʹ����������Сͼ��

												  // 2. ʹ�á����ڽṹ�塿ע�ᴰ��
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("����ע��ʧ�ܣ�"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// ��������
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,       // ���ڵ���չ���
		L"myWindowClass",            // ָ��ע��������ָ��
		TEXT("MouseGesture"),       // ָ�򴰿����Ƶ�ָ��
		WS_OVERLAPPEDWINDOW,    // ���ڷ��
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 500, // ���ڵ� x,y �����Լ����
		NULL,                   // �����ڵľ��
		NULL,                   // �˵��ľ��
		hInstance,              // Ӧ�ó���ʵ���ľ��
		NULL                    // ָ�򴰿ڵĴ�������
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("���ڴ���ʧ��"), TEXT("����"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// ��ʾ����
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// ���ü���ȫ�ּ���
	key_hook = SetWindowsHookEx(
		WH_KEYBOARD_LL, // �������͡����̡�
		KeyboardProc,   // ������
		hInstance,      // ��ǰʵ�����
		0               // �������ھ��(NULLΪȫ�ּ���)
	);

	// �������ȫ�ּ���
	mouse_hook = SetWindowsHookEx(
		WH_MOUSE_LL, // �������͡����̡�
		MouseProc,   // ������
		hInstance,      // ��ǰʵ�����
		0               // �������ھ��(NULLΪȫ�ּ���)
	);


	// ��Ϣѭ��
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}