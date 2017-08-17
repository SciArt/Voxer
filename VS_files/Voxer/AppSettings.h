/////////////////////////////////////////////////////////////////////////////////////////////
// Name: AppSettings.h
// Desc.: Struktura zawieraj�ca ustawienia aplikacji
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AppSettings_h
#define AppSettings_h

// Struktura zawieraj�ca ustawienia aplikacji
struct AppSettings 
{
	bool fullscreen;	// Tryb pe�noekranowy
	unsigned int src_width, src_height;	// Rozdzielczo�� okna (0 dla rozdzielczo�ci optymalnej/maksymalnej)
	const char* title;	// Tytu� okna
	unsigned int MultiSampleSamples;	// Ilo�� pr�bek dla multipr�bkowania
};

#endif