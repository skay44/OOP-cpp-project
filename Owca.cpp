#include "Owca.h"

Owca::Owca(int x, int y) : Zwierze(x, y)
{
	id = 2;
	sila = 4;
	inicjatywa = 4;
}

void Owca::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	putchar('O');
}

void Owca::stworz(Vector2 doStworzenia)
{
	Owca* nowy;
	nowy = new Owca(doStworzenia.x, doStworzenia.y);
	glownySwiat->dodajOrganizm(nowy);
}

void Owca::akcja()
{
	Zwierze::akcja();
}

void Owca::kolizja(Organizm* kolidowany)
{
	Zwierze::kolizja(kolidowany);
}

std::string Owca::getNazwa()
{
	return "owca";
}