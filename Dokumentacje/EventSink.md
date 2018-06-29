## EventSink

Klasa potrzebna w klasie WMI do pilnowania procesu kt�ry zosta� uruchomiony.


| Funkcja                                  | Opis                                     |
| ---------------------------------------- | ---------------------------------------- |
| `void InsterLog(CLog *TLog)`             | ***Pozwala przekaza� wska�nik do obieku zajmuj�cego si� logami*** **Argument::** Wska�nik na plik Log |
| `virtual ULONG STDMETHODCALLTYPE AddRef()` | ***Pobiera referencj� do obiektu i izwi�ksza liczbe ich wyst�pie�*** |
| `virtual ULONG STDMETHODCALLTYPE Release()` | ***Odpowiada za wyczyszczenie utworzonych obiekt�w i dekrementacje wyst�pie� referencji*** |
| `virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);` | ***Odpowiada za utworzenie interfejsu dla odpyta�*** **Argument 1:** ID obiektu **Argument 2:* Wska�nik na adres obiektu |
| `virtual HRESULT STDMETHODCALLTYPE Indicate(LONG lObjectCount,IWbemClassObject __RPC_FAR *__RPC_FAR *apObjArray)` | ***Sprawdza jakie zdarzenie zachodzi w procesie*** **Argument 1:** Liczba obiekt�w **Argument 2:** wska�nik na adres tablicy obiekt�w |
| `virtual HRESULT STDMETHODCALLTYPE SetStatus( LONG lFlags,HRESULT hResult,BSTR strParam,IWbemClassObject __RPC_FAR *pObjParam)` | ***Pozwala sprawdzi� obecny status processu funkcja wykorzystywana przez WMI, nie wywo�uje sie jej z poziomu uzytkownika, potrzebna dla pochodnego obiektu*** |
|  `bool EventSink::DeadSink()`            | ***Zwraca prawd� jesli process si� sko�czy�*** |