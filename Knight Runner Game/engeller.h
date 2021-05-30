#pragma once
class Engeller {
private:
    int x, y;
    float w, h;
    int type;
    Texture texture;
private:
    void drawBigCactus(RenderWindow& window) { //ENGELLERÝN YANMA ALANLARI
        RectangleShape cactusBigShape(Vector2f(w, h));
        cactusBigShape.setOrigin(20.0f, 50.0f); //20 50
        cactusBigShape.setPosition(x, y);
        cactusBigShape.setTexture(&texture);

         cactusBigShape.setOutlineColor(Color::Black);
         cactusBigShape.setOutlineThickness(2.0f);

        window.draw(cactusBigShape);
    }

    void drawSmallCactus(RenderWindow& window) {
        RectangleShape cactusSmallShape(Vector2f(w, h));
        cactusSmallShape.setOrigin(20.0f, 40.0f); ///20 40
        cactusSmallShape.setPosition(x, y);
        cactusSmallShape.setTexture(&texture);
        //
         cactusSmallShape.setOutlineColor(Color::Black);
         cactusSmallShape.setOutlineThickness(2.0f);

        window.draw(cactusSmallShape);
    }

    void drawCacti(RenderWindow& window) {
        RectangleShape cactiShape(Vector2f(w, h));
        cactiShape.setOrigin(45.0f, 40.0f); // 45 40
        cactiShape.setPosition(x, y);
        cactiShape.setTexture(&texture);
        // 
         cactiShape.setOutlineColor(Color::Black);
         cactiShape.setOutlineThickness(2.0f);

        window.draw(cactiShape);
    }
public:
    Engeller(int posX, int typeNum, Texture& textureRef) { //baþlangýç kordinatlarým
        x = posX;
        type = typeNum;
        texture = textureRef;
        switch (type) {
        case 0: //big cactus
            y = 800;//850
            w = 100.0f; h = 150.0f;//100 150
            break;
        case 1: //small cactus
            y = 850;//860
            w = 60.0f; h = 100.0f;//60 100
            break;
        case 2: //cacti
            y = 875;
            w = 200.0f; h = 75.0f; //200 75
            break;
        }
    }

    inline int getX() { return x; } //konumlarý sürekli alýyorum
    inline int getY() { return y; }
    inline int getW() { return w; }
    inline int getH() { return h; }

    void Update(int speed) {
        x -= speed;  //engellerimin hareketi sola dogru
    }

    void Draw(RenderWindow& window) { //Anlýk çizdirme
        switch (type) {
        case 0: //big cactus
            drawBigCactus(window);
            y = 800;//850
            break;
        case 1: //small cactus
            drawSmallCactus(window);
            y = 850;//860
            break;
        case 2: //cacti
            drawCacti(window);
            y = 875;//860
            break;
        }

    }

};