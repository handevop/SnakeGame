#include "stdafx.h"
#include "kvadratic.h"


kvadratic::kvadratic(float pozx, float pozy, float vel1, float vel2 , sf::Color boja ,int smjer)
{
	pozicije.x = pozx;
	pozicije.y = pozy;
	kvadrat.setSize(sf::Vector2f(vel1, vel2));
	kvadrat.setPosition(pozicije);
	kvadrat.setFillColor(boja);
}

void kvadratic::boja()
{
	kvadrat.setFillColor(sf::Color(rand(), rand(), rand(), rand()));
}

RectangleShape kvadratic::getshape()
{
	return kvadrat;
}

void kvadratic::gore()
{
	pozicije.y -= brzina;
}

void kvadratic::dolje()
{
	pozicije.y += brzina;
}

void kvadratic::lijevo()
{
	pozicije.x -= brzina;
}

void kvadratic::desno()
{
	pozicije.x += brzina;
}

void kvadratic::update()
{
	kvadrat.setPosition(pozicije);
}