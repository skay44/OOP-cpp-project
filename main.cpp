#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>

#include "Vector2.h"
#include "Swiat.h"
#include "Organizm.h"
#include "Zwierze.h"
#include "Roslina.h"

#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"

#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"

#include "Czlowiek.h"

int main()
{
	srand(time(NULL));
	int x, y, z;
	std::cout << "rozmiar x, rozmiar y, czy wybor wlasnosci : ";
	std::cin >> x >> y >> z;

	if (z == 0)
	{
		if (x < 10) x = 10;
		if (y < 10) y = 10;
	}

	Swiat sw(x,y);
	Swiat::Wlasciwosci wl;
	
	if (z == 0)
		wl = sw.domysleWlasnosci();
	else
		wl = sw.wczytajWlasnosci();

	sw.losujSwiat(wl);
	sw.setLimit(30);

	while(true)
	{
		sw.rysujSwiat();
		sw.rysujKonsole();
		sw.wejscieZKlawiatury();
		sw.wykonajTure();
	}

	return 0;
}