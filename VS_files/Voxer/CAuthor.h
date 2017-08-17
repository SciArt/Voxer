/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CAuthor.h
// Desc.: Ekran z informacjami o autorze
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAuthor_h
#define CAuthor_h

// Deklracaje zapowiadaj�ce
class CCursor;
class CButton;
class CMesh;
class CGame;

class CAuthor
{
private:
	CMesh *background; // T�o
	CButton *close; // Przycisk close
	CGame *game; // Wska�nik do klasy nadrz�dnej
public:
	CAuthor();
	~CAuthor();

	bool init( CGame *game ); // Inicjalizacja
	void draw(); // Rysowanie
	bool logic( CCursor *cursor, int DeltaTime ); // Cz�� logiczna
};

#endif