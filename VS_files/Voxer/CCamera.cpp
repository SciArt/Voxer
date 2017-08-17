#include "declarations.h"
#include "CCamera.h"
#include <cmath>

#define PI 3.14159265

CCamera::CCamera()
{
	// Pozycja kamery
	PosX = PosY = PosZ = 0.0;
	// K�t obrotu kamery
	AngleX = AngleY = AngleZ = 0.0;
	// Pr�dko�� kamery
	Speed = 1.0;

	Acceleration = 0.0;
	Resistance = 0.5;
}

// Obraca kamer� o k�t (w stopniach): angle_x (o� X), angle_y (o� Y), angle_z (o� Z)
void CCamera::Rotate( double x, double y, double z )
{
	AngleX += x;
	AngleY += y;
	AngleZ += z;

	if(AngleX >= 360.0)
		AngleX -= 360.0;
	if(AngleX <= -360.0)
		AngleX += 360.0;

	if(AngleY >= 360.0)
		AngleY -= 360.0;
	if(AngleY <= -360.0)
		AngleY += 360.0;

	if(AngleZ >= 360.0)
		AngleZ -= 360.0;
	if(AngleZ <= -360.0)
		AngleZ += 360.0;
}

// Ustawia pr�dko��
void CCamera::SetSpeed( double speed )
{
	Speed = speed;
}

// Oblicza pr�dko��
void CCamera::CalculateSpeed( double DeltaTime )
{
	Speed = Speed + (Acceleration - Resistance) * DeltaTime;
}

// Ustawia przyspieszenie
void CCamera::SetAcceleration( double acceleration )
{
	Acceleration = acceleration;
}

// Ustawia op�r (powietrza)
void CCamera::SetResistance( double resistance )
{
	Resistance = resistance;
}

// Ustawia pozycj�
void CCamera::SetPos( double x, double y, double z )
{
	PosX = x;
	PosY = y;
	PosZ = z;
}

// Ustawia obr�t kamery
void CCamera::SetRotate( double x, double y, double z )
{
	AngleX = x;
	AngleY = y;
	AngleZ = z;
}

// Przesuwa kamer� o: pos_x (o� X), pos_y (o� Y), pos_z (o� Z)
void CCamera::Move( double x, double y, double z )
{
	PosX += x;
	PosY += y;
	PosZ += z;
}

void CCamera::MoveForward( void )
{
	PosX -= sin( AngleY * PI/180 ) * cos( AngleX * PI/180 ) * Speed;
	PosY += sin( AngleX * PI/180 ) * Speed;
	PosZ += cos( AngleY * PI/180 ) * cos( AngleX * PI/180 ) * Speed;
}

void CCamera::MoveBackward( void )
{
	PosX += sin( AngleY * PI/180 ) * cos( AngleX * PI/180 ) * Speed;
	PosY -= sin( AngleX * PI/180 ) * Speed;
	PosZ -= cos( AngleY * PI/180 ) * cos( AngleX * PI/180 ) * Speed;
}

void CCamera::MoveLeft( void )
{
	PosX += sin((AngleY+90) * PI/180) * Speed;
	PosZ += -cos((AngleY+90) * PI/180) * Speed;
}

void CCamera::MoveRight( void )
{
	PosX += -sin((AngleY+90) * PI/180) * Speed;
	PosZ += cos((AngleY+90) * PI/180) * Speed;
}

void CCamera::MoveUp( void )
{
	PosY -= Speed;
}

void CCamera::MoveDown( void )
{
	PosY += Speed;
}

// Ustawia kamer� (u�ywa� bezpo�rednio przed rozpocz�ciem renderowania)
void CCamera::UpdateScene( void )
{
	glRotated( AngleZ, 0.0, 0.0, 1.0 );
	glRotated( AngleX, 1.0, 0.0, 0.0 );
	glRotated( AngleY, 0.0, 1.0, 0.0 );
	

	glTranslated( PosX, PosY, PosZ );
}