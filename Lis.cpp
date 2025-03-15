#include "Lis.h"

Lis::Lis(int x, int y) : Zwierze(x, y)
{
	id = 3;
	sila = 3;
	inicjatywa = 7;
}

void Lis::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, FOREGROUND_RED | FOREGROUND_INTENSITY);
	putchar('L');
}

void Lis::stworz(Vector2 doStworzenia)
{
	Lis* nowy;
	nowy = new Lis(doStworzenia.x, doStworzenia.y);
	glownySwiat->dodajOrganizm(nowy);
}

void Lis::akcja()
{
	int ruchX = (rand() % ((zasieg * 2) + 1)) - 1;
	int ruchY = (rand() % ((zasieg * 2) + 1)) - 1;

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
				if (x->getSila() <= sila)
				{
					kolizja(x);
					break;
				}
				else
				{
					glownySwiat->dodajLogi(getNazwa() +
						"[" + std::to_string(polozenie.x) + "," + std::to_string(polozenie.y) +
						"] unika zagrozenia"
					);
					return;
				}
			}
		}
	}
	zmienPolozenie();
}

void Lis::kolizja(Organizm* kolidowany)
{
	Zwierze::kolizja(kolidowany);
}

std::string Lis::getNazwa()
{
	return "lis";
}