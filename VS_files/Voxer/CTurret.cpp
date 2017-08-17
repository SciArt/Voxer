/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CTurret.cpp
// Desc.: Klasa opisuj�ca wie�yczk�
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CTurret.h"
#include "CMesh.h"
#include "CCursor.h"
#include <cmath>

#define PI 3.14159265359

CTurret::CTurret()
{
	Gun1 = 0;
	Gun2 = 0;
	Base = 0;
	RotateCircle = 0;

	Rotate = 0.0; DestRotate = 0.0; // Resetowanie obrotu
	RotateSpeed = 60.0; // Ustawianie bazowej szybko�ci obrotu
	RotateSpeedRatio = 1.0; // Ustawianie mno�nika szybko�ci obrotu

	ReloadSpeedBase = 0.35; // Ustawieanie bazowej szybko�ci prze�adowywania
	ReloadSpeedRatio = 1.0; // Ustawianie mno�nika prze�adowywania

	ActiveGun = 0; // Kt�ra bro� strzela, 0 - �adna bro�, 1 - pierwsza bro�, 2 - druga bro�
	LastActiveGun = 2; // Ostatnia aktywna bro�

	Gun1Fired = false; // Reset wystrza�u z broni nr 1
	Gun2Fired = false; // Reset wystrza�u z broni nr 2

	gunshot = NULL;
	turret_sound = NULL;
}

CTurret::~CTurret()
{
	if( Gun1 )
		delete Gun1;
	if( Gun2 )
		delete Gun2;
	if( Base )
		delete Base;
	if( RotateCircle )
		delete RotateCircle;
	if( gunshot )
		Mix_FreeChunk( gunshot );
	if( turret_sound )
		Mix_FreeChunk( turret_sound );
}

bool CTurret::init()
{
	// Wczytywanie broni nr 1
	Gun1 = new CMesh();
	if( !Gun1 ) return false;
	if( !Gun1->Load( "Ingame/Graphic/Gun1.obj", "Ingame/Graphic/Gun1.png" ) )
		return false;
	Gun1->z = 0.0375;

	// Wczytywanie broni nr 2
	Gun2 = new CMesh();
	if( !Gun2 ) return false;
	if( !Gun2->Load( "Ingame/Graphic/Gun2.obj", "Ingame/Graphic/Gun2.png" ) )
		return false;
	Gun2->z = 0.0375;

	// Wczytywanie podstawy dzia�ka
	Base = new CMesh();
	if( !Base ) return false;
	if( !Base->Load( "Ingame/Graphic/Base.obj", "Ingame/Graphic/Base.png" ) )
		return false;
	Base->y = -0.87413;
	Base->z = 0.02857;
	
	// Wczytywanie obrotowej podstawki pod bro�
	RotateCircle = new CMesh();
	if( !RotateCircle ) return false;
	if( !RotateCircle->Load( "Ingame/Graphic/RotateCircle.obj", "Ingame/Graphic/RotateCircle.png" ) )
		return false;
	RotateCircle->z = 0.05;

	// Wczytywanie d�wi�ku wystrza�u
	gunshot = Mix_LoadWAV( "Ingame/Sounds/gunshot.wav" );
	if( !gunshot )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Initializing Error","Cannot load gunshot.wav", NULL);
		return false;
	}
	
	// Wczytywanie d�wi�ku ruchu dzia�ka
	turret_sound = Mix_LoadWAV( "Ingame/Sounds/turret.wav" );
	if( !turret_sound )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Initializing Error","Cannot load turret.wav", NULL);
		return false;
	}

	// Odtwarzanie d�wi�ku dzia�ka na kanale 0
	Mix_PlayChannel( 0, turret_sound, -1 );
	Mix_Pause( 0 ); // Zatrzymanie odtwarzania d�wi�ku na kanale 0
	return true;
}

void CTurret::draw()
{
	glPushMatrix();

	glScaled(0.65,0.65,0.65); // Przeskalowanie dzia�ka
	glTranslated(0.0, -0.85, -0.0134); // Przemieszczenie
	Base->Draw(); // Rysowanie podstawy

	glTranslated( 0.0, -0.8731, 0.0 ); // Przemieszczenie do g�ry
	glRotated( Rotate, 0.0, 0.0, 1.0 ); // Obr�t na osi Z

	RotateCircle->Draw(); // Rysoawnie obrotowej podstawki pod bro�
	Gun1->Draw(); // Rysowanie broni nr 1
	Gun2->Draw(); // Rysoawnie broni nr 2

	glPopMatrix();

	
}

int CTurret::logic( CCursor *cursor, int DeltaTime )
{
	// Obliczanie docelowej warto�ci obrotu dzia�ka
	DestRotate = -atan2( cursor->x, cursor->y + 0.8731 + 0.25) * 180 / PI;
	
	// Odtwarzanie d�wi�ku podczas ruchu dzia�ka
	if( Mix_Paused( 0 ) == 1  && abs(DestRotate - Rotate) >= 5.0 )
	{
		Mix_Resume( 0 );
	}
	else if( Mix_Playing( 0 ) == 1  && abs(DestRotate - Rotate) == 0.0 )
	{
		Mix_Pause( 0 );
	}
	
	// Obracanie dzia�ka

	// Je�li obr�t jest mniejszy od docelowego
	if( Rotate < DestRotate )
	{
		// Obliczanie nowego obrotu dzia�ka
		Rotate += RotateSpeed * RotateSpeedRatio * DeltaTime/1000.0;
		if( Rotate > DestRotate ) // Je�li wi�kszy
		{
			Rotate = DestRotate;
		}
	}
	else if( Rotate > DestRotate ) // Je�li obr�t wi�kszy od docelowego
	{
		// Obliczanie nowego obrotu dzia�ka
		Rotate -= RotateSpeed * RotateSpeedRatio * DeltaTime/1000.0;
		if( Rotate < DestRotate ) // Je�li mniejszy
		{
			Rotate = DestRotate;
		}
	}

	if( cursor->clicked ) // Je�li LPM wci�ni�ty
	{
		// Ustawienie aktywnej broni
		if( ActiveGun == 0  && LastActiveGun == 1)
			ActiveGun = 2;
		if( ActiveGun == 0  && LastActiveGun == 2)
			ActiveGun = 1;
	}
	if( ActiveGun == 0 ) // Je�li �adna bro� nie jest aktywna
	{
		// Resetowanie pozycji broni

		if( Gun1->y != 0.0 )
		{
			Gun1->y += ReloadSpeedBase * ReloadSpeedRatio * DeltaTime/1000.0;
			if( Gun1->y > 0.0 )
				Gun1->y = 0.0;
		}
		if( Gun2->y != 0.0 )
		{
			Gun2->y += ReloadSpeedBase * ReloadSpeedRatio * DeltaTime/1000.0;
			if( Gun2->y > 0.0 )
				Gun2->y = 0.0;
		}
	}
	if( ActiveGun == 1 ) // Je�li aktywna bron nr 1
	{
		// STRZA� !!!
		if( Gun1->y == 0.0  && !Gun1Fired )
		{
			Gun1Fired = true;
			Mix_PlayChannel(-1,gunshot,0);
			return 1;
		}

		// Odrzut dzia�ka i powr�t

		if( Gun1->y > -0.1 )
		{
			Gun1->y -= ReloadSpeedBase * ReloadSpeedRatio * DeltaTime/1000.0;
			if( Gun1->y < -0.1 ) Gun1->y = -0.1;
		}
		if( Gun2->y < 0.0 )
		{
			Gun2->y += ReloadSpeedBase * ReloadSpeedRatio * DeltaTime/1000.0;
			if( Gun2->y > 0.0 ) Gun2->y = 0.0;
		}
		if( Gun1->y == -0.1 ) // Je�li dzia�ko w maksymalnym wychyleniu
		{
			// Zmiana aktywnej broni

			if( cursor->clicked )
				ActiveGun = 2;
			else
				ActiveGun = 0;
			
			LastActiveGun = 1;
			Gun1Fired = false;
		}
	}
	else if( ActiveGun == 2 )
	{
		// STRZA� !!!
		if( Gun2->y == 0.0 && !Gun2Fired )
		{
			Gun2Fired = true;
			Mix_PlayChannel(-1,gunshot,0);
			return 2;
		}

		// Odrzut dzia�ka i powr�t

		if( Gun2->y > -0.1 )
		{
			Gun2->y -= ReloadSpeedBase * ReloadSpeedRatio * DeltaTime/1000.0;
			if( Gun2->y < -0.1 ) Gun2->y = -0.1;
		}
		if( Gun1->y < 0.0 )
		{
			Gun1->y += ReloadSpeedBase * ReloadSpeedRatio * DeltaTime/1000.0;
			if( Gun1->y > 0.0 ) Gun1->y = 0.0;
		}
		if( Gun2->y == -0.1 ) // Je�li dzia�ko w maksymalnym wychyleniu
		{
			// Zmiana aktywnej broni

			if( cursor->clicked )
				ActiveGun = 1;
			else
				ActiveGun = 0;

			LastActiveGun = 2;
			Gun2Fired = false;
		}
	}

	return 0;
}