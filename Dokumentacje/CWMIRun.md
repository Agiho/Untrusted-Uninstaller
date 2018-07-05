## **CWMIRun**

Klasa która [pozwala na podłączenie się do lokalnego lub dostępnego w sieci komputera za pośrednictwem WMI i wywołuje jej instrukcje

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void InsertLog(CLog *Tlog)`             | ***Przekazuje Wskaźnik na obiekt do logów, wymagane do poprawnej pracy klasy*** **Argument:** wskaźnik na obiekt zajmujacy się logami |
| `void SecPrevAdded(bool Added = false)`  | ***Pozwala czy wczesniej w programie w jakiejkolwiek lkasie juz nastąąpiła próba połączenia, jeśli tak nalezy ustawic wartość na true*** **Argument** wartość czy były dodane wczesniej informacje o zabezpieczeniach(automatycznie przy próbie połączenia) |
| `int ConnectWMI( string SComp = "local", string SUser = "", string SPass = "", bool Force64 = false, std::string Namespace = "\\root\\CIMV2")` | ***Łączy się z przestrzenią nazw WMI na wskazanym komputerze, umozliwia używanie funkcji dla konkretnej przestrzeni*** **Argument 1:** adress IP albo nazwa komputera domyślnie "local" oznacza lokalny **Argument 2:** nazwa użytkownika domyślnie to uzytkownik który uruchamia program **Argument 3:** Hasło domyślnie to które posiada użytkownik uruchamiajacy program **Argument 4:** czy system na który sie łączymy ma być traktowany jako 64 bitowy( przydatne przy automatycznych przekierowaniach) **Argument 5:** Przestrze n nazw WMI domyślnie \root\CIMV2 |
| `bool IsConnected()`                     | ***Czy obiekt jest obecnie podłączony do jakiegos komputera*** |
| `std::string GetCurNamespace()`          | ***Zwraca przestrzeń nazw do której obecnie jest podłączony WMI*** |
| `int ExecMethod(string SMeth)`           | ***Uruchamia polecenie na podłączonym komputerze*** **Argument:** Polecenie do wykonania |
| `int Terminate(UINT ID)`                 | ***Kończy process o podanym ID*** **Argument:** process ID |
| `int Terminate(string Name)`             | ***Kończy process o podanej nazwie*** **Argument:** pnazwa procesu do zzakończenia |
| `int WaitExeEnd(UINT ID)`                | ***Rozpoczyna oczekiwanie na zakończenie procesu*** **Argument:** Process ID |
| `int WaitExeEnd(string Name)`            | ***Rozpoczyna oczekiwanie na zakończenie procesu*** **Argument:** Nazwa procesu |
| `bool IsProcessDead()`                   | ***Wskazuje czy proces na którego zakończenie działania oczekujemy, zakończył juz działanie*** |
| `std::vector<SDiskInfo> GetDiskInfo()`   | ***Zwraca informacje o dyskach w komputerze*** |
| `SSysInfo GetSysInfo()`                  | ***Zwraca informacje o systemie***       |
| `std::vector<SProcessInfo> GetProcessInfo()` | ***Zwraca infomacje o procesach*** |
| `std::vector<std::string> GetSubKeysNames(std::string MainKey,std::string SKey)` | ***zwraca vector nazw podkluczy we wskazanym kluczu*** **Argument 1:** Główny klucz np. "HKEY_LOCAL_MACHINE" **Argument 2:** podklucz w którym będą wyszukiwane nazwy podkluczy |
| `std::string GetSringVal(std::string MainKey,std::string SKey,std::string ValName)` | ***Zwraca warotść string z podanej wartości w kluczu*** **argument 1:** Główny klucz np. "HKEY_LOCAL_MACHINE" **Argument 2:** podklucz z którego bedą pobierane wartości **Argument 3:** Nazwa wartości której wartość string ma być zwrócona |
| `void EndWait()`                         | ***Kończy oczekiwanie na zakończenie procesu*** |
| `void Free()1                            | *** rozłącza ze stacją , zwalnia zajmowaną pamięć na komputerze w którym są uruchamiane funkcje WMI | 