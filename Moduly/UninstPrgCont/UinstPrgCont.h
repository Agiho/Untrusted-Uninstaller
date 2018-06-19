#ifndef UinstPrgCont_h
#define UinstPrgCont_h

#include <string>
#include <algorithm>

enum UStrState
{
	UStr_OK = 0,

	UStr_EXE = 1,

	UStr_Unknown = 2

};

class CUinstPrgCont
{
public:

	int Add(std::string TName, std::string Uninst, std::string QUninst);

private:

	std::string Name;

	std::string Uninsstr;

	UStrState StrState;

	bool BChecked;

	//firend declaration
	friend class CPrepareUninst;
	friend class CPrgSelector;
	template <typename T> friend class CCheckBoxCont;

};

#endif