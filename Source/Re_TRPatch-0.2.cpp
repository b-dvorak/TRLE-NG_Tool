#include <Windows.h>
#include <iostream>
#include <fstream>
#include "CommDlg.h"
#include "tchar.h"
using namespace std;
//v0.2
//用于打开文件
const char* OpenFile()
{
	TCHAR szBuffer[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = _T("exe file(*.exe)\0*.exe\0");
	ofn.lpstrInitialDir = _T("");               // 路径
	ofn.lpstrFile = szBuffer;                   // 缓冲
	ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
	ofn.nFilterIndex = 0;
	//标志如果是多选要加上OFN_ALLOWMULTISELECT    
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
	BOOL bSel = GetOpenFileName(&ofn);
	LPWSTR lpwszStrIn = szBuffer;
	LPSTR pszOut = NULL;
	if (lpwszStrIn != NULL)
	{
		int nInputStrLen = wcslen(lpwszStrIn);
		int nOutputStrLen = WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, NULL, 0, 0, 0) + 2;
		pszOut = new char[nOutputStrLen];       //可能会造成内存泄漏  
		if (pszOut)
		{
			memset(pszOut, 0x00, nOutputStrLen);
			WideCharToMultiByte(CP_ACP, 0, lpwszStrIn, nInputStrLen, pszOut, nOutputStrLen, 0, 0);
		}
	}
	return pszOut;
}
int main(int argc, char** argv) {
	int TRV = 0;
	int VCode = 0;
	int a[8] = { 185, 232, 3, 0, 0, 137, 72, 34 };
	int i = 0;
	bool SelectExe = FALSE;
	const int TR2 = 135041;
	const int TR3 = 212513;
	const int TR4 = 336609;
	const int TR5 = 237153;
	const char* path;
	char* pathbak;
	char bak[5] = ".bak";
	HWND hWnd = GetConsoleWindow();
	HFONT font = CreateFont(
		20, // nHeight
		0, // nWidth
		0, // nEscapement
		0, // nOrientation
		FW_NORMAL, // nWeight
		FALSE, // bItalic
		FALSE, // bUnderline
		0, // cStrikeOut
		ANSI_CHARSET, // nCharSet
		OUT_DEFAULT_PRECIS, // nOutPrecision
		CLIP_DEFAULT_PRECIS, // nClipPrecision
		DEFAULT_QUALITY, // nQuality
		DEFAULT_PITCH | FF_SWISS,
		L"微软雅黑" // nPitchAndFamily Arial
		);
	HWND b1 = CreateWindow(
		L"BUTTON",   // predefined class
		L"选取文件",       // button text
		WS_VISIBLE | WS_CHILD,  //values for buttons.
		50,         // starting x position
		80,         // starting y position
		100,        // button width
		30,        // button height
		hWnd,       // parent window
		0,       // No menu
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
	HWND b2 = CreateWindow(
		L"BUTTON",   // predefined class
		L"TR2",       // button text
		WS_VISIBLE | WS_CHILD,  //values for buttons.
		200,         // starting x position
		80,         // starting y position
		40,        // button width
		30,        // button height
		hWnd,       // parent window
		0,       // No menu
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
	HWND b3 = CreateWindow(
		L"BUTTON",   // predefined class
		L"TR3",       // button text
		WS_VISIBLE | WS_CHILD,  //values for buttons.
		270,         // starting x position
		80,         // starting y position
		40,        // button width
		30,        // button height
		hWnd,       // parent window
		0,       // No menu
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
	HWND b4 = CreateWindow(
		L"BUTTON",   // predefined class
		L"TR4",       // button text
		WS_VISIBLE | WS_CHILD,  //values for buttons.
		340,         // starting x position
		80,         // starting y position
		40,        // button width
		30,        // button height
		hWnd,       // parent window
		0,       // No menu
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
	HWND b5 = CreateWindow(
		L"BUTTON",   // predefined class
		L"TR5",       // button text
		WS_VISIBLE | WS_CHILD,  //values for buttons.
		410,         // starting x position
		80,         // starting y position
		40,        // button width
		30,        // button height
		hWnd,       // parent window
		0,       // No menu
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
	HWND b6 = CreateWindow(
		L"BUTTON",   // predefined class
		L"使用说明",       // button text
		WS_VISIBLE | WS_CHILD,  //values for buttons.
		50,         // starting x position
		150,         // starting y position
		100,        // button width
		30,        // button height
		hWnd,       // parent window
		0,       // No menu
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
	HWND b7 = CreateWindow(
		L"BUTTON",   // predefined class
		L"开始补丁",       // button text
		WS_VISIBLE | WS_CHILD,  //values for buttons.
		200,         // starting x position
		150,         // starting y position
		100,        // button width
		30,        // button height
		hWnd,       // parent window
		0,       // No menu
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
	HWND b8 = CreateWindow(
		L"BUTTON",   // predefined class
		L"退出应用",       // button text
		WS_VISIBLE | WS_CHILD,  //values for buttons.
		350,         // starting x position
		150,         // starting y position
		100,        // button width
		30,        // button height
		hWnd,       // parent window
		0,       // No menu
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),
		NULL);
	SendMessage(b1, WM_SETFONT, (WPARAM)font, 1);
	SendMessage(b2, WM_SETFONT, (WPARAM)font, 1);
	SendMessage(b3, WM_SETFONT, (WPARAM)font, 1);
	SendMessage(b4, WM_SETFONT, (WPARAM)font, 1);
	SendMessage(b5, WM_SETFONT, (WPARAM)font, 1);
	SendMessage(b6, WM_SETFONT, (WPARAM)font, 1);
	SendMessage(b7, WM_SETFONT, (WPARAM)font, 1);
	SendMessage(b8, WM_SETFONT, (WPARAM)font, 1);
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.hwnd == b1 && msg.message == WM_LBUTTONDOWN) {
			system("CLS");
			path = OpenFile();
			if (strcmp(path, "") != 0){
				SelectExe = TRUE;
				std::cout << "已选择" << path << std::endl;
			}
			else{
				std::cout << "未选择exe" << std::endl;
			}
			if (VCode){
				std::cout << "已决定版本为TR" << VCode << std::endl;
			}
		}
		if (msg.hwnd == b2 && msg.message == WM_LBUTTONDOWN) {
			system("CLS");
			TRV = TR2;
			VCode = 2;
			std::cout << "已决定版本为TR2" << std::endl;
			if (SelectExe){
				std::cout << "已选择exe为" << path << std::endl;
			}
		}
		if (msg.hwnd == b3 && msg.message == WM_LBUTTONDOWN) {
			system("CLS");
			TRV = TR3;
			VCode = 3;
			std::cout << "已决定版本为TR3" << std::endl;
			if (SelectExe){
				std::cout << "已选择exe为" << path << std::endl;
			}
		}
		if (msg.hwnd == b4 && msg.message == WM_LBUTTONDOWN) {
			system("CLS");
			TRV = TR4;
			VCode = 4;
			std::cout << "已决定版本为TR4" << std::endl;
			if (SelectExe){
				std::cout << "已选择exe为" << path << std::endl;
			}
		}
		if (msg.hwnd == b5 && msg.message == WM_LBUTTONDOWN) {
			system("CLS");
			TRV = TR5;
			VCode = 5;
			std::cout << "已决定版本为TR5" << std::endl;
			if (SelectExe){
				std::cout << "已选择exe为" << path << std::endl;
			}
		}
		if (msg.hwnd == b6 && msg.message == WM_LBUTTONDOWN) {
			//system("CLS");
			MessageBox(hWnd, L"请先选择您需要打补丁的exe", L"第一步", MB_ICONINFORMATION);
			MessageBox(hWnd, L"然后决定您使用的TR版本。", L"第二步", MB_ICONINFORMATION);
			MessageBox(hWnd, L"最后点击打补丁即可。本应用会将您的exe备份，因此您可以放心使用。", L"第三步", MB_ICONINFORMATION);
		}
		if (msg.hwnd == b7 && msg.message == WM_LBUTTONDOWN) {
			system("CLS");
			//备份文件
			if (SelectExe && TRV != 0){
				pathbak = new char[strlen(path) + strlen(bak) + 1];
				strcpy_s(pathbak, strlen(path) + strlen(bak) + 1, path);
				strcat_s(pathbak, strlen(path) + strlen(bak) + 1, bak);
				ifstream src(path, ios::binary);
				ofstream dst(pathbak, ios::binary);
				dst << src.rdbuf();
				std::cout << "备份为 " << pathbak << "。" << std::endl;
				//书写补丁
				fstream ouF;
				ouF.open(path, ios::in | ios::out | ios::binary);
				for (i = 0; i < 8; i++)
				{
					ouF.seekp(TRV + i);
					ouF.put(a[i]);
				}
				ouF.close();
				std::cout << "已添加补丁至 " << path << std::endl;
				std::cout << "版本为TR" << VCode << std::endl;
			}
			else if (!SelectExe && TRV != 0){
				std::cout << "尚未选择exe" << path << std::endl;
				std::cout << "版本为TR" << VCode << std::endl;
			}
			else if (SelectExe && TRV == 0){
				std::cout << "尚未选择TR版本" << path << std::endl;
				std::cout << "已选择exe为" << path << std::endl;
			}
			else{
				std::cout << "尚未选择exe及TR版本" << path << std::endl;
			}
		}
		if (msg.hwnd == b8 && msg.message == WM_LBUTTONDOWN) {
			system("CLS");
			//防止内存溢出
			if (SelectExe){
				delete[]path;
				delete[]pathbak;
				SelectExe = 0;
			}
			MessageBox(hWnd, L"感谢您的使用", L"谢谢", MB_ICONINFORMATION);
			return 0;
		}
	}
}