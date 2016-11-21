#include "../include/Fase.h"

int Fase::adicionaTerreno(char* arquivo, coordenada mult, coordenada onde){

	terreno.carregaTerreno(arquivo);
	terreno.setMultiplicador(mult);

	//reutilizando variavel, multi aqui significa tamanho
	mult.z = terreno.getTamanhoZ();
	mult.x = terreno.getTamanhoX();
	mult.y = terreno.getPico();

	skybox.setPosicao(onde);
	skybox.setTamanho(mult);


}

Terreno* Fase::getTerreno(){
	return &terreno;
}

int Fase::setJogador(Jogador *j){
	jogador = j;
}
void Fase::inicializa(){
	jogador->setPosicao(inicio);

}

void Fase::setInicio(coordenada c){
	inicio = c;
}
void Fase::setFim(coordenada c){
	fim = c;
}
coordenada Fase::getInicio(){
	return inicio;
}
coordenada Fase::getFim(){
	return fim;
}
