## EventSink

Klasa potrzebna w klasie WMI do pilnowania procesu który zosta³ uruchomiony.


| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void InsterLog(CLog *TLog)`             | ***Pozwala przekazaæ wskaŸnik do obieku zajmuj¹cego siê logami*** **Argument::** WskaŸnik na plik Log |
| `virtual ULONG STDMETHODCALLTYPE AddRef()` | ***Pobiera referencjê do obiektu i izwiêksza liczbe ich wyst¹pieñ*** |
| `virtual ULONG STDMETHODCALLTYPE Release()` | ***Odpowiada za wyczyszczenie utworzonych obiektów i dekrementacje wyst¹pieñ referencji*** |
| `virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);` | ***Odpowiada za utworzenie interfejsu dla odpytañ*** **Argument 1:** ID obiektu **Argument 2:* WskaŸnik na adres obiektu |
| `virtual HRESULT STDMETHODCALLTYPE Indicate(LONG lObjectCount,IWbemClassObject __RPC_FAR *__RPC_FAR *apObjArray)` | ***Sprawdza jakie zdarzenie zachodzi w procesie*** **Argument 1:** Liczba obiektów **Argument 2:** wskaŸnik na adres tablicy obiektów |
| `virtual HRESULT STDMETHODCALLTYPE SetStatus( LONG lFlags,HRESULT hResult,BSTR strParam,IWbemClassObject __RPC_FAR *pObjParam)` | ***Pozwala sprawdziæ obecny status processu funkcja wykorzystywana przez WMI, nie wywo³uje sie jej z poziomu uzytkownika, potrzebna dla pochodnego obiektu*** |
|  `bool EventSink::DeadSink()`            | ***Zwraca prawdê jesli process siê skoñczy³*** |