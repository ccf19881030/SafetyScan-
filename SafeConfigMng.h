#pragma once
#include <set>
using namespace std;
using std::set;
#include <fstream>

class SafeConfigMng
{
public:
	SafeConfigMng(void);
	~SafeConfigMng(void);
	bool init();
	
	set<CString>* getNecessarySet();
	set<CString>* getNoallowSet();
private:
	set<CString>* m_pnecessaryset;
	set<CString>* m_pnoallowset;
};
