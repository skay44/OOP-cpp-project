#pragma once
#include "Roslina.h"

class BarszczSosnowskiego : public Roslina {
private:
public:
	BarszczSosnowskiego(int x, int y);
	void znak(int wx, int wy) override;
	void akcja();
	void kolizja(Organizm* kolidowany);
	Roslina* stworz(Vector2 doStworzenia) override;
	std::string getNazwa() override;
	void attackedBy(Organizm* kolidowany) override;

	void zabijNaokolo();
};