#include "Tablero.h"
#include "Peon.h"
#include "Pieza.h"
#include "Caballo.h"
#include "Reina.h"
#include "Torre.h"
#include "Rey.h"
#include "Alfil.h"

Tablero::~Tablero()
{
	//pieza.destruirContenido();

	// Liberar memoria de las piezas
	/*
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			delete tablero[x][y];
		}
	}
	*/
}



void Tablero::dibuja() {

	gluLookAt(x_ojo, y_ojo, z_ojo, // posicion del ojo
		x_ojo, y_ojo, 0.0, // hacia que punto mira (0,0,0)
		0.0, 1.0, 0.0); // definimos hacia arriba (eje Y)


	// dibujo del tablero
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if ((x + y) % 2 == 0) {
				glColor3ub(93, 155, 155); // Color oscurito
			}
			else {
				glColor3ub(156, 208, 224); // Color clarito
			}
			glBegin(GL_QUADS);
			glVertex2i(x * cellSize, y * cellSize);
			glVertex2i((x + 1) * cellSize, y * cellSize);
			glVertex2i((x + 1) * cellSize, (y + 1) * cellSize);
			glVertex2i(x * cellSize, (y + 1) * cellSize);
			glEnd();

			// Dibujar la pieza en la casilla
			if (tablero[x][y] != nullptr) {
				glPushMatrix();
				glTranslatef(x * cellSize, y * cellSize, 0.1);
				tablero[x][y]->dibuja();
				glPopMatrix();
			}
		}
	}



}

void Tablero::inicializa() {


	x_ojo = 20;
	y_ojo = 20;
	z_ojo = 30; // habria q mirarlo bien


	


	tablero[1][0] = new Caballo('b');
	tablero[6][0] = new Caballo('b');
	tablero[1][7] = new Caballo('n');
	tablero[6][7] = new Caballo('n');
	tablero[3][0] = new Reina('b');
	tablero[3][7] = new Reina('n');
	tablero[0][0] = new Torre('b');
	tablero[7][0] = new Torre('b');
	tablero[0][7] = new Torre('n');
	tablero[7][7] = new Torre('n');
	tablero[4][0] = new Rey('b');
	tablero[4][7] = new Rey('n');
	tablero[2][0] = new Alfil('b');
	tablero[5][0] = new Alfil('b');
	tablero[2][7] = new Alfil('n');
	tablero[5][7] = new Alfil('n');

	for (int i = 0; i < 8; i++) {
		tablero[i][1] = new Peon('b'); //peones blancos en toda la fila 1
		tablero[i][6] = new Peon('n'); //peones negros en toda la fila 6
	}
}

int xInicial = -1, yInicial = -1;
int xFinal = -1, yFinal = -1;

void Tablero::onMouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Calcular la posici�n del clic en t�rminos de celdas del tablero
		int casillaX = x / 75;
		int casillaY = (600 - y) / 75;  // Convertir la coordenada y

		if (xInicial == -1 && yInicial == -1) {
			// Establecer la posici�n inicial del pe�n
			xInicial = casillaX;
			yInicial = casillaY;

			if (tablero[xInicial][yInicial] == nullptr) { //La casilla incial no tiene pieza
				xInicial = -1;
				yInicial = -1;
			}
			else if(tablero[xInicial][yInicial] != nullptr){
				if (turno % 2 != 0 && tablero[xInicial][yInicial]->obtenerColor() != 'b') {
					xInicial = -1;
					yInicial = -1;
				}

				if (turno % 2 == 0 && tablero[xInicial][yInicial]->obtenerColor() != 'n') {
					xInicial = -1;
					yInicial = -1;
				}

			}	
		}

		else {
			xFinal = casillaX;
			yFinal = casillaY;
			char color = tablero[xInicial][yInicial]->obtenerColor();
			TipoPieza tipo= tablero[xInicial][yInicial]->obtenerTipo();
			
			//if para ver si la casilla est� ocupada
			bool ocupado;
			int x = xFinal - xInicial;
			int y = yFinal - yInicial;
			int xI = xInicial, yI = yInicial;

			if (tablero[xFinal][yFinal] == nullptr) {
				ocupado = 0;
			}
			else if (tablero[xFinal][yFinal] != nullptr) {
				ocupado = 1;
				char color2 = tablero[xFinal][yFinal]->obtenerColor();
				if (color == color2) return;
			}


			if (!tablero[xInicial][yInicial]->mover(xInicial, yInicial, xFinal, yFinal, ocupado, *this)) {
				//return; // Movimiento inv�lido, salir de la funci�n
				xInicial = -1;
				yInicial = -1;
				xFinal = -1;
				yFinal = -1;
			}
			else { // La casilla est� vac�a
				// Mover el pe�n a la posici�n final
				delete tablero[xFinal][yFinal];
				tablero[xFinal][yFinal] = nullptr; // Eliminar la pieza de la posici�n final si existe
				delete tablero[xInicial][yInicial];
				tablero[xInicial][yInicial] = nullptr; // Establecer la posici�n inicial como vac�a

				if (tipo == peon) {
					tablero[xFinal][yFinal] = new Peon(color);
				}
				else if (tipo == caballo) {
					tablero[xFinal][yFinal] = new Caballo(color);
				}
				else if (tipo == reina) {
					tablero[xFinal][yFinal] = new Reina(color);
				}
				else if (tipo == torre) {
					tablero[xFinal][yFinal] = new Torre(color);
				}
				else if (tipo == rey) {
					tablero[xFinal][yFinal] = new Rey(color);
				}

				else if (tipo == alfil) {
					tablero[xFinal][yFinal] = new Alfil(color);
				}

				
				// Reiniciar las posiciones inicial y final del pe�n
				xInicial = -1;
				yInicial = -1;
				xFinal = -1;
				yFinal = -1;
				turno++;
				// Redibujar el tablero con el pe�n movido
				glutPostRedisplay();
			}
		}
	}
}




