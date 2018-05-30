//Re:TRPatch V0.3 多国语言 Unicode版

#include "stdafx.h"
#include "ReTRPatchM.h"
#include "ReTRPatchMDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <iomanip>
#include <sstream>
using namespace std;

const int search[8] = { 129, 249, 232, 3, 0, 0, 126, 5 };
const int write[8] = { 185, 232, 3, 0, 0, 137, 72, 34 };
int i = 0;
const int TR2 = 135041;
const int TR3 = 212513;
const int TR4 = 336609;
const int TR5 = 237153;
int TRV = TR4;
bool Loaded = FALSE;
CString path;
CString pathbak;
bool found = FALSE;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CReTRPatchMDlg::CReTRPatchMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CReTRPatchMDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_RTRPICON);
}

void CReTRPatchMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

//各种控件定义
BEGIN_MESSAGE_MAP(CReTRPatchMDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SELECTFILE, &CReTRPatchMDlg::OnBnClickedSelectfile)
	ON_BN_CLICKED(IDEXIT, &CReTRPatchMDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_BACKUPPATCH, &CReTRPatchMDlg::OnBnClickedBackuppatch)
	ON_BN_CLICKED(IDC_VTR2, &CReTRPatchMDlg::OnBnClickedVtr2)
	ON_BN_CLICKED(IDC_VTR3, &CReTRPatchMDlg::OnBnClickedVtr3)
	ON_BN_CLICKED(IDC_VTR4, &CReTRPatchMDlg::OnBnClickedVtr4)
	ON_BN_CLICKED(IDC_VTR5, &CReTRPatchMDlg::OnBnClickedVtr5)
	ON_BN_CLICKED(IDC_BETA1_FIND, &CReTRPatchMDlg::OnBnClickedBeta1Find)
END_MESSAGE_MAP()

// CReTRPatchMDlg message handlers
//初始化
BOOL CReTRPatchMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	((CButton *)GetDlgItem(IDC_VTR4))->SetCheck(TRUE);
	return TRUE;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CReTRPatchMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CReTRPatchMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//选择文件
void CReTRPatchMDlg::OnBnClickedSelectfile()
{
	//FALSE为保存，参数3为默认文件，参数4为打开只读
	CFileDialog fd(TRUE, _T(".exe"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("可执行文件 Executable files (*.exe)|*.exe||"));
	if (fd.DoModal() == IDOK)
	{
		Loaded = TRUE;
		path = fd.GetPathName();
		SetDlgItemText(IDC_MESSAGE, L"选择了 Selected");
		SetDlgItemText(IDC_FILELOC, path);
	}
	else if (!Loaded)
	{
		SetDlgItemText(IDC_MESSAGE, L"未选择文件 No file selected");
		SetDlgItemText(IDC_FILELOC, L"");
	}
}

//备份并补丁
void CReTRPatchMDlg::OnBnClickedBackuppatch()
{
	CString pathbak = path + ".bak";
	if (Loaded){
		//备份
		CopyFile(path, pathbak, FALSE);
		//补丁
		fstream ouF;
		ouF.open(path, ios::in | ios::out | ios::binary);
		for (i = 0; i < 8; i++)
		{
			ouF.seekp(TRV + i);
			ouF.put(write[i]);
		}
		ouF.close();
		//通知
		SetDlgItemText(IDC_MESSAGE, L"已补丁并备份 Patched and made a backup to ");
		SetDlgItemText(IDC_FILELOC, pathbak);
	}
	else{
		SetDlgItemText(IDC_MESSAGE, L"未选择文件 No file selected");
		SetDlgItemText(IDC_FILELOC, L"无法补丁 Cannot patch");
	}
}

//Beta功能1 自动寻址
void CReTRPatchMDlg::OnBnClickedBeta1Find()
{
	CString pathbak = path + ".bak";
	if (Loaded){
		//备份
		CopyFile(path, pathbak, FALSE);
		//打开文件
		fstream ouF;
		ouF.open(path, ios::in | ios::out | ios::binary);
		//自动寻址
		int i = 0;
		int cmprNow = 0;
		bool br = FALSE;
		if (ouF){
			int pos = 0;
			//注意std::streamoff类型实质上等于long long
			//en.cppreference.com/w/cpp/io/streamoff
			long long st, ed;
			st = ouF.tellg();
			ouF.seekg(0, ios::end);
			ed = ouF.tellg();
			long long size = ed - st;
			while (size > pos){
				//初字符一致，八位一组
				ouF.seekp(pos);
				cmprNow = (int)ouF.get();
				if (cmprNow == search[i]){
					i = 1;
					//比对剩余7字符
					for (; i < 8 && !br;){
						ouF.seekp(pos + i);
						cmprNow = (int)ouF.get();
						if (cmprNow != search[i]){
							br = TRUE;
							i = 0;
						}
						else{
							i++;
						}
					}
					//成功返回pos，失败pos+8
					if (!br){
						found = TRUE;
						TRV = pos;
						break;
					}
					else{
						br = FALSE;
						pos = pos + 8;
					}
				}
				//初字符差异，一位一组
				else{
					pos++;
				}
			}
		}
		//判断是否寻址成功
		if (found){
			//补丁
			for (i = 0; i < 8; i++)
			{
				ouF.seekp(TRV + i);
				ouF.put(write[i]);
			}
			ouF.close();
			//通知
			stringstream addrHex;
			addrHex << "0x" << hex << TRV;
			CString addrRes((addrHex.str()).c_str());
			SetDlgItemText(IDC_MESSAGE, L"操作完成于地址 Operatation finished at address");
			SetDlgItemText(IDC_FILELOC, addrRes);
		}
		else
		{
			ouF.close();
			SetDlgItemText(IDC_MESSAGE, L"未能找到地址 Address not found");
			SetDlgItemText(IDC_FILELOC, L"可能载入了错误的文件 Probably loaded a wrong file");
		}
	}
	else{
		SetDlgItemText(IDC_MESSAGE, L"未选择文件 No file selected");
		SetDlgItemText(IDC_FILELOC, L"无法操作 Cannot operate");
	}
}

void CReTRPatchMDlg::OnBnClickedExit(){ exit(0); }
void CReTRPatchMDlg::OnBnClickedVtr2(){ TRV = TR2; }
void CReTRPatchMDlg::OnBnClickedVtr3(){ TRV = TR3; }
void CReTRPatchMDlg::OnBnClickedVtr4(){ TRV = TR4; }
void CReTRPatchMDlg::OnBnClickedVtr5(){ TRV = TR5; }

void CReTRPatchMDlg::OnBnClickedAbout()
{
	// TODO:  在此添加控件通知处理程序代码
}
