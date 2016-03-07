// SafetyScanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SafetyScan.h"
#include "SafetyScanDlg.h"
#include "SystemInfoVisit.h"
#include "tlhelp32.h" 
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSafetyScanDlg dialog

CSafetyScanDlg::CSafetyScanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSafetyScanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSafetyScanDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSafetyScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSafetyScanDlg)
	DDX_Control(pDX, IDC_LIST_INFO, m_ListInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSafetyScanDlg, CDialog)
	//{{AFX_MSG_MAP(CSafetyScanDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSafetyScanDlg message handlers

BOOL CSafetyScanDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	g_pconfigmng.init();
	process();//������Ϣ�õ����
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSafetyScanDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSafetyScanDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSafetyScanDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
int GetProcessCount(const TCHAR* szExeName)
{
	TCHAR sztarget[MAX_PATH];
	lstrcpy(sztarget, szExeName);
	CharLowerBuff(sztarget, MAX_PATH);

	int count = 0;
	PROCESSENTRY32 my;
	HANDLE l = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (((int)l) != -1)
	{
		my.dwSize = sizeof(my);
		if (Process32First(l, &my))
		{
			do
			{
				CharLowerBuff(my.szExeFile, MAX_PATH);
				if (lstrcmp(sztarget, my.szExeFile) == 0)
				{
					count++;
				}
			}while (Process32Next(l, &my));
		}
		CloseHandle(l);
	}

	return count;
}

void CSafetyScanDlg::process()
{
	SystemInfoVisit systeminfovisit;
	CString sysname = systeminfovisit.getSystemName();
	systeminfovisit.getSoftInfo(m_vsoftinfo);//�õ������Ϣ
	vector<CString>::const_iterator info_iter=m_vsoftinfo.begin();
	for (;info_iter!=m_vsoftinfo.end();++info_iter)
	{
		m_ListInfo.AddString(*info_iter);
	}

	m_vsoftinfo.push_back(sysname);
	vector<CString> localMngVec=m_vsoftinfo;;//���������Ϣ
	set<CString>* pnecessaryset=g_pconfigmng.getNecessarySet();//���밲װ�������Ϣ
	set<CString>* pnoallowset=g_pconfigmng.getNoallowSet();//������װ�������Ϣ
	char SystemInfo[4096]={0};
	systeminfovisit.getSystemInfo(SystemInfo);

	//����ˮ�ӣ���Ϣ���ģ��Ƿ�����


	//�����밲װ�����
	vector<CString>::const_iterator itor=localMngVec.begin();
	set<CString>::const_iterator iter=pnecessaryset->begin();
	
	vector<CString> noNeceVec;//���밲װ�����δ��װ�б�
	bool flag;
	for (;iter!=pnecessaryset->end();++iter)
	{
		flag=false;
		vector<CString>::const_iterator itor=localMngVec.begin();
		for (;itor!=localMngVec.end();++itor)
		{
			if (*itor==*iter)
			{
				flag=TRUE;
				break;
			}
		}
		if (!flag)
		{
			noNeceVec.push_back(*iter);
		}
	}
	

	//��鲻����װ�����
	CString localTmp;
	vector<CString> noAllowVec;//��װ�˲�����װ������б�
	itor=localMngVec.begin();
	for (;itor!=localMngVec.end();++itor)
	{
		localTmp=localTmp+(*itor)+"|";
	}
	iter=pnoallowset->begin();
	for (;iter!=pnoallowset->end();++iter)
	{
		int nRet=localTmp.Find(*iter);
		if (nRet!=-1)
		{
			noAllowVec.push_back(*iter);
		}
	}

	CString resultMng;
	if (noAllowVec.size()!=0 && noNeceVec.size()!=0)
	{
		vector<CString>::const_iterator iter=noAllowVec.begin();
		vector<CString>::const_iterator itor=noNeceVec.begin();
		resultMng+="��鲻�ϸ�\n";
		resultMng+="�㰲װ�����������\n";
		for (;iter!=noAllowVec.end();++iter)
		{
			resultMng+=*iter;
			resultMng+="\n";
		}

		resultMng+="�㻹��Ҫ��װ���������\n";
		for (;itor!=noNeceVec.end();++itor)
		{
			resultMng+=*itor;
			resultMng+="\n";
		}
	}
	else if (noNeceVec.size()!=0)
	{
		vector<CString>::const_iterator itor=noNeceVec.begin();
		resultMng+="��鲻�ϸ�\n";
		resultMng+="�㻹��Ҫ��װ�����\n";
		for (;itor!=noNeceVec.end();++itor)
		{
			resultMng+=*itor;
			resultMng+="\n";
		}
	}
	else if (noAllowVec.size()!=0)
	{
		vector<CString>::const_iterator itor=noAllowVec.begin();
		resultMng+="��鲻�ϸ�\n";
		resultMng+="�㰲װ�����������\n";
		for (;itor!=noAllowVec.end();++itor)
		{
			resultMng+=*itor;
			resultMng+="\n";
		}
	}
	else if (noAllowVec.size()==0 && noNeceVec.size()==0)
	{
		CString SysInfo;
		SysInfo.Format("%s",SystemInfo);
		if (SysInfo.Find("����Ȩ")==-1 && SysInfo.Find("Licensed")==-1)
		{
			resultMng+="��鲻�ϸ�\nδʹ�������Ѽ���windows 7ϵͳ";
		}
		else
		{
			int count=GetProcessCount("SPMCenter.exe");
			if (count==0)
			{
				resultMng+="��鲻�ϸ�\n��⵽��ˮ��û������";
			}
			else
			{
				resultMng+="��ϲ!\n���ϸ�";
			}
		}
	}
	else
	{
		resultMng+="δ֪����!\n";
	}

	AfxMessageBox(resultMng);
	return;

}