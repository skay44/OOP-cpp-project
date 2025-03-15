#pragma once
#include "Zwierze.h"

class Owca : public Zwierze {
private:
public:
	Owca(int x, int y);
	void znak(int wx, int wy) override;
	void akcja();
	void kolizja(Organizm* kolidowany);
	void stworz(Vector2 doStworzenia) override;
	std::string getNazwa() override;
};