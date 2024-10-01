#pragma once
#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <vector>
#include "kvadratic.h"
#include <iostream>

using namespace sf;
using namespace std;


class zmija {
private:
	kvadratic kvadratic(float pozx, float pozy, float vel1, float vel2, sf::Color boja, int smjer);
	
public:
	zmija(float pozx, float pozy, float vel1, float vel2, sf::Color boja, int smjer);

};
