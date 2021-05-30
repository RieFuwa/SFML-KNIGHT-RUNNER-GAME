#pragma once
class Savasci {
private:                
    int y;
    int konY, ziplama;
    int originalY;
    int runTimer;
    int textureIndex;
    bool egil;

    bool yanma;

    vector<Texture> textures;
    Texture savasci;
    Texture savK1;
    Texture savK2;
    Texture savK3;
    Texture ziplamak;
    Texture olme;
    Texture egilme;
    Texture egilme2;

private:
    void animasyon() {

        if (!yanma) {            //RESÝMLERÝMÝ TÝMER MANTIGIYLA ÇÝZDÝRME.
            if (y == originalY) {
                if (runTimer == 5) {
                    if (!egil) {
                        switch (textureIndex) {
                        case 0: //KOSMA
                            textureIndex = 1;
                            break;
                        case 1: //run run run run
                            textureIndex = 2;
                            break;
                        case 2: 
                            textureIndex = 3;
                            break;
                        case 3: 
                            textureIndex = 1;
                            break;
                        default:
                            textureIndex = 3;
                            break;
                        }
                    }
                    else {//EGÝLME
                        switch (textureIndex) {
                        case 5:
                            textureIndex = 6;
                            break;
                        case 6:
                            textureIndex = 7;
                            break;
                        default:
                            textureIndex = 6;
                            break;
                        }
                    }
                    runTimer = 0;
                }
            }
            else { //ZIPLAMA
                textureIndex = 4;
                runTimer = 0;
            }
        }
        else {
            textureIndex = 5; // ÖLME
        }
        runTimer++;
    }
public:
    int getY() { return y; }

    Savasci(int posX, int posY) {
        y = posY;
        konY = 0;
        ziplama = 24; //22
        originalY = posY;
        runTimer = 0;
        textureIndex = 0;
        egil = false;
        yanma = false;

        savasci.loadFromFile("resim/savasci.png");
        savK1.loadFromFile("resim/kosmabir.png");
        savK2.loadFromFile("resim/kosmaiki.png");
        savK3.loadFromFile("resim/kosmauc.png");
        ziplamak.loadFromFile("resim/ziplama.png");
        olme.loadFromFile("resim/olme.png");
        egilme.loadFromFile("resim/egilme.png");
        egilme2.loadFromFile("resim/egilmeiki.png");

        textures.push_back(savasci);
        textures.push_back(savK1);
        textures.push_back(savK2);
        textures.push_back(savK3);
        textures.push_back(ziplamak);
        textures.push_back(olme);
        textures.push_back(egilme);
        textures.push_back(egilme2);
    }

    void Egil() { egil = true; } //Egilme

    inline void Negil() { egil = false; }
    inline bool Tegil() { return egil; }
    inline void Reset() { y = originalY; Negil(); }

    void Update(int gravity, bool quit) { //YERÇEKÝMÝ- ZIPLAMA
        yanma = quit ? true : false;
        if (!quit) {
            animasyon();
            if (y < originalY) {//zeminin üstü
                konY += gravity;
            }
            else if (y > originalY) {//zemine düþüyo
                y = originalY;
            }
            else {//yerde
                if (konY == ziplama) {
                    konY = 0;
                }
            }

            y += konY;
        }
        else {
            animasyon();
        }
    }
    void Zipla() {
        if (y == originalY) {
            konY -= ziplama;
        }
    }

    void Draw(RenderWindow& window) {//KAYDIKTAN SONRAKÝ BOYUTLARI, KONUMLARIM
        if (egil && y == originalY) {
            RectangleShape dinoShape(Vector2f(200.0f, 200.0f));//BOYUT 200 200

            dinoShape.setTexture(&textures[textureIndex]);
            dinoShape.setOrigin(100.0f, 100.0f); // 100 100

            dinoShape.setPosition(100, y+50); // 100 Y+30 // 150 y+50 // kaydýktan sonraki pozisyon

            dinoShape.setOutlineColor(Color::White);
            dinoShape.setOutlineThickness(2.0f);

            window.draw(dinoShape);
        }
        else {
            RectangleShape dinoShape(Vector2f(150.0f, 200.0f));//KOÞU ANINDAKÝ BOYUT //150 200

            dinoShape.setTexture(&textures[textureIndex]);
            dinoShape.setOrigin(45.0f, 55.0f);//45 55 zemine bastýrdým.

            dinoShape.setPosition(100, y);

            dinoShape.setOutlineColor(Color::White);
            dinoShape.setOutlineThickness(2.0f);

            window.draw(dinoShape);
        }

    }

};