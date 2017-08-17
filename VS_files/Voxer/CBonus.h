/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CBonus.h
// Desc.: Klasa opisuj¹ca bonus
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CBonus_h
#define CBonus_h

// Deklaracje zapowiadaj¹ce
class CMesh;

class CBonus
{
private:
	CMesh *mesh; // Model
	double speed; // Szybkoœc
	double rotate; // Obrót 
	double size; // Rozmiar
	double rotate_z; // Obrót na osi Z
public:
	double x, xk, y, z; // Wspó³rzêdne pozycji
	double radius; // Promieñ
	unsigned int type; // Typ
	unsigned int value; // Wartoœci

	CBonus();
	~CBonus();

	// Wczytywanie
	void load( CMesh *mesh, unsigned int type, unsigned int value, double speed, double size, double pos_x, double pos_xk );

	void draw(); // Rysowanie
	bool logic( int DeltaTime ); // Czêœæ logiczna
};

#endif