#ifndef COORDENADA_H
#define COORDENADA_H

typedef struct Coordenanda coordenada;
struct Coordenanda{
	int x;
	int y;
	int z;

	// coordenada soma(coordenada c){
	// 	coordenada resultado;

	// 	resultado.x = x + c.x;
	// 	resultado.y = y + c.y;
	// 	resultado.z = z + c.z;

	// 	return resultado;
	// }
};

typedef struct CoordenandaD Dcoordenada;
struct CoordenandaD{
	double x;
	double y;
	double z;

};

#endif
/*
	|y
	|
	|
	|   z
	|  /
	| /
	|/___________x
*/