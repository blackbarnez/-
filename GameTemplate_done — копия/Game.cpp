
#define WIN32_LEAN_AND_MEAN
#include "Engine.h"
#include <stdlib.h>
#include <memory.h>

#include <math.h>
#include <windows.h>
#include <wchar.h>
#include <stdio.h>

#include <string> 
#include <vector>

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

# define M_PI           3.14159265358979323846

using namespace std;

class Circle {
public:
    int rCircle;
    int xCircle;
    int yCircle;
    int colorCircle;

    Circle(int r, int color) {
        rCircle = 150;
        xCircle = 0;
        yCircle = 0;
        colorCircle = 2000;
    }

};

class Player {
public:
    int rPlayer;
    int xPlayer;
    int yPlayer;
    int xPlayer2;
    int yPlayer2;
    int colorPers;

    Player (int r, int color) {
        rPlayer = r;
        xPlayer = 0;
        yPlayer = 0;
        xPlayer2 = 0;
        yPlayer2 = 0;
        colorPers = color;
    }

    void drawPlayer(int thex, int they, int i, int j) {
        
            double a = i * M_PI / 180;

            int x = j * cos(a);
            int y = j * sin(a); 

            xPlayer = thex + (x + SCREEN_HEIGHT / 2);
            yPlayer = they + (y + SCREEN_WIDTH / 2);
            xPlayer2 = -thex + (x + SCREEN_HEIGHT / 2);
            yPlayer2 = -they + (y + SCREEN_WIDTH / 2);

            buffer[xPlayer][yPlayer] = colorPers;
            buffer[xPlayer2][yPlayer2] = colorPers;

    }

};


class Enemy {
public:
    int pEnemy;
    int xEnemy;
    int yEnemy;
    int colorEnemy;

    Enemy (int p, int color) {
        pEnemy = p;
        xEnemy = 0;
        yEnemy = 0;
        colorEnemy = color;
    }

    void draw() {

        for (int j = 0; j < pEnemy; j++) {
            buffer[xEnemy++][yEnemy] = colorEnemy;
        }
        for (int j = 0; j < pEnemy; j++) {
            buffer[xEnemy][yEnemy++] = colorEnemy;
        }
        for (int j = 0; j < pEnemy; j++) {
            buffer[xEnemy--][yEnemy] = colorEnemy;
        }
        for (int j = 0; j < pEnemy; j++) {
            buffer[xEnemy][yEnemy--] = colorEnemy;
        }
    }

};


double aPlayer = 0;

Player player1(15, 6000000);
Enemy enemy1(20, 9450800);
Enemy friend1(20, 4892940);

double thex = 0;
double they = 0;
double thex2 = 0;
double they2 = 0;


Circle circle(150, 2000);

static int thetic = 0;

static int score = 0;
static int chances = 3;

static bool flagPlayer = 1;
static bool dirPlayer = 1;

static bool flagScore = 0;
static bool flagChances = 0;

static bool flagEnemy = 1;
static int dirEnemy = 0;

static bool flagFriend = 1;
static int dirFriend = 0;

void collision(Player player, Enemy enemy, Enemy friend1) {

    for (int j = 0; j < enemy.pEnemy; j++) {
        enemy.xEnemy++;
        friend1.xEnemy++;
        if (player.xPlayer == enemy.xEnemy && player.yPlayer == enemy.yEnemy) {
            flagChances = 1;
            flagEnemy = 1;
        }
        if (player.xPlayer == friend1.xEnemy && player.yPlayer == friend1.yEnemy) {
            flagScore = 1;
            flagFriend = 1;
        }
        if (player.xPlayer2 == enemy.xEnemy && player.yPlayer2 == enemy.yEnemy) {
            flagChances = 1;
            flagEnemy = 1;
        }
        if (player.xPlayer2 == friend1.xEnemy && player.yPlayer2 == friend1.yEnemy) {
            flagScore = 1;
            flagFriend = 1;
        }
    }
    for (int j = 0; j < enemy.pEnemy; j++) {
        enemy.yEnemy++;
        friend1.yEnemy++;
        if (player.xPlayer == enemy.xEnemy && player.yPlayer == enemy.yEnemy) {
            flagChances = 1;
            flagEnemy = 1;
        }
        if (player.xPlayer == friend1.xEnemy && player.yPlayer == friend1.yEnemy) {
            flagScore = 1;
            flagFriend = 1;
        }
        if (player.xPlayer2 == enemy.xEnemy && player.yPlayer2 == enemy.yEnemy) {
            flagChances = 1;
            flagEnemy = 1;
        }
        if (player.xPlayer2 == friend1.xEnemy && player.yPlayer2 == friend1.yEnemy) {
            flagScore = 1;
            flagFriend = 1;
        }
    }
    for (int j = 0; j < enemy.pEnemy; j++) {
        enemy.xEnemy--;
        friend1.xEnemy--;
        if (player.xPlayer == enemy.xEnemy && player.yPlayer == enemy.yEnemy) {
            flagChances = 1;
            flagEnemy = 1;
        }
        if (player.xPlayer == friend1.xEnemy && player.yPlayer == friend1.yEnemy) {
            flagScore = 1;
            flagFriend = 1;
        }
        if (player.xPlayer2 == enemy.xEnemy && player.yPlayer2 == enemy.yEnemy) {
            flagChances = 1;
            flagEnemy = 1;
        }
        if (player.xPlayer2 == friend1.xEnemy && player.yPlayer2 == friend1.yEnemy) {
            flagScore = 1;
            flagFriend = 1;
        }
    }
    for (int j = 0; j < enemy.pEnemy; j++) {
        enemy.yEnemy--;
        friend1.yEnemy--;
        if (player.xPlayer == enemy.xEnemy && player.yPlayer == enemy.yEnemy--) {
            flagChances = 1;
            flagEnemy = 1;
        }
        if (player.xPlayer == friend1.xEnemy && player.yPlayer == friend1.yEnemy--) {
            flagScore = 1;
            flagFriend = 1;
        }
        if (player.xPlayer2 == enemy.xEnemy && player.yPlayer2 == enemy.yEnemy--) {
            flagChances = 1;
            flagEnemy = 1;
        }
        if (player.xPlayer2 == friend1.xEnemy && player.yPlayer2 == friend1.yEnemy--) {
            flagScore = 1;
            flagFriend = 1;
        }
    }
}

void initialize()
{
   
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game(); 

  HWND hwnd = GetActiveWindow();
  HDC hdc = GetDC(hwnd);

  string scorestr = "Score: " + to_string(score);
  LPCSTR scorel = scorestr.c_str();
  TextOutA(hdc, 50, 50, scorel, strlen(scorestr.c_str()));

  string chancesstr = "Chances: " + to_string(chances);
  LPCSTR chancesl = chancesstr.c_str();
  TextOutA(hdc, 50, 80, chancesl, strlen(chancesstr.c_str()));

  if (flagScore  == 1) {
      score += 5;
      flagScore = 0;
  }

  if (flagChances == 1) {
      chances--;
      flagChances = 0;
  }

  if (chances <= 0) {
      score = 0;
      finalize();
      chances = 3;
      flagFriend = 1;
      flagEnemy = 1;
  }

  clear_buffer();
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));

    for (int j = circle.rCircle; j >= circle.rCircle - 5; j--) {
        for (int i = 0; i < 360; i++) {

            double a = i * M_PI / 180;
            int x = j * cos(a);
            int y = j * sin(a);
            buffer[x + SCREEN_HEIGHT / 2][y + SCREEN_WIDTH / 2] = circle.colorCircle;

        }
    }


    aPlayer = thetic * 0.5 * M_PI / 180;

    if (is_key_pressed(VK_SPACE)) {
        if (flagPlayer == 1) {
            if (dirPlayer == 1) {
                dirPlayer = 0;
            }
            else {
                dirPlayer = 1;
            }
            flagPlayer = 0;
        }
    }
    else {
        flagPlayer = 1;
    }

    switch (dirPlayer) {

    case 1:
        thetic++;
        break;
    case 0:
        thetic--;
        break;
    }

    thex = circle.rCircle * cos(aPlayer);
    they = circle.rCircle * sin(aPlayer);

    if (flagEnemy == 1) {
        enemy1.xEnemy = SCREEN_HEIGHT - 21;
        enemy1.yEnemy = 21 + rand() % SCREEN_WIDTH - 21;

        if (enemy1.yEnemy <= SCREEN_WIDTH / 2 - circle.rCircle) {
            dirEnemy = 0;
        }
        else if (enemy1.yEnemy > SCREEN_WIDTH / 2 - circle.rCircle && enemy1.yEnemy < SCREEN_WIDTH / 2 + circle.rCircle) {
            dirEnemy = 1;
        }
        else if (enemy1.yEnemy >= SCREEN_WIDTH / 2 + circle.rCircle) {
            dirEnemy = 2;
        }

        flagEnemy = 0;
    }

    if (enemy1.xEnemy <= SCREEN_HEIGHT  && enemy1.xEnemy >= 0 && enemy1.yEnemy <= SCREEN_WIDTH && enemy1.yEnemy >= 0) {

        switch (dirEnemy)
        {
        case 0:
            enemy1.xEnemy--;
            enemy1.yEnemy++;
            break;
        case 1:
            enemy1.xEnemy--;
            break;
        case 2:
            enemy1.xEnemy--;
            enemy1.yEnemy--;
            break;
        }
    }
    else flagEnemy = 1;


    if (flagFriend == 1) {
        friend1.xEnemy = SCREEN_HEIGHT - 21;
        friend1.yEnemy = 21 + rand() % SCREEN_WIDTH - 21;

        if (friend1.yEnemy <= SCREEN_WIDTH / 2 - circle.rCircle) {
            dirFriend = 0;
        }
        else if (friend1.yEnemy > SCREEN_WIDTH / 2 - circle.rCircle && friend1.yEnemy < SCREEN_WIDTH / 2 + circle.rCircle) {
            dirFriend = 1;
        }
        else if (friend1.yEnemy >= SCREEN_WIDTH / 2 + circle.rCircle) {
            dirFriend = 2;
        }

        flagFriend = 0;
    }

    if (friend1.xEnemy <= SCREEN_HEIGHT && friend1.xEnemy >= 0 && friend1.yEnemy <= SCREEN_WIDTH && friend1.yEnemy >= 0) {

        switch (dirFriend)
        {
        case 0:
            friend1.xEnemy--;
            friend1.yEnemy++;
            break;
        case 1:
            friend1.xEnemy--;
            break;
        case 2:
            friend1.xEnemy--;
            friend1.yEnemy--;
            break;
        }
    }
    else flagFriend = 1;

    for (int j = 1; j <= player1.rPlayer; j++) {

        for (int i = 0; i < 360; i++) {

            player1.drawPlayer(thex, they, i, j);

            if (j == player1.rPlayer)
            collision(player1, enemy1, friend1);
        }
    }

    enemy1.draw();
    friend1.draw();
}

// free game data in this function
void finalize()
{
    clear_buffer();
    Sleep(1000);
}

