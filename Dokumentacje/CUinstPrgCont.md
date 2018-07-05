## **CUInstPrgCont**

Klasa przechowująca informacje do oinstalowania programu

| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `int Add(std::string TName, std::string Uninst, std::string QUninst)` | ***dodaje do obiektu dane i sprawdza poprawność ścieżki do deinstalacji*** **argument 1:** Nazwa programu **Argument 2:** Scieżka do odinstalowania **Argument 3:** ścieżka do cichego odinstalowania o ile istnieje |


### Klasy zaprzyjaźnione:

friend class CPrepareUninst
friend class CPrgSelector
template <typename T> friend class CCheckBoxCont

Dostępna pola dla przyjaciół:

| Pola                                     | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `std::string Name`                       | ***Nazwa programu do odinstalowania***   |
| `std::string Uninsstr`                   | ***ścieżka do odinstalowania programu*** |
| `UStrState StrState`                     | ***ścieżka do cichego odinstalowania***  |
| `bool BChecked`                          | ***czy program został zaznaczony***      |