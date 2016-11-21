#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/Universo.h"

Universo::Universo(){
	d("E disse Deus: Haja luz; e houve luz.")
	time = 0;
}


void Universo::ligaTudo(){
	d(">entrei no ligatudo()");

	//Dummy gera as informações para teste
	dummy();
	//leArquivos();

	teclas = (unsigned int*)malloc(nroBotoes*sizeof(unsigned int));

	io.setTeclas(teclas);
	io.setTime(&time);
	io.setFase(&fase);
	io.setJogador(&jogador);

	jogador.setTeclas(teclas);
	jogador.setTime(&time);
	jogador.setFase(&fase);

	fase.setTime(&time);
	fase.setJogador(&jogador);


	fase.inicializa();
	io.inicializa();
	jogador.inicializa();
	d(">sai do liga tudo");	
}

void Universo::loop(){
	d(">entrei no loop()");
	
	ligaTudo();

	while(/*estado = rodando*/1){
 		io.getEntradas();
 		jogador.atualiza();
 		fase.atualiza();
 		io.renderiza();
	}

	
}

void Universo::dummy(){
	d("entrei no dummy()");
	//função que substitui leitura de dados do jogo por arquivo
	fase.adicionaTerreno("teste.bmp",{16,16,1},{0,0,0});
	fase.setInicio({16,800,1});
	d("adicinei terreno");


	//fase.setInicioFim()







}

Universo::~Universo(){

}