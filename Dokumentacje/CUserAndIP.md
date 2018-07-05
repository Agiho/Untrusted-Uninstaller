## **CUserAndIP**

Klasa która wyświetla okno z pytaniem użytkownika o podanie adresu IP nazwy użytkownika i hasła

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(CLog *TLog, std::shared_ptr<CTexture> TTexture, SDL_Renderer *Render, SDL_Rect Posbyttex, unsigned int SCrW,  unsigned int SCrH, std::string Font)` | ***Inicjalizuje okno wraz z polami tekstowymi przyciskiem i ich pozycjami*** **Argument 1"** Wskaźnik na obiekt zaqjmujacy sie logami **Argument 2:** Wskaxnik na teksturę przycisku **Argumrnt 3:** wskaźnik na renderer **Argument 4:** pozycja w której rozpoczyna sie tektura przycisku **Argument 5,6** szerokość i wysokość głównego okna **Argumernt 7:** ścieżka do czcionki |
| `void Render()`                          | ***Wyświetla oknko z pytaniem  na ekranie*** |
| `bool HandleEvent(SDL_Event *e)`         | ***Odpowiada za obsługę wpisywania do pól, zwraca prawdę gdy zostaje przyciśnięty przycisk potwierdzający zakończenie wprowadzania*** **Argument:** wskaźnik na zmienna ze zdarzeniami |
| `std::string GetIP()`                    | ***Zwraca informację o IP lub nawzie komputera którą podał użytkownik*** |
| `std::string GetUser()`                  | ***Zwraca informację o nazwie użytkownika którą podał użytkownik dla domyślnego zwraca "Domniemany"*** |
| `std::string GetPassword()`              | ***Zwraca informację o haśle którą podał użytkownik dla domyślnego zwraca  Domniemane*** |