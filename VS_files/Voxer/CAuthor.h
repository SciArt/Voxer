/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CAuthor.h
// Desc.: Ekran z informacjami o autorze
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAuthor_h
#define CAuthor_h

// Deklracaje zapowiadaj¹ce
class CCursor;
class CButton;
class CMesh;
class CGame;

class CAuthor
{
private:
	CMesh *background; // T³o
	CButton *close; // Przycisk close
	CGame *game; // WskaŸnik do klasy nadrzêdnej
public:
	CAuthor();
	~CAuthor();

	bool init( CGame *game ); // Inicjalizacja
	void draw(); // Rysowanie
	bool logic( CCursor *cursor, int DeltaTime ); // Czêœæ logiczna
};

#endif