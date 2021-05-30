#pragma once
class KacýsOyunu {
private:
    int w, h;
    Savasci* savasci;
    bool gameover;
    int gravity;
    float speed;
    int score;
    int bestScore;

    vector<Engeller*> engelllers;

    vector<Kilic*> kilics;

    vector<Ates*> atess;

    int engelTimer, engelAyar, kilicTimer, kilicAyar, atesTimer, atesAyar;

    Texture dikenler;
    Texture kucukengel;
    Texture buyukengel;
    Texture arkaplan;

    bool death;

public:
    KacýsOyunu(int height, int width) {
        srand(time(NULL));
        //initialize random distances to 0
        engelAyar = 0;
        kilicAyar = 0;
        atesAyar = 0;

        //set dimensions
        h = height; w = width;

        //TALÝMATLARIM
        savasci = new Savasci(50, 775);//100,600
 
        gameover = false;

        //fizik
        gravity = 1; //1
        speed = 10; //10

        //tiiiimerrr
        engelTimer = 0;
        kilicTimer = 0;
        atesTimer = 0;

        //skorlarým
        score = 0;
        bestScore = 0;

        //texture
        dikenler.loadFromFile("resim/diken.png");
        kucukengel.loadFromFile("resim/engelkucuk.png");
        buyukengel.loadFromFile("resim/engelbuyuk.png");
        arkaplan.loadFromFile("resim/arkaplan.png");

        death = true;
    }

    void Run() {
        RenderWindow window(VideoMode(h, w), "Dino Game", Style::Close | Style::Resize);
        window.setFramerateLimit(60);

        Font font;
        font.loadFromFile("resim/font.ttf");
        Sprite arka(arkaplan);

        while (window.isOpen()) {

            Event evnt;
            while (window.pollEvent(evnt)) {              
                switch (evnt.type) {
                case Event::Closed:
                    window.close();
                    break;

                 case Event::KeyPressed: //herhangi bir tuþla yandýktan sonra oyuna RES ATILIR.
                    if (gameover) {
                        savasci->Reset();
                        window.draw(arka);
                        engelllers.clear();
                        kilics.clear();
                        atess.clear();

                        speed = 10;
                        score = 0;

                        gameover = false;
                    }
                }
            }
            if (!gameover) {  //Oyunum DEVAM EDÝYORRRS
               
                Input();

                window.clear(sf::Color(255, 255, 255));
                window.draw(arka);
                DrawAll(window, font);
               

                savasci->Update(gravity, false);

                EngelYenile();
                KilicYenile();
                AtesYenile();

                if (death)
                     Logic();
                //hýz
                speed += .002; //oyunum hýzlanýr.

                //score arttýr
                score++;
            }

            else {//SKORUN ONCEKÝ SKORUNDAN BUYUK ISE
                if (score > bestScore) {
                    bestScore = score;
                }

               // window.clear(sf::Color(255, 255, 255)); öldügüM an

                savasci->Negil();

                DrawAll(window, font);

                savasci->Update(gravity, true);
            }
            //display window
           
            window.display();


        }
    }
private:
    string getScoreString(int score) {
        switch (to_string(score / 10).length()) {
        case 1:
            return "0000" + to_string(score / 10);
            break;
        case 2:
            return "000" + to_string(score / 10);
            break;
        case 3:
            return "00" + to_string(score / 10);
            break;
        case 4:
            return "0" + to_string(score / 10);
            break;
        case 5:
            return to_string(score / 10);
            break;
        default:
            return "99999";
            break;
        }
    }
    void DrawAll(RenderWindow& window, Font& font) {

        for (int i = 0; i < engelllers.size(); i++) { // engellerimi sürekli çizdiriyorum
            engelllers[i]->Draw(window);
        }
        for (int i = 0; i < kilics.size(); i++) {
            kilics[i]->Draw(window);
        }
        for (int i = 0; i < atess.size(); i++) {
            atess[i]->Draw(window);
        }

        savasci->Draw(window);

        
        Text scoreText(getScoreString(score), font, 35); //SKOR YAZDIRMA ALANIM
        scoreText.setOrigin(0, 0);
        scoreText.setPosition(w + 600, 30);
        scoreText.setFillColor(Color::Yellow);
        window.draw(scoreText);

        if (bestScore != 0) {
            Text bestScoreText("HS " + getScoreString(bestScore), font, 35);
            bestScoreText.setOrigin(0, 0);
            bestScoreText.setPosition(w + 350, 30);
            bestScoreText.setFillColor(Color::Black);
            window.draw(bestScoreText);
        }
    }

    //----------------------------------------------------------------------------
    //                                   Vectors
    //----------------------------------------------------------------------------
    
    void KilicEkle() { //kilic
        Kilic* kilic = new Kilic();
        kilics.push_back(kilic);

        kilicAyar = rand() % 100; //
        kilicTimer = 0;

        engelTimer = 0;
    }


    void KilicYenile() { 

        kilicTimer++;

        //kilicin hareketi
        for (int i = 0; i < kilics.size(); i++) {
            kilics[i]->Update(speed);
            if (kilics[i]->getX() < 5) {
                kilics.erase(kilics.begin() + i);
            }
        }
        if (kilicAyar + 500 <= kilicTimer && engelTimer > 55 && score / 10 > 50) { // 300 gelme çoklugu  55  10 >100puandan sonra kuþ gelir
            KilicEkle();
        }

    }

    void AtesEkle() { //ATES
        Ates* ates = new Ates();
        atess.push_back(ates);

        atesAyar = rand() % 100; //
        atesTimer = 0;

        engelTimer = 0;
    }

    void AtesYenile() {
        atesTimer++;

        //atesin hareketi
        for (int i = 0; i < atess.size(); i++) {
            atess[i]->Update(speed);
            if (atess[i]->getX() < 5) {
                atess.erase(atess.begin() + i);
            }
        }
        if (atesAyar + 300 <= atesTimer && engelTimer > 55 && score / 10 > 100) { // 300 gelme çoklugu  55  10 >100puandan sonra kuþ gelir
            AtesEkle();
        }
    }

    void EngelEkle() { //engel ekliyorum karýþýk.
        int type = rand() % 3;
        switch (type) {
        case 0://büyük engelim
        {Engeller* engel = new Engeller(1800, type, buyukengel); //1800
        engelllers.push_back(engel); }
        break;
        case 1://kucuk engelim
        {Engeller* engel = new Engeller(1800, type, kucukengel);
        engelllers.push_back(engel); }
        break;
        case 2://dikenlerrr
        {Engeller* engel = new Engeller(1800, type, dikenler);
        engelllers.push_back(engel); }
        break;
        }


        engelAyar = (int)(rand() % (50 / (int)((float)speed * .1))); //2 engelin aralýgý , hýzý

        engelTimer = 0;
    }

    void EngelYenile() {

        engelTimer++;

        //move obstacles
        for (int i = 0; i < engelllers.size(); i++) { //engellerin hareketi sola dogru
            engelllers[i]->Update(speed);//hýz fonk göndr
            if (engelllers[i]->getX() < 5) { //engellerim x de5 geldiginde kaybolur.
                engelllers.erase(engelllers.begin() + i);
            }
        }
       
        if (engelAyar + 60 == engelTimer) { //engellerin gelme sýklýgýný ayarlýyorum.
            EngelEkle();
        }

    }
    //----------------------------------------------------------------------------
    //                              Input & Logic
    //----------------------------------------------------------------------------

    void Input() {

        if (Keyboard::isKeyPressed(Keyboard::Key::Space)) { //Klavye Tuþ Atamalarým.
            savasci->Zipla();
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
            savasci->Egil();
        }
        else {
            savasci->Negil();
        }
    }

    bool checkCollision(int x, int y, int oWidth, int oHeight, int xTwo, int yTwo, int oTwoWidth, int oTwoHeight) { //çarpýþmayý kontrol et
        // AABB 1
        int x1Min = x;
        int x1Max = x + oWidth;
        int y1Max = y + oHeight;
        int y1Min = y;

        // AABB 2
        int x2Min = xTwo;
        int x2Max = xTwo + oTwoWidth;
        int y2Max = yTwo + oTwoHeight;
        int y2Min = yTwo;

        // Collision tests
        if (x1Max < x2Min || x1Min > x2Max) {
            return false;
        }
        if (y1Max < y2Min || y1Min > y2Max) {
            return false;
        }

        return true;
    }

    void Logic() {
        int savX = 50;
        int savY = savasci->getY();
        int savW = 150; //baþlangýçta yüksekligi
        int savH = 200; //*

        if (savasci->Tegil()) { //egilme yükseklik ve geniþlik ayarlama
            savW = 200;//150 44
            savH = 200;
        }

        for (int i = 0; i < engelllers.size(); i++) { //ENGELLERE YANDIRDIGIM KISIM
            int engelX = engelllers[i]->getX();
            int engelY = engelllers[i]->getY();
            int engelW = engelllers[i]->getW();
            int engelH = engelllers[i]->getH();

            if (checkCollision(savX, savY, savW, savH, engelX, engelY, engelW, engelH)) {
                gameover = true;
            }

        }

        int atesW = 100; //atesin yuk geniþligi.
        int atesH = 100;

        for (int i = 0; i < atess.size(); i++) { //ATESE YANILAN KISIM
            int atesX = atess[i]->getX();
            int atesY = atess[i]->getY();

            if ((atesY == 710 || atesY == 750) && savasci->Tegil()) { //510 550

            }
            else {
                if (checkCollision(savX, savY, savW, savH, atesX, atesY, atesW, atesH)) {
                    gameover = true;
                }
            }
        }
        
        int kilicW = 50;
        int kilicH = 50;

        for (int i = 0; i < kilics.size(); i++) { //ATESE YANILAN KISIM
            int kilicX = kilics[i]->getX();
            int kilicY = kilics[i]->getY();

            if ((kilicY == 710 || kilicY == 750) && savasci->Tegil()) { //510 550

            }

            else {
                if (checkCollision(savX, savY, savW, savH, kilicX, kilicY, kilicW, kilicH)) { //Eðer savaþcýmýn kordinatý kilic ile eþitse +50 puan alýr.
                    score += 25;
                }
            }
        }
    }
};