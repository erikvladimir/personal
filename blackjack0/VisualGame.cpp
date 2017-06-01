//
//  VisualGame.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//  Copyright © 2017 Erik V. Ortega. All rights reserved.
//

#include "VisualGame.hpp"


#include <curses.h>

#define TICKRATE 100

#define WORLD_WIDTH 50
#define WORLD_HEIGHT 20

#define USING_CURSES


#ifdef USING_CURSES
#define PRINT printw
#define GETC getch
#else
#define PRINT printf
#endif

void VisualGame::initialise()
{
    
    setlocale (LC_ALL, "");
    initscr();
    
    
    
    if(has_colors() == FALSE)
    {	endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    noecho();
    
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(2, COLOR_WHITE, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(4, COLOR_BLUE, COLOR_WHITE);
    init_pair(5, COLOR_BLACK, COLOR_YELLOW);
    init_pair(6, COLOR_WHITE, COLOR_BLUE);
    
    
    init_pair(10, COLOR_BLACK, COLOR_WHITE);
    init_pair(11, COLOR_RED, COLOR_WHITE);
    
    cbreak();
    //timeout(TICKRATE);
    keypad(stdscr, TRUE);
}

void VisualGame::deinitialise()
{
    endwin();
}

VisualGame::VisualGame():
    Game()
{
    initialise();
}

VisualGame::~VisualGame()
{
    deinitialise();
}

void VisualGame::drawRoundMenu() const
{
    constexpr uint line = 22;
    if (m_state == PLAY)
    {
        attron(COLOR_PAIR(1));
        move(line, 15);
        printw(" [H] : HIT  ");
        attroff(COLOR_PAIR(1));
    
        attron(COLOR_PAIR(2));
        move(line, 35);
        printw(" [S] : STAND  ");
        attroff(COLOR_PAIR(2));
    
        attron(COLOR_PAIR(3));
        move(line, 55);
        printw(" [X] : EXIT  ");
        attroff(COLOR_PAIR(3));
    }
    else if (m_state == WAIT)
    {
        attron(COLOR_PAIR(3));
        move(line, 28);
        printw("    Press any key to continue  ");
        attroff(COLOR_PAIR(3));
    }
    else if (m_state == DEALER_HAND)
    {
        attron(COLOR_PAIR(3));
        move(line, 28);
        printw("    Dealer is playing its hand  ");
        attroff(COLOR_PAIR(3));
    }
}

void VisualGame::drawScores() const
{
    attron(COLOR_PAIR(6));
    constexpr uint line = 1;
    constexpr uint column = 6;
    for (uint i=0; i<4; i++)
    {
        move(line+i, column);
        printw("               ");
    }
    move(line,   column);  printw(" Scores:      ");
    move(line+1, column);  printw(" Player:  %2u ", m_scores.player);
    move(line+2, column);  printw(" Dealer:  %2u ", m_scores.dealer);
    move(line+3, column);  printw(" Ties:    %2u ", m_scores.ties);
    attroff(COLOR_PAIR(6));
}


void VisualGame::showText(uint y, uint x, const char* format, ...)
{
    char buff[1000] = "";
    va_list args;
    va_start (args, format);
    vsprintf (buff, format, args);
    va_end (args);
    
    attron(COLOR_PAIR(0));
    move(y, x);
    printw(buff);
    attroff(COLOR_PAIR(0));
}

void VisualGame::showMessageBox(uint y, uint x, uint lines, uint columns,  std::string message)
{
    attron(COLOR_PAIR(5));
    for (uint i=0; i<lines; i++)
    {
        move(y+i, x);
        for (uint i=0; i<columns; i++)
        {
            printw(" ");
        }
    }
    int posy = y + lines/2;
    int posx = x+columns/2 - message.size()/2;
    move(posy, posx);
    printw(message.c_str());
    attroff(COLOR_PAIR(5));
    
}

void VisualGame::draw()
{
    
    wclear(stdscr);
    
    drawRoundMenu();
    drawScores();
    
    //showText(6, 5, "Dealer :");
    m_dealer.draw(7,  20);
    
    //showText(13, 5, "Player :");
    m_player.draw(14, 20);
    
    
    if (m_status_msg.size() > 0)
    {
        showMessageBox(1, 23, 4, 50, m_status_msg);
    }
    
    // put cursor out of sight
    move(0, 75);
    
    
    
    refresh();
}
