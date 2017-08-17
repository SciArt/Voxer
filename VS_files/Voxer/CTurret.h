/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CTurret.h
// Desc.: Klasa opisuj�ca wie�yczk�
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CTurret_h
#define CTurret_h

#include <SDL_mixer.h>
#include <vector>

// Deklaracje zapowiadaj�ce
class CMesh;
class CCursor;

class CTurret
{
private:
	Mix_Chunk *gunshot; // D�wi�k wystrza�u
	Mix_Chunk *turret_sound; // D�wi�k ruchu dzia�ka
	
	int ActiveGun; // Kt�ra bro� strzela, 0 - �adna bro�, 1 - pierwsza bro�, 2 - druga bro�
	int LastActiveGun; // Ostatnia aktywana bro�

	bool Gun1Fired, Gun2Fired; // Flagi wystrz�u

public:
	CTurret();
	~CTurret();

	CMesh *Gun1; // Model broni nr 1
	CMesh *Gun2; // Model broni nr 2
	CMesh *Base; // Model podstawy
	CMesh *RotateCircle; // Model obrotowej podstawki pod bro�

	double Rotate, DestRotate; // K�t obrotu wie�yczki
	double RotateSpeed, RotateSpeedRatio; // Szybko�� bazowa obrotu i mno�nik
	double ReloadSpeedBase, ReloadSpeedRatio; // Szybko�� bazowa prze�adowywania i mno�nik

	bool init();
	void draw();
	int logic( CCursor *cursor, int DeltaTime ); // Zwraca: 0 - brak strza�u, 1 - strzal z lewej broni, 2 - strza� z prawej broni
};

#endif
