#include "MsgBox.h"
#include <Windows.h>

CMsgBox::CMsgBox()
{
	Log = nullptr;

	BTypeChoosed = false;

	BCreated = false;

	BColorDefined = false;

	ButtonsNr = 0;
}

CMsgBox::~CMsgBox()
{
	if(BTypeChoosed) delete []Buttons;
	
	Log = nullptr;

	BTypeChoosed = false;

	BCreated = false;

	BColorDefined = false;

	ButtonsNr = 0;
}

void CMsgBox::IstertLog(CLog *TLog)
{
	Log = TLog;
}

void CMsgBox::MakeOK()
{
	Buttons = new SDL_MessageBoxButtonData[1];

	//Creating one button
	Buttons[0].flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
	Buttons[0].buttonid = 0;
	Buttons[0].text = "Ok";

	ButtonsNr = 1;

	BTypeChoosed = true;   
}

void CMsgBox::MakeYesNo()
{
	Buttons = new SDL_MessageBoxButtonData[2];

	//Creating two buttons
	Buttons[0].flags = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
	Buttons[0].buttonid = 0;
	Buttons[0].text = "Nie";

	Buttons[1].flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
	Buttons[1].buttonid = 1;
	Buttons[1].text = "Tak";

	ButtonsNr = 2;

	BTypeChoosed = true;
}

void CMsgBox::MakeCustom(const SDL_MessageBoxButtonData buttons[], int NrButtons)
{
	 Buttons = new SDL_MessageBoxButtonData[NrButtons];

	 for(int i = 0; i < NrButtons; ++i)
	 {
		 Buttons[i] = buttons[i]; //copy buttons info
	 }

	 ButtonsNr = NrButtons; //take number of buttons

	 BTypeChoosed = true;
}

void CMsgBox::CreateColorScheme(SDL_MessageBoxColor Background, SDL_MessageBoxColor Text, SDL_MessageBoxColor ButtonBorder, SDL_MessageBoxColor ButtonBackground, SDL_MessageBoxColor ButtonSelected)
{
	 //ccopy colors
	ColorScheme.colors[SDL_MESSAGEBOX_COLOR_BACKGROUND] = Background;

	ColorScheme.colors[SDL_MESSAGEBOX_COLOR_TEXT] = Text;

	ColorScheme.colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] = ButtonBorder;

	ColorScheme.colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] = ButtonBackground;

	ColorScheme.colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] = ButtonSelected;

	BColorDefined = true;
}

int CMsgBox::ShowMsg(std::string Title, std::string Message)
{
	if(!BCreated) //if it is used first time
	{
		if(!BTypeChoosed) return -2; //if event type of messagebox is not choose return error

		if(!BColorDefined) //if color scheme is not defined, define default colors
		{
			SDL_MessageBoxColorScheme colorScheme = 
			{
				{ /* .colors (.r, .g, .b) */
					/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
					{ 255,   255,   0 },
					/* [SDL_MESSAGEBOX_COLOR_TEXT] */
					{   0, 255,   0 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
					{ 255, 255,   0 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
					{   0,   0, 255 },
					/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
					{ 255,   0, 255 }
				}
			};
			ColorScheme = colorScheme;
		

		const SDL_MessageBoxData messageboxdata = 
		{
			SDL_MESSAGEBOX_INFORMATION, /* .flags */
			NULL, /* .window */
			Title.c_str(), /* .title */
			Message.c_str(), /* .message */
			ButtonsNr, /* .numbuttons */
			Buttons, /* .buttons */
			&ColorScheme /* .colorScheme */
		};

		MessageBoxData = messageboxdata;

		BCreated = true;
		}
	}

    int buttonid;
    if (SDL_ShowMessageBox(&MessageBoxData, &buttonid) < 0)  //some error
	{
		if(Log != nullptr)Log->WriteTxt("error displaying message box");
        return -1;
    }
    if (buttonid == -1) //button not selected
	{
        if(Log != nullptr) Log->WriteTxt("no selection");
		return -1;
    } 
	else //button was selected
	{
       return buttonid;
    }

}