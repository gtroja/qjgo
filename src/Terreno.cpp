#include "../include/Imagem.h"
#include "../include/Terreno.h"
Terreno::Terreno(){
	d("criado um terreno")
	terrenoCarregado = false;
}

int Terreno::carregaTerreno(char* arquivo){

	int i,j;
	setMultiplicador({0,0,0});
	Imagem1C *mapa;
	mapa = abreImagem1C(arquivo);
	if(mapa == NULL) return 1;
	tamanhoZ = mapa->altura;
	tamanhoX = mapa->largura;
	d = mapa->dados;

	pico = d[0][0];

	for(i=0; i<tamanhoZ; i++){
		for(j=0; j<tamanhoX; j++){
			if(d[i][j]>pico) pico = (int)d[i][j];
		}
	}

	d("carreguei um mapa para o terreno")

	terrenoCarregado = true;
	return 0;
}

Terreno::~Terreno(){

	unsigned long i;

    for (i = 0; i < tamanhoZ; i++)
        free(d[i]);
	free(d);

}

int Terreno::getY(int x, int z){


	if(x < 0 || z < 0 || x >= tamanhoX*multiplicador.x || z >= tamanhoZ) return 0;

	return (multiplicador.x*getYRaw(x/multiplicador.x,z));

}

unsigned char Terreno::getYRaw(int x, int z){

	if(x < 0 || z < 0 || x >= tamanhoX || z >= tamanhoZ) return 0;

	return d[z][x];

}

int Terreno::getTamanhoZ(){
	return tamanhoZ*multiplicador.z;
}

int Terreno::getTamanhoX(){
	return tamanhoX*multiplicador.x;

}

int Terreno::getTamanhoZRaw(){
	return tamanhoZ;
}

int Terreno::getTamanhoXRaw(){
	return tamanhoX;

}

int Terreno::getPico(){
	return pico*multiplicador.y;
}

int Terreno::setMultiplicador(coordenada m){
	multiplicador = m;
}
coordenada Terreno::getMultiplicador(){
	return multiplicador;
}

// Terreno Terreno::getCrop(Bloco onde){
// 	int i,j;

// 	Terreno result;
// 	result.setTamanho(onde.getTamanho());
// 	result.setMultiplicador(multiplicador);

// 	for(i = onde.z/multiplicador.z+1; )

// }