/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CLogic.h
// Desc.: Klasa pocisku
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CBullet_h
#define CBullet_h

// Deklaracje zapowiadaj�ce
class CMesh;

class CBullet
{
public:
	CMesh *mesh; // Wska�nik na model pocisku
	
	double Rotate; // Obr�t na osi Z
	double x, y; // Pozycja pocisku

	CBullet(){mesh = 0; x=0.0; y=0.0; Rotate=0.0;}
	~CBullet(){}

	void draw(); // Rysowanie pocisku
};

#endif