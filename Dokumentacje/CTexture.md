**CTexture**

Klasa do zarządzania teksturą.

| Funkcja                                                      | Objaśnienie                                                  |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| `CTexture()`                                                 | ***Konstruktor,zeruje  wartości***                           |
| `~CTexture()`                                                | ***Destruktor –  zwalnia pamięć zajmowaną przez teksture***  |
| `void Free()`                                                | ***Zwalnia pamięć  zajmowaną przez teksturę***               |
| `void Init(SDL_Renderer*  Rende**r,** CLog *LogT)`           | ***Przypisuje wskaźnik  z rendererem by umożliwić wyświetlanie tekstury, I przypisuje plik Log***  **Argument 1**:  wskaźnik do renderera   Argument 2:  wskaźnik do pliku Log |
| `bool Load(std::string path)`                                | ***Tworzy teksturę I  ją zapisuje.  Zwraca prawdę  jeśli uda się utworzyć teksturę***  **Argument** –  ścieżka do obrazu z którego ma być utworzona |
| `void SetBlendMode(SDL_BlendMode blend)`                     | ***Ustawia tryb  przenikania***  **Argument** – tryb  przenikania |
| `void CTexture::SetAlpha(Uint8 alpha)`                       | ***Zmienia wartość  kanału alfa***  **Argument** –  wartość kanało alpha na jaką ma sie zmienić |
| `void Render(int x = 0, int y = 0, SDL_Rect* Clip = NULL, double Angle = 0.0, SDL_Point* Center = NULL,   SDL_RendererFlip Flip = SDL_FLIP_NONE)` | ***Wyświetla  teksturę na ekranie***  **Argument 1**(x) – wartość współżędnej x gdzie ma się wyświetlić  **Argument 2**(y) –  wartość współżędnej y gdzie ma się wyświetlić  **Argument 3** Clip-  jaki fragment tekstury ma się wyświetlić.  (domyślnie cała)  **Argument 4** Angle-  kąt o jaki obrócić teksturę(domyślnie brak)  **Argument 5** center –  wskazuje pkt   według którego ma się  obracać tekstura(domyślnie środek)  **Argument 6** Flip –  umożliwia odwracanie tekstury, wyświetlenia jako odbicie  (domyślnie brak) |
| `int GetWidth()`                                             | ***Zwraca szerokość  tekstury***                             |
| `int GetHeight()`                                            | ***Zwraca wysokość  tekstury***                              |