#include "BarszczSosnowskiego.h"
#include "Zwierze.h"

BarszczSosnowskiego::BarszczSosnowskiego(int x, int y) : Roslina(x, y)
{
	id = 5;
	sila = 10;
	szansaZasiania = 2;
}

void BarszczSosnowskiego::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	for (int i = 0; i < wx; i++)
	{
		putchar('X');
	}
}

Roslina* BarszczSosnowskiego::stworz(Vector2 doStworzenia)
{
	BarszczSosnowskiego* nowy;
	nowy = new BarszczSosnowskiego(doStworzenia.x, doStworzenia.y);
	glownySwiat->dodajOrganizm(nowy);
	return nowy;
}

void BarszczSosnowskiego::zabijNaokolo()
{
	for (std::list<Organizm*>::iterator iter = glownySwiat->getOrganizmy().begin(); iter != glownySwiat->getOrganizmy().end(); iter++)
	{
		Organizm* x = (*iter);
		Vector2 nPolozenie = x->getPolozenie();
		if (nPolozenie.x - polozenie.x >= -1 && nPolozenie.x - polozenie.x <= 1)
		{
			if (nPolozenie.y - polozenie.y >= -1 && nPolozenie.y - polozenie.y <= 1)
			{
				if (dynamic_cast<Zwierze*>(x) && x->isAlive())
				{
					if (x->niesmiertelnosc() == false)
					{
						glownySwiat->dodajLogi(x->getNazwa() +
							"[" + std::to_string(getPolozenie().x) + "," + std::to_string(getPolozenie().y) +
							"] zostaje popazony"
						);
						x->attackedBy(this);
					}
					else
					{
						glownySwiat->dodajLogi(x->getNazwa() +
							"[" + std::to_string(x->getPolozenie().x) + "," + std::to_string(x->getPolozenie().y) +
							"] unika popazenia od " + getNazwa()
						);
					}
				}
			}
		}
	}
}

void BarszczSosnowskiego::akcja()
{
	zabijNaokolo();
	if(!dead)
		Roslina::akcja();
}

void BarszczSosnowskiego::kolizja(Organizm* kolidowany)
{
	Roslina::kolizja(kolidowany);
}

std::string BarszczSosnowskiego::getNazwa() {
	return "barszcz sosnowskiego";
}

void BarszczSosnowskiego::attackedBy(Organizm* kolidowany)
{
	std::cout << "B " << kolidowany << " " << kolidowany->getNazwa();
	kill();
	if(kolidowany->isAlive())
		kolidowany->attackedBy(this);
}