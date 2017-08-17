/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CMesh.h
// Desc.: Klasa opisuj�ca model 3D
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CMesh_h
#define CMesh_h

#include "declarations.h"

// Struktura opisuj�ca wierzcho�ek 3D
struct vertex3D
{
	double x;
	double y;
	double z;
};

// Struktura opisuj�ca wierzcho�ek 2D
struct vertex2D
{
	double x;
	double y;
};

// Struktura opisuj�ca �ciank� (tr�jk�t)
struct face
{
	vertex3D* v1; vertex3D* vn1; vertex2D* vt1;
	vertex3D* v2; vertex3D* vn2; vertex2D* vt2;
	vertex3D* v3; vertex3D* vn3; vertex2D* vt3;
};

// Klasa modelu 3D
class CMesh
{
	private:
		std::vector< vertex3D > v;	// Wsp�rz�dne wierzcho�k�w
		std::vector< vertex2D > vt;	// Wsp�rz�dne tekstur
		std::vector< vertex3D > vn;	// Normalne

		std::vector< face > f; // �cianki
		
		void CreateList(); // Tworzenie listy wy�wietlania

	public:
		GLuint texture; // Tekstura
		GLuint MeshList; // Lista wy�wietlania
		double x, y, z; // Pozycja
		double ax, ay, az; // Obr�t
		double sx, sy, sz; // Skala

		CMesh();
		~CMesh();

		void Draw(); // Rysowanie
		bool Load( char* file_model, char* file_texture ); // Wczytywanie
};

#endif