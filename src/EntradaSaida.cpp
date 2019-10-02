#include <string.h>
#include <stdio.h>
#include "../include/EntradaSaida.h"

int EntradaSaida::inicializa(){


	setTamanho({800,608,16});
	camera.setTamanho({800,608,16});
	janelaLargura = tamanho.x;
	janelaAltura = tamanho.y;
	strcpy(janelaNome,"queJogo");


	//inicia o sdl
	if(SDL_Init( SDL_INIT_VIDEO ) < 0 ){
		fprintf(stderr, "Falhei em iniciar a sdl\n");
		return 0;
	}
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY,"0")){
		fprintf(stderr, "Aviso! algo estranho aconteceu com a sdl hint (eu sla qq isso significa, na real n muda nada)\n");
	}
	//inicia a janela
	janela = SDL_CreateWindow( janelaNome, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (unsigned int)janelaLargura, (unsigned int)janelaAltura, SDL_WINDOW_SHOWN );
	if(janela == NULL){
		fprintf(stderr, "Não consegui instanciar uma janela SDL Error: %s\n", SDL_GetError());

	}
	//inicia o render
	render = SDL_CreateRenderer( janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC  );
	if( render == NULL ){
		fprintf(stderr,"Erro ao criar o render! SDL Error: %s\n", SDL_GetError());	
	} 
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00);

	textura = SDL_CreateTexture( render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, janelaLargura*2, janelaLargura*2 );
	texturaTela	= SDL_CreateTexture( render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, janelaLargura, janelaLargura);

	SDL_SetTextureBlendMode(textura,SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(texturaTela,SDL_BLENDMODE_BLEND);


	criado = SDL_GetTicks();
	ultimaVezAtualizado = criado;

	seguindo = jogador;

	perspectiva.x = 64;
	perspectiva.y = 64;

	rectTela.x = 0;
	rectTela.y = 0;
	rectTela.w = janelaLargura;
	rectTela.h = janelaAltura;

	return 0;
}

int EntradaSaida::setTeclas(unsigned int *t){
	teclas = t;
	return 0;
}

void EntradaSaida::setTime(unsigned int* t){
	time = t;
	criado = *time;
	ultimaVezAtualizado = *time;
 	d("setei um time %i",*time);
}


void EntradaSaida::getEntradas(){

	tempoPassado = SDL_GetTicks() - *time; 
	*time += tempoPassado;

	while( SDL_PollEvent( &e ) != 0 ){
		if( e.type == SDL_QUIT ) exit(0);
	}

	currentKeyStates = SDL_GetKeyboardState( NULL );

	if(currentKeyStates[SDL_SCANCODE_RIGHT]){
		teclas[xmais] += tempoPassado;
	}
	else{
		teclas[xmais] = 0;
	}

	
	if(currentKeyStates[SDL_SCANCODE_LEFT]){
		teclas[xmenos] += tempoPassado;
	}
	else{
		teclas[xmenos] = 0;
	}
	
	if(currentKeyStates[SDL_SCANCODE_SPACE]){
		teclas[ymais] += tempoPassado;
	}
	else{
		teclas[ymais] = 0;
	}
	
	if(currentKeyStates[SDL_SCANCODE_LCTRL]){
		teclas[ymenos] += tempoPassado;
	}
	else{
		teclas[ymenos] = 0;
	}
	
	if(currentKeyStates[SDL_SCANCODE_UP]){
		teclas[zmais] += tempoPassado;
	}
	else{
		teclas[zmais] = 0;
	}
	
	if(currentKeyStates[SDL_SCANCODE_DOWN]){
		teclas[zmenos] += tempoPassado;
	}
	else{
		teclas[zmenos] = 0;
	}
	
	if(currentKeyStates[SDL_SCANCODE_Z]){
		teclas[funca] += tempoPassado;
	}
	else{
		teclas[funca] = 0;
	}
	
	if(currentKeyStates[SDL_SCANCODE_X]){
		teclas[funcb] += tempoPassado;
	}
	else{
		teclas[funcb] = 0;
	}
	

	
}


EntradaSaida::EntradaSaida(){

}

int EntradaSaida::setFase(Fase *f){
	fase = f;
}

int EntradaSaida::setJogador(Jogador *j){
	jogador = j;
}


void EntradaSaida::atualizaCamera(){
	// camera que segue o jogador e muda de tela (mais ou menos como os megamen do nes)

	Terreno* terreno = fase->getTerreno();
	coordenada tam =camera.getTamanho();
	tam.z = 48;
	camera.setTamanho(tam);


	coordenada novaPos;
	/*funciona bem, n mexe
	novaPos.x = seguindo->getPosicao().x/camera.getTamanho().x;
	novaPos.y = seguindo->getPosicao().y/camera.getTamanho().y;
	novaPos.x*= camera.getTamanho().x;
	novaPos.y*= camera.getTamanho().y;
	*/


	
	// Esses troço ai fazem o jodador ficar em diferentes posições na tela de ocordo com a posição do jogador na fase;
	
	// float offx = (float)(seguindo->getPosicao().x) / ((float)(fase->getTerreno()->getTamanhoX()));
	// offx = offx*janelaLargura*0.5;
	// offx -= jogador->getPosicao().z*((1/(float)2)-(jogador->getPosicao().x/(float)terreno->getTamanhoX()))*40;

	// float offy = (jogador->getPosicao().z*(((jogador->getPosicao().y/(float)terreno->getPico()))*16));
	// offy += (float)(seguindo->getPosicao().y) / ((float)(fase->getTerreno()->getPico()))*(janelaAltura*0.7);
	// offy += 20;
	// novaPos.x = seguindo->getPosicao().x-offx;
	// novaPos.y = seguindo->getPosicao().y-offy;

	// novaPos.z = seguindo->getPosicao().z-24; 

	//opção mais simples
	float off = (float)(seguindo->getPosicao().x) / (float)(fase->getTerreno()->getTamanhoX());
	off = off*janelaLargura;

	novaPos.x = seguindo->getPosicao().x-off;
	novaPos.y = seguindo->getPosicao().y-200;

	camera.setPosicao(novaPos);
	
	//DEBUG {
	#define DEBUG 0
		coordenada mul = terreno->getMultiplicador();

		novaPos = jogador->getPosicao();
		d("m(%i,%i,%i)",mul.x,mul.y,mul.z)
		d("j(%i,%i,%i)",novaPos.x,novaPos.y,novaPos.z)
		d("t(%i,%i,%i)",novaPos.x,terreno->getY(novaPos.x,novaPos.z),novaPos.z)
		d("tRAW(%i,%i,%i)",novaPos.x/mul.x,terreno->getYRaw(novaPos.x/mul.x,novaPos.z/mul.z)*mul.y,novaPos.z/mul.z)
	#define DEBUG 0
	//DEBUG }
}

//RENDER 3D :O
int EntradaSaida::renderiza(){

	int perspectiva = 16;

	d("entrei no renderiza");

	//limpo a tela
	SDL_SetRenderTarget( render, NULL );
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0 );
	SDL_RenderClear(render);

	//seto a textura, para eu trabalhar nela, e limpo
	SDL_SetRenderTarget( render, textura);
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0 );
	SDL_RenderClear(render);

	SDL_SetRenderTarget( render, texturaTela );
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0 );
	SDL_RenderClear(render);


	Terreno* terreno = fase->getTerreno();

	int i,j,k;
	int offsetX,offsetY;
	int multX, multY, multZ;
	int nroPlanos = terreno->getTamanhoZRaw(); ///camera.getTamanho().z;//not today :(
	int iniX,iniY,fimX,fimY;
	SDL_Rect canvas;
	SDL_Rect dest;

	canvas.x = 0;
	canvas.y = 0;


	//Material m = terreno.getMaterial();


	multX = terreno->getMultiplicador().x;
	multY = terreno->getMultiplicador().y;
	multZ = terreno->getMultiplicador().z;

	atualizaCamera();
	d("seguido = (%i,%i)",seguindo->getPosicao().x, seguindo->getPosicao().y)
	d("camera = (%i,%i)",camera.getPosicao().x, camera.getPosicao().y);
	d("irei renderizar %i planos", nroPlanos);
	d("camera é de tamando(%i,%i), canvas(%i,%i)",camera.getTamanho().x,camera.getTamanho().y,canvas.w,canvas.h)

	//loop que desenha no render
	for(i=0;i<=nroPlanos;i++){// varre cada plano xy;
		SDL_SetRenderTarget( render, textura );
		SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
		SDL_RenderClear(render);
			int distanceFromPlayer = jogador->getPosicao().z - i;
		fprintf(stderr,"distancia do jogador %i\n", distanceFromPlayer);
		
		//setar a cor e offset;
		SDL_SetRenderDrawColor( render, 20+(200/nroPlanos)*i ,20+(255/nroPlanos)*i , 20+(255/nroPlanos)*i, 255);
		

		offsetX = perspectiva*(nroPlanos-i);

		//offsetX =  -2*i; //jogador->getPosicao().z*i; //um 3d loco :)
		offsetY = perspectiva*(nroPlanos-i);

	
		//define o tamanho da cavas:
		canvas.h = camera.getTamanho().y+offsetY;
		canvas.w = camera.getTamanho().x+offsetX;

		if(distanceFromPlayer != 0){
			canvas.h += rand() % distanceFromPlayer;
			canvas.w += rand() % distanceFromPlayer;
		}
		d("canvas size: (%i,%i)",canvas.w,canvas.h)

		//encontra em que posição do terreno começa a desenhar ()
		iniX = camera.getPosicao().x - offsetX/2;
		iniY = camera.getPosicao().y - offsetY/2;
		d("iniTRU:(%i,%i)",iniX,iniY)


		fimX = iniX + camera.getTamanho().x + offsetX;//é arbitrario, mas é pro offset não quebrar a imagem
		fimY = iniY + camera.getTamanho().y + offsetY;
		d("fimTRU:(%i,%i)",fimX,fimY)


		iniX /= multX; // como cada pixel de terreno representa multx pixels printados, descubro qualpegar;
		iniY /= multY;
		d("iniPIX:(%i,%i)",iniX,iniY)

		fimX /= multX;
		fimY /= multY;

		iniX--; // isso é só pra ele printar um pouco mais q deve
		iniY--;

		fimX++;
		fimY++;

		// iniX e Y marcam as posições reais do inicio da tela render
		//


		//define o tamanho de um pixel printado;
		quadrado.h = multY;
		quadrado.w = multX;
		quadrado.x = 0;
		quadrado.y = 0-(iniY*multY);


		
		//desenha o terreno na textura:
		for(j=iniX; j<fimX; j++){

			int meio = abs(distanceFromPlayer) > 3 ? distanceFromPlayer : 1;
			meio *= jogador->getVelocidade().y/10;
			
			quadrado.h = terreno->getYRaw(j,i)*multY;
			if(meio != 0){quadrado.h += rand() % meio;} 

			if(quadrado.h > 0){
				quadrado.h -= (iniY*multY)+(iniY*multY)*-1;//evita flics 
				
				SDL_RenderFillRect( render, &quadrado);
			}	

			quadrado.x+=multX;

		}
		

		iniX *= multX;//posição real printada;
		iniY *= multY;//posição real printada;

		//define a posição do canvas:
		canvas.x = camera.getPosicao().x - iniX - offsetX/2;
		canvas.y = camera.getPosicao().y - iniY - offsetY/2;// - iniY;


		//verifica se o player está neste plano
		if( jogador->getPosicao().z == i){
			//printa ele
			//SDL_SetRenderDrawColor( render, 100+(255/nroPlanos)*i ,(200/nroPlanos)*i, (200/nroPlanos)*i, 255);
			quadrado.x = jogador->getPosicao().x - iniX;
			quadrado.y = jogador->getPosicao().y - iniY;
			quadrado.w = jogador->getTamanho().x;
			quadrado.h = jogador->getTamanho().y;
			SDL_RenderFillRect( render, &quadrado);
		}
		SDL_SetRenderTarget( render, texturaTela );
		SDL_RenderCopy( render, textura, &canvas, NULL);


	}

	SDL_SetRenderTarget( render, NULL );

	SDL_RenderCopyEx( render, texturaTela, NULL, NULL, 0, NULL, (SDL_RendererFlip) (SDL_FLIP_VERTICAL) );
	
	SDL_RenderPresent(render);
	SDL_Delay(1000/30);
}




// int EntradaSaida::renderiza(){

// 	d("entrei no renderiza");

// 	//limpo a tela
// 	SDL_SetRenderTarget( render, NULL );
// 	SDL_SetRenderDrawColor(render, 0, 0, 0, 0 );
// 	SDL_RenderClear(render);

// 	//seto a textura, para eu trabalhar nela, e limpo
// 	SDL_SetRenderTarget( render, textura);
// 	SDL_SetRenderDrawColor(render, 0, 0, 0, 0 );
// 	SDL_RenderClear(render);

// 	Terreno* terreno = fase->getTerreno();

// 	int i,j,k;
// 	int r,g,b;
// 	int offsetX,offsetY;
// 	int multX, multY, multZ;
// 	int nroPlanos = /*terreno->getTamanhoZRaw(); ///*/camera.getTamanho().z;//not today :(
// 	int iniX,iniY,fimX,fimY;
// 	SDL_Rect canvas;
// 	SDL_Rect dest;

// 	canvas.x = 0;
// 	canvas.y = 0;
// 	canvas.h = janelaAltura;
// 	canvas.w = janelaLargura;



// 	//Material m = terreno.getMaterial();


// 	multX = terreno->getMultiplicador().x;
// 	multY = terreno->getMultiplicador().y;
// 	multZ = terreno->getMultiplicador().z;

// 	atualizaCamera();
// 	d("seguido = (%i,%i)",seguindo->getPosicao().x, seguindo->getPosicao().y)
// 	d("camera = (%i,%i)",camera.getPosicao().x, camera.getPosicao().y);
// 	d("irei renderizar %i planos", nroPlanos);
// 	d("camera é de tamando(%i,%i), canvas(%i,%i)",camera.getTamanho().x,camera.getTamanho().y,canvas.w,canvas.h)

// 	//loop que desenha no render
// 	for(i=camera.getPosicao().z;i<=camera.getPosicao().z+nroPlanos;i++){// varre cada plano xy;

// 		//setar a cor e offset;
// 		r = (200/nroPlanos)*(i-camera.getPosicao().z);
// 		g = (255/nroPlanos)*(i-camera.getPosicao().z);
// 		b = (255/nroPlanos)*(i-camera.getPosicao().z);

// 		//if(jogador->getPosicao().z == i) r+=20;//realça o plano que o usuario está
// 		SDL_SetRenderDrawColor( render,r,g,b, 255);
		



// 		offsetX = ((1/(float)2)-(jogador->getPosicao().x/(float)terreno->getTamanhoX()))*40*i; // DA UM EFEITO 3D
// 		offsetY = ((jogador->getPosicao().y/(float)terreno->getPico()))*-16*i;	//DA UM EFEITO 3D
// 		//offsetX = -2*i; // fica isometrico, é mais facil de prever onde o jogador ficar se mudar de plano 
// 		//offsetY = -8*i; // isometrico
	
// 		//define o tamanho da cavas:
		
// 		d("canvas size: (%i,%i)",canvas.w,canvas.h)

// 		//encontra em que posição do terreno começa a desenhar ()
// 		iniX = camera.getPosicao().x;
// 		iniY = camera.getPosicao().y;
// 		d("iniTRU:(%i,%i)",iniX,iniY)


// 		fimX = iniX + camera.getTamanho().x + multX*nroPlanos;//é arbitrario, mas é pro offset não quebrar a imagem
// 		fimY = iniY + camera.getTamanho().y + multY*nroPlanos;
// 		d("fimTRU:(%i,%i)",fimX,fimY)


// 		iniX /= multX; // como cada pixel de terreno representa multx pixels printados, descubro qualpegar;
// 		iniY /= multY;
// 		d("iniPIX:(%i,%i)",iniX,iniY)

// 		fimX /= multX;		
// 		fimY /= multY;

// 		iniX = 0;
// 		iniY = 0;

// 		fimY = terreno->getPico();
// 		fimX = terreno->getTamanhoXRaw();

// 		// iniX-=20;
// 		// iniY-=20;

// 		// fimX+=10;
// 		// fimY+=10;

// 		// iniX e Y marcam as posições reais do inicio da tela render


// 		//define o tamanho de um pixel printado;
// 		quadrado.h = multY;
// 		quadrado.w = multX;
// 		quadrado.x = offsetX;
// 		quadrado.y = 0-(iniY*multY)+offsetY;

		
// 		//desenha o terreno na textura:
// 		for(j=iniX; j<fimX; j++){

// 			// linha guia
// 			// if(jogador->getPosicao().x-j*multX < multX && jogador->getPosicao().x-j*multX >= 0)
// 			// SDL_SetRenderDrawColor( render,r+20,g,b, 255);

// 			quadrado.h = terreno->getYRaw(j,i)*multY;

// 			if(quadrado.h > 0){
// 				quadrado.h -= (iniY*multY)+(iniY*multY)*-1;//evita flics 
// 				SDL_RenderFillRect( render, &quadrado);
// 			}
// 			// if(jogador->getPosicao().x-j*multX < multX && jogador->getPosicao().x-j*multX >= 0)
// 			// SDL_SetRenderDrawColor( render,r,g,b, 255);	

// 			quadrado.x+=multX;

// 		}

		

// 		iniX *= multX;//posição real printada;
// 		iniY *= multY;//posição real printada;

// 		//define a posição do canvas:

// 			canvas.x = camera.getPosicao().x - iniX;

// 			canvas.y = camera.getPosicao().y - iniY;

// 		/*
// 		//mostra uma linha guia
// 		SDL_SetRenderDrawColor( render,r+60,g,b, 255);
// 		SDL_RenderDrawLine( render, jogador->getPosicao().x - iniX + offsetX, 0,  jogador->getPosicao().x - iniX + offsetX, terreno->getY( jogador->getPosicao().x,i)+offsetY+1-iniY);
// 		SDL_SetRenderDrawColor( render,r,g,b, 255);
// 		*/

// 		//verifica se o player está neste plano
// 		if( jogador->getPosicao().z == i){
// 			//printa ele
// 			//SDL_SetRenderDrawColor( render, 100+(255/nroPlanos)*i ,(200/nroPlanos)*i, (200/nroPlanos)*i, 255);
// 			quadrado.x = jogador->getPosicao().x - iniX + offsetX;
// 			quadrado.y = jogador->getPosicao().y - iniY + offsetY;
// 			quadrado.w = jogador->getTamanho().x;
// 			quadrado.h = jogador->getTamanho().y;
// 			SDL_RenderFillRect( render, &quadrado);
// 		}

// 	}

// 	if(canvas.x < 0) canvas.x = 0;
// 	if(canvas.y < 0) canvas.y = 0;

// 	SDL_SetRenderTarget( render, NULL );

// 	SDL_RenderCopyEx( render, textura, &canvas, NULL, 0, NULL, (SDL_RendererFlip) (SDL_FLIP_VERTICAL) );
	
// 	SDL_RenderPresent(render);
// 	#define DEBUG 1
// 	d("tempo passado: %i", tempoPassado)

// 	SDL_Delay(1000/30);
// }


/*
void EntradaSaida::atualizaCamera(){
	// //verifica se o objeto seguido esta dentro das bordas
	// if(!bordas.estaDentro(seguindo->getPosicao()){
	// 	//se estiver fora, verifica movimento e centra o objeto
//aproach mais simples, a camera estara sempre com o player no centro

	d("entrei no atualizaCamera()")
	coordenada novaPos;

	d("tentarei pegar a posição do seguido")
	novaPos.x = seguindo->getPosicao().x - tamanho.x/2;
	novaPos.y = seguindo->getPosicao().y - tamanho.y/2;
	novaPos.z = seguindo->getPosicao().z - tamanho.z/2;
	d("consegui")

	camera.setPosicao(novaPos);

}
*/


