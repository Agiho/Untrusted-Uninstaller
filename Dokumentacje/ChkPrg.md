## **ChkPrg**

Klasa do pobierania danych z klucza rejestru, pozwala na pobranie danych znajdujących sie w podkluczach SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall, takich jak nazwa i ścieżka pozwalająca odinstalowac program

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void InsertLog(CLog *TLog)`             | ***Przekazuje plik Log do klasy by mogła zapisywac informacje*** |
| `void InstertWMIPointer(CWMIRun *TWMI)`  | ***Przekazuje Obiekt WMI w celu podłączenia się do innego komputera*** |
| `std::vector<CUinstPrgCont> GetPrgandPath(std::string Computer = "local", std::string User = "", std::string Pass = "")` | ***Pobiera dane z klucza Uninstall na wskazanym komputerze i zwracaca je w postaci vectora struktur z danymi*** **Argument 1:** IP bądź nazwa stacji do odczytania rejestru, jesli ten argument ma wartość "local" sprawdzany jest lokany komputer **Argument 2:** Nazwa użytkownika, jesli brak danych uzywany jest obecny użytkownik **Argument 3:** Hasło uzytkownika, jesli brak używane jest hasło obecnego użytkownika |