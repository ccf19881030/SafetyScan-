#include "stdafx.h"
#include "SafeConfigMng.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
SafeConfigMng::SafeConfigMng(void)
{
	m_pnoallowset=new set<CString>;
	m_pnecessaryset=new set<CString>;
}

SafeConfigMng::~SafeConfigMng(void)
{
	delete m_pnecessaryset;
	delete m_pnoallowset;
}
bool SafeConfigMng::init()
{
	ifstream fin;
	fin.open(L"noallowset.inf");
	char str[1024];
	CString cstr;
	if(!fin)
	{
		AfxMessageBox("noallowset.inf文件打开失败！");
		return false;
	}
	
	while(fin.getline(str,1024))
	{
		cstr.Format("%s",str);
		m_pnoallowset->insert(cstr);
		cstr ="";
	}
	fin.close();
	fin.clear();
	fin.open(L"necessaryset.inf");
	if(!fin)
	{
		AfxMessageBox("necessaryset.inf文件打开失败！");
		return false;
	}

	while(fin.getline(str,1024))
	{	
		cstr.Format("%s",str);
		m_pnecessaryset->insert(cstr);
		cstr="";
	}

	return true;
}

set<CString>* SafeConfigMng::getNecessarySet()
{
	return m_pnecessaryset;
}

set<CString>* SafeConfigMng::getNoallowSet()
{
	return m_pnoallowset;
}