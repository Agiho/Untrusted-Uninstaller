## **CMainInterface**

Klasa do zarządzania głównymi funkcjami w programie i pozwalająca przełączac sie między głownymi trybami

| Nazwa funkcji                 | Objaśnienie                              |
| ----------------------------- | ---------------------------------------- |
| `void Init(CLog *TLog, ChkPrg *TChecker, CWMIRun *WMI, SDL_Renderer* Render, unsigned int ScrW, unsigned int ScrH, std::string FontPath)` | ***Inicjalizuje głowny interfejs, ustawia pozycję przycisków*** | **Argument 1:** Wskaxnik na obiekt log **Argumtn 2:** Wskaźnik do obiektu odpowiedzialnego za sprawdzanie rejestru **Argument 3:** wskaźnik na obiekt WMI **Argument 4:** wskaźnik na renderer **Argument 5,6:** Szerokość i wysokość okna głównego **Argument 7:** ścieżka do czcionki
| `void Render()`              | ***Wyświetla aktualny interfejs***       |
| `void Update()`               | ***Odpowiada za wywoływanie funkcji Update w podinterfejsach i oknach*** |
| `void HandleEvent(SDL_Event *e)` | ***Odpowiada za przekazanie zdarzeń do reszty obiektów*** **Argument:** Wskaxnik na zmienną ze zdarzeniami |
| `bool IsQuit()`              | ***Zwraca prawdę jeśli zajdzie potrzeba opuszczenia programu*** |
