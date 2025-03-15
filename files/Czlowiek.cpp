#include "Czlowiek.h"

Czlowiek::Czlowiek(int x, int y) : Zwierze(x, y)
{
	id = 0;
	sila = 5;
	inicjatywa = 4;
	zdolnosc = 0;
	opoznienie = 0;
}

void Czlowiek::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	if (zdolnosc > 0)
		SetConsoleTextAttribute(out, FOREGROUND_RED | FOREGROUND_INTENSITY);
	else if (opoznienie > 0)
		SetConsoleTextAttribute(out, FOREGROUND_BLUE | FOREGROUND_GREEN);
	else
		SetConsoleTextAttribute(out, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	putchar('C');
}

void Czlowiek::stworz(Vector2 doStworzenia)
{
	return;
}

void Czlowiek::akcja()
{
	if (glownySwiat->getZdolnosc() == true && opoznienie == 0)
	{
		opoznienie = 10;
		zdolnosc = 5;
	}
	else
	{
		if (zdolnosc > 0)
			zdolnosc--;
		if (opoznienie > 0)
			opoznienie--;
	}

	int ruch = glownySwiat->getRuch();
	int ruchX = 0;
	int ruchY = 0;
	if (ruch == Swiat::GORA)
	{
		ruchY = -1;
	}
	else if (ruch == Swiat::DOL)
	{
		ruchY = 1;
	}
	else if (ruch == Swiat::LEWO)
	{
		ruchX = -1;
	}
	else if (ruch == Swiat::PRAWO)
	{
		ruchX = 1;
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

void Czlowiek::kolizja(Organizm* kolidowany)
{
	Zwierze::kolizja(kolidowany);
}

bool Czlowiek::niesmiertelnosc()
{
	if (zdolnosc > 0)
		return true;
	else
		return false;
}

std::string Czlowiek::getNazwa()
{
	return "czlowiek";
}