/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CShop.h
// Desc.: Ekran ze sklepem
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CShop_h
#define CShop_h

#include <SDL_mixer.h>

// Deklaracje zapowiadaj�ce
class CCursor;
class CMesh;
class CButton;
class CIngame;

class CShop
{
private:
	CMesh *background; // T�o
	CButton *buy[4]; // Przyciski kupowania
	CButton *close; // Przycisk close
	CIngame *ingame; // Wska�nik do obiektu nadrz�dnego
	Mix_Chunk *buy_sound; // D�wi�k udanego zakupu
	Mix_Chunk *buyfail_sound; // D�wi�k nieudanego zakupu

public:
	CShop();
	~CShop();
	
	bool init( CIngame *Ingame ); // Inicjalizacja
	bool logic( CCursor *cursor ); // Cz�� logiczna
	void draw(); // Rysowanie
};

#endif