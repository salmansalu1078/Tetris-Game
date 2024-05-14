
#include <iostream>
#include <SFML/Audio.hpp>
using namespace std;




// Add this function to perform selection sort

void fallingPiece(float& timer, float& delay, int& colorNum)
{
    sf::SoundBuffer buffer;
    sf::Sound sound;

    buffer.loadFromFile("audio/bombaDrop.wav"); // Sound that plays when the bomb drops.
    sound.setBuffer(buffer);
    if (timer > delay)
    {
        for (int i = 0; i < 4; i++)
        {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            point_1[i][1] += 1;                   //How much units downward
        }
        if (!anamoly())
        {
            for (int i = 0; i < 4; i++)
                gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
            colorNum = 1 + rand() % 7;
            int n = rand() % 7;
            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
            }

        }
        timer = 0;
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
////////////////////////////////////score validation for count of score/////////////////
void scorevalidation(int ncount, int& score)
{
    if (ncount == 1)                                                         //when ncount is 1, 10 score is added
        score += 20;
    else if (ncount == 2)                                                    //when ncount is 2, 30 score is added
        score += 30;
    else if (ncount == 3)                                                    //when ncount is 3, 60 score is added
        score += 60;
    else if (ncount == 4)                                                    //when ncount is 4, 100 score is added
        score += 80;
    else if (ncount == 5)                                                    //when ncount is 5, 200 score is added
        score += 100;
    else if (ncount >= 6)                                                          //when a row of blocks is removed and it contains 5 or more blocks, 50 extra points are awarded
        score += 120;
    else if (ncount >= 7) {
        score += 140; 
    }
}


///////////////////////////////////time function acording to level////////////////////////

void tmerfunction(double& timelevel, float& delay, int& level)
{

    if (timelevel < 40)                                                     //timelevel is when less than 50 delay is 0.3
    {

        delay = 0.3;
    }
    if (timelevel > 40)                                                    //timelevel is when greater than 50 delay is 0.1 and level is 2
    {
        delay = 0.1;
        level = 2;
    }
}
//////////////////////////////////////////file Handling Function ////////////////////////////////////
void scoreInString(int& score, sf::Text& textScore)
{
    char a[10] = {};
    int digit = 0;
    for (int i = 5; i >= 0; i--) // Max value of an int is billion, so 10 positions.
    {
        digit = 0;
        digit = score / pow(10, (5 - i));
        digit = digit % 10;
        digit += 48;
        a[i] = char(digit);
    }
    string b = a;
    textScore.setString(b);
}

// Same functionality as scoreInString except with an std::string return data type.
// scoreInString was not edited so the already existing code was not affected.
string scoreInStringFile(int score) // This was declared later for the file handling strings.
{
    char a[10] = {};
    int digit = 0;
    for (int i = 5; i >= 0; i--) // Max value of an int is billion, so 10 positions.
    {
        digit = 0;
        digit = score / pow(10, (5 - i));
        digit = digit % 10;
        digit += 48;
        a[i] = char(digit);
    }
    return a;
}
/////////////////////////////////////////shadow function///////////////////////////////////////////

void shadowfunction(int shadowarray[][2])                         //import shadowarray to form shadow according to the block 
{
    int llcheck = 0;                                                   //this is check for entering the code                                    
    for (int i = 0; i < 4; i++)
    {
        if (point_1[i][1] == 30)                                       //to remove shadow at line 19 
            llcheck = 1;
    }
    if (llcheck == 0)
    {
        for (int j = 0; j < 4; j++)                                       //store the values of piece in shadow
        {
            shadowarray[j][0] = point_1[j][0];
            shadowarray[j][1] = point_1[j][1];
        }
        int check = 1;
        while (check == 1)                                                //contineous loop start
        {
            for (int i = 0; i < 4; i++)
            {
                ++shadowarray[i][1];                                //increase in y value of the block

                if (shadowarray[i][1] > 29)
                    check = 0;
                if (gameGrid[shadowarray[i][1] + 1][shadowarray[i][0]] != 0)   //this is validation to check is there a block next to shadow
                    check = 0;
            }
        }
    }

}

//////////////////////////////////////////////////hard drop////////////////////////////////////////////////


void harddrop()
{
    bool check = true;
    for (int i = 0; i < 4; i++)
        if (point_1[i][1] == 31)                                                //this is for stop falling for 19 line 
            check = false;
    while (check == true)                                                //this is loop whis stop when check goes to false
    {
        for (int i = 0; i < 4; i++)
        {
            point_1[i][1] = point_1[i][1] + 1;
            if (gameGrid[point_1[i][1] + 1][point_1[i][0]] != 0)    //this is validation to check is there a block next to shadow
                check = false;

        }
    }
}



//////////////////////////////////////////////Left move Function///////////////////////////////////////////




void left(int delta_x)
{
    int blockstopl = 1;
    for (int i = 0; i < 4; i++)
    {
        if (gameGrid[point_1[i][1]][point_1[i][0] - 1])                  // check is there a block in left side 
            blockstopl = 0;
    }
    if (blockstopl == 1)                                              //this is in normal condition is true 
    {
        int x = 0;
        for (int i = 0; i < 4; i++)
        {
            if (point_1[i][0] < 1)                                  //validation for last column 
                x = 1;
        }
        if (x != 1)
        {

            for (int i = 0; i < 4; i++)
                point_1[i][0] += delta_x;                                //decrease  in x value of block
        }
    }
}
///////////////////////////////////////////////Right move function////////////////////////////////////    

void right(int delta_x)
{
    int blockstopl = 1;
    for (int i = 0; i < 4; i++)
    {
        if (gameGrid[point_1[i][1]][point_1[i][0] + 1])                  // check is there a block in right side
            blockstopl = 0;
    }
    if (blockstopl == 1)                                                 //this is in normal condition is true 
    {
        int x = 0;
        for (int i = 0; i < 4; i++)
        {
            if (point_1[i][0] > 8)                                   //validation for last column 
                x = 1;
        }
        if (x != 1)
        {

            for (int i = 0; i < 4; i++)
                point_1[i][0] += delta_x;                         //decrease  in x value of block
        }
    }
}

//////////////////////////////////////////////////////bomb function////////////////////////////////////         

void bombfun(int& bombcheck, int& bombcheck2, int& bombcheck3, int& xaxis, int& yaxis, float& timer1, float& delay1, int& bombcolor, int& score)
{
    bombcheck = rand() % 100;                                          //for random generate bomb by picking from 80000
    if (bombcheck == 5)
        bombcheck2 = 1;
    if (timer1 > delay1)
    {

        if (bombcheck == 5 || bombcheck2 == 1)                         // check for entering in bomb code 
        {

            if (bombcheck3 == 1)                                         //check if fulfiled bomb start on screen 
            {
                bombcolor = rand() % 7 + 1;
                xaxis = rand() % 9;
                bombcheck3 = 0;
            }

            int x = 0, k = 0;
            if (yaxis == 30)                                            //this to disapear bomb at 31 row 
                k = 1;
            if (k == 0)
            {
                if (gameGrid[yaxis + 1][xaxis] != 0)                      //comdion for blast of bomb
                    x = 1;
                if (x == 0)
                    ++yaxis;
                if (x == 1)
                {
                    if (gameGrid[yaxis + 1][xaxis] == bombcolor)           //if next piece is of bomb color
                    {
                        for (int i = 0; i < 31; i++)
                            for (int j = 0; j < 10; j++)
                                gameGrid[i][j] = 0;

                        bombcheck2 = 0;
                        xaxis = 25;
                        bombcheck3 = 1;
                        yaxis = 0;
                        score += 50; // Increment score by 50 when bomb explodes

                    }
                    else                                            //if next piece is of not bomb color
                    {
                        for (int i = (yaxis + 1); i < (yaxis + 3); i++)
                            for (int j = (xaxis); j < (xaxis + 2); j++)
                                gameGrid[i][j] = 0;

                        bombcheck2 = 0;
                        xaxis = 25;
                        bombcheck3 = 1;
                        yaxis = 0;

                    }
                }
            }
            else                                              //if random value is not meet to given condion(5)
            {
                bombcheck2 = 0;
                xaxis = 25;
                bombcheck3 = 1;
                yaxis = 0;
            }
            timer1 = 0;
        }
    }
}



///////////////////////////////////////////////remove line function//////////////////////////////////////////

void removeline(int& ncount)
{
    ncount = 0;
    for (int i = 30; i > 0; i--)                                  //for check rows from bottom to top  
    {

        int a = 0;
        for (int j = 0; j < 10; j++)                                 //for check column from left to right
        {

            if (gameGrid[i][j] != 0)                             //to count how many blocks are in row 
            {
                ++a;
            }
            if (a == 10)
            {

                ncount = ncount + 1;
                for (int k = i; k > 0; k--)
                {
                    for (int l = 0; l < 10; l++)
                    {
                        gameGrid[k][l] = gameGrid[k - 1][l];          //remove row

                    }

                }
                ++i;                                     //this is to check uper row again

            }
        }
    }

}

////////////////////////////////////////////////Rotate///////////////////////////////////////////////////////          
void Block_rotate(int rotate)
{
    int xr = 0;
    bool square = false;
    int c = 0;
    int checkarray[4][2];

    for (int i = 0; i < 4; i++)
    {
        if (gameGrid[point_1[i][1]][point_1[i][0] + 1] || gameGrid[point_1[i][1]][point_1[i][0] - 1])
            rotate = 1;
    }
    if (rotate == 0)
    {
        for (int j = 0; j < 4; j++)
        {
            checkarray[j][0] = point_1[j][0];
            checkarray[j][1] = point_1[j][1];
        }
        if (c == 0)
        {
            for (int i = 0; i < 4; i++)
            {


                int sh1 = checkarray[i][1] - checkarray[0][1];
                int sh2 = checkarray[i][0] - checkarray[0][0];
                checkarray[i][0] = checkarray[0][0] - sh1;
                checkarray[i][1] = checkarray[0][1] + sh2;

            }
            for (int i = 0; i < 4; i++)
            {
                if (checkarray[i][0] < 0 || checkarray[i][0]>9)
                    xr = 1;
            }
            if (point_1[0][0] == point_1[2][0] && point_1[1][0] == point_1[3][0] && point_1[0][1] == point_1[1][1] && point_1[2][1] == point_1[3][1])
                square = true;
            if (!square)
            {
                for (int i = 0; i < 4; i++)
                {

                    if (xr != 1)
                    {
                        int sh1 = point_1[i][1] - point_1[0][1];
                        int  sh2 = point_1[i][0] - point_1[0][0];
                        point_1[i][0] = point_1[0][0] - sh1;
                        point_1[i][1] = point_1[0][1] + sh2;
                        c = 1;

                    }
                }
            }
            xr = 0;
        }
        for (int j = 0; j < 4; j++)
        {
            checkarray[j][0] = point_1[j][0];
            checkarray[j][1] = point_1[j][1];
        }
        if (c == 0)
        {
            for (int i = 0; i < 4; i++)
            {


                int sh1 = checkarray[i][1] - checkarray[3][1];
                int sh2 = checkarray[i][0] - checkarray[3][0];
                checkarray[i][0] = checkarray[3][0] - sh1;
                checkarray[i][1] = checkarray[3][1] + sh2;

            }
            for (int i = 0; i < 4; i++)
            {
                if (checkarray[i][0] < 0 || checkarray[i][0]>9)
                    xr = 1;

            }
            if (point_1[0][0] == point_1[2][0] && point_1[1][0] == point_1[3][0] && point_1[0][1] == point_1[1][1] && point_1[2][1] == point_1[3][1])
                square = true;
            if (!square)
            {

                for (int i = 0; i < 4; i++)
                {

                    if (xr != 1)
                    {
                        int sh1 = point_1[i][1] - point_1[3][1];
                        int sh2 = point_1[i][0] - point_1[3][0];
                        point_1[i][0] = point_1[3][0] - sh1;
                        point_1[i][1] = point_1[3][1] + sh2;
                        c = 1;
                    }
                }
            }
        }
        for (int j = 0; j < 4; j++)
        {
            checkarray[j][0] = point_1[j][0];
            checkarray[j][1] = point_1[j][1];
        }
        if (c == 0)
        {
            for (int i = 0; i < 4; i++)
            {

                int sh1 = checkarray[i][1] - checkarray[1][1];
                int sh2 = checkarray[i][0] - checkarray[1][0];
                checkarray[i][0] = checkarray[1][0] - sh1;
                checkarray[i][1] = checkarray[1][1] + sh2;

            }
            for (int i = 0; i < 4; i++)
            {
                if (checkarray[i][0] < 0 || checkarray[i][0]>9)
                    xr = 1;
            }
            if (point_1[0][0] == point_1[2][0] && point_1[1][0] == point_1[3][0] && point_1[0][1] == point_1[1][1] && point_1[2][1] == point_1[3][1])
                square = true;
            if (!square)
            {

                for (int i = 0; i < 4; i++)
                {

                    if (xr != 1)
                    {
                        int sh1 = point_1[i][1] - point_1[1][1];
                        int sh2 = point_1[i][0] - point_1[1][0];
                        point_1[i][0] = point_1[1][0] - sh1;
                        point_1[i][1] = point_1[1][1] + sh2;
                        c = 1;
                    }
                }
                xr = 0;
            }
        }
        for (int j = 0; j < 4; j++)
        {
            checkarray[j][0] = point_1[j][0];
            checkarray[j][1] = point_1[j][1];
        }
        if (c == 0)
        {
            for (int i = 0; i < 4; i++)
            {


                int sh1 = checkarray[i][1] - checkarray[2][1];
                int sh2 = checkarray[i][0] - checkarray[2][0];
                checkarray[i][0] = checkarray[2][0] - sh1;
                checkarray[i][1] = checkarray[2][1] + sh2;

            }
            for (int i = 0; i < 4; i++)
            {
                if (checkarray[i][0] < 0 || checkarray[i][0]>9)
                    xr = 1;
            }
            if (point_1[0][0] == point_1[2][0] && point_1[1][0] == point_1[3][0] && point_1[0][1] == point_1[1][1] && point_1[2][1] == point_1[3][1])
                square = true;
            if (!square)
            {

                for (int i = 0; i < 4; i++)
                {

                    if (xr != 1)
                    {
                        int sh1 = point_1[i][1] - point_1[2][1];
                        int sh2 = point_1[i][0] - point_1[2][0];
                        point_1[i][0] = point_1[2][0] - sh1;
                        point_1[i][1] = point_1[2][1] + sh2;
                        c = 1;
                    }
                }
                xr = 0;
            }
        }

    }
}

///////////////////////////////////////////////game over/////////////////////////////////////////////
void gameoverfun(int& checkgamepause, int& checkgameover)
{
    for (int i = 0; i <= 9; i++)
    {
        if (gameGrid[0][i] != 0)                                 //to check is there any block at boundry 
        {
            checkgamepause = 1;
            checkgameover = 1;
        }

    }



}


///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////







