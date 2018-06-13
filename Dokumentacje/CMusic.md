## **CMusic**

Klasa obsługująca muzykę, pozwala wczytać ja z pliku, przechowuje jąi odtwarza. Zainicjalizować wystarczy raz w programie. Inicjalizuje dźwięk.

| Funkcja:                       | Opis:                                    |
| ------------------------------ | ---------------------------------------- |
| `bool Init(CLog *TLog)`        | ***Inicjalizuje  moduł dźwięku zwraca wartość prawda jeśli proces zakończy się powodzeniem rzuca wyjątek tupu string.***  **Argument 1**:  wskaźnik do pliku Log |
| `bool Load(std::string SPath)` | ***Wczytuje z pliku  muzykę  Zwraca prawdę  jeśli się to powiedzie rzuca wytjątek typu string***  **Argument 1** :  ścieżka do pliku |
| `void Play()`                  | ***Odtwarza wczytaną  muzykę***          |
| `void Pause()`                 | ***Wstrzymuje i  wznawia odtwarzanie wczytanej muzyki*** |
| `void Stop()`                  | ***Zatrzymuje  odtwarzaną muzykę wyzerowując czas odtwarzania.*** |
| `bool IsStoped()`              | ***Sprawdza czy  muzyka jest zatrzymana, zwraca prawdę jeśli tak*** |
| `bool IsPaused()`              | ***Sprawdza czy  muzyka jest wstrzymana, zwraca prawdę jeśli tak*** |

