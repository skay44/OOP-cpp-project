#pragma once
#include "Zwierze.h"

class Antylopa : public Zwierze {
private:
public:
	Antylopa(int x, int y);
	void znak(int wx, int wy) override;
	void akcja();
	void kolizja(Organizm* kolidowany);
	void stworz(Vector2 doStworzenia) override;
	std::string getNazwa() override;
	bool czy_ucieczka();
};