#include "InputTextBox.h"

void CInputTextBox::Init(CLog *TLog, SDL_Rect Pos, std::string FontPath, SDL_Renderer *Render,SDL_Color Color, unsigned int Size)
{
	RPos = Pos;
	Log = TLog;
	Renderer = Render;
	Txt = "";

	if(!Size)
	{
		Size = Pos.h -2;
	}

	TxtSize = Size;
	//sets font, position, size, and delault test " " 
	SDL_Point Point;
	Point.x = Pos.x + 2;
	Point.y = Pos.y + (Pos.h/2) - Size/2 + 1;
	TextColor = Color;
	TxtOnScreen.Init(Point, FontPath, Size, TLog, Render);
	TxtOnScreen.LoadFromRenderedText(" ",Color);

	BHide = false;
	BInput = false;
}

int CInputTextBox::Input(SDL_Event *e)
{
	
	if (e->type == SDL_MOUSEBUTTONDOWN)
	{
		BInput = true;

		//Get mause position
		int X, Y;
		SDL_GetMouseState(&X, &Y);

		//Mouse is left of the box
		if (X < RPos.x)
		{
			BInput = false;
		}
		//Mouse is right of the box
		else if (X > RPos.x + RPos.w)
		{
			BInput = false;
		}
		//Mouse above the box
		else if (Y < RPos.y)
		{
			BInput = false;
		}
		//Mouse below the box
		else if (Y > RPos.y + RPos.h)
		{
			BInput = false;
		}

	}

	if (BInput)
	{
		bool renderText = false;
		
		//Special key input
		if (e->type == SDL_KEYDOWN)
		{ //Handle backspace 
			if (e->key.keysym.sym == SDLK_BACKSPACE && Txt.length() > 0)
			{
				//lop off character 
				if((int)(Txt[Txt.size() - 1]) < 0)Txt.pop_back(); //if it is special character
				Txt.pop_back(); 
				renderText = true;

			} 
			//Enter button clicked
			if (e->key.keysym.sym == SDLK_RETURN)
			{
				return SDLK_RETURN;
			}
			//TAB button clicked
			if (e->key.keysym.sym == SDLK_TAB)
			{
				return SDLK_TAB;
			}
			//Handle copy else 
			if (e->key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
			{
				SDL_SetClipboardText(Txt.c_str());
			}
			//Handle paste 
			else if (e->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
			{
				Txt = SDL_GetClipboardText();
				renderText = true;
			}
		}

		//Special text input event e
		else if (e->type == SDL_TEXTINPUT)
		{
			//Not copy or pasting 
			if (!((e->text.text[0] == 'c' || e->text.text[0] == 'C') && (e->text.text[0] == 'v' || e->text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
			{ //Append character
				Txt += e->text.text;
				renderText = true;
			}
		}
		//Rerender text if needed 
		if (renderText)
		{
			//Text is not empty 
			if (Txt != "")
			{
				
				// render dots to Hide text
				if(BHide)
				{
					int DotsNr = Txt.size(); // size of string
					int Special = 0;
					for(int i = 0; i < Txt.size(); ++i)
					{
						if(Txt[i] < 0) ++Special; //how many special charaters
					}
					DotsNr = DotsNr - Special/2; // that many characters
					std::string TempTxt ="";
					for(int i = 0; i < DotsNr; ++i)
					{
						TempTxt = TempTxt + "*"; //create dots
					}
					TxtOnScreen.LoadFromRenderedText(TempTxt.c_str(), TextColor); //update text
				}
				else TxtOnScreen.LoadFromRenderedText(Txt.c_str(), TextColor);//Render new text 
			}
			//Text is empty 
			else
			{
				//Render space texture 
				TxtOnScreen.LoadFromRenderedText(" ", TextColor);
			}
		}
	}
	return 0;
}

void CInputTextBox::ChangeActiv(bool Activation)
{
	BInput = Activation;
}

bool CInputTextBox::IsActive()
{
	return BInput;
}

std::string CInputTextBox::GetText()
{
	return Txt;
}

void CInputTextBox::ClrTxt()
{
	//clear text
	Txt.clear();
	Txt = "";
}

void CInputTextBox::Hide(bool Hid)
{
	BHide = Hid;
}

void CInputTextBox::SetTxt(std::string SetTxt)
{
	Txt = SetTxt;
	TxtOnScreen.LoadFromRenderedText(Txt,TextColor); //load new text
}

void CInputTextBox::ChangeColor(SDL_Color textCol)
{
	TextColor = textCol;
}

void CInputTextBox::Render()
{
	//render box
	if(!BInput) SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF  ); // white
	else SDL_SetRenderDrawColor( Renderer, 0, 0xFF, 0xFF, 0xFF  );
	SDL_RenderFillRect( Renderer, &RPos ); //render filled rect

	SDL_SetRenderDrawColor( Renderer, 0x00, 0x00, 0x00, 0xFF ); //black
	SDL_RenderDrawRect( Renderer, &RPos ); //border

	TxtOnScreen.Render(RPos.x+1, RPos.y + RPos.h/2 - TxtSize/2  + 1); //render on screen
}