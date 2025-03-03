#include "stdafx.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>
#include <algorithm>
using namespace std;
// Avoid having to put sf in front of all the SFML classes and functions
using namespace sf;
#define gore 0;
#define dolje 1;
#define desno 2;
#define lijevo 3;



int brzina = 1;
int pozicijaLaznjaka=0;
int t = 0;
// C++ program to demonstrate constructors

using namespace std;

class Obrok
{
private:
	
public:
	CircleShape oblikHrane;
	Vector2f mjesto;
	
	Obrok()
	{

	}

	Obrok(float pozx, float pozy, int velicina)
	{
		if (velicina < 15) velicina = 20;
		mjesto.x = pozx;
		mjesto.y = pozy;
		if (mjesto.x < 0) mjesto.x = 0;
		if (mjesto.y < 0) mjesto.y = 0;
		if (velicina < 5) velicina = 10;
		oblikHrane.setRadius(velicina);
		oblikHrane.setPosition(mjesto);
		oblikHrane.setFillColor(Color(0,0,0,255));
	}

	CircleShape getshape()
	{
		return oblikHrane;
	}

	Color bojica()
	{
		return oblikHrane.getFillColor();
	}
};

//--------------------------------------------------------------------

class Obroci
{
private:
	
public:
	vector <Obrok> hrana;
	Obrok hranilica;
	vector <int> velicine;
	int velicinaObroka = 25;

	Obroci()
	{

	}

	Obroci(int duljina, int visina, int velicina , int kolicina)
	{
		for (int i = 0; i < kolicina; i++)
		{
			velicinaObroka = rand()%50;
			if (velicinaObroka < 25) velicinaObroka = 25;
			velicine.push_back(velicinaObroka);
			hranilica = Obrok( rand()%1024, rand()%768, velicinaObroka);
			hrana.push_back(hranilica);
		} 
	}

	CircleShape hranaOUT(int i)
	{
		return hrana[i].getshape();
	}

	int ObrokSize() {
		return velicinaObroka;
	}

	int pozitionsX(Vector2f(mjesto))
	{
		return mjesto.x;
	}

	int pozitionsY(Vector2f(mjesto))
	{
		return mjesto.y;
	}

	void izbaci1(int i)
	{
		hrana.erase(hrana.begin() + i);
	}

	Color bojanje(int i)
	{
		return hrana[i].bojica();
	}
};

//--------------------------------------------------------------------
class Element
{
private:
	int boja;
	RectangleShape oblikElementa;
	float velicinaElementa;

public:
	bool jeLazan;
	int smjer1;
	Vector2f pozicije;


	//Default Constructor
	Element()
	{
	}

	//Parametrized Constructor
	Element(float pozx, float pozy, float velicina, sf::Color boja, int smjer, bool lazan)
	{
		pozicije.x = pozx;
		pozicije.y = pozy;
		oblikElementa.setSize(Vector2f(velicina, velicina));
		oblikElementa.setPosition(pozicije);
		oblikElementa.setFillColor(boja);
		velicinaElementa = velicina;
		smjer1 = smjer;
		jeLazan = lazan;
	}
	void PromijeniSmjerGore()
	{
		smjer1 = gore;
		
	}
	void PromijeniSmjerDolje()
	{
		smjer1 = dolje;
	}
	void PromijeniSmjerLijevo()
	{
		smjer1 = lijevo;
	}
	void PromijeniSmjerDesno()
	{
		smjer1 = desno;
	}
	void PromijeniBoju(Color boja)
	{
		oblikElementa.setFillColor(boja);
	}
	void PromijeniVelicinu(float vel ,float vel1)
	{
		oblikElementa.setSize(Vector2f(vel,vel1));
	}
	/*int PromijeniSmjer()
	{
		return rand() % 4;
	}*/
	void KretanjeIzvanOkvira(float duljina, float visina)
	{
		if (pozicije.x <= 0 - velicinaElementa) pozicije.x = duljina;
		else if (pozicije.x >= duljina + velicinaElementa) pozicije.x = 0;
		else if (pozicije.y >= visina + velicinaElementa) pozicije.y = 0;
		else if (pozicije.y <= 0 - velicinaElementa) pozicije.y = visina;
	}
	RectangleShape getshape()
	{
		return oblikElementa;
	}

	void PokreniKretanjeElementa(float duljina, float visina)
	{
		if (!jeLazan)
		{
			switch (smjer1)
			{
			case 0:
				pozicije.y = pozicije.y - brzina;
				break;
			case 1:
				pozicije.y = pozicije.y + brzina;
				break;
			case 2:
				pozicije.x = pozicije.x + brzina;
				break;
			case 3:
				pozicije.x = pozicije.x - brzina;
				break;
			}

			KretanjeIzvanOkvira(duljina, visina);
		}

		oblikElementa.setPosition(pozicije);
	}

	int VratiX(Vector2f(pozicije))
	{
		return pozicije.x;
	}

	int VratiY(Vector2f(pozicije))
	{
		return pozicije.y;
	}
};

//----------------------------------------------------------------------------

class Zmija
{
private:
	int velicinaElementa;
	int smjerKretanja;

public:
	vector <Element> elementi;
	
	//Default Constructor
	Zmija()
	{
	}

	//Parametrized Constructor
	Zmija(float pozx, float pozy, int vel1, sf::Color boja, int smjer, int brojElemenata)
	{
		velicinaElementa = vel1;
		smjerKretanja = smjer;
		Element element;

	
		switch (smjerKretanja)
		{
		case 0:
			for (int i = 0; i < brojElemenata; i++)
			{
				element = Element(pozx, pozy - i * velicinaElementa, velicinaElementa, boja, smjerKretanja, false);
				elementi.push_back(element);
				
			}
			break;
		case 1:
			for (int i = 0; i < brojElemenata; i++)
			{
				element = Element(pozx, pozy + i * velicinaElementa, velicinaElementa, boja, smjerKretanja, false);
				elementi.push_back(element);
				
			}
			break;
		case 2:
			for (int i = 0; i < brojElemenata; i++)
			{
				element = Element(pozx + i * velicinaElementa, pozy, velicinaElementa, boja, smjerKretanja, false);
				elementi.push_back(element);
				
			}
			break;
		case 3:
			for (int i = 0; i < brojElemenata; i++)
			{
				element = Element(pozx - i * velicinaElementa, pozy, velicinaElementa, boja, smjerKretanja, false);
				elementi.push_back(element);
			}
			break;
		default:
			break;
		}
	}

	void PromijeniSmjer(int smjer , int element, bool kreirajLaznjak)
	{
		smjerKretanja = smjer;

		// kreiraj lažnjaka

		if ( kreirajLaznjak )
		{
			Element laznjak = elementi[element];
			laznjak.jeLazan = true;
			laznjak.smjer1 = smjer;

			std::vector<Element>::iterator it;
			it = elementi.begin();

			elementi.insert(it+element, laznjak);

			element = element + 1;
		}

		switch (smjerKretanja)
		{
		case 0:
			elementi[element].PromijeniSmjerGore();
			break;
		case 1:
			elementi[element].PromijeniSmjerDolje();
			break;
		case 3:
			elementi[element].PromijeniSmjerLijevo();
			break;
		case 2:
			elementi[element].PromijeniSmjerDesno();
			break;
		default:
			break;
		}

	}
	
	void izbaci(int i)
	{
		elementi.erase(elementi.begin() + i);
	}

	void Promijeniboju1(Color boja)
	{
		for (int i = 0; i < elementi.size(); i++)
		{
			elementi[i].PromijeniBoju(boja);
		}
	}
	void PokreniKretanje(float duljina, float visina , int smjer)
	{
		Element laznjak;
		
		for (int i = elementi.size()-1; i >= 0; i--)
		{
			elementi[i].PokreniKretanjeElementa(duljina, visina);

			if (elementi[i].jeLazan)
			{
				laznjak = elementi[i];
				laznjak.PromijeniVelicinu(velicinaElementa,velicinaElementa);
				pozicijaLaznjaka = i;	
				t = 1;
			}
			else
			{
				if (elementi[i].pozicije.x == laznjak.pozicije.x && elementi[i].pozicije.y == laznjak.pozicije.y)
				{
					PromijeniSmjer(laznjak.smjer1, i, false);

					if (i == 0)
					{
						//elementi.erase(elementi.begin());
						t = 0;
					}

					swap(elementi[i], elementi[i + 1]);
				}

			
				/*std::vector<Element>::iterator it;
				it = elementi.begin();*/

				/*elementi.insert(elementi.begin() + i, laznjak);
				elementi.erase(elementi.begin() + pozicijaLaznjaka);*/
			}

			/*cout << elementi.size();*/
			
			// briši zadnji lažni element kada predzadnji se preklopi sa zadnjim
			
			/*if (i==n-1) elementi.pop_back();*/

			
			// mijenjamo smijer kada se prekope, a nisu zadnji ili može i iskoristiti status jeLazan

			if (i == 0 && elementi[i].jeLazan)
			{
				elementi.erase(elementi.begin());
			}

		

		}

	}

	RectangleShape Oblik(int i)
	{
		return elementi[i].getshape();
	}
};

//--------------------------------------------
int windowWidth = 1024;
int windowHeight = 768; 

std::stringstream ss;
RenderWindow window1(VideoMode(windowWidth, windowHeight), "Pongi");

int main()
{
	int score = 0;
	int smjer = 0;
	int br = 0;
	int windowWidth = 1024;
	int windowHeight = 768;
	int velicinaLoptice = 20;
	float x=500, y = 500;
	int m, p;
	
	RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");
	
	Text poruka, poruka1, poruka2, poruka3;

	Font vrsta;

	vrsta.loadFromFile("game_over.ttf");

	poruka.setFont(vrsta);
	poruka3.setFont(vrsta);

	poruka.setCharacterSize(100);
	poruka3.setCharacterSize(100);

	poruka.setFillColor(sf::Color::Black);
	poruka3.setFillColor(sf::Color::White);

	
	ss << "Score: " << score;
	poruka3.setString(ss.str());
	score++;
	window1.draw(poruka3);
	poruka.setString("GAME OVER!");
	Zmija zmija1(x, y, velicinaLoptice,  Color::Red, smjer, 15);
	Obroci obroci1(windowWidth-velicinaLoptice, windowHeight-velicinaLoptice, velicinaLoptice+5 , 15);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Someone closed the window- bye
				window.close();
			if (event.type == Event::Resized)
			{
				Vector2u velicina ;
				velicina.x = windowWidth;
				velicina.y = windowHeight;
				window.setSize(velicina);
			}
		}
		while (window1.pollEvent(event))
		{
			if (event.type == Event::Closed)
				// Someone closed the window- bye
				window1.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) && smjer!= 2 ) smjer = lijevo;
		if (Keyboard::isKeyPressed(Keyboard::Right) && smjer != 3 ) smjer = desno;
		if (Keyboard::isKeyPressed(Keyboard::Up) && smjer != 1 ) smjer = gore;
		if (Keyboard::isKeyPressed(Keyboard::Down) && smjer != 0 ) smjer = dolje;
		
		if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::Down)) 
			zmija1.PromijeniSmjer(smjer, zmija1.elementi.size()-1, true);

		window.clear(Color(255,255,255,255));
		window1.clear(Color(0, 0, 0, 0));

		zmija1.PokreniKretanje(windowWidth, windowHeight,smjer);

		for (size_t i = 0; i < obroci1.hrana.size(); i++)
		{
			window.draw(obroci1.hranaOUT(i));
		}

		for (size_t i = 0; i < zmija1.elementi.size(); i++)
		{
			window.draw(zmija1.Oblik(i));
			//cout << i <<' ';
		}
		for (size_t i = 0; i < obroci1.hrana.size(); i++)
		{
			int	pozicijaxZmije , pozicijayZmije , pozicijaxObrok , pozicijayObrok , velObr;
			pozicijaxZmije = zmija1.elementi[zmija1.elementi.size() - 1].pozicije.x;
			pozicijayZmije = zmija1.elementi[zmija1.elementi.size() - 1].pozicije.y;
			pozicijaxObrok = obroci1.hrana[i].mjesto.x;
			pozicijayObrok = obroci1.hrana[i].mjesto.y;
			velObr = obroci1.velicine[i];
			if (pozicijaxZmije >= pozicijaxObrok - obroci1.velicine[i] && pozicijaxZmije <= pozicijaxObrok + obroci1.velicine[i] &&
				pozicijayZmije >= pozicijayObrok - obroci1.velicine[i] && pozicijayZmije <= pozicijayObrok + obroci1.velicine[i])
			//if (sqrt(pow(pozicijaxZmije-pozicijaxObrok,2)+pow(pozicijayZmije - pozicijayObrok,2)) <= velObr)
			{
				//zmija1.Promijeniboju1(obroci1.bojanje(i));
				obroci1.izbaci1(i);
			}

		}
		/*std::this_thread::sleep_for(std::chrono::microseconds(1));*/
		window1.clear();
		window1.draw(poruka3);

		cout << obroci1.hrana.size()<<endl;
		if (obroci1.hrana.size() <= 0)
		{			
			poruka1 = poruka;
			poruka1.setFillColor(sf::Color::Black);
			poruka2 = poruka1;
			poruka2.setString("\n Press Escape to QUIT or Space to continue");
			window.draw(poruka1);
			window.draw(poruka2);
			window1.draw(poruka3);
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window1.close();
				window.close();
			}
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				window.close();
				main();
				br++;
			}
		}
		window1.display();
		window.display();
	}
	return 0;
}