## **CTexturesMgr**

Klasa przechowująca tekstury dla obietków i zwracająca wskaźniki do odpowiedniej na ich prośbę



| Funkcja:                                 | Opis:                                    |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(SDL_Renderer* Render, CLog* LogT)` | ***Funckja inicjalizuje klasę i przygotowuje do pracy*** **Argument 1:** Wskaźnik do renderera, **Argument 2:** Wskaźnik do obiektu Log |
| `std::shared_ptr<CTexture> LoadTex(const char *Text)` | ***Zwraca wzkaźnik do tekstury i ładuje do kontenera*** **Argument 1** Ścieżka do potrzebnej tekstury, której wskaźnik jest zwracany |

