#pragma once
#include <iostream>
#include <Windows.h>
#include "Vector2.h"
#include "Swiat.h"

class Organizm {
protected:
	Swiat* glownySwiat;
	Vector2 polozenie;
	int sila;
	int inicjatywa;
	int id;
	bool dead;

	void kill();
public:
	Organizm(int x, int y);
	Organizm(Vector2& nowePolozenie);	
	Organizm(Vector2&& nowePolozenie);

	Vector2 getPolozenie();
	void setPolozenie(Vector2 nowePolozenie);

	int getSila();
	void setSila(int nowaSila);

	int getInicjatywa();

	bool isAlive();

	Swiat* getGlownySwiat();
	void setGlownySwiat(Swiat* nowyGlownySwiat);

	int getID();

	virtual void akcja() = 0;
	virtual void kolizja(Organizm* koldowany) = 0;
	void rysowanie(int widthX, int widthY, int offsetX, int offsetY);
	virtual void znak(int wx, int wy) = 0;

	virtual bool niesmiertelnosc() = 0;
	virtual std::string getNazwa() = 0;
	virtual void attackedBy(Organizm* kolidowany) = 0;
};
