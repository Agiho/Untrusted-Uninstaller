## **CBasicFileDialog**

Klasa do wyświetlenia okna z prośbą o podanie pliku izwracająca ścieżkę do niego

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void CreateOpenFileDialog(HWND hWnd, LPCSTR Title, LPCSTR InitialDirectory, LPCSTR Filter, int FilterIndex)` | ***Wyświtla okno z prośba o wskazanie pliku do odczytu*** **Argument 1:** Uchwyt okna nadrzędnego(może być NULL) **Argument 2:** Tytuł okna **Argument 3:** Początkowa lokazliacja którą wyświetli jako domyślną ""Argument 4:**  Filtr, jakie pliki wyświetlić **Argument 5:** Ile jest filtrów |
| `const char* ReturnLastPath()`           | ***Zwraca ściężkę do ostatnio otwartego pliku*** |
