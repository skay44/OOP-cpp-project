#include "Trawa.h"

Trawa::Trawa(int x, int y) : Roslina(x, y)
{
	id = 1;
	sila = 0;
	szansaZasiania = 10;
}

void Trawa::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, BACKGROUND_GREEN);
	for (int i = 0; i < wx; i++)
	{
		putchar(' ');
	}
}

Roslina* Trawa::stworz(Vector2 doStworzenia)
{
	Trawa* nowy;
	nowy = new Trawa(doStworzenia.x, doStworzenia.y);
	glownySwiat->dodajOrganizm(nowy);
	return nowy;
}

void Trawa::akcja()
{
	Roslina::akcja();
}

void Trawa::kolizja(Organizm* kolidowany)
{
	Roslina::kolizja(kolidowany);
}

std::string Trawa::getNazwa()
{
	return "trawa";
}