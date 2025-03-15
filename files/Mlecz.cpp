#include "Mlecz.h"

Mlecz::Mlecz(int x, int y) : Roslina(x, y)
{
	id = 2;
	sila = 0;
	szansaZasiania = 10;
}

void Mlecz::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, BACKGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	for (int i = 0; i < wx; i++)
	{
		putchar('*');
	}
}

Roslina* Mlecz::stworz(Vector2 doStworzenia)
{
	Mlecz* nowy;
	nowy = new Mlecz(doStworzenia.x, doStworzenia.y);
	glownySwiat->dodajOrganizm(nowy);
	return nowy;
}

void Mlecz::akcja()
{
	for(int i = 0; i < 3; i++)
		Roslina::akcja();
}

void Mlecz::kolizja(Organizm* kolidowany)
{
	Roslina::kolizja(kolidowany);
}

std::string Mlecz::getNazwa()
{
	return "mlecz";
}