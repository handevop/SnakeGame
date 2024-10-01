#include "stdafx.h"
#include "zmija.h"
#include "kvadratic.h"


zmija::zmija(float pozx, float pozy, float vel1, float vel2, sf::Color boja, int smjer)
{
	kvadratic kvadratic(pozx, pozy, vel1, vel2, boja, smjer);
}