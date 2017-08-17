/////////////////////////////////////
// __      __                      //
// \ \    / /                      //
//  \ \  / /___ __  __ ___  _ __   //
//   \ \/ // _ \\ \/ // _ \| '__|  //
//    \  /| (_) |>  <|  __/| |     //
//     \/  \___//_/\_\\___||_|     //                       
//                                 //
/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// Name: main.cpp
// Desc.: Plik zawieraj�cy g��wn� funkcj� programu
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CApp.h"
#include "AppSettings.h"

int main( int argc, char *argv[] )
{
	CApp app;
	AppSettings settings;

	// Zerowanie i konfigurowanie ustawie� aplikacji
	ZeroMemory( &settings, sizeof( AppSettings ) );
	settings.fullscreen = 0;
	settings.src_width  = 0;
	settings.src_height = 0;
	settings.MultiSampleSamples = 4;
	settings.title = "Voxer || version 1.0 beta || Author: Gerard Wypych";

	// Inicjalizacja z zadanymi ustawieniami
	if( !app.init( settings ) )
		return -1;

	// Wykonywanie programu
	app.run();

	return 0;
}
