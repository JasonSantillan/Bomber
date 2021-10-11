#include "GameManager.h"


GameManager::GameManager() {
	gWindow = nullptr;
	gRenderer = nullptr;
	texturaBomber = nullptr;
	texturaBomber2 = nullptr;
}

bool GameManager::onInit() {

	//Initialization flag
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("Bomber Man USFX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{

			////Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == nullptr)
			{
				cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
};

bool GameManager::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	gTexture = loadTexture("texture.png");
	if (gTexture == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}

	return success;
}


void GameManager::close()
{
	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = nullptr;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gRenderer = nullptr;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


int GameManager::onExecute() {		//Ejecutar el Programa
	if (!onInit()) {				//inicializar la Ventana y Opciones de Renderización
		cout << "Failed to initialize!" << endl;
		return -1;
	}
	else
	{
		//Load media
		if (!loadMedia())			//Transforma la imagen que tenemos en otra imagen que reciba el SDL
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event event;

			texturaBomber = new Texture(gRenderer);					//creamos una textura en texturaBomber
			texturaBomber->loadFromImage("resources/bomber.bmp");	//le damos una imagen a la textura

			texturaBomber2 = new Texture(gRenderer);
			texturaBomber2->loadFromImage("resources/bomber.bmp");

			Bomber* b1 = new Bomber(texturaBomber);					//cola?
			Bomber* b2 = new Bomber(texturaBomber2);
			

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&event) != 0)
				{
					//User requests quit
					if (event.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				//Clear screen
				//SDL_RenderClear(gRenderer);

				//Render texture to screen
				//SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
			
				
				////Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Update screen

				/*onLoop();
				onRender();*/
				b1->render();
				b2->setPosicionX(rand() % SCREEN_WIDTH);
				b2->setPosicionY(rand() % SCREEN_HEIGHT);
				b2->render();

				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;

}

SDL_Texture* GameManager::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}