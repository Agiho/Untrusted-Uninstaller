#ifndef BasicFileDialog_h
#define BasicFileDialog_h

#include <shobjidl.h> 
#include <windows.h>      // For common windows data types and function headers
#define STRICT_TYPED_ITEMIDS
#include <objbase.h>      // For COM headers
#include <shobjidl.h>     // for IFileDialogEvents and IFileDialogControlEvents
#include <shlwapi.h>
#include <knownfolders.h> // for KnownFolder APIs/datatypes/function headers
#include <propvarutil.h>  // for PROPVAR-related functions
#include <propkey.h>      // for the Property key APIs/datatypes
#include <propidl.h>      // for the Property System APIs
#include <strsafe.h>      // for StringCchPrintfW
#include <shtypes.h>      // for COMDLG_FILTERSPEC
#include <new>


class CBasicFileDialog
{ 
public:

	//Opens  window dialog for openning file
	void CreateOpenFileDialog(HWND hWnd, LPCSTR Title, LPCSTR InitialDirectory, LPCSTR Filter, int FilterIndex);

	//return path to file
	const char* ReturnLastPath();

private:

	//variables where is stored path to file
	LPSTR result;
	TCHAR szFile[MAX_PATH];
};

#endif
