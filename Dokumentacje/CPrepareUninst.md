## **CPrepareUninst**

Klasa która wyświetla okno proszące o podanie argumentów odinstalowania dla programów nie instalowanych przez msi

| Nazwa funkcji                 | Objaśnienie                              |
| ----------------------------- | ---------------------------------------- |
| `void Init(CLog *TLog, std::shared_ptr<CTexture> TTexture, SDL_Renderer *Render, SDL_Rect Posbyttex, unsigned int SCrW,  unsigned int SCrH, std::string Font)` | ***Inicjalizuje obiekt, ustawia pozycje okna i pól, i rozpoczyna oczekiwanie na wywołanie*** **Argument 1:** wskaźnik do obiektu log **Argument 2:** wskaźnik na teksturę przycisku **Argument 3:** wskaźnik na renderer **Argument 4:** pozycja w której zaczyna tekstura przycisku i jej rozmiar **Argument 5,6:** Szerokość i wysokość głównego okna **Argument 7:** ścieżka do pliku z czcionką
| `void CheckPrg(std::vector<CUinstPrgCont> Cont)` | ***Sprawdza czy przekazana lista programów potrzebuje dodatkowych argumentów na podstawie pola StrState*** **Argument:** vector z programami które należy sprawdzić |
| `std::vector<CUinstPrgCont> GetPrg()` | ***Zwraca listę programów które posiadają odpowiedni string do odinstalowania*** |
| `bool AllOK()`                | ***Zwraca prawdę jeśli wszystkie odpowiedzi zostały udzielone przez użytkownika*** |
| `void Render()`               | ***Wyświetla Okno***                     |
| `void HandleEvent(SDL_Event *e)` | ***Odpowiada za wprowadzenie danych do pola i oczekuje przyśnięcia przycisku*** **Argument:** Wskaxnik na zmienną ze zdarzeniami |