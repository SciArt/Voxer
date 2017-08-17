/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CSwitch.h
// Desc.: Klasa opisuj¹ca przycisk - prze³¹cznik
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CSwitch_h
#define CSwitch_h

// Deklaracje zapowiadaj¹ce
class CMesh;
class CCursor;

class CSwitch
{
private:
	double x, y, z; // Pozycja
	double height, width; // Wysokoœæ, szerokoœæ
	CMesh *SwitchON; // Model przycisku w³¹czonego
	CMesh *SwitchOFF; // Model przycisku wy³¹czonego
	
	bool mouse_on; // Myszka na przycisku
	bool clicked; // Przycisk wciœniêty
public:
	CSwitch();
	~CSwitch();

	bool state; // Status przycisku

	// Wczytywanie przycisku
	bool Load( char *mesh, char *tex_on, char *tex_off,
		double height, double width, double x, double y, double z );

	bool Logic( CCursor *cursor ); // Czêœæ logiczna
	void Draw(); // Rysowanie
};

#endif