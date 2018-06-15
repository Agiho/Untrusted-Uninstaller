#include "Slider.h"

void CSlider::Init(CLog *TLog, int Tx, int Ty, int Tw, int Th, int ButW, int ButH, int SliderW, int SliderH,
	std::shared_ptr<CTexture> Tex, int StartTexX, int StartTexY,
	SDL_Renderer* Render, std::string SSoundOn, std::string SSoundClick)
{
	Log = TLog;

	SliderPos.x = Tx;
	SliderPos.y = Ty;
	SliderPos.w = Tw;
	SliderPos.h = Th;

	Textures = Tex;

	if (Tw < Th)Vertical = true;
	else Vertical = false;
	
	if (Vertical)
	{
		
		More.Init(Tx, (Ty + Th - ButH), ButW, ButH, Tex, StartTexX,0, TLog, Render, SSoundOn, SSoundClick);
		Less.Init(Tx, Ty, ButW, ButH, Tex, (StartTexX + ButW),0, TLog, Render, SSoundOn, SSoundClick);
		Slider.Init(Tx, Ty + ButH, ButW, ButH, Tex, StartTexX + 2*ButW,0, TLog, Render, SSoundOn, SSoundClick);
		BarPos.x = Tx;
		BarPos.y = Ty;
		Bar.x = StartTexX + 3 * ButW;
		Bar.y = StartTexY;
		Bar.w = ButW;
		Bar.h = Th;
	}
	else
	{	
		More.Init(Tx + Tw - ButW, Ty , ButW, ButH, Tex, StartTexX,0, TLog, Render, SSoundOn, SSoundClick);
		Less.Init(Tx, Ty, ButW, ButH, Tex, (StartTexX + ButW),0, TLog, Render, SSoundOn, SSoundClick);
		Slider.Init(Tx + ButW, Ty, ButW, ButH, Tex, StartTexX + 2 * ButW + 1, 0, TLog, Render, SSoundOn, SSoundClick);
		BarPos.x = Tx;
		BarPos.y = Ty;
		Bar.x = StartTexX + 3 * ButW ;
		Bar.y = StartTexY;
		Bar.w = Tw;
		Bar.h = ButH;
	}
	CurValue = 0;
}

void CSlider::SetMaxVal(unsigned int Val)
{
	MaxValue = Val;
	
	if (Vertical) Jumpvalue = (SliderPos.h - (2 * Less.GetHeight())) / Val;
	else Jumpvalue = (SliderPos.w - (2 * Less.GetWidth()) )/ Val;
}


void CSlider::SetVal(unsigned int Val)
{
	CurValue = Val;
	
}

void CSlider::Render()
{
	if (BVisible)
	{
		Textures->Render(BarPos.x, BarPos.y, &Bar);
		Less.Render();
		More.Render();
		Slider.Render();

	}
}

void CSlider::HandleEvent(SDL_Event *e)
{
	if (BVisible)
	{
		if (Less.HandleEvent(e))
		{
			if (CurValue) --CurValue;
		}
		if (More.HandleEvent(e))
		{
			if (CurValue < MaxValue) ++CurValue;
		}
		if (Slider.HandleEvent(e))
		{
			if (Vertical)
			{
				
			}
			else
			{

			}
		}
		//Slide(e);
	}
}

unsigned int CSlider::GetCurValue()
{
	return CurValue;
}

bool CSlider::GetVis()
{
	return BVisible;
}
void CSlider::ChangeVis(bool BVis)
{
	BVisible = BVis;

}

void CSlider::Slide(SDL_Event *e)
{
	bool BInside = true;

	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mause position
		int X, Y;
		SDL_GetMouseState(&X, &Y);

		//Check if mouse is inside button
		bool BInside = true;
		//Mouse is left of the button
		if (X < BarPos.x)
		{
			BInside = false;
		}
		//Mouse is right of the button
		else if (X > BarPos.x + Bar.w)
		{
			BInside = false;
		}
		//Mouse above the button
		else if (Y < BarPos.y)
		{
			BInside = false;
		}
		//Mouse below the button
		else if (Y > BarPos.y + Bar.h)
		{
			BInside = false;
		}
		//Mouse is outside button
		if (!BInside)
		{
			
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
				// When mouse is on button
			case SDL_MOUSEMOTION:
				
				//When button is clicked
			case SDL_MOUSEBUTTONDOWN:
				if (Vertical)
				{
					//count current value thanks to divide position on bar by JumpValue
					CurValue = (Y - SliderPos.y) / Jumpvalue;
				}
				else
				{
					//count current value thanks to divide position on bar by JumpValue
					CurValue = (X - SliderPos.x) / Jumpvalue;
				}
			}
		}
	}

}