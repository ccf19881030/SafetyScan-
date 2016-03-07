#include "stdafx.h"
#include "SystemInfoVisit.h"
#include <tchar.h>
SystemInfoVisit::SystemInfoVisit(void)
{
}

SystemInfoVisit::~SystemInfoVisit(void)
{
}
CString SystemInfoVisit::getSystemName()
{
	SYSTEM_INFO info;                //用SYSTEM_INFO结构判断64位AMD处理器
	GetSystemInfo(&info);            //调用GetSystemInfo函数填充结构
	OSVERSIONINFOEX os;
	os.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX); 
	if(GetVersionEx((OSVERSIONINFO *)&os))                  
	{
		CString vname;
		//下面根据版本信息判断操作系统名称
		switch(os.dwMajorVersion)
		{					//判断主版本号
			case 4:
				switch(os.dwMinorVersion)
				{				//判断次版本号
					case 0:
						if(os.dwPlatformId==VER_PLATFORM_WIN32_NT)
							vname = WIN_NT_40;  //1996年7月发布
						else if(os.dwPlatformId==VER_PLATFORM_WIN32_WINDOWS)
							vname = WIN_95;
						break;
					case 10:
						vname = WIN_98;
						break;
					case 90:
						vname = WIN_ME;
						break;
				}
				break;
			case 5:
				switch(os.dwMinorVersion)
				{               //再比较dwMinorVersion的值
					case 0:
						vname = WIN_2000;    //1999年12月发布
						break;
					case 1:
						vname = WIN_XP;      //2001年8月发布
						break;
					case 2:
						if(os.wProductType==VER_NT_WORKSTATION && 
							info.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
							vname = WIN_XP_X64;
						else if(GetSystemMetrics(SM_SERVERR2)==0)
							vname = WIN_2003;   //2003年3月发布
						else if(GetSystemMetrics(SM_SERVERR2)!=0)
							vname = WIN_2003_R2;
						break;
				}
				break;
			case 6:
				switch(os.dwMinorVersion)
				{
					case 0:
						if(os.wProductType==VER_NT_WORKSTATION)
							vname = WIN_VISTA;
						else
							vname = WIN_2008;   //服务器版本
						break;
					case 1:
						if(os.wProductType==VER_NT_WORKSTATION)
							vname = WIN_7;
						else
							vname = WIN_2008_R2;
						break;
					case 2:
						vname = WIN_8;
						break;
				}
				break;
			default:
				vname = SYSTEM_NONE;
				break;
		}
		return vname;
	}
	else
		return _T("");
}

bool SystemInfoVisit::getSoftInfo(vector<CString> &vStrSoft)
{
	TCHAR szSubKey[MAX_PATH] = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall");
	HKEY hKey, hSubKey;
	LONG lRetVal, lRetVal2;
	DWORD nIndex = 0;
	DWORD nNameLen = MAX_PATH;
	DWORD nDisplayLen = MAX_PATH;
	DWORD nUninstallLen = MAX_PATH;
	TCHAR szName[MAX_PATH];
	TCHAR szDisplayName[MAX_PATH];
	TCHAR szSystemComponent[MAX_PATH];//新增
	TCHAR szParentDisplayName[MAX_PATH];//新增
	TCHAR szUninstall[MAX_PATH];
	lRetVal = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szSubKey, 0, KEY_ALL_ACCESS, &hKey);
	DWORD nAttribute = REG_BINARY|REG_DWORD|REG_SZ|REG_EXPAND_SZ|REG_MULTI_SZ|REG_NONE;

	if(ERROR_SUCCESS == lRetVal)
	{
		lRetVal = RegEnumKeyEx(hKey, nIndex, szName, &nNameLen, 0, NULL, NULL, 0);
		while(lRetVal != ERROR_NO_MORE_ITEMS)
		{
			nIndex++;
			if(_tcscmp(szName, _T("")) == 0) continue;
			_stprintf(szUninstall, "%s\\%s", szSubKey, szName);
			memset(szDisplayName, 0, MAX_PATH);
			memset(szSystemComponent, 0, MAX_PATH);//新增
			memset(szParentDisplayName, 0, MAX_PATH);
			nDisplayLen = MAX_PATH;
			lRetVal2 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szUninstall, 0, KEY_ALL_ACCESS, &hSubKey);
			if(lRetVal2 == ERROR_SUCCESS)
			{   
				RegQueryValueEx(hSubKey, _T("DisplayName"), 0, &nAttribute, (LPBYTE)szDisplayName, &nDisplayLen);
				RegQueryValueEx(hSubKey, _T("SystemComponent"), 0, &nAttribute, (LPBYTE)szSystemComponent, &nDisplayLen);
				RegQueryValueEx(hSubKey, _T("ParentDisplayName"), 0, &nAttribute, (LPBYTE)szParentDisplayName, &nDisplayLen);
				
				if(_tcscmp(szDisplayName, _T("")) != 0 && _tcscmp(szSystemComponent,_T(""))==0 && _tcscmp(szParentDisplayName,_T(""))==0)
				{
					vStrSoft.push_back(szDisplayName);
				}
			}
			nNameLen = MAX_PATH;
			memset(szName, 0, MAX_PATH);
			lRetVal = RegEnumKeyEx(hKey, nIndex, szName, &nNameLen, 0, NULL, NULL, 0);
		}
	}
   return true;
}

void ThreadFun(char SystemStr[])
{
	CString tmpSystem;
	while(true)
	{
		HWND hwnd=FindWindow(NULL,"Windows Script Host");
		if (hwnd!=NULL)
		{
			//GetWindowText(hwnd,SystemStr,4096);
			SendMessage(hwnd,WM_GETTEXT,4096,long(SystemStr));
			CWnd* pwindown = CWnd::FromHandle(hwnd);
			if(!pwindown)
			{
				break;
			}

			pwindown->GetDlgItemText(0xffff,tmpSystem);
			strcpy(SystemStr,tmpSystem.GetBuffer(tmpSystem.GetLength()));
			break;
		}
	}
}

bool SystemInfoVisit::getSystemInfo(char SystemStr[])
{
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead,hWrite;
    CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFun,SystemStr,0,0);//检测系统对话框的信息
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead,&hWrite,&sa,0))
	{
		AfxMessageBox("Error on CreatePipe()!");
		return false;
	}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;
	si.hStdOutput = hWrite;
	si.wShowWindow = SW_HIDE;
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	if (!CreateProcess(NULL,"cmd.exe /c slmgr.vbs -dlv",NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi))
	{
		AfxMessageBox("Error on CreateProcess()!");
		return false;
	}

	CloseHandle(hWrite);

	char buffer[4096];
	memset(buffer,0,4096);
	DWORD byteRead;
	while(true)
	{
		if (ReadFile(hRead,buffer,4095,&byteRead,NULL) == NULL)
		{
			break;
		}

		strcat(SystemStr,buffer);
	}
	return true;
}