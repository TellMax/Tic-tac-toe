#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <Windows.h>
#include <sstream>


using namespace std;
using namespace sf;

#define N 3

class Object 
{
public:
    float x, y;
    String File;
    
    Texture texture;
    Sprite sprite;

    Object(string file, float X, float Y) 
    {
        texture.loadFromFile(file);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setPosition(x, y);
    }
};

string victory_check(string field[N][N], string p)
{
    string victory = "a";

    if (field[0][0] == p && field[1][1] == p && field[2][2] == p)
    {
        victory = p;
    }
    else if (field[2][0] == p && field[1][1] == p && field[0][2] == p)
    {
        victory = p;
    }
    else if (field[0][0] == p && field[1][0] == p && field[2][0] == p)
    {
        victory = p;
    }
    else if (field[0][1] == p && field[1][1] == p && field[2][1] == p)
    {
        victory = p;
    }
    else if (field[0][2] == p && field[1][2] == p && field[2][2] == p)
    {
        victory = p;
    }
    else if (field[0][0] == p && field[0][1] == p && field[0][2] == p)
    {
        victory = p;
    }
    else if (field[1][0] == p && field[1][1] == p && field[1][2] == p)
    {
        victory = p;
    }
    else if (field[2][0] == p && field[2][1] == p && field[2][2] == p)
    {
        victory = p;
    }

    return victory;
}

string check_field(string field[N][N], string motion)
{
    int x = 3, y = 3;
    char g;
    if (field[0][0] == motion && field[1][0] == motion && field[2][0] == "empty")
    {
        x = 2;
        y = 0;
    }
    else if (field[0][0] == motion && field[1][0] == "empty" && field[2][0] == motion)
    {
        x = 1;
        y = 0;
    }
    else if (field[0][0] == "empty" && field[1][0] == motion && field[2][0] == motion)
    {
        x = 0;
        y = 0;
    }
    else if (field[0][1] == motion && field[1][1] == motion && field[2][1] == "empty")
    {
        x = 2;
        y = 1;
    }
    else if (field[0][1] == motion && field[1][1] == "empty" && field[2][1] == motion)
    {
        x = 1;
        y = 1;
    }
    else if (field[0][1] == "empty" && field[1][1] == motion && field[2][1] == motion)
    {
        x = 0;
        y = 1;
    }
    else if (field[0][2] == motion && field[1][2] == motion && field[2][2] == "empty")
    {
        x = 2;
        y = 2;
    }
    else if (field[0][2] == motion && field[1][2] == "empty" && field[2][2] == motion)
    {
        x = 1;
        y = 2;
    }
    else if (field[0][2] == "empty" && field[1][2] == motion && field[2][2] == motion)
    {
        x = 0;
        y = 2;
    }
    else if (field[0][0] == motion && field[0][1] == motion && field[0][2] == "empty")
    {
        x = 0;
        y = 2;
    }
    else if (field[0][0] == motion && field[0][1] == "empty" && field[0][2] == motion)
    {
        x = 0;
        y = 1;
    }
    else if (field[0][0] == "empty" && field[0][1] == motion && field[0][2] == motion)
    {
        x = 0;
        y = 0;
    }
    else if (field[1][0] == motion && field[1][1] == motion && field[1][2] == "empty")
    {
        x = 1;
        y = 2;
    }
    else if (field[1][0] == motion && field[1][1] == "empty" && field[1][2] == motion)
    {
        x = 1;
        y = 1;
    }
    else if (field[1][0] == "empty" && field[1][1] == motion && field[1][2] == motion)
    {
        x = 1;
        y = 0;
    }
    else if (field[2][0] == motion && field[2][1] == motion && field[2][2] == "empty")
    {
        x = 2;
        y = 2;
    }
    else if (field[2][0] == motion && field[2][1] == "empty" && field[2][2] == motion)
    {
        x = 2;
        y = 1;
    }
    else if (field[2][0] == "empty" && field[2][1] == motion && field[2][2] == motion)
    {
        x = 2;
        y = 0;
    }
    else if (field[0][2] == motion && field[1][1] == motion && field[2][0] == "empty")
    {
        x = 2;
        y = 0;
    }
    else if (field[0][2] == motion && field[1][1] == "empty" && field[2][0] == motion)
    {
        x = 1;
        y = 1;
    }
    else if (field[0][2] == "empty" && field[1][1] == motion && field[2][0] == motion)
    {
        x = 0;
        y = 2;
    }
    else if (field[0][0] == motion && field[1][1] == motion && field[2][2] == "empty")
    {
        x = 2;
        y = 2;
    }
    else if (field[0][0] == motion && field[1][1] == "empty" && field[2][2] == motion)
    {
        x = 1;
        y = 1;
    }
    else if (field[0][0] == "empty" && field[1][1] == motion && field[2][2] == motion)
    {
        x = 0;
        y = 0;
    }

    return to_string(x) + to_string(y);

}

int hard_bot(string field[N][N], string motion, int i)
{
    int n;
    string str = check_field(field, motion);

    str = str[i];

    istringstream ist(str);
    ist >> n;
    
    return n;
}

int main()
{
    srand(time(NULL));

    //Sit - положение игры в данный момент
    int sit = 0;
    //sit 0 - до того, как игрок нажал любую клавишу
    //sit 1 - меню pvp pvb st
    //sit 2 - игра pvp
    //sit 3 - игра pvb
        //sit 8 - выбор сложности бота
    //sit 4 - st
    //sit 5 - победа ноликов/крестиков
    //sit 6 - ничья
    //sit 7 - проверка на выход

    bool isMusic;
    double volume;
    double volume_mem;
    double volume_max = 20.0;
    int bot_difficulty = 0;
    int x = 770;
    int x_ = 100;
    int flagDraw;
    int Music_num;
    int music_num_max = 5;
    int l = 0;

    string motion = "cross";

    string field[N][N] = 
    {
        {"empty", "empty", "empty"},
        {"empty", "empty", "empty"},
        {"empty", "empty", "empty"}
    };

    //Запись isMusic из файла
    ifstream isMusic_file_input("Files/isMusic.txt");
    isMusic_file_input >> isMusic;
    isMusic_file_input.close();

    //Запись volume из файла
    ifstream volume_file_inpute("Files/volume.txt");
    volume_file_inpute >> volume;
    volume_file_inpute.close();

    //Запись volume_mem из файла
    ifstream volume_mem_file_inpute("Files/volume_mem.txt");
    volume_mem_file_inpute >> volume_mem;
    volume_mem_file_inpute.close();
    
    //Запись Music_num из файла
    ifstream Music_num_file_inpute("Files/Music_num.txt");
    Music_num_file_inpute >> Music_num;
    Music_num_file_inpute.close();
    
    //Перевод из числа в строку
    string Music_num_c = to_string(Music_num);

    //Создание окна
    RenderWindow window(VideoMode(1280, 720), "Tic-tac-toe", Style::Close);
    
    //Загрузка заднего фона
    Object MenuBG("Images/BG/bg1.jpg", 0.0, 0.0);


    //Загрузка текстуры кнопки pvp
    Object pvp("Images/Text/pvp.png", 300, 290);

    //Загрузка текстуры кнопки pvb
    Object pvb("Images/Text/pvb.png", 300, 360);

    //Загрузка текстуры кнопки st
    Object st("Images/Text/st.png", 300, 430);

    //Загрузка текстуры кнопки ex
    Object ex("Images/Text/exit.png", 300, 500);

    //Загрузка текстуры кнопки back
    Object bc("Images/Text/back.png", 300, 500);

    //Загрузка текстуры кнопки music
    Object mc("Images/Text/music on.png", 300, 360);

    //Загрузка текстуры кнопки volume
    Object vl("Images/Text/volume.png", 300, 430);
    
    //Загрузка текстуры кнопки pvp
    Object mstyle("Images/Text/musics.png", 300, 290);
    
    //Загрузка текстуры кнопки pvp
    Object dif_easy("Images/Text/easy.png", 300, 400);
    
    //Загрузка текстуры кнопки pvp
    Object dif_hard("Images/Text/hard.png", 300, 490);
    
    //Загрузка текстуры клетка1
    Object cell1("Images/empty.png", 430, 240);
    //Загрузка текстуры клетка2
    Object cell2("Images/empty.png", 595, 240);
    //Загрузка текстуры клетка3
    Object cell3("Images/empty.png", 760, 240);
    //Загрузка текстуры клетка4
    Object cell4("Images/empty.png", 430, 375);
    //Загрузка текстуры клетка5
    Object cell5("Images/empty.png", 595, 375);
    //Загрузка текстуры клетка6
    Object cell6("Images/empty.png", 760, 375);
    //Загрузка текстуры клетка7
    Object cell7("Images/empty.png", 430, 510);
    //Загрузка текстуры клетка8
    Object cell8("Images/empty.png", 595, 510);
    //Загрузка текстуры клетка 9
    Object cell9("Images/empty.png", 760, 510);

    Music music;
    music.openFromFile("Music/OST-" + Music_num_c + ".wav");
    music.play();
    music.setLoop(true);

    //Главный цикл
    while (window.isOpen())
    {
        //Проверка окна на закрытие
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        
        //Вот тут можно кодить
        music.setVolume(volume);

        //Установка дефолтного скина кнопкам
        pvp.texture.loadFromFile("Images/Text/pvp.png");
        pvb.texture.loadFromFile("Images/Text/pvb.png");
        st.texture.loadFromFile("Images/Text/st.png");
        ex.texture.loadFromFile("Images/Text/exit.png");
        bc.texture.loadFromFile("Images/Text/back.png");
        vl.texture.loadFromFile("Images/Text/volume.png");
        mstyle.texture.loadFromFile("Images/Text/musics.png");
        dif_easy.texture.loadFromFile("Images/Text/easy.png");
        dif_hard.texture.loadFromFile("Images/Text/hard.png");

        if (sit == 7) { MenuBG.texture.loadFromFile("Images/BG/bg4.jpg"); }
        if (isMusic) { mc.texture.loadFromFile("Images/Text/music on.png"); }
        else { mc.texture.loadFromFile("Images/Text/music off.png"); }
        if (sit == 8) { MenuBG.texture.loadFromFile("Images/BG/bg2.5.jpg"); }

        cell1.texture.loadFromFile("Images/" + field[0][0] + ".png");
        cell2.texture.loadFromFile("Images/" + field[0][1] + ".png");
        cell3.texture.loadFromFile("Images/" + field[0][2] + ".png");
        cell4.texture.loadFromFile("Images/" + field[1][0] + ".png");
        cell5.texture.loadFromFile("Images/" + field[1][1] + ".png");
        cell6.texture.loadFromFile("Images/" + field[1][2] + ".png");
        cell7.texture.loadFromFile("Images/" + field[2][0] + ".png");
        cell8.texture.loadFromFile("Images/" + field[2][1] + ".png");
        cell9.texture.loadFromFile("Images/" + field[2][2] + ".png");

        window.clear();

        //Отрисовка bg
        window.draw(MenuBG.sprite);

        //Проверка ситуации игры
        switch (sit)
        {
        case 0:
            //Нажатие enter
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                //Смена фона
                MenuBG.texture.loadFromFile("Images/BG/bg1.jpg");

                //Смена ситуации игры
                sit = 1;
            }
            
            break;
        case 1:
            //Проверка на наведение мышки на кнопку
            if (IntRect(300, 290, 680, 50).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                pvp.texture.loadFromFile("Images/Text/pvp2.png");

                if (Mouse::isButtonPressed(Mouse::Left)) { sit = 2; Sleep(1000); }
            }
            //Проверка на наведение мышки на кнопку
            if (IntRect(380, 360, 520, 50).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                pvb.texture.loadFromFile("Images/Text/pvb2.png");

                if (Mouse::isButtonPressed(Mouse::Left)) { sit = 8; Sleep(100); }
            }
            //Проверка на наведение мышки на кнопку
            if (IntRect(480, 430, 320, 50).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                st.texture.loadFromFile("Images/Text/st2.png");

                if (Mouse::isButtonPressed(Mouse::Left)) { sit = 4; }
            }
            //Проверка на наведение мышки на кнопку
            if (IntRect(480, 500, 320, 50).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                ex.texture.loadFromFile("Images/Text/exit2.png");

                if (Mouse::isButtonPressed(Mouse::Left)) { sit = 7; }
            }
            
            break;
        case 4:
            Sleep(100);
            
            //Проверка на наведении мышки на кнопку
            if (IntRect(505, 500, 270, 50).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                bc.texture.loadFromFile("Images/Text/back2.png");
                if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Escape)) { sit = 1; Sleep(100); }
            }
            
            //Проверка на наведении мышки на кнопку
            if (IntRect(x, 360, x_, 50).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                if (isMusic) { mc.texture.loadFromFile("Images/Text/music on2.png"); }
                else { mc.texture.loadFromFile("Images/Text/music off2.png"); }

                if (Mouse::isButtonPressed(Mouse::Left)) 
                {
                    //Выключение / включение музыки
                    if (isMusic) { volume_mem = volume; volume = 0; isMusic = 0; x = 740; x_ = 130; }
                    else { volume = volume_mem; isMusic = 1; x = 770; x_ = 100; }
                }
            }

            //Проверка на наведении мышки на кнопку
            if (IntRect(735, 430, 40, 50).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                vl.texture.loadFromFile("Images/Text/volume2.png");

                if (Mouse::isButtonPressed(Mouse::Left) && volume > 0.5) { volume -= 0.5; }
            }

            //Проверка на наведении мышки на кнопку
            if (IntRect(825, 430, 40, 50).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                vl.texture.loadFromFile("Images/Text/volume3.png");

                if (Mouse::isButtonPressed(Mouse::Left) && volume < volume_max) { volume += 0.5; }
            }

            //Проверка на наведении мышки на кнопку
            if (IntRect(800, 290, 50, 55).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                mstyle.texture.loadFromFile("Images/Text/musics2.png");

                if (Mouse::isButtonPressed(Mouse::Left) && Music_num > 0) 
                {
                    Music_num -= 1;
                    
                    //Перевод из числа в строку
                    string Music_num_c = to_string(Music_num);

                    music.stop();
                    music.openFromFile("Music/OST-" + Music_num_c + ".wav");
                    if (isMusic) { music.play(); }
                }
            }

            //Проверка на наведении мышки на кнопку
            if (IntRect(870, 290, 50, 55).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                mstyle.texture.loadFromFile("Images/Text/musics3.png");

                if (Mouse::isButtonPressed(Mouse::Left) && Music_num < music_num_max) 
                {
                    Music_num += 1;
                    
                    //Перевод из числа в строку
                    string Music_num_c = to_string(Music_num);

                    music.stop();
                    music.openFromFile("Music/OST-" + Music_num_c + ".wav");
                    if (isMusic) { music.play(); }
                }
            }

            break;

        case 2:
            //Смена фона
            MenuBG.texture.loadFromFile("Images/BG/bg3.jpg");

            if (motion == "cross") 
            {
                
                if (IntRect(430, 240, 110, 110).contains(Mouse::getPosition(window))) {
                    if (Mouse::isButtonPressed(Mouse::Left) && (field[0][0] == "empty")) {
                        field[0][0] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(595, 240, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[0][1] == "empty")) {
                        field[0][1] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(760, 240, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[0][2] == "empty")) {
                        field[0][2] = motion;
                        motion = "zero";
                    }
                }



                else if (IntRect(430, 375, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[1][0] == "empty")) {
                        field[1][0] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(595, 375, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[1][1] == "empty")) {
                        field[1][1] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(760, 375, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[1][2] == "empty")) {
                        field[1][2] = motion;
                        motion = "zero";
                    }
                }



                else if (IntRect(430, 510, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[2][0] == "empty")) {
                        field[2][0] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(595, 510, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[2][1] == "empty")) {
                        field[2][1] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(760, 510, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[2][2] == "empty")) {
                        field[2][2] = motion;
                        motion = "zero";
                    }
                }
            }
            else if (motion == "zero") 
            {
                
                if (IntRect(430, 240, 110, 110).contains(Mouse::getPosition(window))) 
                {
                    if (Mouse::isButtonPressed(Mouse::Left) && (field[0][0] == "empty")) 
                    {
                        field[0][0] = motion;
                        motion = "cross";
                    }
                }

                else if (IntRect(595, 240, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[0][1] == "empty")) {
                        field[0][1] = motion;
                        motion = "cross";
                    }
                }

                else if (IntRect(760, 240, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[0][2] == "empty")) {
                        field[0][2] = motion;
                        motion = "cross";
                    }
                }



                else if (IntRect(430, 375, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[1][0] == "empty")) {
                        field[1][0] = motion;
                        motion = "cross";
                    }
                }

                else if (IntRect(595, 375, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[1][1] == "empty")) {
                        field[1][1] = motion;
                        motion = "cross";
                    }
                }

                else if (IntRect(760, 375, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[1][2] == "empty")) {
                        field[1][2] = motion;
                        motion = "cross";
                    }
                }



                else if (IntRect(430, 510, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[2][0] == "empty")) {
                        field[2][0] = motion;
                        motion = "cross";
                    }
                }

                else if (IntRect(595, 510, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[2][1] == "empty")) {
                        field[2][1] = motion;
                        motion = "cross";
                    }
                }

                else if (IntRect(760, 510, 110, 110).contains(Mouse::getPosition(window))) {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[2][2] == "empty")) {
                        field[2][2] = motion;
                        motion = "cross";
                    }
                }
            }

            if ((victory_check(field, "cross") == "cross") || (victory_check(field, "zero") == "zero")) { sit = 5; break; }

            flagDraw = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (field[i][j] != "empty") {
                        flagDraw++;
                    }
                }
            }

            if (flagDraw == 9) { sit = 6; }
            else { flagDraw = 0; }
           
            break;
        case 8:
            //Смена фона
            MenuBG.texture.loadFromFile("Images/BG/bg2.5.jpg");

            if (IntRect(520, 400, 230, 50).contains(Mouse::getPosition(window)))
            {
                dif_easy.texture.loadFromFile("Images/Text/easy2.png");
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    bot_difficulty = 1;
                    Sleep(1000);
                    sit = 3;
                }
            }
            
            if (IntRect(500, 485, 260, 55).contains(Mouse::getPosition(window)))
            {
                dif_hard.texture.loadFromFile("Images/Text/hard2.png");
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    bot_difficulty = 2;
                    Sleep(1000);
                    sit = 3;
                }
            }
        case 3:
            //Смена фона
            MenuBG.texture.loadFromFile("Images/BG/bg3.jpg");
            if (motion == "cross") 
            {
                if (IntRect(430, 240, 110, 110).contains(Mouse::getPosition(window))) 
                {
                    if (Mouse::isButtonPressed(Mouse::Left) && (field[0][0] == "empty")) 
                    {
                        field[0][0] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(595, 240, 110, 110).contains(Mouse::getPosition(window))) 
                {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[0][1] == "empty")) 
                    {
                        field[0][1] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(760, 240, 110, 110).contains(Mouse::getPosition(window))) 
                {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[0][2] == "empty")) 
                    {
                        field[0][2] = motion;
                        motion = "zero";
                    }
                }




                else if (IntRect(430, 375, 110, 110).contains(Mouse::getPosition(window))) 
                {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[1][0] == "empty")) 
                    {
                        field[1][0] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(595, 375, 110, 110).contains(Mouse::getPosition(window))) 
                {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[1][1] == "empty")) 
                    {
                        field[1][1] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(760, 375, 110, 110).contains(Mouse::getPosition(window))) 
                {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[1][2] == "empty")) 
                    {
                        field[1][2] = motion;
                        motion = "zero";
                    }
                }



                else if (IntRect(430, 510, 110, 110).contains(Mouse::getPosition(window))) 
                {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[2][0] == "empty")) 
                    {
                        field[2][0] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(595, 510, 110, 110).contains(Mouse::getPosition(window))) 
                {

                    if (Mouse::isButtonPressed(Mouse::Left) && (field[2][1] == "empty")) 
                    {
                        field[2][1] = motion;
                        motion = "zero";
                    }
                }

                else if (IntRect(760, 510, 110, 110).contains(Mouse::getPosition(window))) 
                {
                    if (Mouse::isButtonPressed(Mouse::Left) && (field[2][2] == "empty")) 
                    {
                        field[2][2] = motion;
                        motion = "zero";
                    }
                }
            }
            
            else if (motion == "zero") 
            {
                if (bot_difficulty == 1) 
                {
                    int x = rand() % 3;
                    int y = rand() % 3;

                    if (field[x][y] != "empty")
                    {
                        while (field[x][y] != "empty")
                        {
                            x = rand() % 3;
                            y = rand() % 3;
                        }
                    }
                    field[x][y] = "zero";
                }
                else if (bot_difficulty == 2) 
                {
                    int x;
                    int y;
                    
                    x = hard_bot(field, "zero", 0);
                    y = hard_bot(field, "zero", 1);

                    if (x == 3 || y == 3) 
                    {
                        x = hard_bot(field, "cross", 0);
                        y = hard_bot(field, "cross", 1);
                        if (x == 3 || y == 3) 
                        {
                            x = rand() % 3;
                            y = rand() % 3;

                            if (field[x][y] != "empty")
                            {
                                while (field[x][y] != "empty")
                                {
                                    x = rand() % 3;
                                    y = rand() % 3;
                                }
                            }
                        }
                    }
                    
                    field[x][y] = "zero";
                }

                window.draw(cell1.sprite); window.draw(cell2.sprite); window.draw(cell3.sprite);
                window.draw(cell4.sprite); window.draw(cell5.sprite); window.draw(cell6.sprite);
                window.draw(cell7.sprite); window.draw(cell8.sprite); window.draw(cell9.sprite);
                window.display();
                
                Sleep(1000);
                motion = "cross";

            }

            if ((victory_check(field, "cross") == "cross") || (victory_check(field, "zero") == "zero")) { sit = 5; break; }

            flagDraw = 0;
            for (int i = 0; i < 3; i++) 
            {
                for (int j = 0; j < 3; j++) 
                {
                    if (field[i][j] != "empty") 
                    {
                        flagDraw++;
                    }
                }
            }

            if (flagDraw == 9) { sit = 6; }
            else { flagDraw = 0; }
            
            break;

        case 7:
            if (Keyboard::isKeyPressed(Keyboard::Escape)) { sit = 1; }

            //Проверка на наведении мышки на кнопку
            if (IntRect(390, 435, 165, 70).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                MenuBG.texture.loadFromFile("Images/BG/bg4_2.jpg");
                window.draw(MenuBG.sprite);

                if (Mouse::isButtonPressed(Mouse::Left)) 
                {
                    window.close();
                }
            }

            //Проверка на наведении мышки на кнопку
            if (IntRect(750, 435, 130, 70).contains(Mouse::getPosition(window))) 
            {
                //Смена скина
                MenuBG.texture.loadFromFile("Images/BG/bg4_3.jpg");
                window.draw(MenuBG.sprite);
                if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Escape)) { sit = 1; }
            }
        }

        //Отрисовка кнопок
        if (sit == 1) { window.draw(pvp.sprite); window.draw(pvb.sprite); window.draw(st.sprite); window.draw(ex.sprite); MenuBG.texture.loadFromFile("Images/BG/bg2.jpg"); }
        if (sit == 4) { window.draw(bc.sprite); window.draw(mc.sprite); window.draw(vl.sprite); window.draw(mstyle.sprite); MenuBG.texture.loadFromFile("Images/BG/bg2.jpg"); }
        if (sit == 8) { window.draw(dif_easy.sprite); window.draw(dif_hard.sprite); }
        if (sit == 2 || sit == 3)
        {
            window.draw(cell1.sprite); window.draw(cell2.sprite); window.draw(cell3.sprite);
            window.draw(cell4.sprite); window.draw(cell5.sprite); window.draw(cell6.sprite);
            window.draw(cell7.sprite); window.draw(cell8.sprite); window.draw(cell9.sprite);
            if (sit == 2) 
            { 
                if (motion == "cross") { MenuBG.texture.loadFromFile("Images/BG/bg3_p1.jpg"); }
                else if (motion == "zero") { MenuBG.texture.loadFromFile("Images/BG/bg3_p2.jpg"); }
            }
            if (sit == 3)
            {
                if (motion == "cross") { MenuBG.texture.loadFromFile("Images/BG/bg3_p1_b.jpg"); }
                else if (motion == "zero") { MenuBG.texture.loadFromFile("Images/BG/bg3_p2_b.jpg"); }
            }
        }
        
        if (sit == 5 || sit == 6)
        {
            if (l == 1) {
                window.draw(cell1.sprite); window.draw(cell2.sprite); window.draw(cell3.sprite);
                window.draw(cell4.sprite); window.draw(cell5.sprite); window.draw(cell6.sprite);
                window.draw(cell7.sprite); window.draw(cell8.sprite); window.draw(cell9.sprite);
                window.display();
                Sleep(2000);
                
                for (int i = 0; i < N; i++) 
                {
                    for (int j = 0; j < N; j++) 
                    {
                        field[i][j] = "empty";
                    }
                }
                motion = "cross";
                
                bot_difficulty = 0;
                l = -1;
                sit = 1;
            }
            l++;
        }
        if (sit == 5) 
        {
            if (victory_check(field, "cross") == "cross") { MenuBG.texture.loadFromFile("Images/BG/bg3_kross.jpg");}
            else if (victory_check(field, "zero") == "zero") { MenuBG.texture.loadFromFile("Images/BG/bg3_zero.jpg"); }
            
            window.draw(cell1.sprite); window.draw(cell2.sprite); window.draw(cell3.sprite);
            window.draw(cell4.sprite); window.draw(cell5.sprite); window.draw(cell6.sprite);
            window.draw(cell7.sprite); window.draw(cell8.sprite); window.draw(cell9.sprite);
        }
        
        if (sit == 6) 
        {
            MenuBG.texture.loadFromFile("Images/BG/bg3_draw.jpg");

            window.draw(cell1.sprite); window.draw(cell2.sprite); window.draw(cell3.sprite);
            window.draw(cell4.sprite); window.draw(cell5.sprite); window.draw(cell6.sprite);
            window.draw(cell7.sprite); window.draw(cell8.sprite); window.draw(cell9.sprite);
        }

        window.display();
    }
    
    //Вывод в файл isMusic
    ofstream isMusic_file_output("Files/isMusic.txt");
    isMusic_file_output << isMusic;
    isMusic_file_output.close();

    //Вывод в файл volume
    ofstream volume_file_output("Files/volume.txt");
    volume_file_output << volume;
    volume_file_output.close();

    //Вывод в файл volume_mem
    ofstream volume_mem_file_output("Files/volume_mem.txt");
    volume_mem_file_output << volume;
    volume_mem_file_output.close();

    //Вывод в файл isMusic
    ofstream Music_num_file_output("Files/Music_num.txt");
    Music_num_file_output << Music_num;
    Music_num_file_output.close();

    return 0;
}