/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CMeteor.h
// Desc.: Klasa opisuj¹ca meteoroid
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CMeteor_h
#define CMeteor_h

#include "CFont.h"

// Deklaracje zapowiadaj¹ce
class CMesh;

class CMeteor
{
private:
	CMesh *mesh; // Model
	
	double speed; // Szybkoœæ
	double rotate; // Obrót
	double scale_z; // Skala na osi Z
	double alpha; // Przezroczystoœæ
	double size; // Rozmiar
	double rotate_z; // Obrót na osi Z

public:
	double radius; // Promieñ
	double x, xk, y, z; // Wspó³rzêdne po³o¿enia
	unsigned int base_lives, lives; // Iloœæ ¿yæ, bazowa i aktualna

	CMeteor();
	~CMeteor();

	// Wczytywanie
	void load( CMesh *mesh, unsigned int lives, double speed, double size, double pos_x, double pos_xk );

	void draw(); // Rysowanie
	bool logic( int DeltaTime ); // Czêœæ logiczna
};

#endif