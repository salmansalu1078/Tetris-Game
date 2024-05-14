#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<fstream>
#include<sstream>
#include<cstring>
#include<string>
#include <time.h>
#include <algorithm>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"

using namespace sf;
using namespace std;
Text createText(const Font& font, const string& str, const Vector2f& position, unsigned int characterSize, const Color& fillColor, Uint32 style) {
    Text text;
    text.setFont(font); // Set the font
    text.setString(str); // Set the string to display
    text.setCharacterSize(characterSize); // Set the character size (in points)
    text.setFillColor(fillColor); // Set the fill color
    text.setStyle(style); // Set the text style
    text.setPosition(position); // Set the position
    return text;
}
void drawOffsetRectangle(RenderWindow& window, const Vector2f& size, const Color& fillColor, const Vector2f& position, const Vector2f& offset, const Color& outlineColor, float outlineThickness) {
    // Create a rectangle shape
    RectangleShape rectangle(size);
    rectangle.setFillColor(fillColor);
    rectangle.setOutlineColor(outlineColor);
    rectangle.setOutlineThickness(outlineThickness);
    // Set the origin and position of the rectangle with the given offset
    rectangle.setOrigin(offset);
    rectangle.setPosition(position + offset); // Apply the offset to the position

    // Draw the rectangle
    window.draw(rectangle);
}
void loadHighScores() {
    std::string line;
    std::ifstream file("highscores.txt");
    highScoreCount = 0;

    while (std::getline(file, line) && highScoreCount < MAX_HIGH_SCORES) {
        size_t pos = line.find(',');
        if (pos != std::string::npos) {
            highScoreNames[highScoreCount] = line.substr(0, pos);
            highScoreValues[highScoreCount] = std::stoi(line.substr(pos + 1));
            std::cout << "Loaded high score: " << highScoreNames[highScoreCount] << ", " << highScoreValues[highScoreCount] << std::endl;
            highScoreCount++;

        }
    }
}

void saveHighScore(const std::string& playerNameText, int score) {
    std::cout << "Saving high score: " << playerNameText << ", " << score << std::endl;
    std::ofstream file("highscores.txt", std::ios_base::app);
    file << playerNameText << ',' << score << '\n';
}

bool compareHighScores(int index1, int index2) {
    return highScoreValues[index1] > highScoreValues[index2];
}
void selectionSort() {
    int i, j, maxIndex;

    for (i = 0; i < highScoreCount - 1; i++) {
        maxIndex = i;
        for (j = i + 1; j < highScoreCount; j++) {
            if (compareHighScores(j, maxIndex)) {
                maxIndex = j;
            }
        }
        std::swap(highScoreNames[maxIndex], highScoreNames[i]);
        std::swap(highScoreValues[maxIndex], highScoreValues[i]);
    }
}
int main()
{
    srand(time(0));
    //window is set according to the requirements 
    RenderWindow window(VideoMode(550, 650), title);
 // All the images are load from there and then texture and also sprite as well. 
    Texture obj0, obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8, obj9, obj10 , obj11 , obj12, obj13, obj14, obj15, obj16, obj17,  obj18 , obj19;
    obj0.loadFromFile("img/Welcome.jpeg");
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/back.jpg");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/tiles.png");
    obj5.loadFromFile("img/bomb (2) (1).png");
    obj6.loadFromFile("img/MainMenu.jpeg");
    obj7.loadFromFile("img/pause.png");
    obj8.loadFromFile("img/gameover.jpg");
    obj9.loadFromFile("img/Background_name.jpeg");
    obj10.loadFromFile("img/bg1.jpg");
    obj11.loadFromFile("img/pause.jpeg"); 
    obj12.loadFromFile("img/pausemenu.jpeg");
    obj13.loadFromFile("img/Help.png");
    obj14.loadFromFile("img/bg2.jpeg");
    obj15.loadFromFile("img/bg3.jpeg"); 
    obj16.loadFromFile("img/bg4.png");
    obj17.loadFromFile("img/backgroundimage2.jpeg");
    obj18.loadFromFile("img/score_back.jpeg");
    obj19.loadFromFile("img/bg52.jpg");
    //===========================All the sprites are load from here=============================== 
    Sprite  welcome(obj0), sprite(obj1), background(obj2), frame(obj3), shadow(obj4), bomb(obj5), startmenu(obj6), pause(obj7), gameover(obj8), back_name(obj9), block_back(obj10), pause1(obj11), pausemenu(obj12), help(obj13) , bg2(obj14) , bg3(obj15) , bg4(obj16) , backgroundimage2(obj17), score_back(obj18) , highscore_back(obj19);
        startmenu.setTexture(obj6);
    startmenu.setScale(window.getSize().x / startmenu.getLocalBounds().width,//  setscale is used to load the image on the full screen 
        window.getSize().y / startmenu.getLocalBounds().height);
    welcome.setTexture(obj0);
    welcome.setScale(window.getSize().x / welcome.getLocalBounds().width,
        window.getSize().y / welcome.getLocalBounds().height);
    back_name.setTexture(obj9);
    back_name.setScale(window.getSize().x / back_name.getLocalBounds().width,
        window.getSize().y / back_name.getLocalBounds().height);
    background.setTexture(obj2);
    background.setScale(window.getSize().x / background.getLocalBounds().width,
        window.getSize().y / background.getLocalBounds().height);
    back_name.setScale(window.getSize().x / background.getLocalBounds().width,
        window.getSize().y / background.getLocalBounds().height);
    backgroundimage2.setScale(window.getSize().x / backgroundimage2.getLocalBounds().width,
        window.getSize().y / backgroundimage2.getLocalBounds().height);
    gameover.setScale(window.getSize().x / gameover.getLocalBounds().width,
        window.getSize().y / gameover.getLocalBounds().height);
    highscore_back.setScale(window.getSize().x / highscore_back.getLocalBounds().width,
        window.getSize().y / highscore_back.getLocalBounds().height);
    help.setScale(window.getSize().x / help.getLocalBounds().width,
        window.getSize().y / help.getLocalBounds().height);
    //=========================//  the position is set for them where it had to be drawn =====================
    block_back.setPosition(28, 62); 
    bg2.setPosition(28, 62);
    bg3.setPosition(28, 62);
    bg4.setPosition(28, 62);
    frame.setPosition(Vector2f(-1, 20));
    frame.setScale(Vector2f(1.25f, 1.25f)); 
    sprite.setScale(Vector2f(1.15f, 1.15f));
    pause1.setPosition(Vector2f(508, 0));
    pausemenu.setPosition(Vector2f(87, 120)); 
    score_back.setPosition(245, 255);
    // =================================clock is declared which is used for all where the time is used 
    Clock clock;
    Time elapsed = clock.restart();

    //======================This code is for the music play ====================================
    Music bgMusic;
    bgMusic.openFromFile("audio/repeatedStage.ogg");
    bgMusic.setVolume(25);
    bgMusic.setLoop(true); // Loops music. 
    bgMusic.play();
    // Display the welcome image for 1 seconds
    while (elapsed.asSeconds() < 1.0)
    {
        window.clear();
        window.draw(welcome);
        window.display();

        elapsed = clock.getElapsedTime();
    }
   
    ////////////////////////////////Declaration & intialize(of some variable) of given variable//////////////////////

    int delta_x = 0, colorNum = 1;
    float timer = 0, delay = 0.3;
    int rotate = 0;
   
         //////////////////checks variable/////////////////    

    int bombcheck = 20;
    int bombcheck2 = 0, bombcheck3 = 1;
    int checkrotate = 0;
    int checkleft = 0;
    int checkright = 0;
    int checkharddrop = 0;
    int checkgamepause = 0, checkgamepause1 = 1, displaygamepause = 0;
    int windowstartcheck = 0;
    int checkgameover = 0;
   
    //////////////////simple variable////////////////

    int score = 0;
    double timelevel = 0;
    float timer1 = 0, delay1 = 0.3;
    int shadowarray[4][2];
    int xaxis = 25, yaxis = 0;
    int ncount = 0;
    int level = 1;
    int a1[4];
    int x = 0;
    int bombcolor = 2;

    ////////////////////font declare///////////////////
    Font font,salman,Player_name;
    salman.loadFromFile("font/LEMONMILK-Light.otf");
    font.loadFromFile("font/Soul_Calibur.ttf");
    Player_name.loadFromFile("font/Maximum Impact.ttf");

    /////for fist piece not to be not single block////

    int p = rand() % +1;

    for (int i = 0; i < 4; i++)
    {
        point_1[i][0] = BLOCKS[p][i] % 2;
        point_1[i][1] = BLOCKS[p][i] / 2;
    }

    //=============================Drawing the text for the mainmenuand the other functions===========================================
        Text text, leveldis;
        Text Newgame = createText(salman, " New Game!", Vector2f(142, 400), 15, Color::Cyan, Text::Bold | Text::Underlined);
        Text HighScore = createText(salman, "High Score", Vector2f(142, 440), 15, Color::Cyan, Text::Bold | Text::Underlined);
        Text Help = createText(salman, "Help", Vector2f(142, 480), 15, Color::Cyan, Text::Bold | Text::Underlined);
        Text Exit = createText(salman, "Exit", Vector2f(142, 520), 15, Color::Cyan, Text::Bold | Text::Underlined);
      Text PlayerName = createText(salman, "Player's Name ", Vector2f(195, 225), 20, Color::Black, Text::Bold | Text::Underlined);
        Text ENter_Name = createText(salman, "Enter Name :-  ", Vector2f(110, 352), 20, Color::Black, Text::Bold | Text::Underlined);
        Text Next = createText(salman, "Next  ", Vector2f(723, 36), 44, Color::White, Text::Bold | Text::Regular);
        Text Score = createText(salman, "Score  ", Vector2f(328, 270), 30, Color::White, Text::Bold | Text::Regular);
        Text Level = createText(salman, "Level  ", Vector2f(328, 405), 30, Color::White, Text::Bold | Text::Regular);
        Text Lines = createText(salman, "Lines  ", Vector2f(328, 520), 30, Color::White, Text::Bold | Text::Regular);
        Text Continue= createText(salman, "Continue  ", Vector2f(207, 250), 15, Color::Yellow, Text::Bold | Text::Regular);
        Text Restart = createText(salman, "Restart Game  ", Vector2f(207, 290), 15, Color::White, Text::Bold | Text::Regular);
        Text HighScore_pause = createText(salman, "See High Score  ", Vector2f(207, 325), 15, Color::White, Text::Bold | Text::Regular);
        Text Help_pause = createText(salman, "Help", Vector2f(207, 355), 15, Color::White, Text::Bold | Text::Regular);
        Text Exit_pause = createText(salman, "Exit", Vector2f(207, 385), 15, Color::White, Text::Bold | Text::Regular);
        Text change = createText(salman, "Change", Vector2f(200, 420), 15, Color::Red, Text::Bold | Text::Regular);
        Text Background = createText(salman, "Background", Vector2f(230, 435), 15, Color::Red, Text::Bold | Text::Regular);
        Text Total_Score = createText(salman, "Your Score:- ", Vector2f(99 ,243), 30, Color::White , Text::Bold | Text::Regular);
        Text StartNewgame = createText(salman, "Restart Game  ", Vector2f(99, 370), 30 ,  Color::White, Text::Bold | Text::Regular);
        Text Exit_End = createText(salman, "Exit  ", Vector2f(99, 450), 30, Color::White, Text::Bold | Text::Regular);
        Text Backgroundimage1 = createText(salman, " Change Backgroud Image 1  ", Vector2f(85, 120), 22, Color::Black, Text::Bold | Text::Regular);
        Text Backgroundimage3 = createText(salman, " Change Backgroud Image 2  ", Vector2f(85, 310), 22, Color::Black, Text::Bold | Text::Regular);
        Text Backgroundimage4 = createText(salman, " Change Backgroud Image 3  ", Vector2f(85, 490), 22, Color::Black, Text::Bold | Text::Regular);
 //========================Here is the declaration of the rectangles that are used in the input of player name =================== 
        RectangleShape rectangle(Vector2f(400, 150)); // Size: width = 400, height = 150
        RectangleShape Playername(Vector2f(240, 90));
        RectangleShape name(Vector2f(310, 70));
        rectangle.setPosition(87, 350);
        name.setPosition(137, 400); // Position the rectangle at (300, 200) on the window
        Playername.setPosition(166, 195); // Position the rectangle at (300, 200) on the window
        Playername.setFillColor(Color::White);
        rectangle.setFillColor(Color::White);
        name.setFillColor(Color(48 , 48 , 48));
        Text star;
            string playerNameText = "";
            Text playerNameDisplay;// Store the entered player name
            playerNameDisplay.setFont(salman); // Set the font
            playerNameDisplay.setCharacterSize(24); // Set the character size
            playerNameDisplay.setFillColor(Color::White); // Set the fill color
            playerNameDisplay.setStyle(Text::Bold); // Set the text style
            playerNameDisplay.setPosition(name.getPosition().x + 20, name.getPosition().y + 20); // Adjust position          
            RectangleShape square(Vector2f(50, 50));
            square.setFillColor(Color::Cyan);
            square.setOrigin(100, 100);
            square.setPosition(190, 852);

            Text enterNameText;
            enterNameText.setFont(font);
            enterNameText.setCharacterSize(24);
            enterNameText.setFillColor(Color::White);
            enterNameText.setPosition(35, 130);
            enterNameText.setString("Enter Name:");

            std::string playerName;

        //=====================Here is teh declaration of the stars that are printed in the input of name 
               const int numStars = 100;
                Vector2f starPositions[numStars];
                Color starColors[numStars];
                // Generate positions for the stars
               
                    starPositions[1] = Vector2f(1, 263);
                    starPositions[2] = Vector2f(30, 240);
                    starPositions[3] = Vector2f(55, 216);
                    starPositions[4] = Vector2f(81, 191);
                    starPositions[5] = Vector2f(107, 165);
                    starPositions[6] = Vector2f(134, 138);
                    starPositions[7] = Vector2f(162, 110);
                    starPositions[8] = Vector2f(191, 81);
                    starPositions[9] = Vector2f(221, 51);
                    starPositions[22] = Vector2f(252, 20);
                    starPositions[23] = Vector2f(284, -1);
                    starPositions[24] = Vector2f(54, 3);
                  // starPositions[25] = Vector2f(351, -1);

                    starPositions[10] = Vector2f(319, 20);
                    starPositions[11] = Vector2f(349, 51);
                    starPositions[12] = Vector2f(378, 81);
                    starPositions[13] = Vector2f(406, 110);
                    starPositions[14] = Vector2f(433, 138);
                    starPositions[15] = Vector2f(459, 165);
                    starPositions[16] = Vector2f(484, 191);
                    starPositions[17] = Vector2f(508, 216);
                    starPositions[18] = Vector2f(531, 240);
                    starPositions[19] = Vector2f(553, 263);
//==================This is the position of stars by loop .I cannot use it becuase it is more uniform and does not looks good 
                   /* starPositions[20] = Vector2f(939, 298);
                    starPositions[21] = Vector2f(978, 318);
                    starPositions[46] = Vector2f(978, -1);*/
                    // Define the initial position values
                   /* float xPos = 42.0f;
                    float yPos = 31.0f;*/

                    //// Loop to assign coordinates to each element of the array
                    //for (int i = 26; i <= 35; ++i) {
                    //    starPositions[i] = Vector2f(xPos, yPos);
                    //    xPos += 47.0f; // Increase x position by 60 units for each iteration
                    //    yPos += 24.0f; // Decrease y position by 24 units for each iteration
                    //}
                    //float xPos_1 = 518.0f;
                    //float yPos_1 = 231.0f;

                    //// Loop to assign coordinates to each element of the array
                    //for (int i = 36; i <= 45; ++i) {

                    //    starPositions[i] = Vector2f(xPos_1, yPos_1);
                    //    xPos_1 += 47.0f; // Increase x position by 60 units for each iteration
                    //    yPos_1 -= 24.0f; // Decrease y position by 24 units for each iteration
                    //}
                    













                    //////////widow contineous display start from here//////////////////////////
                    while (window.isOpen())
                    {
                        float time = clock.getElapsedTime().asSeconds();
                        clock.restart();
                        timer += time;
                        timer1 += time;
                        timelevel += time;
                        /////////////////////////////////////////part which cantain Keys retated work///////////////////////////////////
                        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
                        Event e;
                        while (window.pollEvent(e))
                        {
                            if (e.type == Event::Closed)
                                window.close();
                            if (e.type == Event::MouseMoved) {
                                // Get the current mouse position relative to the window
                                Vector2i mousePosition = Mouse::getPosition(window);
                                //ack_image = true; 
                                // Print the coordinates to the console
                                cout << "Mouse X: " << mousePosition.x << ", Mouse Y: " << mousePosition.y << endl;
                            }
                            if (e.type == Event::MouseButtonPressed) {

                                // Check if the mouse click is within the region of "New Game!"
                                Vector2i mousePosition = Mouse::getPosition(window);
                                if (Newgame.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {

                                    cout << "Clicked on New Game!" << endl;
                                    back_image = true;



                                }
                                //=======pause the game ======
                                if (pause1.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                                    showpauseimage = true;
                                }
                                //continue teh game 
                                if (Continue.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                                    showpauseimage = false;
                                }
                                //===========Restart the game 
                                if (Restart.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                                    // Reset game state
                                    timelevel = 0;
                                    level = 1;
                                    score = 0;
                                    for (int i = 30; i >= 0; i--)
                                        for (int j = 0; j <= 9; j++)
                                            gameGrid[i][j] = 0;
                                    displaygamepause = 0;
                                    checkgamepause = 0;
                                    checkgameover = 0;
                                    windowstartcheck == 1;

                                    // Generate new blocks
                                    int k = rand() % +1;
                                    for (int i = 0; i < 4; i++)
                                    {
                                        point_1[i][0] = BLOCKS[k][i] % 2;
                                        point_1[i][1] = BLOCKS[k][i] / 2;
                                    }
                                    showpauseimage = false; 
                                }
                                //===========shows the high score==============
                                if ((HighScore_pause.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) || (HighScore_pause.getGlobalBounds().contains(mousePosition.x, mousePosition.y))) {
                                    showhighscore = true; 
                                    back_image = false; 
                                    showpauseimage = false; 
                                }
                                //=============show the help ===============
                                if (Help_pause.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || Help.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                                    showhelpimage = true;
                                }
                        //==============Exit the game ============
                                if (Exit_pause.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || Exit_End.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || Exit.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                                    return 0;

                                }

                                if (change.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || Background.getGlobalBounds().contains(mousePosition.x, mousePosition.y) || Exit.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                                    showchooseimage = true;
                                }
                                // channges the background according to the user wants ============
                                if (Backgroundimage1.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                                    windowstartcheck = 1;
                                    showchooseimage = false;
                                    showpauseimage = false;
                                    showBackgroundimage1 = true;
                                }
                                if (Backgroundimage3.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                                    windowstartcheck = 1;
                                    showchooseimage = false;
                                    showpauseimage = false;
                                    showBackgroundimage3 = true;
                                }
                                if (Backgroundimage4.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                                    windowstartcheck = 1;
                                    showchooseimage = false;
                                    showpauseimage = false;
                                    showBackgroundimage4 = true;
                                }
                        //====================it restarts the game when game is end  =========
                                if (StartNewgame.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                                    windowstartcheck = 1; 
                                    showpauseimage = false;
                                    timelevel = 0;
                                    level = 1;
                                    score = 0;
                                    for (int i = 30; i >= 0; i--)
                                        for (int j = 0; j <= 10; j++)
                                            gameGrid[i][j] = 0;
                                    displaygamepause = 0;
                                    checkgamepause = 0;
                                    checkgameover = 0;
                                    windowstartcheck == 1;

                                    // Generate new blocks
                                    int k = rand() % +1;
                                    for (int i = 0; i < 4; i++)
                                    {
                                        point_1[i][0] = BLOCKS[k][i] % 2;
                                        point_1[i][1] = BLOCKS[k][i] / 2;
                                    }
                                }
                            }

                    //==================when name is entered it shows the board image ==========
                            if (back_image && e.type == Event::TextEntered) {
                                //                // Handle ASCII characters only
                                if (e.text.unicode >= 32 && e.text.unicode <= 126) {
                                    // Append character to player name text
                                    playerNameText += static_cast<char>(e.text.unicode);
                                    playerNameDisplay.setString(playerNameText); // Update the displayed player name  

                                }
                                // Handle backspace
                                else if (e.text.unicode == 8 && playerNameText.length() > 0) {
                                    // Remove last character from player name text
                                    playerNameText.pop_back();
                                    playerNameDisplay.setString(playerNameText); // Update the displayed player name

                                }
                            }
                            if (e.key.code == Keyboard::Enter && e.type == Event::KeyPressed) {
                                cout << "HY";
                                back_image = false;
                                windowstartcheck = 1;
                            }
                            //===========functions for the game paused ============
                            if (e.type == Event::KeyPressed)
                            {
                                if (e.key.code == Keyboard::Escape)
                                {
                                    showhelpimage = false;
                                    showhighscore = false;
                                }
                                if (e.type == Event::KeyPressed && e.key.code == Keyboard::Enter) {

                                }

                                if (e.key.code == Keyboard::Up)                           // this key is for rotation 
                                {
                                    checkrotate = 1;
                                }

                                else if (e.key.code == Keyboard::Left)                           // this key is for left move ment 
                                {
                                    checkleft = 1;
                                    delta_x = -1;
                                }
                                else if (e.key.code == Keyboard::Right)                           //this key is for right movement 
                                {
                                    checkright = 1;
                                    delta_x = 1;
                                }
                                else if (e.key.code == Keyboard::Space)                            //this key is for hard drop 
                                {
                                    checkharddrop = 1;
                                }
                                else if (e.key.code == Keyboard::H)                            //this key is for pause 
                                {
                                    showpauseimage = true;

                                }


                                else if (e.key.code == Keyboard::X)                            // this key is for close the window of game  
                                {
                                    window.close();
                                }
                                else if (e.key.code == Keyboard::R)                            //f this key is for restart 
                                {
                                    timelevel = 0;
                                    level = 1;
                                    score = 0;
                                    for (int i = 30; i >= 0; i--)
                                        for (int j = 0; j <= 10; j++)
                                            gameGrid[i][j] = 0;
                                    displaygamepause = 0;
                                    checkgamepause = 0;
                                    checkgameover = 0;
                                    int k = rand() % +1;

                                    for (int i = 0; i < 4; i++)
                                    {
                                        point_1[i][0] = BLOCKS[k][i] % 2;
                                        point_1[i][1] = BLOCKS[k][i] / 2;
                                    }



                                }
                            }
                        }
                        
                        if (Keyboard::isKeyPressed(Keyboard::Down))                      //this key is for fast downward movement 
                            delay = 0.05;


                        //////////////////////////////////////////////////////////////////////////////////////////////
                        //////////////////////////////////*** START CALLING YOUR FUNCTIONS HERE ***///////////////////

                        if (checkgamepause == 0 && windowstartcheck == 1)
                        {
                            if (checkgamepause1 == 2)
                            {
                                checkgamepause1 = 1;
                            }
                            if (!showpauseimage)
                                fallingPiece(timer, delay, colorNum); //faling piece function 

                            removeline(ncount);                       //remove line function i use this to remove line on spwcific condion
                            // that is when all row is completed it is removed by working of this function
                            //ncount is to calculate number of lines destroyed at a time and we use it in another
                            //function to count score that is why we use it by bypass

                            shadowfunction(shadowarray);                 //shadow falling function is for making shaodw according to coming
                            // block and shadowarray is its array which store coming block position
                            // and we use it to make shadow and we pass it by bypass mathod beacuse 
                            //we need it chage values to display it 

                            if (checkrotate == 1)
                                Block_rotate(rotate);                   //rotate function is for block roatation according and we need rotate value 
                            //to start rotation except at some checks
                            checkrotate = 0;

                            if (checkleft == 1)
                                left(delta_x);                          //left move function to move piece to left and delta_x is for how many unit we 
                            //have to use 
                            checkleft = 0;

                            if (checkright == 1)
                                right(delta_x);                        //right move function to move piece to right and delta_x is for how many unit we 
                            //have to use 
                            checkright = 0;

                            if (checkharddrop == 1)
                                harddrop();                           //haed drop function work according to + value in block till it reack to boundry or at back of a block
                            checkharddrop = 0;

                            scorevalidation(ncount, score);           //this is score count funtion according to line remove so we give it name validation as we have  to
                            //increase according to remove line we use score as bypass beacase we need score vale to diplay in main after 
                            //changes and ncount value direct because we need it only in function and after it we need not to do change in it   
                            if (!showpauseimage)
                                bombfun(bombcheck, bombcheck2, bombcheck3, xaxis, yaxis, timer1, delay1, bombcolor, score);  //bomb function use thrcheck which are basically at diffrent step for its work
                            //x and y axis are the cordinates of the block bombcolor is used to check in which ways
                            // line have to be destroyed delay and timer are for its working 

                            gameoverfun(checkgamepause, checkgameover);  //this is to stop game and display menue and score 
                            tmerfunction(timelevel, delay, level);         //this is for increse level conditions 

                        }

                        ///////////////////////////////////////////////*** YOUR CALLING STATEMENTS END HERE ***///////////////////////////
                        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////





                        ////////////////////////////////////////////given display////////////////////////////////////////////            

                        window.clear(Color::Black);
                        window.draw(background);
                        window.draw(score_back);
                        Text leveltex(std::to_string(level), font);
                        leveltex.setPosition(370, 430);
                        leveltex.setCharacterSize(100);
                        leveltex.setFillColor(Color::White);
                        //===========validation for teh background image ======
                        if (showBackgroundimage1) {
                            window.draw(bg2);
                        }
                        else  if (showBackgroundimage3 || leveltex.getString() == "2") {
                            window.draw(bg3);
                        }
                        else   if (showBackgroundimage4) {
                            window.draw(bg4);
                        }
                        else {
                            window.draw(block_back);
                        }window.draw(pause1);
                        for (int i = 0; i < M; i++)
                        {
                            for (int j = 0; j < N; j++)
                            {
                                if (gameGrid[i][j] == 0)
                                    continue;
                                sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                                sprite.setPosition(j * 18, i * 18);
                                sprite.move(28, 32); //offset
                                window.draw(sprite);
                            }
                        }
                        for (int i = 0; i < 4; i++)
                        {
                            sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                            sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
                            sprite.move(28, 31);
                            window.draw(sprite);
                        }



                        /////////////////////////////////////shadow display/////////////////////////////////////////////////////

                        for (int i = 0; i < 4; i++)
                        {
                            shadow.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                            shadow.setPosition(shadowarray[i][0] * 18, shadowarray[i][1] * 18);
                            shadow.move(28, 31);
                            shadow.setColor((Color(255, 255, 255, 50)));
                            window.draw(shadow);

                        }

                        /////////////////////////////////////////-bomb display///////////////////////////////////////////////            

                        if (bombcolor == 1)
                        {
                            bomb.setColor(Color::Red);
                            bomb.setPosition(xaxis * 18, yaxis * 18);
                            bomb.move(28, 31);
                            window.draw(bomb);
                        }
                        if (bombcolor == 2)
                        {
                            bomb.setColor(Color::Green);
                            bomb.setPosition(xaxis * 18, yaxis * 18);
                            bomb.move(28, 31);
                            window.draw(bomb);
                        }
                        if (bombcolor == 3)
                        {
                            bomb.setColor(Color::Magenta);
                            bomb.setPosition(xaxis * 18, yaxis * 18);
                            bomb.move(28, 31);
                            window.draw(bomb);
                        }
                        if (bombcolor == 4)
                        {
                            bomb.setColor(Color(255, 120, 0));
                            bomb.setPosition(xaxis * 18, yaxis * 18);
                            bomb.move(28, 31);
                            window.draw(bomb);
                        }
                        if (bombcolor == 5)
                        {
                            bomb.setColor(Color::Cyan);
                            bomb.setPosition(xaxis * 18, yaxis * 18);
                            bomb.move(28, 31);
                            window.draw(bomb);
                        }
                        if (bombcolor == 6)
                        {
                            bomb.setColor(Color::Blue);
                            bomb.setPosition(xaxis * 18, yaxis * 18);
                            bomb.move(28, 31);
                            window.draw(bomb);
                        }
                        if (bombcolor == 7)
                        {

                            bomb.setColor(Color::Yellow);
                            bomb.setPosition(xaxis * 18, yaxis * 18);
                            bomb.move(28, 31);
                            window.draw(bomb);
                        }
                        /////////////////////////////////////////////////for score display///////////////////////////////////////////


                        text.setFont(salman);
                        text.setString("Score");
                        text.setPosition(320, 260);
                        text.setCharacterSize(30);
                        text.setFillColor(Color::White);
                        text.setStyle(Text::Bold | Text::Underlined);

                        //////////////////////////////////////score dsplay////////////////////////////////////////////////////

                        Text dis_score(to_string(score), font);
                        dis_score.setPosition(370, 300);
                        dis_score.setCharacterSize(100);
                        dis_score.setFillColor(Color::White);
                        int remlines = score / 10;

                        //////////////////////////////////////////////display written level///////////////////////////////////////////

                        leveldis.setFont(salman);
                        leveldis.setString("Level");
                        leveldis.setPosition(337, 400);
                        leveldis.setCharacterSize(30);
                        leveldis.setFillColor(Color::White);
                        leveldis.setStyle(Text::Bold | Text::Underlined);
                        ///////////////////////////////////////////////display level/////////////////////////////////////////////////       




                                      
                        Text Lines_rem(std::to_string(remlines), font);
                        Lines_rem.setPosition(370, 530);
                        Lines_rem.setCharacterSize(100);
                        Lines_rem.setFillColor(Color::White);



                        window.draw(dis_score);
                        window.draw(Score);
                        window.draw(leveltex);
                        window.draw(Level);
                        window.draw(Lines);
                        window.draw(Lines_rem);

                        if (windowstartcheck == 0) {
                            window.draw(startmenu);
                            window.draw(Newgame);
                            window.draw(HighScore);
                            window.draw(Help);
                            window.draw(Exit);
                        }
                        if (back_image) {

                         
                            window.draw(back_name);
                            window.draw(Playername);
                            window.draw(rectangle);
                            window.draw(PlayerName);
                            window.draw(ENter_Name);
                            window.draw(name);
                            window.draw(playerNameDisplay);
                            windowstartcheck = 1;
                            for (int i = 0; i < numStars; i++) {
                                // Create star text with changing color

                                Text star = createText(salman, "*", starPositions[i], 40, starColors[i], Text::Bold | Text::Regular);
                                window.draw(star);
                            }
                        }
                        // these are the random rgb values that are print after evry 0.5 secod
                        static Clock colorClock;

                        if (colorClock.getElapsedTime().asSeconds() >= 0.5) {
                            colorClock.restart();
                            for (int i = 0; i < numStars; i++) {
                                // Generate new random color for each star
                                int r = rand() % 256;
                                int g = rand() % 256;
                                int b = rand() % 256;
                                starColors[i] = Color(r, g, b);
                            }
                        }


                        if (showpauseimage) {
                            window.draw(pausemenu);
                            window.draw(Continue);
                            window.draw(Restart);
                            window.draw(Help_pause);
                            window.draw(HighScore_pause);
                            window.draw(Exit_pause);
                            window.draw(change);
                            window.draw(Background);
                        }
                        if (showhelpimage) {
                            window.draw(help);
                        }
                        if (showchooseimage) {
                            window.draw(backgroundimage2);
                            window.draw(Backgroundimage1);
                            window.draw(Backgroundimage3);
                            window.draw(Backgroundimage4);
                        }
                        if (showhighscore) {
                            window.draw(highscore_back);
                            window.clear();

                            loadHighScores();
                            selectionSort();

                            // Display high scores header
                            Text highScoreTitle("HIGH SCORES", salman, 48);
                            highScoreTitle.setPosition(120, 20);
                            highScoreTitle.setFillColor(Color::Red);
                            window.draw(highScoreTitle);

                            // Display player name and score
                            int y_pos = 100;
                            for (int i = 0; i < highScoreCount; ++i) {
                                Text playerNameText(highScoreNames[i], salman, 24);
                                Text playerScoreText(std::to_string(highScoreValues[i]), salman, 24);

                                playerNameText.setPosition(250, y_pos);
                                playerScoreText.setPosition(400, y_pos);
                                window.draw(playerNameText);
                                window.draw(playerScoreText);

                                y_pos += 50;
                            }
                        }
                        if (displaygamepause == 1)

                            window.draw(pause);
                        if (displaygamepause == 1)

                            window.draw(pause);
                        if (checkgameover == 1)
                        {
                            saveHighScore(playerName, score);
                            window.draw(gameover);
                            Text dis_score(std::to_string(score), salman);
                            dis_score.setPosition(355, 290);
                            dis_score.setCharacterSize(40);
                            dis_score.setFillColor(Color::White);
                            window.draw(dis_score);
                            window.draw(StartNewgame);
                            window.draw(Total_Score);
                            window.draw(Exit_End);
                        }

                        window.display();
                    }
        return 0;
}





