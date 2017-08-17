/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CTurret.h
// Desc.: Klasa opisuj¹ca wie¿yczkê
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CTurret_h
#define CTurret_h

#include <SDL_mixer.h>
#include <vector>

// Deklaracje zapowiadaj¹ce
class CMesh;
class CCursor;

class CTurret
{
private:
	Mix_Chunk *gunshot; // DŸwiêk wystrza³u
	Mix_Chunk *turret_sound; // DŸwiêk ruchu dzia³ka
	
	int ActiveGun; // Która broñ strzela, 0 - ¿adna broñ, 1 - pierwsza broñ, 2 - druga broñ
	int LastActiveGun; // Ostatnia aktywana broñ

	bool Gun1Fired, Gun2Fired; // Flagi wystrz³u

public:
	CTurret();
	~CTurret();

	CMesh *Gun1; // Model broni nr 1
	CMesh *Gun2; // Model broni nr 2
	CMesh *Base; // Model podstawy
	CMesh *RotateCircle; // Model obrotowej podstawki pod broñ

	double Rotate, DestRotate; // K¹t obrotu wie¿yczki
	double RotateSpeed, RotateSpeedRatio; // Szybkoœæ bazowa obrotu i mno¿nik
	double ReloadSpeedBase, ReloadSpeedRatio; // Szybkoœæ bazowa prze³adowywania i mno¿nik

	bool init();
	void draw();
	int logic( CCursor *cursor, int DeltaTime ); // Zwraca: 0 - brak strza³u, 1 - strzal z lewej broni, 2 - strza³ z prawej broni
};

#endif
