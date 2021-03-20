#pragma once
#include "GameState.h"
#include "GGraphic.h"
#include<d3d9.h>
#include<d3dx9.h>
class Level1 : public GameState
{
private:
	D3DXVECTOR3 vPosition;
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DTEXTURE9 texture_car;
	LPD3DXSPRITE sprite;
	D3DXMATRIX mat;
	RECT background_spriteRect;
	RECT car_spriteRect;
	///RECT textRect;
	D3DXVECTOR2 spriteCentre;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scaling;
	float rotation = 0;
	int x = 0;
	int y = 0;
	int speed = 1.5;

	D3DXVECTOR2 mainCarSize;
	int mainCarCurrentFrame;
	float animationRate;
	float animationTimer;
	int animationRow;
	bool isMainCarForward;

public: 
	Level1();
	~Level1(); 

	void init();
	void update();
	void fixedUpdate();
	void draw();
	void release();
	
};


