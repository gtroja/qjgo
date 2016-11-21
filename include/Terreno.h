#ifndef TERRENO_H
#define TERRENO_H
#include "Defines.h"

#include "Coordenada.h"

class Terreno{
public:
	Terreno();
	~Terreno();
	void setTamanho(coordenada tam);
	int carregaTerreno(char* arquivo);
	int getY(int x, int y);
	//unsigned char set(int x, int y);
	unsigned char getYRaw(int x, int y);
	int getTamanhoX();
	int getTamanhoZ();
	int getTamanhoXRaw();
	int getTamanhoZRaw();
	int getPico();
	int setMultiplicador(coordenada m);
	coordenada getMultiplicador();
	//Terreno getCrop(Bloco onde);
private:
	coordenada multiplicador;
	int tamanhoZ, tamanhoX, pico;
	unsigned char** d;

	bool terrenoCarregado;
	
};
#endif