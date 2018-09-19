## **CTerminator**

Klasa która służy do zamykania procesów na komputerach do których jest podłączony WMI

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(CLog SDL_Renderer *Render, SDL_Rect Size, std::shared_ptr<CTexture> Slider, std::shared_ptr<CTexture> Buttons, int ButW, int But2W, int ButH, std::string FontPath)` | ***Inicjalizuje obiekt i przygotowuje go do użycia*** *8Argument 1:** Wskaxnik na obiekt  log **Argument 2:** wskaźnik na renderer **Argument 3:** rozmiar okna **Argument 4:** wskaźnik z tekstura suwaka **Argument 5:** wskaźnik z teksturą przycisków, **Argument 6:** szerokość przycisku **Argument 7:** szerokość przycisku od dodawania i suwaka **Argument 8:** wysokość przycisku |
| `void AddProcesses(std::vector<std::string> ProcNames)` | ***dodaje listę procesów do pojemnika w terminatorze*** **Argument:** kontener zawierający nazwy procesów do zakończenia |
| `void AddOne(std::string ProcName)`      | ***Dodaje jeden proces do listy procesów do zakończenia*** **Argument:** Nazwa procesu do zakończenia |
| `void ClrLst()`                          | ***Czyści listę z programów***           |
| `std::vector<std::string> GetProcesses()` | ***Zwraca listę procesów które są w kontenerze*** |
| `void Activate()`                        | ***zmienia status obiektu na aktywny***  |
| `bool IsActive()`                        | ***Zwraca wartość czy terminator jest aktywny*** |
| `void Terminate(CWMIRun *WMI)`           | ***Kończy procesy zapisane w kontenerze na komputerze podłaczonym do wskazanego WMI*** **Argument:** Wskaźnik do podłączonego obiektu WMI |
| `void Terminate(CWMIRun *WMI, std::vector<std::string> ProcNames)` | ***Kończy procesy przekazane jako argument w w przekazanym podłączonym obiekcie WMI*** **Argument 1:** Wskaźnik do podłączonego obiektu WMI **Argument 2:** kontener z nazwami procesów do zakończenia |
| `bool HandleEvent(SDL_Event *e)`         | ***Odpowiada za obsługe zdarzeń w oknie terminatora*** **Argument:** wskaxnik na zmienna zawierającą zdarzenia |
| `void Render()`                          | ***Wyświetla okno terminatora na ekranie*** |