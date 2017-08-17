/*
Name: camera.h
Desc: Obs�uga kamery
*/

#ifndef CCamera_h
#define CCamera_h

class CCamera
{
private:
	// K�t obrotu kamery
	double AngleX, AngleY, AngleZ;

	// Pr�dko�� kamery, przyspieszenie i op�r (powietrza)
	double Speed, Acceleration, Resistance;

public:
	// Pozycja kamery
	double PosX, PosY, PosZ;

	CCamera();
	~CCamera(){}
	// Obraca kamer� o k�t (w stopniach): angle_x (o� X), angle_y (o� Y), angle_z (o� Z)
	void Rotate( double x, double y, double z );

	// Ustawia pr�dko��
	void SetSpeed( double speed );

	// Ustawia przyspieszenie
	void SetAcceleration( double acceleration );

	// Ustawia op�r (powietrza)
	void SetResistance( double resistance );

	// Oblicza pr�dko��
	void CalculateSpeed( double DeltaTime );

	// Ustawia pozycj�
	void SetPos( double x, double y, double z );

	// Ustawia obr�t kamery
	void SetRotate( double x, double y, double z );

	// Przesuwa kamer� o: pos_x (o� X), pos_y (o� Y), pos_z (o� Z)
	void Move( double x, double y, double z );

	void MoveForward( void );
	void MoveBackward( void );
	void MoveLeft( void );
	void MoveRight( void );
	void MoveUp( void );
	void MoveDown( void );

	// Ustawia kamer� (u�ywa� bezpo�rednio przed rozpocz�ciem renderowania)
	void UpdateScene( void );
};

#endif