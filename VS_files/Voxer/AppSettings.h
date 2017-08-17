/////////////////////////////////////////////////////////////////////////////////////////////
// Name: AppSettings.h
// Desc.: Struktura zawieraj¹ca ustawienia aplikacji
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AppSettings_h
#define AppSettings_h

// Struktura zawieraj¹ca ustawienia aplikacji
struct AppSettings 
{
	bool fullscreen;	// Tryb pe³noekranowy
	unsigned int src_width, src_height;	// Rozdzielczoœæ okna (0 dla rozdzielczoœci optymalnej/maksymalnej)
	const char* title;	// Tytu³ okna
	unsigned int MultiSampleSamples;	// Iloœæ próbek dla multipróbkowania
};

#endif