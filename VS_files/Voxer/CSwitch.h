/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CSwitch.h
// Desc.: Klasa opisuj�ca przycisk - prze��cznik
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CSwitch_h
#define CSwitch_h

// Deklaracje zapowiadaj�ce
class CMesh;
class CCursor;

class CSwitch
{
private:
	double x, y, z; // Pozycja
	double height, width; // Wysoko��, szeroko��
	CMesh *SwitchON; // Model przycisku w��czonego
	CMesh *SwitchOFF; // Model przycisku wy��czonego
	
	bool mouse_on; // Myszka na przycisku
	bool clicked; // Przycisk wci�ni�ty
public:
	CSwitch();
	~CSwitch();

	bool state; // Status przycisku

	// Wczytywanie przycisku
	bool Load( char *mesh, char *tex_on, char *tex_off,
		double height, double width, double x, double y, double z );

	bool Logic( CCursor *cursor ); // Cz�� logiczna
	void Draw(); // Rysowanie
};

#endif