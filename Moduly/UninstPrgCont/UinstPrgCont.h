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

	// fills values in class
	int Add(std::string TName, std::string Uninst, std::string QUninst);

private:

	std::string Name; //program name

	std::string Uninsstr; //Uninstall string

	UStrState StrState; // string stae, if OK uninstal string can used to uninstall

	bool BChecked; //is checked

	//firend declaration
	friend class CPrepareUninst;
	friend class CPrgSelector;
	template <typename T> friend class CCheckBoxCont;

};

#endif