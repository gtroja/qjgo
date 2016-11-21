#include <stdio.h>
#include "../include/Jogador.h"
#include "../include/Defines.h"


Dcoordenada Jogador::getVelocidade(){
	return velocidade;
}

Dcoordenada Jogador::getVelocidadeMaxima(){
	return velocidadeMaxima;
}

Jogador::Jogador(){
	time = NULL;
	dposicao = {0,0,0};
	aceleracao = {50,-60,11};
	velocidade = {0,0,0};
	atrito = {10,0,0};
	velocidadeMaxima = {10,30,1};
};


#define DEBUG 1

void Jogador::atualiza(){

	d("velocidade: %f", velocidade.x);

	dposicao.x = posicao.x; 
	dposicao.y = posicao.y;
	dposicao.z = posicao.z;
	
	//pega as entradas
	tempoPassado = (float)(*time - ultimaVezAtualizado)/1000.0;

	if(teclas[xmais]){	
		// if(parado){
		// 	velocidade.x = velocidadeMaxima.x/2;
		// 	parado = false;
		// }
		velocidade.x += aceleracao.x*tempoPassado;
	}

	if(teclas[xmenos]){
		// if(parado){
		// 	velocidade.x = -1*velocidadeMaxima.x/2;
		// 	parado = false;
		// }
		velocidade.x -= aceleracao.x*tempoPassado;
	}
	if(teclas[ymais]){
		if(noChao && teclas[ymais] < 100){
			velocidade.y = velocidadeMaxima.y/2;
			noChao = false;
		}
		else{
			velocidade.y -= aceleracao.y*tempoPassado/2;// arbritario, mudar
		}

	}
	if(teclas[ymenos]){
		velocidade.y -= aceleracao.y*tempoPassado;

	}
	if(/*teclas[zmais] < 100 &&*/ teclas[zmais] > 0){
		posicao.z--;
		//teclas[zmais]+=10000;	
	}
	if(/*teclas[zmenos] < 100 && */teclas[zmenos] > 0){
		posicao.z++;
		//teclas[zmenos]+=10000;
	}
	if(teclas[funca]){	

	}
	if(teclas[funcb]){
		
	}

	//aplica atrito
	//por algum motivo ridiculo, qndo a velocidade é negativa o atrito funciona diferente
	
	if(!(teclas[xmais]||teclas[xmenos])&&noChao){
		velocidade.x -= (velocidade.x*atrito.x)*tempoPassado;//comportamento ruim
		
		if(velocidade.x>0){//aproach linear
			velocidade.x -= aceleracao.x/100 * tempoPassado;
			if(velocidade.x<0) velocidade.x = 0;
		}
		if(velocidade.x<0){
			velocidade.x += aceleracao.x/100 * tempoPassado;
			if(velocidade.x>0) velocidade.x = 0;
		}
	}
	// d("velocidade:(%f)",velocidade.x)
	// velocidade.y -= (velocidade.y*atrito.y)*tempoPassado;
	//aplica gravidade
	velocidade.y += aceleracao.y*tempoPassado;

	//aplica limites
	if(velocidade.y < 0 && velocidade.y*-1 > velocidadeMaxima.y){
		velocidade.y = velocidadeMaxima.y*-1;
	}
	if(velocidade.x < 0 && velocidade.x*-1 > velocidadeMaxima.x){
		velocidade.x = velocidadeMaxima.x*-1;
	}
	if(velocidade.x > velocidadeMaxima.x)velocidade.x = velocidadeMaxima.x;

	//move
	if(velocidade.x>1 || velocidade.x<-1){ // lida com problemas de precisao do double
		dposicao.x += velocidade.x;
	}
	dposicao.y += velocidade.y;

	coordenada antes = posicao;
	posicao.x = dposicao.x;
	posicao.y = dposicao.y;


	if(terreno->getY(posicao.x,posicao.z) >= posicao.y){
	if(velocidade.y<0){
		posicao.y = terreno->getY(posicao.x,posicao.z);
		velocidade.y = 0;
		noChao = true;
	}
		else posicao.x = antes.x;

	}
	if(velocidade.x<1 && velocidade.x>-1){
		parado = true;
	}


	ultimaVezAtualizado = *time;
}

void Jogador::setTeclas(unsigned int* t){
	teclas = t;
}

void Jogador::setFase(Fase *f){
	fase = f;
	terreno = fase->getTerreno();

}

void Jogador::inicializa(){
	setTamanho({16,32,1});
	setPosicao(fase->getInicio());
	dposicao.x = posicao.x; 
	dposicao.y = posicao.y;
	dposicao.z = posicao.z;
}

 void Jogador::setTime(unsigned int* t){
	time = t;
	criado = *time;
	ultimaVezAtualizado = *time;
 	d("setei um time %i",*time);
}
