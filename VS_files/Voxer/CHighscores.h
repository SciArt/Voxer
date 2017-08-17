/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CHighscores.h
// Desc.: Ekran z najwy�szymi wynikami
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////


#ifndef CHighscores_h
#define CHighscores_h

#include "declarations.h"
#include "CFont.h"

// Deklaracje zapowiadaj�ce
class CCursor;
class CButton;
class CMesh;

class CHighscores
{
private:
	CMesh *background; // T�o
	CButton *close; // Przycisk close
	std::ostringstream convert; // Zmienna tymczasowa do konwertowania tekstu
	std::string name_txt[10]; // Lista nazw graczy
	int score_txt[10]; // Lista puntk�w
	CFont name[10]; // Lista napis�w nazw graczy
	CFont score[10]; // Lista napis�w punkt�w
public:
	CHighscores();
	~CHighscores();

	bool init(); // Inicjalizacja
	void draw(); // Rysowanie
	bool refresh(); // Od�wie�enie wynik�w
	bool logic( CCursor *cursor ); // Cz�� logiczna
};

#endif