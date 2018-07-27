## **CButton**

Klasa do zarządzania przyciskiem, tworzy przycisk i sprawdza czyzostała wykonana dla niego akcja. Odtwarza dźwięk jeśli najedzie się myszkąbądź kliknie. Obsługuje 3 stany przycisku.

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(int Tx, int Ty, int Tw, int Th, CTexture *TButtonsTexture, int IButtonX, CLog *TLog, SDL_Renderer* Render,  std::string SSoundOnn= "", std::string SSoundClick = "", std::string FontPath = "") ` | **I*nicjalizuje  przycisk, tworzy go I przygotowuje do działania.*  Argument 1** , **2 ,  3 ,4**: to pozycja x i y przycisku oraz jego szerokość i wysokość  **Argument 5**:  wskaźnik do pliku z teksturą przycisku/przycisków zawierającą wszystkie stany  Przyciski  wczytują się od y = 0 i zmieniają stan co wysokość  **Argument 6**:  wartość x od której w pliku tekstury zaczyna się dany przycisk  **Argument 7**: plik  do wykonywania logów  **Argument 8**:  wskaźnik do renderera   **Argument 9**:  ścieżka do pliku z dźwiękiem gdy się najedzie się na niego myszką.  **Argument 10**:  ścieżka do pliku z dźwiękiem gdy się kliknie się przycisk **Argument 11:** ścieżka do pliku zawierającego czcionkę |
| `void SetPos(int Tx, int Ty, int Tw =  NULL, int Th = NULL)` | ***Ustawienie  pozycji przycisku, I jego rozmiarów.*  Argument 1, 2 , 3  , 4** współżędne x i y oraz szerokość i wysokość |
| `bool HandleEvent(SDL_Event* e)`         | **Obsługuje  zdarzenia przycisku, zmienia stany odtwarza dźwięk, zwraca prawdę jeśli zostaje  kliknięty  *Argument***:  wskaźnik do zdarzenia. |
| `void Render()`                          | **Wyświetla  przycisk w odpowiednim na ekranie** |
| `void SetDiam(int W, int H)`             | **Ustawienie  wymiarów przycisku  Argument 1, 2**:  szerokość wysokość |
| `int GetHeight()`                        | ***Zwraca wysokość  przycisku***         |
| `int GetWidth()`                         | ***Zwraca szerokość  przycisku***        |
| `void SoundOn()`                         | ***Odtwarza dźwięk  przypisany do tego przy podświetleniu*** |
| `void SoundDown()`                       | ***Odtwarza dźwięk  przypisany do tego przy przyciśnięciu*** |
| `void SetCaption(std::string Cap)`       | ***Pozwala ustawic napis na przycisku*** **Argument:** napis do wyświetlenia |
| `std::string GetCaption()`               | ***zwraca obecny napis na przycisku***   |
| `void StateOut()`                        | ***Zmienia stan  przycisku na taki gdy nie znajduje się nad nim myszka*** |
| `void StateOn()`                         | ***Zmienia stan  przycisku na taki gdy myszka jest nad*** |
| `void StateDown()`                       | ***Zmienia stan  przycisku na taki gdy zostaje wciśnięty*** |
| `void Active(bool active)`               | ***Aktywuje/dezakywuje przycisk*** **argument:** wartość czy ma być aktywny |
| `bool IsActive()`                        | ***Pozwala sprawdzić czy przycisk jest aktywny*** |
| `void ChangeVis(bool BVis)`              | ***Zmienia stan widoczności przycisku*** **Argument:** wartość czy ma byc widoczny |
| `bool ChangeVis()`                       | ***Zmienia stan widoczności przycisku na przeciwny do obecnego i zwraca obecny stan*** |
| `bool GetVis()`                          | ***Zwraca informację czy przycisk jest obecnie widoczny*** |