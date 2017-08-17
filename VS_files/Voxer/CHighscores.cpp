/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CHighscores.cpp
// Desc.: Ekran z najwy�szymi wynikami
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CHighscores.h"

#include "CCursor.h"
#include "CMesh.h"
#include "CButton.h"

CHighscores::CHighscores()
{
	background = NULL;
	close = NULL;

	// Resetowanie listy punkt�w i nazw graczy
	for( unsigned int i = 0; i < 10; ++i )
	{
		score_txt[i] = -1;
		name_txt[i].clear();
	}
}

CHighscores::~CHighscores()
{
	if( background )
		delete background;
	if( close )
		delete close;
}

bool CHighscores::init()
{
	// Wczytywanie t�a
	background = new CMesh();
	if( !background )
		return false;
	if( !background->Load( "Highscores/Graphic/background.obj","Highscores/Graphic/background.png" ) )
		return false;

	// Wczytywanie przycisku close
	close = new CButton();
	if( !close )
		return false;
	if( !close->Load( "Highscores/Graphic/close.obj", "Highscores/Graphic/close1.png" ) )
		return false;
	if( !close->LoadTex2( "Highscores/Graphic/close2.png" ) )
		return false;
	close->x = -1.975;
	close->y = 1.347;
	close->z = 0.001;
	close->width = 0.306;
	close->height = 0.067;

	// Od�wie�enie listy wynik�w
	refresh();

	return true;
}

void CHighscores::draw()
{
	background->Draw(); // Rysowanie t�a
	close->Draw(); // Rysowanie przycisku

	// Kolor tekstu
	SDL_Color text_color;
	text_color.a = 0; text_color.r = 0; text_color.g = 65; text_color.b = 145;
	
	// Wy�wietlanie wynik�w
	for( unsigned int i = 0; i < 10; ++i )
	{
		if( score_txt[i] == -1 ) // Je�li brak wyniku to zako�cz wy�wietlanie
			break;

		// Wy�wietlanie nazw graczy
		convert.str("");
		convert << "       " << name_txt[i] << "       ";
		name[i].RenderText( convert.str().c_str(), text_color, F_Center, 0.12, 1.2, -0.5, 0.878 - (i * 0.25), 0.0 );

		// Wy�wietlanie liczby punkt�w
		convert.str("");
		convert << "       " << score_txt[i] << "       ";
		score[i].RenderText( convert.str().c_str(), text_color, F_Center, 0.12, 1.2, 1.244, 0.878  - (i * 0.25), 0.0 );
	}
}

bool CHighscores::logic( CCursor *cursor )
{
	if( close->Logic( cursor ) ) // Obs�uga przycisku
		return true;

	return false;
}

bool CHighscores::refresh()
{
	// Resetowanie listy puntk�w i nazw graczy
	for( unsigned int i = 0; i < 10; ++i )
	{
		score_txt[i] = -1;
		name_txt[i].clear();
	}

	std::ifstream file( "Highscores/highscores.txt" ); // Otwieranie pliku
	if( !file )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Data loading error...", "Highscores/highscores.txt", NULL);
		return false;
	}

	// Zmienne tymczasowe
	std::string name_tmp;
	int score_tmp = -1;
	bool file_damaged = false; // Flaga uszkodzenia pliku

	for( int i = 0; i < 10; ++i )
	{
		while( !file.eof() ) // Do ko�ca pliku
		{
			// Wczytywanie wyniku
			file >> name_tmp;
			file >> score_tmp;

			if( file.fail() ) // Je�li b��d wczytywania
			{
				if( !file.eof() ) // I brak ko�ca pliku
					file_damaged = true; // Plik uszkodzony
				file.clear(); // Czyszczenie flag pliku
				// Przeskoczenie do nast�pnej linijki pliku
				file.ignore( std::numeric_limits < std::streamsize >::max(), '\n' ); 
				continue;
			}

			// Sortowanie wynik�w
			if( i-1 >= 0 && score_tmp > score_txt[i-1] )
				continue;
			if( i-1 >= 0 && score_tmp == score_txt[i-1] )
			{
				for( unsigned int j = 0; j < 10; ++j )
				{
					if( score_txt[j] == score_tmp && name_txt[j] == name_tmp )
						goto przerwanie;
				}
				name_txt[i] = name_tmp;
				score_txt[i] = score_tmp;
				
				przerwanie:
				continue;
			}
			if( score_txt[i] < score_tmp )
			{
				name_txt[i] = name_tmp;
				score_txt[i] = score_tmp;
			}
		}
		
		file.clear(); // Czyszczenie flag pliku
		file.seekg(0); // Skok na pocz�tek pliku
	}

	if(file_damaged)
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Data loading error...", "Highscores/highscores.txt - file damaged", NULL);

	file.close();

	return true;
}