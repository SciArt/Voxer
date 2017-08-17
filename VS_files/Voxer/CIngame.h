/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CIngame.h
// Desc.: Klasa zawieraj�ca rozgrywk�
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CIngame_h
#define CIngame_h

#include <SDL_mixer.h>
#include <vector>
#include <sstream>
#include "CFont.h"

// Deklaracje zapowiadaj�ce
class CCursor;
class CMesh;
class CMeteor;
class CTurret;
class CBullet;
class CLevel;
class CBonus;
class CShop;
class CGame;
class CApp;
class CGameover;

class CIngame
{
private:
	CLevel *lvl; // Obiekt level'a

	// Napisy interfejsu
	CFont Scores_Text, ReloadSpeed_Text, BulletSpeed_Text, TrackingSpeed_Text, Level_Text, Money_Text;
	std::ostringstream convert; // Zmienna tymczasowa do konwerotwania tekstu

	CMesh *background; // T�o

	Mix_Chunk *hit; // D�wi�k trafienia w meteoroid
	Mix_Chunk *coin_gain; // D�wi�k trafienia w bonus pieni�ny
	
	std::vector<CBullet> Bullets; // Pociski
	std::vector<CMeteor> meteors; // Meteoroidy
	
	int m_time; // Czas po jakim pojawia si� kolejny obiekt (w milisekundach)
	int dm_time; // Up�yw czasu od chwili pojawienia si� ostatniego obiektu
	CMesh *shield; // Model tarczy
	
public:
	CIngame();
	~CIngame();

	bool init( CApp *App ); CApp *app;
	void draw();
	void logic( CCursor *cursor, int DeltaTime );

	CShop *shop; // Sklep
	CGameover *gameover; // Ekran ko�ca gry
		
	unsigned int scores; // Liczba punkt�w
	unsigned int level; // Numer level'a

	double BulletSpeed; // Szybko�� bazowa pocisku
	double BulletSpeedRatio; // Mno�nik szybko�ci pocisku
	int shields; // Liczba tarcz
	unsigned int money; // Ilo�� pieni�dzy

	CMesh *BulletMesh; // Model pocisku
	CMesh *moneybonus_mesh; // Model monety
	CMesh *meteor_mesh; // Model meteoroidu

	std::vector<CBonus> bonuses; // Bonusy
	CTurret *turret; // Wie�yczka
};

#endif