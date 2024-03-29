#pragma once
#include "Pieza.h"
#include "ETSIDI.h"
#include "freeglut.h"
#include "Tablero.h"
using ETSIDI::SpriteSequence;




class Peon : public Pieza
{
	SpriteSequence sprite1{ "imagenes/peonblanco_.png", 1 };
	SpriteSequence sprite2{ "imagenes/peonnegro_.png", 1 };
	//int x, y;
	//int numero;

public:
	// A�ADIR VECTOR 2D
	// Vector2D posicion;

	Peon(char _color) {
		color = _color;
		tipo = TipoPieza(peon);
		sprite1.setCenter(-0.5, -0.5); //blancas
		sprite1.setSize(4, 4);
		sprite2.setCenter(-0.5, -0.5);
		sprite2.setSize(4, 4);

	}
	

	virtual~Peon(){};


	
	void dibuja() override ;

	// PRUBEBA
	bool mover(int xInicial, int yInicial, int xFinal, int yFinal, bool ocupado, Tablero& t) override ;

	// FUNCIONES DEL PEON
	/*
	void setPos(float ix, float iy);
	float getPosX();
	float getPosY();
	void mover();

	*/

};


