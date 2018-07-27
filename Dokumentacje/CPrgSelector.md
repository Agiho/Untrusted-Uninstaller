## **CPrgSelector**

Klasa która wyświetla okno w którym mozna dokonac wyboru aplikacji do odinstalowania i dopisać dodatkowe komputery

| Nazwa funkcji                 | Objaśnienie                              |
| ----------------------------- | ---------------------------------------- |
| `void Init(CLog *TLog, CWMIRun *TWMI, unsigned int ScrW ,unsigned int ScrH ,SDL_Renderer *Render,  std::vector<CUinstPrgCont> *Programslst, std::string FontPath, std::shared_ptr<CTexture> FirstSlid, std::shared_ptr<CTexture> SecondSlid, std::shared_ptr<CTexture> StdButton)` | ***Onicjalizuje podstawowe składniki klasy, ustawia pozycje boxów i przycisków*** **Argument 1:** Wskaźcnik do obiektu log **Argument 2:** Wskaźnik na obiekt połączony WMI **Argument 3,4:** Szerokość i wysokość głównego okna **Argument 5:** wskaźnik na renderer **Argument 6:** wskaźnik na listę programów do wyświetlenia **Argument 7:** ścieżka do pliku z czcionką ** **Argument 8:** tekstura z suwakiem **Argument 9:** Tekstura z drugim suwakiem (niepotrzebne) **Argument 10:** tekstura przycisku |
| `void SetWhereConnected(std::string Name)` | ***Pozwala przekazać klasie gdzie obecnie jest podłączony uzytkownik** **Argument:** Lokalizacja do której jest zalogowany, jako lokalny komputer nalezy wpisac "Ten Komputer"
| `void SetUninstMgr(CUninstMgr *Mgr` | ***Pozwala przekazać obiekt który zarządza procesami odinstalowywania*** **Argument:** Wskaźnik na obiekt do zarządzania procesami |
| `void Update()`               | ***Uruchamia funkcje aktualizujące podklasy*** |
| `void HandleEvent(SDL_Event *e)` | ***Przekazuje zdarzenia do poszczególnych obiektów*** **Argument:** Wskaxnik na zmienną ze zdarzeniami |
| `void Render()`               | ***Wyświetla Okno wraz z przyciskami i polami i podległymi oknami innych klas*** |
| `void SetPrg(std::vector<CUinstPrgCont> *Prg)` | ***Pozwala wyświetlic nową liste programów do wyświetlania*** **Argument:** Nowy vector z programami do wyświetlenia|
