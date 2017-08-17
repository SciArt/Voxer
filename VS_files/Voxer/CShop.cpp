/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CShop.cpp
// Desc.: Ekran ze sklepem
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CShop.h"
#include "CMesh.h"
#include "CButton.h"
#include "CLogic.h"
#include "CIngame.h"
#include "CTurret.h"

CShop::CShop()
{
	background = NULL;
	buy[0] = NULL;
	buy[1] = NULL;
	buy[2] = NULL;
	buy[3] = NULL;
	close = NULL;
	buy_sound = NULL;
	buyfail_sound = NULL;
}

CShop::~CShop()
{
	if( background )
		delete background;
	if( buy[0] )
		delete buy[0];
	if( buy[1] )
		delete buy[1];
	if( buy[2] )
		delete buy[2];
	if( buy[3] )
		delete buy[3];
	if( close )
		delete close;
	if( buy_sound )
		Mix_FreeChunk( buy_sound );
	if( buyfail_sound )
		Mix_FreeChunk( buyfail_sound );
}

bool CShop::init( CIngame *Ingame )
{
	// Wczytywanie t³a
	background = new CMesh();
	if( !background ) return false;
	if( !background->Load( "Ingame/Graphic/background.obj", 
		"Ingame/Graphic/shop.png" ) )
		return false;
	background->z = 0.0002;

	// Wczytywanie przycisków kupowania
	buy[0] = new CButton();	if( !buy[0] ) return false;
	buy[1] = new CButton();	if( !buy[0] ) return false;
	buy[2] = new CButton();	if( !buy[0] ) return false;
	buy[3] = new CButton();	if( !buy[0] ) return false;

	if( !buy[0]->Load( "Ingame/Graphic/buy.obj",
		"Ingame/Graphic/buy1.png" ) )
		return false;
	if( !buy[0]->LoadTex2( "Ingame/Graphic/buy2.png" ) )
		return false;
	buy[0]->x = 0.494;
	buy[0]->z = 0.0003;
	buy[0]->width = 0.3917;
	buy[0]->height = 0.1417;
	buy[0]->y = 0.5028 - (buy[0]->height/2.0);

	*buy[1] = *buy[0];
	buy[1]->y = 0.2528 - (buy[0]->height/2.0);

	*buy[2] = *buy[0];
	buy[2]->y = 0.0028 - (buy[0]->height/2.0);

	*buy[3] = *buy[0];
	buy[3]->y = -0.2472 - (buy[0]->height/2.0);

	// Wczytywanie przycisku close
	close = new CButton(); if( !close ) return false;
	if( !close->Load( "Ingame/Graphic/close.obj",
		"Ingame/Graphic/close1.png" ) )
		return false;
	if( !close->LoadTex2( "Ingame/Graphic/close2.png" ) )
		return false;

	close->z = 0.0003;
	close->width = 0.4917;
	close->height = 0.0806;
	close->x = 0.7528;
	close->y = 0.9583;

	// Wczytywanie dŸwiêku kupowania
	buy_sound = Mix_LoadWAV( "Ingame/Sounds/buy.wav" );
	if( !buy_sound )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Initializing Error","Cannot load buy.wav", NULL);
		return false;
	}
	
	// Wczytywanie dŸwiêku nieudanego zakupu
	buyfail_sound = Mix_LoadWAV( "Ingame/Sounds/buyfail.wav" );
	if( !buyfail_sound )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Initializing Error","Cannot load buyfail.wav", NULL);
		return false;
	}

	ingame = Ingame; // Kopiowanie wskaŸnika do obiektu nadrzêdnego

	return true;
}

void CShop::draw()
{
	background->Draw(); // Rysowanie t³a
	// Rysowanie przycisków kupowania
	glPushMatrix();
		glTranslated( 0.0, buy[0]->height/2.0, 0.0 );
		buy[0]->Draw();
		buy[1]->Draw();
		buy[2]->Draw();
		buy[3]->Draw();
	glPopMatrix();
	glPushMatrix();
		close->Draw(); // Rysowanie przycisku close
	glPopMatrix();
}

bool CShop::logic( CCursor *cursor )
{
	if( buy[0]->Logic( cursor ) ) // Kupowanie Reload Speed
	{
		// Potrzebne $100 i mno¿nik musi byæ mniejszy od 2.5
		if(	ingame->money >= 100 && ingame->turret->ReloadSpeedRatio < 2.5 )
		{
			ingame->money -= 100;
			Mix_PlayChannel(-1,buy_sound,0);
			ingame->turret->ReloadSpeedRatio += 0.1;
		}
		else
		{
			Mix_PlayChannel(-1,buyfail_sound,0);
		}
	}
	
	if( buy[1]->Logic( cursor ) ) // Kupowanie Bullet Speed
	{
		// Potrzebne $50 i mno¿nik musi byæ mniejszy od 2.0
		if( ingame->money >= 50 && ingame->BulletSpeedRatio < 2.0 )
		{
			ingame->money -= 50;
			Mix_PlayChannel(-1,buy_sound,0);
			ingame->BulletSpeedRatio += 0.1;
		}
		else
		{
			Mix_PlayChannel(-1,buyfail_sound,0);
		}
	}

	if(	buy[2]->Logic( cursor ) ) // Kupowanie Rotate Speed
	{
		// Potrzebne $100 i mno¿nik musi byæ mniejszy od 2.0
		if( ingame->money >= 100 && ingame->turret->RotateSpeedRatio < 2.0 )
		{
			ingame->money -= 100;
			Mix_PlayChannel(-1,buy_sound,0);
			ingame->turret->RotateSpeedRatio += 0.1;
		}
		else
		{
			Mix_PlayChannel(-1,buyfail_sound,0);
		}
	}
	if( buy[3]->Logic( cursor ) ) // Kupowanie Shield
	{
		// Potrzebne $50 i musi byæ mniej ni¿ 4 tarcze
		if( ingame->money >= 50 && ingame->shields < 4)
		{
			ingame->money -= 50;
			Mix_PlayChannel(-1,buy_sound,0);
			ingame->shields += 1;
		}
		else
		{
			Mix_PlayChannel(-1,buyfail_sound,0);
		}
	}
	
	// Obs³uga przycisku close
	if( close->Logic( cursor ) )
		return true;

	return false;
}