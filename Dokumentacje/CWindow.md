## **CWindow**

Klasa przechowuje wskaźnik do okna i renderera. Odpowiada zautworzenie okna i inicjalizację SDL.

| Funkcja                                  | Objaśnienie                              |
| ---------------------------------------- | ---------------------------------------- |
| `CWindow(std::string WTitle, Clog* LogT, int SCRW = 1024, int SCRH = 768, Uint32 Type = SDL_WINDOW_FULLSCREEN, std::string IconPathT = "")` | ***Konstruktor –  inicjalizuje klasę wartościami 0***   **Argument 1**:WTitle – przyjmuje nazwę okna  **Argument 2** :Log – wskaźnik do  pliku Log **Argument 3,4:** Szerokość i wysokość okna **Argument 5:** w jakim oknie ma być wyświetlona zawartość (domyślnie cały ekran) **Argument 6:** ścieżka do ikonki okna i tej widocznej na pasku zadań |
| `bool Init()`                            | **Inicjalizuje SDL  i tworzy okno oraz renderer** |
| `void Close()`                           | **Zamyka okno,  czyści pamięć, kończy pracę na obrazach i zamyka SDL** |
| `void ClearScr(Uint8 r = 0xff, Uint8 g = 0xff,  Uint8 b = 0xff, Uint8 a = 0xff)` | ***Czyści ekran i  zmienia go na kolor podany w argumentach*** (domyślnie białe) |
| `void UpdateScr()`                       | ***Odświeża okno,  dzięki temu zmiany z renderera mogą się wyświetlić.*** |
| `SDL_Renderer* GetRenderer()`            | ***Zwraca wskaźnik do utworzonego Renderera*** |