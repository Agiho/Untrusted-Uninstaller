## **CRSrvStart**

Klasa która uruchamia wybrana usługę

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void InsertLog(CLog *TLog)`             | ***Przekazuje plik Log do klasy by mogła zapisywac informacje*** |
| `int StartRemoteService(std::string Where, std::string Which)` | ***Uruchamia usługę na wybranym komputerze*** **Argument 1:** Nazwa bądź IP komputera **Argument 2:** Nazwa usługi do uruchomienia |
| `int StopRemoteService(std::string Where, std::string Which)` | ***Zatrzymuje usługę na wybranym komputerze*** **Argument 1:** Nazwa bądź IP komputera **Argument 2:** Nazwa usługi do uruchomienia |