#include "Antylopa.h"

Antylopa::Antylopa(int x, int y) : Zwierze(x, y)
{
	id = 5;
	sila = 4;
	inicjatywa = 4;
	zasieg = 2;
}

void Antylopa::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	putchar('A');
}

void Antylopa::stworz(Vector2 doStworzenia)
{
	Antylopa* nowy;
	nowy = new Antylopa(doStworzenia.x, doStworzenia.y);
	glownySwiat->dodajOrganizm(nowy);
}

void Antylopa::akcja()
{
	Zwierze::akcja();
}

void Antylopa::kolizja(Organizm* kolidowany)
{
	Zwierze::kolizja(kolidowany);
}

std::string Antylopa::getNazwa()
{
	return "antylopa";
}

bool Antylopa::czy_ucieczka()
{
	int rng = rand() % 2;
	if (rng == 0)
		return false;
	else
		return true;
}