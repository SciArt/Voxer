/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CAuthor.cpp
// Desc.: Ekran z informacjami o autorze
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CAuthor.h"
#include "CMesh.h"
#include "CCursor.h"
#include "CButton.h"
#include "CApp.h"
#include "CGame.h"
#include "CIngame.h"
#include "CTurret.h"

CAuthor::CAuthor()
{
	background = NULL;
	close = NULL;
	game = NULL;
}

CAuthor::~CAuthor()
{
	if( background )
		delete background;
	if( close )
		delete close;
}

bool CAuthor::init( CGame *game )
{
	// Wczytywanie t³a
	background = new CMesh();
	if( !background ) return false;
	if( !background->Load( "Author/Graphic/background.obj", "Author/Graphic/background.png" ) )
		return false;

	// Wczytywanie przycisku close
	close = new CButton();
	if( !close ) return false;
	if( !close->Load( "Author/Graphic/close.obj", "Author/Graphic/close1.png" ) )
		return false;
	if( !close->LoadTex2( "Author/Graphic/close2.png" ) )
		return false;
	close->x = -1.853;
	close->y = 1.325;
	close->z = 0.0;
	close->width = 0.45;
	close->height = 0.108;

	// Zapisywanie wskaŸnika do obiektu nadrzêdnego
	this->game = game;

	return true;
}

void CAuthor::draw()
{
	background->Draw(); // Rysowanie t³a
	close->Draw(); // Rysowanie przycisku close
	
	// Rysowanie imitacji dzia³ka

	glPushMatrix();
	
	glTranslated(1.12,0.55,0.0);
	glRotated(180,0.0,0.0,1.0);		

	glScaled(0.65,0.65,0.65);
	game->ingame->turret->Base->Draw();

	glTranslated( 0.0, -0.8731, 0.0 );
	glRotated( -30, 0.0, 0.0, 1.0 );

	game->ingame->turret->RotateCircle->Draw();
	game->ingame->turret->Gun2->Draw();

	glTranslated( 0.0, -0.1, 0.0 );
	game->ingame->turret->Gun1->Draw();
	
	// Rysowanie imitacji pocisku nr 1
	glPushMatrix();
		glTranslated( -0.1, 0.6, 0.0 );
		game->ingame->BulletMesh->Draw();
	glPopMatrix();

	// Rysowanie imitacji pocisku nr 2
	glTranslated( 0.1, 0.9, 0.0 );
	game->ingame->BulletMesh->Draw();

	glPopMatrix();

	// Koniec rysowania imitacji dzia³ka

	// Rysowanie imitacji metoroidu
	glPushMatrix();

	glTranslated( 0.5, 0.5, 0.0 );
	game->ingame->meteor_mesh->Draw();

	glPopMatrix();
	// Koniec rysowania imitacji meteoroidu
}

bool CAuthor::logic( CCursor *cursor, int DeltaTime )
{
	if( close->Logic( cursor ) ) // Obs³uga przycisku
	{
		return true;
	}
	return false;
}