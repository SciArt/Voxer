/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CLogic.h
// Desc.: Zawiera klas� odpowiedzialn� za cz�� logiczn�
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLogic_h
#define CLogic_h

#include "declarations.h"

// Deklaracje zapowiadaj�ce
class CApp;

class CLogic
{
	private:
		void CameraControl( void ); // Obs�uga sterowania kamer�
		SDL_Event ev; // Zdarzenia SDL'a
		int FPS_Buffer, FPS_ResetTime; // Zmienne do pomiaru klatek na sekund�
		int DT_Start; // Cza pocz�tkowy pomiaru DeltaTime

	public:
		bool mouse_release;	bool mouse_center; // Flagi sterowania kamer� za pomoc� myszki
		bool debug_mode; // Flaga trybu debugowania (wolnej kamery)
		bool draw_FPS; // Flaga rysowania klatek na sekudn�

		int DeltaTime; // Up�yw czasu
		int FPS; // Liczba klatek na sekunde

		CApp *app; // Wska�nik na klas� nadrz�dn� CApp
		CLogic(CApp *app){this->FPS = 0; this->FPS_Buffer = 0; this->FPS_ResetTime = 1000; this->DeltaTime = 0; this->app = app; mouse_release = true; mouse_center = true; debug_mode = false; draw_FPS = false;}
		~CLogic(){}

		bool check_events( void ); // Sprawdzanie zdarze�

		// Pomiar up�ywu czasu
		void DT_Begin( void ); // Rozpocz�cie pomiaru up�ywu czasu
		void DT_End( void ); // Zako�czenie pomiaru up�ywu czasu
		const int DT_Return( void ); // Zwr�cenie up�ywu czasu
};

#endif