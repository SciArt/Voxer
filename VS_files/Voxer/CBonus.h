/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CBonus.h
// Desc.: Klasa opisuj�ca bonus
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CBonus_h
#define CBonus_h

// Deklaracje zapowiadaj�ce
class CMesh;

class CBonus
{
private:
	CMesh *mesh; // Model
	double speed; // Szybko�c
	double rotate; // Obr�t 
	double size; // Rozmiar
	double rotate_z; // Obr�t na osi Z
public:
	double x, xk, y, z; // Wsp�rz�dne pozycji
	double radius; // Promie�
	unsigned int type; // Typ
	unsigned int value; // Warto�ci

	CBonus();
	~CBonus();

	// Wczytywanie
	void load( CMesh *mesh, unsigned int type, unsigned int value, double speed, double size, double pos_x, double pos_xk );

	void draw(); // Rysowanie
	bool logic( int DeltaTime ); // Cz�� logiczna
};

#endif