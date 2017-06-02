//
//  VisualGame.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#include <curses.h>

#include "VisualGame.hpp"

void rectangle(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

VisualGame::VisualGame():
    Game()
{
    setlocale (LC_ALL, "");
    initscr();
    
    if(has_colors() == false)
    {	endwin();
        printf("Your terminal does not support color.\n");
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
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    
    init_pair(10, COLOR_BLACK, COLOR_WHITE);
    init_pair(11, COLOR_RED, COLOR_WHITE);
    
    cbreak();
    keypad(stdscr, true);
}

VisualGame::~VisualGame()
{
    
}

/**
 * Main method that draw all the visual output
 */
void VisualGame::draw()
{
    wclear(stdscr);
    
    // draw borders
    attron(COLOR_PAIR(0));
    rectangle(0,0,25,80);
    attron(COLOR_PAIR(0));
    
    drawRoundMenu();
    drawScores();
    
    m_dealer.draw(7,  4);
    m_player.draw(14, 4);
    
    if (m_status_msg.size() > 0)
    {
        showMessageBox(1, 26, 4, 53, m_status_msg);
    }
    
    // put cursor out of sight
    move(0, 75);
    
    refresh();
}

void VisualGame::DrawRectangle(uint y, uint x, uint lines, uint columns)
{
    for (uint i=0; i<lines; i++)
    {
        move(y+i, x);
        for (uint j=0; j<columns; j++)
        {
            printw(" ");
        }
    }
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
    constexpr uint line = 1;
    constexpr uint column = 4;
    
    attron(COLOR_PAIR(6));
    
    DrawRectangle(line, column, 4, 19);
    move(line,   column);  printw(" Scores in percent");
    
    const uint sum_wins = m_scores.player + m_scores.dealer + m_scores.ties;
    auto compute_percent =  [](const uint & n, const uint & total) { return (total == 0) ? 0.f : (n * 100.f) / total; };
    
    const float player_percent = compute_percent(m_scores.player, sum_wins);
    const float dealer_percent = compute_percent(m_scores.dealer, sum_wins);
    const float tie_percent    = compute_percent(m_scores.ties, sum_wins);
    
    // percentage needs to be printed like this so it can be properly displayed
    move(line+1, column);  printw(" Player: %2.1f %s", player_percent, std::string("\u0025").c_str());
    move(line+2, column);  printw(" Dealer: %2.1f %s", dealer_percent, std::string("\u0025").c_str());
    move(line+3, column);  printw(" Ties:   %2.1f %s", tie_percent,    std::string("\u0025").c_str());
    
    attroff(COLOR_PAIR(6));
}


void VisualGame::showText(uint y, uint x, uint color, const char* format, ...)
{
    char buff[1000] = "";
    va_list args;
    va_start (args, format);
    vsprintf (buff, format, args);
    va_end (args);
    
    attron(COLOR_PAIR(color));
    move(y, x);
    printw(buff);
    attroff(COLOR_PAIR(color));
}

void VisualGame::showMessageBox(uint y, uint x, uint lines, uint columns,  std::string message)
{
    attron(COLOR_PAIR(5));
    DrawRectangle(y, x, lines, columns);
    int posy = y + (lines/2);
    int posx = x + (columns/2) - int(message.size()/2);
    move(posy, posx);
    printw(message.c_str());
    attroff(COLOR_PAIR(5));
    
}
