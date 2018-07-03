## **CInputTextBox**

Klasa do zarządzania polem do wpisywania tekstu

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(CLog *TLog, SDL_Rect Pos, std::string FontPath, SDL_Renderer *Render,SDL_Color Color, unsigned int Size = 0);` | ***Ustawia pozycję textboxa jego czcionkę, jej kolor oraz rozmiar*** **Argument 1:** Wskaźnik do obiektu log** **Argument 2:** Pozycja z której będzie rysowany oraz wielkość **Argument 3:** ścieżka do czcionki **Argument 4:** Wskaźnik na Renderer **Argument 5:** Kolor czcionki **Argument 6:** Rozmiar czcionki |
| `void Input(SDL_Event *e)`               | ***Sprawdza czy box został kliknięty, jesli tak to rozpoczyna wprowadzanie znaków*** **Argument:** wskaźnik do zmiennej ze zdarzeniami |
| `std::string GetText()`                  | ***Zwraca tekst przechowywany w textboxie*** |
| `void ClrTxt()`                          | ***Czyści przechowywany tekst***         |
| `void SetTxt(std::string SetTxt)`        | ***Ustawia tekst na podany w argumencie*** **Argument:** tekst do umieszczenia w textboxie |
| `void ChangeColor(SDL_Color textCol)`    | ***Zmienia kolor czcionki na podany*** **Argument** Nowy kolor czcionki |
| `void Render()`                          | ***Wyświetla texbox i tekst w nim        |