/////////////////////////////////////////////////////////////////////////////////////////////
// Name: AppSettings.h
// Desc.: Struktura zawierająca ustawienia aplikacji
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AppSettings_h
#define AppSettings_h

// Struktura zawierająca ustawienia aplikacji
struct AppSettings 
{
	bool fullscreen;	// Tryb pełnoekranowy
	unsigned int src_width, src_height;	// Rozdzielczość okna (0 dla rozdzielczości optymalnej/maksymalnej)
	const char* title;	// Tytuł okna
	unsigned int MultiSampleSamples;	// Ilość próbek dla multipróbkowania
};

#endif