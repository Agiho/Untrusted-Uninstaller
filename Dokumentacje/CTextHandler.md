## **CTextHandler**

Klasa do wyœwietlania tekstu

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void Init(SDL_Point TPos, std::string Path, unsigned int Size, CLog *TLog, SDL_Renderer *Render)` | ***Ustawia pozycjê textboxa jego czcionkê, jej kolor oraz rozmiar*** **Argument 1:** pozycja w której zaczyna siê rysowanie tekstu **Argument 2:** œcie¿ka do czcionki **Argument 3:** rozmiar czcionki **Argument 4:** wskaŸnik na obiekt zajmujacy sie logami **Argument 5:** wskaŸnik na renderer |
| `void SetPos(SDL_Point Point)`           | ***Ustawia pozycje z której zaczyna sie renderowanie tekstu*** **Argument:** pozycja z której zacz¹æ|
| `bool LoadFromRenderedText(std::string textureText, SDL_Color textColor)` | ***Ustawia tekst do wyœwietlenia i jego kolor*** **Argument 1:** tekst do wyœwietlenia **Argument 2:** kolor czcionki |
| `bool LoadFromRenderedTextUnicode(std::wstring textureText, SDL_Color textColor)` | ***Ustawia tekst utf16 do wyœwietlenia i jego kolor*** **Argument 1:** tekst do wyœwietlenia **Argument 2:** kolor czcionki |
| `void Free()`                            | ***Zwalnia pamiêc zajmowan¹ przez teksturê*** |
| `void SetColor(Uint8 red, Uint8 green, Uint8 blue)`  | ***Ustawia kolo tekstury na wskazany kolor*** **Argument 1,2,3:** kolory czerwony zielony niebieski  |
| `void SetBlendMode(SDL_BlendMode blending)` | ***ustawia tryb mieszania*** **Argument:** tryb mieszania** |
| `void SetAlpha(Uint8 alpha)`             | ***ustawia przeŸroczystoœæ tekstury*** **wartoœæ przeŸroczystoœci** |
| `void Render(int x = (-1), int y = (-1), SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE)` | ***Wyœwietla tekst na ekranie*** **Argument 1,2:  pozycja x i y, domyœlnie pobierana z klasy **argument 3** fragment tekstury do wyœwietlenia **Argument 4:** k¹t **argument 5:** gdzie jest œrodek **Argument 6:** odwrócenie tekstury | 
| `int GetWidth()`                         | ***Zwraca szerokoœæ tekstury***         |
| `int GetHeight()`                        | ***Zwraca wysokoœæ tekstury***          |