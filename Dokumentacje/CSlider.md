## **CRSrvStart**

Klasa która zajmuje sie obsługa suwaka, przechowywaniem obecnej wartośći przesuwanej rzeczy i wyświetleniem suwaka

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(CLog *TLog, int Tx, int Ty, int Tw, int Th, int ButW, int ButH, int SliderW, int SliderH, std::shared_ptr<CTexture> Tex, int StartTextX, int StartTextY, SDL_Renderer* Render, std::string SSoundOn = "", std::string SSoundClick = "")` | ***Inicjalizuje suwak, ustawia jego pozycję i ustawia teksturę*** **Argument 1:** wskaźnik na obiekt zajmujacy się logami **Argument 2,3,4,5** pozycja i rozmiar całego suwaka **Argument** 6,7:** szerokość i wysokość przycisków (więcej/mniej) **Argument 8,9:** Szerokość i wysokość przycisku suwak **Argument 10:** wskaźnik na teksturę suwaka **Argument 11,12:** pozycja x i y w której zaczyna sie tekstura suwaka **Argument 13:** Wskaźnik na renderer **Argumrnt 13:** ściezka do dzwięku gdy myszka najeżdża na przyciski **Argument 14** Dzwięk gdy przycisk zostaje przyciśnięty  |
| `void SetMaxVal(unsigned int Val)`       | ***Ustawia wartość makymalna jaką może przyjąć i zwrócic suwak (wartość ta służy do przewijania, może to być np. liczba elementów)*** **Argument:** nowa wartośc maksymalna |
| `void SetVal(unsigned int Val)`          | ***Ustawia obecną wartość suwaka na podana*** **Argument 1:** Nowa wartość rzeczy którą się wyświetla i którą obecnie ma przyjąć suwak |
| `void Render()`                          | ***wyświetla suwak***                    |
| `void Update(unsigned int Val)`          | ***Aktualizuje informacje o suwaku*** **Argument:** obecna wartość suwaka |
| `void HandleEvent(SDL_Event *e)`         | ***Zajmuje się obsługą zdarzeń dla całego suwaka, przyciski mniejsze/większe i przesuwanie suwaka*** **Argument:** wskaxnik na zmienna ze zdarzeniami |
| `unsigned int GetCurValue()`             | ***Zwraca obecną wartośc jaką posiada rzecz do wyświetlenia i która powinno się wyświetlić*** |
| `unsigned int GetMaxVal()`               | ***Zwraca maksymalna wartość jaką może przyjąć suwak*** |
| `bool GetVis()`                          | ***Przekazuje informacje czy suwak jest widoczny*** |
| `void ChangeVis(bool BVis)`              | ***Zmienia widoczność suwaka*** **Argument:** czy ma być widoczny suwak |