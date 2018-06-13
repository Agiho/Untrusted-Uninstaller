## **CSFX**

Klasa obsługująca odgłosy Pozwala je wczytać z pliku i odtwarzać

 

| Funkcja:                       | Opis:                                    |
| ------------------------------ | ---------------------------------------- |
| `void Init(Clog *TLog)`        | ***Pozwala przypisać  plik Log***  **Argument 1**:  wskaźnik do pliku Log |
| `bool Load(std::string SPath)` | ***Wczytuje dźwięk z  pliku, zwraca prawdę jeśli się powiedzie***  **Argument 1**:  Ścieżka do pliku |
| `void Play()`                  | ***Odtwarza dźwięk  jednokrotnie***      |
| `void Free()`                  | ***Zwalnia pamięć  zajmowaną przez dźwięk*** |

