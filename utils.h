 
const char title[] = "Tiles";

 
const int M = 31;
const int N = 10;
const int MAX_HIGH_SCORES = 10;
std::string highScoreNames[MAX_HIGH_SCORES];
int highScoreValues[MAX_HIGH_SCORES];
int highScoreCount = 0;
bool showpauseimage = false;
bool  showhelpimage = false;
bool showchooseimage = false;
bool showBackgroundimage1 = false;
bool showBackgroundimage3 = false;
bool showBackgroundimage4 = false;
bool showhighscore = false;
bool back_image = false;

int gameGrid[M][N] = { 0 };
int p[7] = { 0 };
///////////////////////////////////////////these are the diffrent pieces used in this game /////////////////////



int point_1[4][2], point_2[4][2];

bool anamoly() {
    for (int i = 0; i < 4; i++)
        if (point_1[i][0] < 0 || point_1[i][0] >= N || point_1[i][1] >= M)
            return false;
        else if (gameGrid[point_1[i][1]][point_1[i][0]])
            return false;
    return true;
}
