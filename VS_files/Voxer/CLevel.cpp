/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CLevel.cpp
// Desc.: Klasa zawieraj¹ca level, struktura zawierajca obiekt
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CLevel.h"
#include "declarations.h"

using namespace std;

bool CLevel::Load( const char *level_file )
{
	ifstream file( level_file ); // Otwieranie pliku
	if( !file )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Level loading error... Missing file: ", level_file, NULL);
		return false;
	}

	object_number = 0; // Zerowanie liczby obiektów
	objects.clear(); // Resetowanie obiektów

	// Wczytywanie obiektów
	while( !file.eof() )
	{
		if( file.good() )
		{
			objects.resize( objects.size() + 1 );
		}
		else
		{
			file.clear();
			file.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
			if( file.eof() )
			{
				objects.pop_back();
				break;
			}
		}
		file >> objects[ objects.size()-1 ].type;
		file >> objects[ objects.size()-1 ].value;
		file >> objects[ objects.size()-1 ].speed;
		file >> objects[ objects.size()-1 ].size;
		file >> objects[ objects.size()-1 ].pos_x;
		file >> objects[ objects.size()-1 ].pos_xk;
		file >> objects[ objects.size()-1 ].delay;
	}

	return true;
}