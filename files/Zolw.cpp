#include "Zolw.h"

Zolw::Zolw(int x, int y) : Zwierze(x, y)
{
	id = 4;
	sila = 2;
	inicjatywa = 1;
}

void Zolw::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	putchar('Z');
}

void Zolw::stworz(Vector2 doStworzenia)
{
	Zolw* nowy;
	nowy = new Zolw(doStworzenia.x, doStworzenia.y);
	glownySwiat->dodajOrganizm(nowy);
}

void Zolw::akcja()
{
	int rng = rand() % 4;
	if(rng == 0)
		Zwierze::akcja();
}

void Zolw::kolizja(Organizm* kolidowany)
{
	Zwierze::kolizja(kolidowany);
}

std::string Zolw::getNazwa()
{
	return "zolw";
}

void Zolw::attackedBy(Organizm* kolidowany)
{
	Zwierze* kolidowanyCasted = dynamic_cast<Zwierze*>(kolidowany);
	if (kolidowanyCasted)
	{
		if (kolidowany->getSila() <= 5)
		{
			if (nowePolozenie == polozenie)//zolw nie jest napastnikiem
			{
				glownySwiat->dodajLogi(getNazwa() +
					"[" + std::to_string(polozenie.x) + "," + std::to_string(polozenie.y) +
					"] odbija atak " + kolidowanyCasted->getNazwa()
				);
				kolidowanyCasted->zmienNowePolozenie(kolidowanyCasted->getPolozenie());
				return;
			}
		}
	}
	kill();
}