#pragma once
class Ates {
private:
    int x, y;

    int texturesIndex;
    vector<Texture> textures;
    Texture ates1;
    Texture ates2;

    int flyTimer;
public:
    Ates() {
        x = 1800;//1800
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
        ates1.loadFromFile("resim/ates1.png");
        ates2.loadFromFile("resim/ates2.png");
        textures.push_back(ates1);
        textures.push_back(ates2);

        flyTimer = 0;
    }

    int getX() { return x; } //konumlarýný sürekli alýyorum
    int getY() { return y; }

    void Animasyon() { //animasyon
        if (flyTimer == 20) {
            switch (texturesIndex) {
            case 0:
                texturesIndex = 1;
                break;
            case 1:
                texturesIndex = 0;
                break;
            }
            flyTimer = 0;
        }
        flyTimer++;
    }

    void Update(float speed) {
        x -= speed;  //sürekli hareketim sola dogru
        Animasyon();
    }

    void Draw(RenderWindow& window) { //Buyuklugu yanma alanýný ayar.
        RectangleShape birdShape(Vector2f(120.0f, 100.0f)); // 90 100
        birdShape.setOrigin(45.0f, 50.0f); // 45 50
        birdShape.setPosition(x, y);
        birdShape.setTexture(&textures[texturesIndex]);

        birdShape.setOutlineColor(Color::Black);
        birdShape.setOutlineThickness(2.0f);

        window.draw(birdShape);
    }
};