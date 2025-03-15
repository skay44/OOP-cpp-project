#include "Zwierze.h"
#include <ctime>
#include <Windows.h>

Zwierze::Zwierze(int x, int y) :Organizm(x, y)
{
	zasieg = 1;//domyslny
	nowePolozenie = polozenie;
}

void Zwierze::rozmnoz()
{
	int ruchX = (rand() % 3) - 1;
	int ruchY = (rand() % 3) - 1;

	if (polozenie.x + ruchX >= 0 &&
		polozenie.y + ruchY >= 0 &&
		polozenie.x + ruchX < glownySwiat->getRozmiar().x &&
		polozenie.y + ruchY < glownySwiat->getRozmiar().y)
	{
		Vector2 nowePolozenie(polozenie.x + ruchX, polozenie.y + ruchY);

		bool czy_udane = true;
		for (std::list<Organizm*>::iterator iter = glownySwiat->getOrganizmy().begin(); iter != glownySwiat->getOrganizmy().end(); iter++)
		{
			Organizm* x = (*iter);
			if (x->isAlive() && x->getPolozenie() == nowePolozenie)
			{
				if(dynamic_cast<Zwierze*>(x))
					czy_udane = false;
				else
				{
					if (x->getSila() > sila)
						czy_udane = false;
					else
					{
						x->attackedBy(this);
					}
				}
				break;
			}
		}
		if (czy_udane)
		{
			stworz(nowePolozenie);

			glownySwiat->dodajLogi(getNazwa() +
				" [" + std::to_string(polozenie.x) + "," + std::to_string(polozenie.y) +
				"] rozmnaza sie " +
				"[" + std::to_string(nowePolozenie.x) + "," + std::to_string(nowePolozenie.y) +
				"]"
			);
		}
		else
		{
			glownySwiat->dodajLogi(getNazwa() +
				" [" + std::to_string(polozenie.x) + "," + std::to_string(polozenie.y) +
				"] nie udaje sie rozmnozyc"
			);
		}
	}
	else
	{
		glownySwiat->dodajLogi(getNazwa() +
			" [" + std::to_string(polozenie.x) + "," + std::to_string(polozenie.y) +
			"] nie udaje sie rozmnozyc"
		);
	}
}

void Zwierze::zmienPolozenie()
{
	polozenie = nowePolozenie;
}

void Zwierze::akcja()
{
	//glownySwiat->dodajLogi(getNazwa() + "Wykonuje ruch");
	int ruchX;
	int ruchY;
	if (zasieg > 0)
	{
		ruchX = (rand() % ((zasieg * 2) + 1)) - zasieg;
		ruchY = (rand() % ((zasieg * 2) + 1)) - zasieg;
	}
	else
	{
		ruchX = 0;
		ruchY = 0;
	}


	if (polozenie.x + ruchX >= 0 && polozenie.x + ruchX < glownySwiat->getRozmiar().x)
		nowePolozenie.x = polozenie.x + ruchX;
	else
		nowePolozenie.x = polozenie.x;

	if (polozenie.y + ruchY >= 0 && polozenie.y + ruchY < glownySwiat->getRozmiar().y)
		nowePolozenie.y = polozenie.y + ruchY;
	else
		nowePolozenie.y = polozenie.y;

	if (!(nowePolozenie == polozenie))
	{
		for (std::list<Organizm*>::iterator iter = glownySwiat->getOrganizmy().begin(); iter != glownySwiat->getOrganizmy().end(); iter++)
		{
			Organizm* x = (*iter);
			if (x->isAlive() && x->getPolozenie() == nowePolozenie)
			{
				kolizja(x);
				break;
			}
		}
	}
	zmienPolozenie();
}

bool Zwierze::niesmiertelnosc()
{
	return false;
}

void Zwierze::kolizja(Organizm* kolidowany)
{
	bool czy_uceklo = false;
	Zwierze* casted = dynamic_cast<Zwierze*>(kolidowany);
	if (casted)
	{
		glownySwiat->dodajLogi(getNazwa() +
			" [" + std::to_string(nowePolozenie.x) + "," + std::to_string(nowePolozenie.y) +
			"] napotyka " + kolidowany->getNazwa()
);
if (kolidowany->getID() == id)
{
	nowePolozenie = polozenie;
	rozmnoz();
}
else
{
	if (casted->czy_ucieczka())
	{
	czy_uceklo = casted->ucieczka();
	}
	if (!czy_uceklo)
		if (kolidowany->getSila() > sila)
		{
			if (niesmiertelnosc() == false)
			{
				attackedBy(kolidowany);
			}
			else
			{
				glownySwiat->dodajLogi(getNazwa() +
					" [" + std::to_string(nowePolozenie.x) + "," + std::to_string(nowePolozenie.y) +
					"] unika " + kolidowany->getNazwa()
				);
				Zwierze::akcja();
			}
		}
		else
		{
			if (kolidowany->niesmiertelnosc() == false)
			{
				kolidowany->attackedBy(this);
			}
			else
			{
				glownySwiat->dodajLogi(kolidowany->getNazwa() +
					" [" + std::to_string(nowePolozenie.x) + "," + std::to_string(nowePolozenie.y) +
					"] unika " + getNazwa()
				);
				kolidowany->akcja();
			}
		}
}
	}
	else
	{
	if (kolidowany->getSila() > sila)
	{
		if (niesmiertelnosc() == false)
		{
			glownySwiat->dodajLogi(getNazwa() +
				" [" + std::to_string(nowePolozenie.x) + "," + std::to_string(nowePolozenie.y) +
				"] zjada " + kolidowany->getNazwa()
			);
			attackedBy(kolidowany);
			kolidowany->attackedBy(this);
		}
		else
		{
			glownySwiat->dodajLogi(getNazwa() +
				" [" + std::to_string(nowePolozenie.x) + "," + std::to_string(nowePolozenie.y) +
				"] unika " + kolidowany->getNazwa()
			);
			Zwierze::akcja();
		}
	}
	else
	{
		glownySwiat->dodajLogi(getNazwa() +
			" [" + std::to_string(nowePolozenie.x) + "," + std::to_string(nowePolozenie.y) +
			"] zjada " + kolidowany->getNazwa()
		);
		kolidowany->attackedBy(this);
	}
	}
}

void Zwierze::attackedBy(Organizm* kolidowany)
{
	kill();
}

void Zwierze::zmienNowePolozenie(Vector2 np)
{
	nowePolozenie = np;
}

bool Zwierze::czy_ucieczka() {
	return false;
}

bool Zwierze::ucieczka()
{
	//akcja();
	Vector2 kierunki[] = { {-1,0} ,{ 0,-1 }, {1,0} ,{0,1}};
	for (int i = 0; i < sizeof(kierunki)/sizeof(Vector2); i++)
	{
		if (polozenie.x + kierunki[i].x >= 0 &&
			polozenie.y + kierunki[i].y >= 0 &&
			polozenie.x + kierunki[i].x < glownySwiat->getRozmiar().x &&
			polozenie.y + kierunki[i].y < glownySwiat->getRozmiar().y
			)
		{
			nowePolozenie.x = polozenie.x + kierunki[i].x;
			nowePolozenie.y = polozenie.y + kierunki[i].y;
			bool czyOK = true;
			for (std::list<Organizm*>::iterator iter = glownySwiat->getOrganizmy().begin(); iter != glownySwiat->getOrganizmy().end(); iter++)
			{
				Organizm* x = (*iter);
				if (x->isAlive() && x->getPolozenie() == nowePolozenie)
				{
					czyOK = false;
				}
			}
			if (czyOK)
			{
				glownySwiat->dodajLogi(getNazwa() +
					" [" + std::to_string(polozenie.x) + "," + std::to_string(polozenie.y) +
					"] ucieka na " +
					"[" + std::to_string(nowePolozenie.x) + "," + std::to_string(nowePolozenie.y) +
					"]"
				);
				zmienPolozenie();
				return true;
			}
		}
	}
	return false;
}