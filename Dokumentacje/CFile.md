## **CFile**

Klasa służąca do zapisu i odczytu z pliku

| Nazwa funkcji                            | Objaśnienie                              |
| ---------------------------------------- | ---------------------------------------- |
| `~Cfile()`                               | ***Destruktor –  zamyka plik***          |
| `void Init(const char *FileName, std::ios_base::openmode  Mode)` | ***Otwiera plik.*  Argument 1** – nazwa pliku który  ma otworzyć  **Argument 2** – tryb w jakim plik ma  być otwarty |
| `bool AllOk()`                           | ***Zwraca prawdę jeśli z plikiem wszystko  w porządku.*** |
| `bool IsErr()`                           | ***Zwraca prawdę jeśli wystąpił błąd***  |
| `bool Bad()`                             | ***Zwraca prawdę jeśli wystąpił problem z  plikiem i nie można na nim pracować.*** |
| `bool EoF()`                             | ***Zwraca prawdę kiedy dotarliśmy do  końca pliku*** |
| `bool IOpened()`                         | ***Zwraca prawdę jeśli plik jest otwarty.*** |
| `void Close()`                           | ***Zamyka plik***                        |
| `void SetWritePos(std::streampos Pos)`   | ***Ustawia pozycję kursora zapisu jako  argument przyjmuje gdzie ma go ustawić*** |
| `void WriteTxt(std::string STxt)`        | ***Zapisuje do pliku text.*  Argument** – text do zapisania |
| `long GetWritePos()`                     | ***Zwraca pozycje kursora zapisu***      |
| `void SetReadPos(std::streampos Pos = std::ios_base::beg)` | ***Ustawia kursor odczytu*  Argument-** pozycja w którym ma ustawić  kursor, domyślna wartość to początek |
| `void GetLineTxt(char  *Text, std::streamsize Size, const char Endl = '\n')` | ***Wczytuję linie textu z pliku*  Argument** to wskażnik do  którego zostanie przesłany text,   **Argument 2** to ilość znaków do  wczytania **Argument3:** znak kończący linię do wczytania |
| `long NrOfChar()`                        | ***Zwraca ilość znaków w plików***       |
| `long WhereReadPos()`                    | ***Zwraca pozycję kursora odczytu***     |

