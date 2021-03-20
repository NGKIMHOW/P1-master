#include <iostream>
#include "Level1.h"
#include "GInput.h"
#include "car.h"
#include <string>
#include "GameStateManager.h"
#include <d3d9.h>
#include <d3dx9.h>

using namespace std;

Level1::Level1()
{
}

Level1::~Level1()
{
}

void Level1::init()
{
	//	Create sprite. Study the documentation. 	D3DXCreateSprite(GGraphic::getInstance()->d3dDevice, &sprite);
	D3DXCreateSprite(GGraphic::getInstance()->d3dDevice, &sprite);

	D3DXCreateTextureFromFileEx(GGraphic::getInstance()->d3dDevice, "img/roadbackground.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 255, 255),
		NULL, NULL, &texture);

	D3DXCreateTextureFromFileEx(GGraphic::getInstance()->d3dDevice, "img/MainCar.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255),
		NULL, NULL, &texture_car);


	vPosition = { 0,-200,0 };

	//width = 400/ 4 = 100
	//Height = 450 / 3 = 150

	mainCarSize.x = 100;
	mainCarSize.y = 150;

	mainCarCurrentFrame = 0;
	car_spriteRect.left = 12;
	car_spriteRect.top = 6;	
	car_spriteRect.right = car_spriteRect.left + mainCarSize.x;
	car_spriteRect.bottom = car_spriteRect.top + mainCarSize.y;

	spriteCentre = D3DXVECTOR2(0, 0);
	position = D3DXVECTOR2(100, 100);
	scaling = D3DXVECTOR2(1.2f, 1.2f);

	animationTimer = 0;
	animationRate = 0.3f / 4;
	animationRow = 0;
	
}

void Level1::update()
{
	
	if (GInput::getInstance()->isKeyDown(DIK_N)) {
		GameStateManager::getInstance()->changeGameState(GameStateManager::LEVEL_1);
	}

	else if (GInput::getInstance()->isKeyDown(DIK_UP))
	{
		cout << "UP" << endl;
		Car::getInstance()->mainCar_position.y += speed;
		Car::getInstance()->mainCar_position.y++;
		Car::getInstance()->direction.x = 0;
		Car::getInstance()->direction.y = -1;

		animationRow = 0;
		
		
	}

	else if (GInput::getInstance()->isKeyDown(DIK_LEFT)) {
		cout << "LEFT" << endl;
		Car::getInstance()->mainCar_position.x += speed;
		Car::getInstance()->mainCar_position.x++;
		Car::getInstance()->direction.x = -1;
		Car::getInstance()->direction.y = 0;
		
		animationRow = 1;
		
	}

	else if (GInput::getInstance()->isKeyDown(DIK_RIGHT)) {
		cout << "RIGHT" << endl;
		Car::getInstance()->mainCar_position.x -= speed;
		Car::getInstance()->mainCar_position.x--;
		Car::getInstance()->direction.x = 1;
		Car::getInstance()->direction.y = 0;
		
		animationRow = 2;
		
		
	}

	else if (GInput::getInstance()->isKeyDown(DIK_DOWN))
	{
		cout << "DOWN" << endl;
		Car::getInstance()->mainCar_position.y -= speed;
		Car::getInstance()->mainCar_position.y--;
		Car::getInstance()->direction.x = 0;
		Car::getInstance()->direction.y = 1;
		
	}
	

}

void Level1::fixedUpdate() 
{
	
	animationTimer += 1 / 60.0f;
	
	if (animationTimer >= animationRate) {
		animationTimer -= animationRate;
		mainCarCurrentFrame++;
		mainCarCurrentFrame %= 4;
	}


	car_spriteRect.left = mainCarSize.x * mainCarCurrentFrame;
	car_spriteRect.top = animationRow * mainCarSize.y;
	car_spriteRect.right = car_spriteRect.left + mainCarSize.x;
	car_spriteRect.bottom = car_spriteRect.top + mainCarSize.y;

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, NULL, NULL, &position);
}


void Level1::draw()
{
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMatrixTransformation2D(&mat, NULL, 0.0, NULL, NULL, NULL, NULL);
	sprite->SetTransform(&mat);
	sprite->Draw(texture, NULL, NULL, &vPosition, D3DCOLOR_XRGB(255, 255, 255));
	
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &position);
	
	sprite->SetTransform(&mat);
	sprite->Draw(texture_car, &car_spriteRect, &Car::getInstance()->mainCar_position, NULL, D3DCOLOR_XRGB(255, 255, 255));

	sprite->End();
}
void Level1::release()
{
	sprite->Release();
	sprite = NULL;
	texture->Release();
	texture = NULL;
	
}