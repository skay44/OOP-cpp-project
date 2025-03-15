#pragma once
#include "Zwierze.h"

class Czlowiek : public Zwierze {
private:
	int zdolnosc;
	int opoznienie;
public:
	Czlowiek(int x, int y);
	void znak(int wx, int wy) override;
	void akcja();
	void kolizja(Organizm* kolidowany);
	void stworz(Vector2 doStworzenia);
	bool niesmiertelnosc();
	std::string getNazwa() override;
};