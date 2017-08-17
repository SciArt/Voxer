/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CGraphic.h
// Desc.: Zawiera klasê odpowiedzialn¹ za czêœæ graficzn¹
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CGraphic_h
#define CGraphic_h

#include "declarations.h"

// Deklaracje zapowiadaj¹ce
class CApp;
struct AppSettings;

class CGraphic
{
	private:
		CApp *app; // WskaŸnik na klasê nadrzêdn¹
	public:
		CGraphic(CApp *app){this->app = app;}
		~CGraphic(){};

		void init( AppSettings &settings ); // Inicjalizowanie grafiki
		void set_viewport( unsigned int width, unsigned int height ); // Ustawienie obszaru roboczego i perspektywy
		void draw(); // Rysowanie
};

#endif