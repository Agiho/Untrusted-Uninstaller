## **template <class T> class CCheckBoxCont**

Szblon Klasy pozwalającej tworzyć checkboxy obiektów jedyny wymóg to posiadanie pola name służącego wyświetlenia nazwy i checked do sprawdzania czy zostało zaznaczone

| Funkcja                                  | Objaśnienie                              |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(CLog *TLog, SDL_Rect Pos, unsigned int SliderSize, unsigned int WinW, unsigned int WintH, SDL_Renderer *Renderer, std::vector<T> *WhatContains, std::string FontPath, std::shared_ptr<CTexture> SliderTex)` | ***ustawia pozycję okna z checkboxami i tworzy checkboxy a następnie wypełnia jr danymi z vectora*** **Argument 1"** Wskaźnik na obiekt zajmujący sie logami **Argument 2:** pozycja z której będzie rysowany checkbox i rozmiar **Argument 3** rozmiar przycisku suwaka **Argument 4,5:** Szerokość okna i jego wysokość **argument 6:** wskaźnik na renderer **Argument 7:** vector z obiektami które ma przechowywac checkbox **Argument 8:** ścieżka do czcionki **Argument 9:** wskaźnik na teksturę suwaka |
| `void Render()`                          | ***Wyświetla biały konterner z checkboxami*** |
| `void HandleEvent(SDL_Event *e)`         | ***Odpowiada za czaznaczanie/odznaczanie checkboxów i przewijanie zawartości*** **Argument:** wskaźnik na zmienna z zdarzeniami |
| `std::vector<T> GetChk()`                | ***Zwraca zaznaczone obiekty***          |
| `void SetNewList(std::vector<T> *PNewrg)` | ***pozwala zmienić obecną zawartość na nową podanną w argumencie*** **Argument:** vector z nowymi obiektami |
| `unsigned int Checked()`                 | ***Zwraca liczbę zaznaczonych obiektów*** |
| `unsigned int ResetChecked()`            | ***resetuje liczbę zaznaczonych(ustawia 0)*** |
| `std::vector<T>* GetAll()`               | ***Zwraca wskaźnik do wszystkich obiektów*** |
| `void AddNewOne(T New)`                  | ***POzwala dodać nowy element do zbioru*** **Argument:** Obiekt do dodania |