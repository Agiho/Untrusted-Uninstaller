## **CLog**

Klasa służąca do tworzenia pliku log i wpisywania tam stosownych informacji

| Nazwa funkcji                 | Objaśnienie                              |
| ----------------------------- | ---------------------------------------- |
| `CLog()`                      | ***Konstruktor- Tworzy czysty plik Log do zapisu, jeśli plik istnieje to  usuwa zawartość.*** |
| `CLog(std::string Path)`      | ***Konstruktor- Tworzy w podanej lokalizacji czysty plik Log do zapisu, jeśli plik istnieje to  usuwa zawartość.*** **Argument:** lokalizacja w której ma byc utworzony plik log|
| `~Clog()`                     | ***Destruktor – Zamyka plik***           |
| `Write(std::string STempTxt)` | ***Zapisuje podaną teść w pliku*** **Argument:** Treść do zapisania |
| `void WriteTxt(int IN)`       | ***Zapisuje liczbę to pliku*** **Argument:** Liczba która ma być zapisana w pliku log |

