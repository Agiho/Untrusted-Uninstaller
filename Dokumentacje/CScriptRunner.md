## **CScriptRunner**

Klasa która odczytuje dostępne pliki skryptów z folderu, pozwala je wyświetlic i wybrac w specjalnym oknie, oraz pozwala je uruchomić na wskazanym komputerze wykorzystując WMI

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(CLog *TLog, SDL_Renderer *Render, SDL_Rect Size, std::shared_ptr<CTexture> Slider, std::shared_ptr<CTexture> Buttons, int ButW, int But2W, int ButH , std::string MainLoc , std::string FontPath)` | ***Inicjalizuje klasę, ustawia pozycję oknka, inicjalizuje wymagane obiekty i ustawia tekstury*** **Argument 1:** wskaźnik na obiekt zajmujacy się logami **Argument 2** Wskaźnik na SDL_Renderer **Argument 3:** rozmiar okna **Argument 4:** Wskaźnik na teksturę suwaka **Argument 5:** Szerokość przycisku OK **Argument 6:** rozmiar przycisków suwaka **Argument 7:** Wysokość przycisku OK **Argumrnt 8:** ściezka dp lokalizacji w której znajduje się plik wykonywalny( potrzebny dostęp do folderu Scripts\ i plików w nim (narazie nie uzywane)) **Argument 9** Ścieżka do pliku z czcionką |
| `void Activate()`                        | ***pozwala aktywować okno, wartość aktywacji zwraca wtedy prawdę dzięki czemu można przełączać się na obsługe tej klasy*** |
| `bool IsActive()`                        | ***Zwraca prawde jeśli ktoś aktywował obiekt i ma on zostac wyświetlony, przyciśnięcie przycisku OK pozwala zmienić tą wartość na fałszywą*** |
| `void AddCred(std::string TUser = "", std::string SPass = "")` | ***Pozwala na przekazanie loginu i hasła do klasy w przypadku braku przekazania, stosowane są domyślne uprawnienia*** **Argument 1:** Login **Argument 2** hasło |
| `void RunScript(std::vector<std::string> Where)`  | ***Uruchamia wybrane skrypty na wskazanych w argumencie komputerach*** **Argument:** Kontener z nazwami bądź adresami komputerów |
| `bool HandleEvent(SDL_Event *e)`         | ***Pozwala na obsługę zdarzeń dla okna wyboru skryptów*** **Argument:** Wskaźnik na zmienna zawierającą zdarzenia   |
| `void Render()`                          | ***Wyświetla okno wyboru skryptów*** |
| `bool IsStarted()`                       | ***Zwraca prawdę jesli juz uruchomiono skrypty dla komputerów*** |
| `void SetNotStarted()`                   | ***Pozwala ponownie ustawic zminną zawierającą informacje czy skrypty zostały uruchomione na taka wartość jakby nie były jeszcze uruchamiane*** |