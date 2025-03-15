#include "WilczeJagody.h"

WilczeJagody::WilczeJagody(int x, int y) : Roslina(x, y)
{
	id = 4;
	sila = 99;
	szansaZasiania = 5;
}

void WilczeJagody::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, BACKGROUND_GREEN | FOREGROUND_RED);
	for (int i = 0; i < wx; i++)
	{
		putchar('&');
	}
}

Roslina* WilczeJagody::stworz(Vector2 doStworzenia)
{
	WilczeJagody* nowy;
	nowy = new WilczeJagody(doStworzenia.x, doStworzenia.y);
	glownySwiat->dodajOrganizm(nowy);
	return nowy;
}

void WilczeJagody::akcja()
{
	Roslina::akcja();
}

void WilczeJagody::kolizja(Organizm* kolidowany)
{
	Roslina::kolizja(kolidowany);
}

std::string WilczeJagody::getNazwa(){
	return "wilcze jagody";
}

void WilczeJagody::attackedBy(Organizm* kolidowany)
{
	std::cout << "A " << kolidowany << " " << kolidowany->getNazwa();
	kill();
	if(kolidowany->isAlive())
		kolidowany->attackedBy(this);
}