## **CMsgBox**

Klasa która wyœwietla message box ró¿nego rodzaju

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void IstertLog(CLog *TLog)`             | ***Przekazuje plik Log do klasy by mog³a zapisywac informacje*** |
| `void MakeOK()`                          | ***Ustawia obiekt tak by wyœwietla³ okna powiadomieñ z przyskiem OK*** |
| `void MakeYesNo()`                       | ***Ustawia obiekt tak by wyœwietla³ okna powiadomieñ z przyskami tak i nie*** |
| `void MakeCustom(const SDL_MessageBoxButtonData buttons[], int NrButtons)` | ***Ustawia obiekt tak by wyœwietla³ okna powiadomieñ z przyskami zdefiniowanymi przez u¿ytkownika*** **Argument 1:** tablica z danymi przycisków dla okna **Argument 2:** Liczba przysków w oknie |
| `void CreateColorScheme(SDL_MessageBoxColor Background, SDL_MessageBoxColor Text, SDL_MessageBoxColor ButtonBorder, SDL_MessageBoxColor ButtonBackground, SDL_MessageBoxColor ButtonSelected)` | ***Pozwala ustalic kolory jakie bêd¹ wystêpowac w oknie powiadomieñ (nie dzia³a na systemie WIndows)*** **Argument 1:** kolor t³a **Argument 2:** kolor tekstu **Argument 3:** kolor obramowania przycisków **Argument 4:** kolor przycisków **Argument 5:** kolor przycisku który zosta³ wybrany |
| `int ShowMsg(std::string Title, std::string Message)` | ***Wyœwietla okno z powiadomieniem i zwraca ID wybranego przysku (OK - 0, Tak - 1, Nie - 0)*** **Argument 1:** tytu³ okna **Argument 2:** wiadomoœæ w oknie |