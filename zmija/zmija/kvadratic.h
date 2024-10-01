#pragma once
#include "stdafx.h"
#include <SFML\Graphics.hpp>

using namespace sf;


class kvadratic{
private:
	RectangleShape kvadrat;
	Vector2f pozicije;

	float brzina = .1f;
	
	float pozx, pozy;
public:
	kvadratic(float pozx,float pozy,float vel1,float vel2,Color boja,int smjer);

	void boja();
	RectangleShape getshape();
	void gore();
	void dolje();
	void lijevo();
	void desno();
	void update();
};
