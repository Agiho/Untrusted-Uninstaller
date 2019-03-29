## **CFilesList**

Klasa która pozwala sprawdzić jakie pliki znajduą sie w folderze, przechowuje tę informację i może ją zwrócić

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void SetLog(CLog *TLog)`                | ***Przekazuje wskaźnik na plik log do klasy*** **Argument:** Wskaźnik na obiekt log |
| `void Read(std::string Folder)`          | ***Odczytuje nazy plików ze wskazanego folderu*** **Argument:** Nazwa folderu z którego ma być odczytana lista plików |
| `std::vector<std::string> GetFileNames()` | ***Zwraca kontener z uzyskanymi nazwami plików*** |