## **CMsgBox**

Klasa kt�ra wy�wietla message box r�nego rodzaju

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void IstertLog(CLog *TLog)`             | ***Przekazuje plik Log do klasy by mog�a zapisywac informacje*** |
| `void MakeOK()`                          | ***Ustawia obiekt tak by wy�wietla� okna powiadomie� z przyskiem OK*** |
| `void MakeYesNo()`                       | ***Ustawia obiekt tak by wy�wietla� okna powiadomie� z przyskami tak i nie*** |
| `void MakeCustom(const SDL_MessageBoxButtonData buttons[], int NrButtons)` | ***Ustawia obiekt tak by wy�wietla� okna powiadomie� z przyskami zdefiniowanymi przez u�ytkownika*** **Argument 1:** tablica z danymi przycisk�w dla okna **Argument 2:** Liczba przysk�w w oknie |
| `void CreateColorScheme(SDL_MessageBoxColor Background, SDL_MessageBoxColor Text, SDL_MessageBoxColor ButtonBorder, SDL_MessageBoxColor ButtonBackground, SDL_MessageBoxColor ButtonSelected)` | ***Pozwala ustalic kolory jakie b�d� wyst�powac w oknie powiadomie� (nie dzia�a na systemie WIndows)*** **Argument 1:** kolor t�a **Argument 2:** kolor tekstu **Argument 3:** kolor obramowania przycisk�w **Argument 4:** kolor przycisk�w **Argument 5:** kolor przycisku kt�ry zosta� wybrany |
| `int ShowMsg(std::string Title, std::string Message)` | ***Wy�wietla okno z powiadomieniem i zwraca ID wybranego przysku (OK - 0, Tak - 1, Nie - 0)*** **Argument 1:** tytu� okna **Argument 2:** wiadomo�� w oknie |