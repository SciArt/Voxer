/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CMesh.cpp
// Desc.: Klasa opisuj¹ca model 3D
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CMesh.h"

CMesh::CMesh()
{
	x = y = z = 0;
	ax = ay = az = 0;
	sx = sy = sz = 1;
}

CMesh::~CMesh()
{
}

// Wczytywanie modelu [plik z modelem .obj , plik z tekstur¹]
bool CMesh::Load( char* file_model, char* file_texture )
{
	std::ifstream file( file_model ); // Otwieranie pliku
	if( !file )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Data loading error...", file_model, NULL);
		return false;
	}

	std::string sign; // Znak ("v", "vt", "vn")

	// Wczytywanie modelu
	while( file >> sign )
	{
		if( sign == "v" ) // Wczytywanie wierzcho³ków
		{
			v.resize( v.size() + 1 );

			file >> v[ v.size() - 1 ].x;
			file >> v[ v.size() - 1 ].y;
			file >> v[ v.size() - 1 ].z;
		}
		else if( sign == "vt" ) // Wczytywanie wspó³rzêdnych tekstur
		{
			vt.resize( vt.size() + 1 );

			file >> vt[ vt.size() - 1 ].x;
			file >> vt[ vt.size() - 1 ].y;
		}
		else if( sign == "vn" ) // Wczytywanie normalnych
		{
			vn.resize( vn.size() + 1 );

			file >> vn[ vn.size() - 1 ].x;
			file >> vn[ vn.size() - 1 ].y;
			file >> vn[ vn.size() - 1 ].z;
		}
		else if( sign == "f" ) // Wczytywanie opisów œcianek (trójk¹tów)
		{
			f.resize( f.size() + 1 );
			unsigned int index;
			
			file >> index;
			f[ f.size() - 1 ].v1 = &v[ index - 1 ];	file.ignore(1);

			file >> index;
			f[ f.size() - 1 ].vt1 = &vt[ index - 1 ]; file.ignore(1);

			file >> index;
			f[ f.size() - 1 ].vn1 = &vn[ index - 1 ];

			//====================================================
			
			file >> index;
			f[ f.size() - 1 ].v2 = &v[ index - 1 ];	file.ignore(1);

			file >> index;
			f[ f.size() - 1 ].vt2 = &vt[ index - 1 ]; file.ignore(1);

			file >> index;
			f[ f.size() - 1 ].vn2 = &vn[ index - 1 ];

			//====================================================

			file >> index;
			f[ f.size() - 1 ].v3 = &v[ index - 1 ];	file.ignore(1);

			file >> index;
			f[ f.size() - 1 ].vt3 = &vt[ index - 1 ]; file.ignore(1);

			file >> index;
			f[ f.size() - 1 ].vn3 = &vn[ index - 1 ];
		}
		if( file.fail() ) // Jeœli b³¹d wczytywania
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Data loading error...", file_model, NULL);
			return false;
		}
	}
	
	file.close(); // Zamkniêcie pliku

	SDL_Surface *tex = IMG_Load( file_texture ); // Wczytanie tekstury (SDL)

    if(tex) // Jeœli wczyta³o
    {
		// Utowrzenie tekstury (OpenGL)
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, 4, tex->w, tex->h, 
			0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);
        
        SDL_FreeSurface(tex);
    }
    else
    {
       SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
					"Data loading error...", file_texture, NULL);
	   return false;
    }

	CreateList(); // Tworzenie listy wyœwietlania

	return true;
}

// Tworzenie listy wyœwietlania
void CMesh::CreateList()
{
	MeshList = glGenLists(1); // Generowanie 1 listy

	glNewList( MeshList, GL_COMPILE ); // Kompilowanie listy
		glBegin( GL_TRIANGLES );
		for( unsigned int i = 0; i < f.size(); ++i )
		{
			glNormal3d( f[i].vn1->x, f[i].vn1->y, f[i].vn1->z );
		    glTexCoord2d( f[i].vt1->x, -f[i].vt1->y ); glVertex3d( f[i].v1->x, f[i].v1->y, f[i].v1->z );
			glTexCoord2d( f[i].vt2->x, -f[i].vt2->y ); glVertex3d( f[i].v2->x, f[i].v2->y, f[i].v2->z );
			glTexCoord2d( f[i].vt3->x, -f[i].vt3->y ); glVertex3d( f[i].v3->x, f[i].v3->y, f[i].v3->z );
		}
		glEnd();
	glEndList();
}

// Rysowanie modelu
void CMesh::Draw()
{
	glPushMatrix();
		glEnable(GL_LIGHTING); // W³¹cznie oœwietlenia
		glEnable(GL_TEXTURE_2D); // W³¹czenie teksturowania
		glBindTexture(GL_TEXTURE_2D, texture); // U¿ycie tekstury modelu
		glScaled( sx, sy, sz ); // Skalowanie

		// Obrót
		glRotated( ax, 1.0, 0.0, 0.0 );
		glRotated( ay, 0.0, 1.0, 0.0 );
		glRotated( az, 0.0, 0.0, 1.0 );

		// Przemieszczenie
		glTranslated( x, y, z );

		// Wywo³anie listy wyœwietlania
		glCallList( MeshList );

		glDisable(GL_TEXTURE_2D); // Wy³¹czenie teksturowania
		glDisable(GL_LIGHTING); // Wy³aczenie oœwietlenia
	glPopMatrix();
}