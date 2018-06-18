#include "BasicFileDialog.h"

void CBasicFileDialog::CreateOpenFileDialog(HWND hWnd, LPCSTR Title, LPCSTR InitialDirectory, LPCSTR Filter, int FilterIndex)
	{
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


		if (GetOpenFileName(&ofn))
		{
			 result = ofn.lpstrFile;
		}
		else
		{
			result = "Empty";
		}
	}

char* CBasicFileDialog::ReturnLastPath()
{
	return result;
}