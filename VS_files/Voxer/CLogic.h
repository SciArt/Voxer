/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CLogic.h
// Desc.: Zawiera klasê odpowiedzialn¹ za czêœæ logiczn¹
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLogic_h
#define CLogic_h

#include "declarations.h"

// Deklaracje zapowiadaj¹ce
class CApp;

class CLogic
{
	private:
		void CameraControl( void ); // Obs³uga sterowania kamer¹
		SDL_Event ev; // Zdarzenia SDL'a
		int FPS_Buffer, FPS_ResetTime; // Zmienne do pomiaru klatek na sekundê
		int DT_Start; // Cza pocz¹tkowy pomiaru DeltaTime

	public:
		bool mouse_release;	bool mouse_center; // Flagi sterowania kamer¹ za pomoc¹ myszki
		bool debug_mode; // Flaga trybu debugowania (wolnej kamery)
		bool draw_FPS; // Flaga rysowania klatek na sekudnê

		int DeltaTime; // Up³yw czasu
		int FPS; // Liczba klatek na sekunde

		CApp *app; // WskaŸnik na klasê nadrzêdn¹ CApp
		CLogic(CApp *app){this->FPS = 0; this->FPS_Buffer = 0; this->FPS_ResetTime = 1000; this->DeltaTime = 0; this->app = app; mouse_release = true; mouse_center = true; debug_mode = false; draw_FPS = false;}
		~CLogic(){}

		bool check_events( void ); // Sprawdzanie zdarzeñ

		// Pomiar up³ywu czasu
		void DT_Begin( void ); // Rozpoczêcie pomiaru up³ywu czasu
		void DT_End( void ); // Zakoñczenie pomiaru up³ywu czasu
		const int DT_Return( void ); // Zwrócenie up³ywu czasu
};

#endif