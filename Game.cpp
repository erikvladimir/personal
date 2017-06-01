//
//  Game.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//  Copyright © 2017 Erik V. Ortega. All rights reserved.
//

#include "Game.hpp"

#include <cstdio>
#include <cstdlib>
#include <algorithm>

#include <curses.h>
#include <unistd.h>

const size_t RESHUFFLE_RATE_ROUNDS = 6;

Game::Game():
    m_state(GameState::WELCOME),
    m_deck(),
    m_player("Player"),
    m_dealer("Dealer", false),
    m_roundCount(0)
{
    m_deck.suffle();
    initialiseRound();
    
}

Game::~Game()
{

}

void Game::initialiseRound()
{
    m_state = PLAY;
    
    // collect cards from all participants
    m_deck.pileCards(m_player.collectCards());
    m_deck.pileCards(m_dealer.collectCards());
    
    // resuffle every six rounds
    if (m_roundCount % RESHUFFLE_RATE_ROUNDS == 0)
    {
        m_deck.suffle();
    }
    m_roundCount++;
    
    // give participants first two cards each
    m_player.giveCard(m_deck.pop());
    m_player.giveCard(m_deck.pop());
    
    m_dealer.giveCard(m_deck.pop());
    m_dealer.giveCard(m_deck.pop(), false);
    
}

void Game::finishRound()
{
    
}

void Game::draw()
{
    printf("to be overriden draw method\n");
}

void Game::checkGame()
{
    auto points = m_player.getPoints();
    int p_player = *std::max_element(points.begin(), points.end());
    if (p_player > 21)
    {
        m_status_msg = "you busted!! you loss";
        m_state = WAIT;
    }
        
}

void Game::dealerPlays()
{
    m_dealer.showPoints();
    m_dealer.showCards();
    
    
    draw();
    sleep(2);
    
    do{
        
        auto points = m_dealer.getPoints();
        int p_dealer = *std::max_element(points.begin(), points.end());
        
        if (p_dealer == 21)
        {
            m_status_msg = "Dealer wins";
            m_state = WAIT;
            break;
        }
        
        m_dealer.giveCard(m_deck.pop());
        
        draw();
        sleep(2);
    } while(true);
    
    getch();
}

void Game::gameLoop()
{
    int c;

    fflush(stdin);
    
    do
    {
        draw();
        
        c = getch();
        if (c == 'x' || c == 'X') break;
        
        if (m_state == PLAY)
        {
            switch (c)
            {
                case 'h':
                case 'H':
                    m_player.giveCard(m_deck.pop());
                    break;
                case 's':
                case 'S':
                    dealerPlays();
                    break;
            }
        }
        
        if (m_state == WAIT)
        {
            initialiseRound();
            m_status_msg = "";
            m_state = PLAY;
        }
        checkGame();

    }while(true);
    
    endwin();
    
    
}
