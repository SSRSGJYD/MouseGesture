#pragma once

#include "global.h"

void OneKeyAction(BYTE key, DWORD dwFlags);
void TwoKeysAction(BYTE key1, DWORD dwFlags1, BYTE key2, DWORD dwFlags2);

void copy();
void paste();
void Win();
void AltTab(); //�л�����
void WinTab(); //�鿴����
void WinD(); //����
void WinUp(); //��󻯣��ϰ���
void WinDown(); //��С�����°���
void WinLeft(); //�����
void WinRight(); //�Ұ���
void AltLeft(); //����
void AltRight(); //ǰ��
void mute(); //����
void soundUp(); //��������
void soundDown(); //��С����

//�������
void ControlPanel();
//���������
void TaskManager();
//���±�
void NotePad();
//������
void Calculator();
//��Ĭ�������������
void WebSearchText(const char* text);
void WebSearchAuto();
