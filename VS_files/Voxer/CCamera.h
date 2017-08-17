/*
Name: camera.h
Desc: Obs³uga kamery
*/

#ifndef CCamera_h
#define CCamera_h

class CCamera
{
private:
	// K¹t obrotu kamery
	double AngleX, AngleY, AngleZ;

	// Prêdkoœæ kamery, przyspieszenie i opór (powietrza)
	double Speed, Acceleration, Resistance;

public:
	// Pozycja kamery
	double PosX, PosY, PosZ;

	CCamera();
	~CCamera(){}
	// Obraca kamerê o k¹t (w stopniach): angle_x (oœ X), angle_y (oœ Y), angle_z (oœ Z)
	void Rotate( double x, double y, double z );

	// Ustawia prêdkoœæ
	void SetSpeed( double speed );

	// Ustawia przyspieszenie
	void SetAcceleration( double acceleration );

	// Ustawia opór (powietrza)
	void SetResistance( double resistance );

	// Oblicza prêdkoœæ
	void CalculateSpeed( double DeltaTime );

	// Ustawia pozycjê
	void SetPos( double x, double y, double z );

	// Ustawia obrót kamery
	void SetRotate( double x, double y, double z );

	// Przesuwa kamerê o: pos_x (oœ X), pos_y (oœ Y), pos_z (oœ Z)
	void Move( double x, double y, double z );

	void MoveForward( void );
	void MoveBackward( void );
	void MoveLeft( void );
	void MoveRight( void );
	void MoveUp( void );
	void MoveDown( void );

	// Ustawia kamerê (u¿ywaæ bezpoœrednio przed rozpoczêciem renderowania)
	void UpdateScene( void );
};

#endif