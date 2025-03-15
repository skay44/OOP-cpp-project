#include "Guarana.h"
#include "Zwierze.h"

Guarana::Guarana(int x, int y) : Roslina(x, y)
{
	id = 3;
	sila = 0;
	szansaZasiania = 5;
}

void Guarana::znak(int wx, int wy)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_RED);
	for (int i = 0; i < wx; i++)
	{
		putchar('8');
	}
}

Roslina* Guarana::stworz(Vector2 doStworzenia)
{
	Guarana* nowy;
	nowy = new Guarana(doStworzenia.x, doStworzenia.y);
	glownySwiat->dodajOrganizm(nowy);
	return nowy;
}

void Guarana::akcja()
{
	Roslina::akcja();
}

void Guarana::kolizja(Organizm* kolidowany)
{
	Roslina::kolizja(kolidowany);
}

std::string Guarana::getNazwa()
{
	return "guarana";
}

void Guarana::attackedBy(Organizm* kolidowany)
{
	if (dynamic_cast<Zwierze*>(kolidowany))
	{
		glownySwiat->dodajLogi(kolidowany->getNazwa() +
			"[" + std::to_string(getPolozenie().x) + "," + std::to_string(getPolozenie().y) +
			"] zostaje wzmocniony"
		);
		int s = kolidowany->getSila();
		kolidowany->setSila(s + 3);
	}
	kill();
}