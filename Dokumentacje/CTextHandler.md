## **CTextHandler**

Klasa do wy�wietlania tekstu

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(SDL_Point TPos, std::string Path, unsigned int Size, CLog *TLog, SDL_Renderer *Render)` | ***Ustawia pozycj� textboxa jego czcionk�, jej kolor oraz rozmiar*** **Argument 1:** pozycja w kt�rej zaczyna si� rysowanie tekstu **Argument 2:** �cie�ka do czcionki **Argument 3:** rozmiar czcionki **Argument 4:** wska�nik na obiekt zajmujacy sie logami **Argument 5:** wska�nik na renderer |
| `void SetPos(SDL_Point Point)`           | ***Ustawia pozycje z kt�rej zaczyna sie renderowanie tekstu*** **Argument:** pozycja z kt�rej zacz��|
| `bool LoadFromRenderedText(std::string textureText, SDL_Color textColor)` | ***Ustawia tekst do wy�wietlenia i jego kolor*** **Argument 1:** tekst do wy�wietlenia **Argument 2:** kolor czcionki |
| `bool LoadFromRenderedTextUnicode(std::wstring textureText, SDL_Color textColor)` | ***Ustawia tekst utf16 do wy�wietlenia i jego kolor*** **Argument 1:** tekst do wy�wietlenia **Argument 2:** kolor czcionki |
| `void Free()`                            | ***Zwalnia pami�c zajmowan� przez tekstur�*** |
| `void SetColor(Uint8 red, Uint8 green, Uint8 blue)`  | ***Ustawia kolo tekstury na wskazany kolor*** **Argument 1,2,3:** kolory czerwony zielony niebieski  |
| `void SetBlendMode(SDL_BlendMode blending)` | ***ustawia tryb mieszania*** **Argument:** tryb mieszania** |
| `void SetAlpha(Uint8 alpha)`             | ***ustawia prze�roczysto�� tekstury*** **warto�� prze�roczysto�ci** |
| `void Render(int x = (-1), int y = (-1), SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)` | ***Wy�wietla tekst na ekranie*** **Argument 1,2:  pozycja x i y, domy�lnie pobierana z klasy **argument 3** fragment tekstury do wy�wietlenia **Argument 4:** k�t **argument 5:** gdzie jest �rodek **Argument 6:** odwr�cenie tekstury | 
| `int GetWidth()`                         | ***Zwraca szeroko�� tekstury***         |
| `int GetHeight()`                        | ***Zwraca wysoko�� tekstury***          |