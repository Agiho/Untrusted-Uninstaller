## **CUninstMgr**

Klasa do zarządzania procesami odinstalowania na różnych komputerach i pilnująca by procesy odpalały sie dopiero po zakończeniu poprzednich.
| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(CLog *TLog,  CTerminator *TTerminator = nullptr)` | ***Przekazuje wskaźnik na Log do klasy by mogła zapisywac informacje a także wskaxnik na obiekt który kończy procesy na komputerze docelowym*** **Argument 1:** wskaxnik na log **Argument 2:** Wskaxnik na terminatora|
| `void AddCred( std::string TUser = "", std::string TPass = "")`  | ***dodaje do klasy potrzebne informacje o użytkowniku( jeśli zostana użyte argumenty domyślne użytkownikiem będzie odpalajacy aplikację*** **Argument 1:** nazwa użytkownika **Argument 2:** hasło |
| `void StartUninstall(std::vector<std::string> Where, std::vector<CUinstPrgCont> TUninstlst)` | ***Rozpoczyna proces odinstalowywaina oprogramowania na wskazanych komputerach*** **Argument 1:** kontener z nazwami komputerów bąź adresami IP (local oznacza komputer lokalny) **Argument 2:** polecenia do wykonania na komputerach |
| `void Update()`                          | ***Pilnuje procesu odinstalowywania, odinstalowuje kolejne oprogramowania z listy gdy poprzednie się zakończy*** |
| `std::vector<std::pair<int, bool> > GetStatus()` | ***Zwraca kontener z informacjami dla każdego komputera o tym jak przebiega proces odinstalowywania, każdy obiekt to kolejny komputer, 1 zmienna oznacza który obecnie przeprowadzany proces, drugi o świadczy o tym czy wszystkie operacje zostały zakończone*** | 
| `bool AllEnd()`                          | **Zwraca prawdę gdy zakończą się wsztkie uruchomione procesy odinstalowywania** |