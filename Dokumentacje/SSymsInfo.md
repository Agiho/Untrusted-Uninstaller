## **SDiskInfo**

Struktura przechowująca informacje o podłączonych dyskach komputera

| Pole                                     | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `std::string Name`                       | ***Zawiera nazwe systemu (pełną wraz z wersją np. home i spacją na końcu)*** |
| `std::string SP`                         | ***Zawiera informacje o zainstalowanym service packu*** |
| `std::string OSArch`                     | ***Zawiera informacje o architekturze systemu (np. "64-bit")*** |
| `unsigned int FreeMem`                   | ***Dostępna wolna pamięc w systemie*** |
| `unsigned int Lang`                      | ***Zawiera informację o języku systemu (np. j.polski to warotść 1045)*** |
| `unsigned int Type`                      | ***Zawiera typ systemu (np. linux, WinNT)*** |