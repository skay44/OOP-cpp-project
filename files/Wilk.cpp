#include "Wilk.h"

Wilk::Wilk(int x, int y) : Zwierze(x, y)
{
	id = 1;
	sila = 9;
	inicjatywa = 5;
}

void Wilk::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	putchar('W');
}

void Wilk::stworz(Vector2 doStworzenia)
{
	Wilk* nowy;
	nowy = new Wilk(doStworzenia.x, doStworzenia.y);
	glownySwiat->dodajOrganizm(nowy);
}

void Wilk::akcja()
{
	Zwierze::akcja();
}

void Wilk::kolizja(Organizm* kolidowany)
{
	Zwierze::kolizja(kolidowany);
}

std::string Wilk::getNazwa()
{
	return "wilk";
}