#pragma once
const CString WIN_NT_40 = _T("Microsoft Windows NT 4.0");
const CString WIN_95 = _T("Microsoft Windows 95"); //6.2
const CString WIN_98 = _T("Microsoft Windows 98"); //6.2
const CString WIN_ME = _T("Microsoft Windows Me"); //6.2
const CString WIN_2000 = _T("Microsoft Windows 2000"); //6.2
const CString WIN_XP = _T("Microsoft Windows XP"); //6.2
const CString WIN_XP_X64 = _T("Microsoft Windows XP Professional x64 Edition"); //6.2
const CString WIN_2003 = _T("Microsoft Windows Server 2003"); //6.2
const CString WIN_2003_R2 = _T("Microsoft Windows Server 2003 R2"); //6.2
const CString WIN_VISTA = _T("Microsoft Windows Vista"); //6.2
const CString WIN_2008 = _T("Microsoft Windows Server 2008"); //6.2
const CString WIN_7 = _T("Microsoft Windows 7"); //6.2
const CString WIN_2008_R2 = _T("Microsoft Windows Server 2008 R2"); //6.2
const CString WIN_8 = _T("Microsoft Windows 8"); //6.2
const CString SYSTEM_NONE = _T("未知操作系统"); //6.2

#include <vector>
using std::vector;
class SystemInfoVisit
{
public:
	SystemInfoVisit(void);
	virtual ~SystemInfoVisit(void);
	//获取系统版本名称
	CString getSystemName();
	//获取安装软件的信息
	bool getSoftInfo(vector<CString> &vStrSoft);
	bool getSystemInfo(char SystemStr[]);
};
