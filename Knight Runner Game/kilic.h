#pragma once
class Kilic {
private:
    int x, y;
    int texturesIndex;
    vector<Texture> textures;
    Texture kilicbir;
    Texture kiliciki;

    int kilicTimer;

public:
    Kilic() {
        x = 1800;
        int randNum = rand() % 3;
        switch (randNum) {
        case 0:
            y = 850; //600 700 710
            break;
        case 1:
            y = 710;  //550 750
            break;
        case 2:
            y = 600; //510
            break;
        }

        texturesIndex = 1;
        kilicbir.loadFromFile("resim/kilicbir.png");
        kiliciki.loadFromFile("resim/kiliciki.png");
        textures.push_back(kilicbir);
        textures.push_back(kiliciki);

        kilicTimer = 0;
    }
    int getX() { return x; } //konumlarýný sürekli alýyorum
    int getY() { return y; }

    void Animasyon() { //animasyon
        if (kilicTimer == 20) {
            switch (texturesIndex) {
            case 0:
                texturesIndex = 1;
                break;
            case 1:
                texturesIndex = 0;
                break;
            }
            kilicTimer = 0;
        }
        kilicTimer++;
    }

    void Update(float speed) {
        x -= speed;  //sürekli hareketim sola dogru
        Animasyon();
    }

    void Draw(RenderWindow& window) { //Buyuklugu yanma alanýný ayar.
        RectangleShape kilicShape(Vector2f(50.0f, 50.0f)); // 90 100
        kilicShape.setOrigin(45.0f, 50.0f); // 45 50
        kilicShape.setPosition(x, y);
        kilicShape.setTexture(&textures[texturesIndex]);

        kilicShape.setOutlineColor(Color::Black);
        kilicShape.setOutlineThickness(2.0f);

        window.draw(kilicShape);
    }

};
