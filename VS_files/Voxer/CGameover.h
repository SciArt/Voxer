/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CGameover.h
// Desc.: Ekran po przegranej
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CGameover_h
#define CGameover_h

#include "declarations.h"
#include "CFont.h"

// Deklaracje zapowiadaj¹ce
class CCursor;
class CMesh;
class CButton;
class CIngame;

class CGameover
{
private:
	CMesh *background; // T³o
	CButton *close; // Przycisk
	CIngame *ingame; // WskaŸnik do obiektu nadrzêdnego
	CFont fname[16]; // Napisy zawieraj¹ce pojedyncze litery nazwy gracza
public:
	CGameover();
	~CGameover();

	std::string name; // Nazwa gracza
	std::ostringstream convert; // Zmienna tymczasowa do konwertowania napisu

	bool init( CIngame *Ingame ); // Inicjalizowanie
	bool logic( CCursor *cursor ); // Czêœæ logiczna
	void draw(); // Rysowanie
	void restart(); // Restartowanie
};

#endif