/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CShop.h
// Desc.: Ekran ze sklepem
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CShop_h
#define CShop_h

#include <SDL_mixer.h>

// Deklaracje zapowiadaj¹ce
class CCursor;
class CMesh;
class CButton;
class CIngame;

class CShop
{
private:
	CMesh *background; // T³o
	CButton *buy[4]; // Przyciski kupowania
	CButton *close; // Przycisk close
	CIngame *ingame; // WskaŸnik do obiektu nadrzêdnego
	Mix_Chunk *buy_sound; // DŸwiêk udanego zakupu
	Mix_Chunk *buyfail_sound; // DŸwiêk nieudanego zakupu

public:
	CShop();
	~CShop();
	
	bool init( CIngame *Ingame ); // Inicjalizacja
	bool logic( CCursor *cursor ); // Czêœæ logiczna
	void draw(); // Rysowanie
};

#endif