## **CInfoBox**

Klasa która wyświetla informacje w ramce na ekranie

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(CLog *TLog, SDL_Rect TSize, SDL_Renderer *Render, std::string TFont, SDL_Color NewCol)` | ***Inicjuje ramkę i konfiguje czcionkę*** **Argument 1:** Wskaźnik na plik Log **Argument 2:** rozmiar ramki **Argument 3:** wskaźnik na renderer **argument 4:** ścieżka do pliku z czcionką **Argument 5:** kolor czcionki |
| `void SetInfo(std::string Txt)`          | ***Ustawia jaki tekst ma być wyświetlony w ramce*** **Argument:** Tekst do wyświetlenia |
| `void SetInfo(std::wstring Txt)`         | ***Ustawia jaki tekst ma być wyświetlony w ramce*** **Argument:** Tekst do wyświetlenia |
| `std::string GetCurText()`               | ***Zwraca obecnie przechowywany tekst*** |
| `std::wstring GetCurText()`              | ***Zwraca obecnie przechowywany tekst*** **Argument:** potrzebny dla rozróżnienia którą wartość zwrócić |
| `void ChangeSize(SDL_Rect NewSize)`      | ***Zmienia rozmiar ramki*** **Argument:** Nowy rozmiar ramki |
| `SDL_Rect GetSize()`                     | ***Zwraca rozmiar ramki***               |
| `void ChangeTxtSize(unsigned int NewSize)` | ***Zmienia rozmiar tekstu*** **Argument:** Nowy rozmiar czcionki |
| `void ChangeTxtCol(SDL_Color NewCol)`    | ***Zmienia kolor tekstu*** **Argument:** nowy kolor |
| `void Render()`                          | ***Wyświetla ramkę z tekstem***          |