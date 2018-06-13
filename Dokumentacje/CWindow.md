## **CWindow**

Klasa przechowuje wskaźnik do okna i renderera. Odpowiada zautworzenie okna i inicjalizację SDL.

| Funkcja                                  | Objaśnienie                              |
| ---------------------------------------- | ---------------------------------------- |
| `CWindow(std::string WTitle, Clog* Log)` | ***Konstruktor –  inicjalizuje klasę wartościami 0***   **Argument 1**:WTitle – przyjmuje nazwę okna  **Argument 2** :Log – wskaźnik do  pliku Log |
| `bool Init()`                            | **Inicjalizuje SDL  i tworzy okno oraz renderer** |
| `void Close()`                           | **Zamyka okno,  czyści pamięć, kończy pracę na obrazach i zamyka SDL** |
| `void ClearScr(Uint8 r = 0xff, Uint8 g = 0xff,  Uint8 b = 0xff, Uint8 a = 0xff)` | ***Czyści ekran i  zmienia go na kolor podany w argumentach*** (domyślnie białe) |
| `void UpdateScr()`                       | ***Odświeża okno,  dzięki temu zmiany z renderera mogą się wyświetlić.*** |
| `SDL_Renderer* GetRenderer()`            | ***Zwraca wskaźnik do utworzonego Renderera*** |

