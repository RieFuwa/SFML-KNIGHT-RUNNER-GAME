#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include <vector>
#include <string>

using namespace sf;
using namespace std;


#include "savasci.h"
#include "engeller.h"
#include "kilic.h"
#include "ates.h"
#include "oyun.h"


int main() {
	//Texture arkaplan;
	//Sprite arka(arkaplan);

	//arkaplan.loadFromFile("art/arkaplan.png");

	KacýsOyunu kacýsoyunu(1800, 1000);
	kacýsoyunu.Run();
	//window.draw(arka);

	return 0;
}