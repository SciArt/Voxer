/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CMeteor.h
// Desc.: Klasa opisuj�ca meteoroid
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CMeteor_h
#define CMeteor_h

#include "CFont.h"

// Deklaracje zapowiadaj�ce
class CMesh;

class CMeteor
{
private:
	CMesh *mesh; // Model
	
	double speed; // Szybko��
	double rotate; // Obr�t
	double scale_z; // Skala na osi Z
	double alpha; // Przezroczysto��
	double size; // Rozmiar
	double rotate_z; // Obr�t na osi Z

public:
	double radius; // Promie�
	double x, xk, y, z; // Wsp�rz�dne po�o�enia
	unsigned int base_lives, lives; // Ilo�� �y�, bazowa i aktualna

	CMeteor();
	~CMeteor();

	// Wczytywanie
	void load( CMesh *mesh, unsigned int lives, double speed, double size, double pos_x, double pos_xk );

	void draw(); // Rysowanie
	bool logic( int DeltaTime ); // Cz�� logiczna
};

#endif