#pragma once
#include<iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include "Bomber.h"

using namespace std;

const int SCREEN_WIDTH = 800;       //ancho y largo de la ventana
const int SCREEN_HEIGHT = 600;
  
class GameManager
{
private:
    //The window we'll be rendering to
    SDL_Window* gWindow;

    //The window renderer
    SDL_Renderer* gRenderer;

    //Current displayed texture
    SDL_Texture* gTexture = nullptr;

    Texture* texturaBomber;         //
    Texture* texturaBomber2;

public:
    GameManager();
	int onExecute(); //Método de Ejecución PRINCIPAL
    bool onInit();  //Método para inicializr la ventana secundario
    void close();
    bool loadMedia();   // AQUI cargamos la imagen que queremos que se muestre


    //Loads individual image as texture
    SDL_Texture* loadTexture(std::string path);

};
