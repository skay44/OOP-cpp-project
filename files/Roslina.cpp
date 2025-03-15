#include "Roslina.h"
#include <ctime>
#include <Windows.h>


Roslina::Roslina(int x, int y) :Organizm(x, y)
{
	inicjatywa = 0;
}

void Roslina::kolizja(Organizm* kolidowany)
{
	if (dynamic_cast<Roslina*>(kolidowany))
	{
		if (kolidowany->getID() != id)
		{
			if (kolidowany->getSila() <= sila)
			{
				if (kolidowany->niesmiertelnosc() == false)
				{
					glownySwiat->dodajLogi(getNazwa() +
						" [" + std::to_string(polozenie.x) + "," + std::to_string(polozenie.y) +
						"] zarasta " + kolidowany->getNazwa()
					);
					kolidowany->attackedBy(this);
					stworz(kolidowany->getPolozenie());
				}
			}
		}
	}
	else
	{
		if (kolidowany->getSila() <= sila)
		{
			if (kolidowany->niesmiertelnosc() == false)
			{
				//stworz(kolidowany->getPolozenie());
				kolidowany->attackedBy(this);

				glownySwiat->dodajLogi(getNazwa() +
					" [" + std::to_string(polozenie.x) + "," + std::to_string(polozenie.y) +
					"] zostaje zjedzone przez" + kolidowany->getNazwa()
				);
			}
			else
			{
				kolidowany->akcja();

				glownySwiat->dodajLogi(getNazwa() +
					" [" + std::to_string(polozenie.x) + "," + std::to_string(polozenie.y) +
					"] odgania " + kolidowany->getNazwa()
				);
			}
		}
	}
}

void Roslina::akcja()
{
	int zasianie = (rand() % 100) + 1;
	if (zasianie < szansaZasiania)
	{
		int ruchX = (rand() % 3) - 1;
		int ruchY = (rand() % 3) - 1;

		if (polozenie.x + ruchX >= 0 &&
			polozenie.y + ruchY >= 0 &&
			polozenie.x + ruchX < glownySwiat->getRozmiar().x &&
			polozenie.y + ruchY < glownySwiat->getRozmiar().y
			)
		{
			Vector2 doZasiania(polozenie.x + ruchX, polozenie.y + ruchY);
			Organizm* kolidujZ = nullptr;
			bool czy_udane = true;
			for (std::list<Organizm*>::iterator iter = glownySwiat->getOrganizmy().begin(); iter != glownySwiat->getOrganizmy().end(); iter++)
			{
				Organizm* x = (*iter);
				if (x->isAlive() && x->getPolozenie() == doZasiania)
				{
					czy_udane = false;
					kolidujZ = x;
					break;
				}
			}
			if (czy_udane)
			{
				glownySwiat->dodajLogi(getNazwa() +
					" [" + std::to_string(polozenie.x) + "," + std::to_string(polozenie.y) +
					"] rozsiewa sie" +
					"[" + std::to_string(doZasiania.x) + "," + std::to_string(doZasiania.y) +
					"]"
				);
				stworz(doZasiania);
			}
			else
			{
				//Organizm* a;
				//a = stworz(doZasiania);
				//a->kolizja(kolidujZ);
				kolizja(kolidujZ);
			}
		}
	}
}


bool Roslina::niesmiertelnosc()
{
	return false;
}

void Roslina::attackedBy(Organizm* kolidowany)
{
	kill();
}
