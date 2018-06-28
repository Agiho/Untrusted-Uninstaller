#include "BasicFileDialog.h"


void CBasicFileDialog::CreateOpenFileDialog(HWND hWnd, LPCSTR Title, LPCSTR InitialDirectory, LPCSTR Filter, int FilterIndex)
	{

		//OPENFILENAME structure
		OPENFILENAME ofn;
   
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.hwndOwner = hWnd;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = Filter;
		ofn.nFilterIndex = FilterIndex;
		ofn.lpstrTitle = Title;
		ofn.lpstrInitialDir = InitialDirectory;
		ofn.lpstrFileTitle = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		//opens window and take path to file
		if (GetOpenFileName(&ofn))
		{
			 result = ofn.lpstrFile;
		}
		else
		{
			result = NULL;
		}
	}

const char* CBasicFileDialog::ReturnLastPath()
{
	//returns path if its not empty
	if (result == NULL)return "Empty";
	else return result;
}