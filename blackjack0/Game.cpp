//
//  Game.cpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#include "Game.hpp"

#include <cstdio>
#include <cstdlib>
#include <algorithm>

#include <curses.h>
#include <unistd.h>

const size_t RESHUFFLE_RATE_ROUNDS = 6;

Game::Game():
    m_scores{},
    m_state(GameState::WAIT),
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
    
    m_dealer.showPoints(false);
    
}

void Game::finishRound()
{
    
}

void Game::draw()
{
    printf("to be overriden draw method\n");
}

void Game::dealerPlays()
{
    
    m_dealer.showPoints(true);
    m_dealer.showCards();
    
    m_state = DEALER_HAND;
    
    draw();
    sleep(2);
    
    auto p_points = m_player.getPoints();
    int p_player = *std::max_element(p_points.begin(), p_points.end());
    
    // on player bust, dealer does not need to play his hand
    if (p_player > 21) return;
    
    do{
        
        auto d_points = m_dealer.getPoints();
        int p_dealer = *std::max_element(d_points.begin(), d_points.end());
        
        // dealer must hit until the sum is less than 17
        // dealer must hit in soft-17
        if (p_dealer >= 17 &&
            !(p_dealer == 17 && d_points.size() > 1) ) // dealer must also hit in soft-17
        {
            // no more hits for the dealer
            break;
        }
        
        m_dealer.giveCard(m_deck.pop());
        
        draw();
        sleep(2);
    } while(true);
}

Game::RoundWinner Game::checkWinner(int p_player, int p_dealer)
{
    
    if (p_player > 21 && p_dealer > 21)
    {
        return RoundWinner::DEALER;
    }
    else if (p_player == p_dealer)
    {
        return RoundWinner::TIE;
    }
    else if (p_player > p_dealer)
    {
        if (p_player <= 21)
            return RoundWinner::PLAYER;
        else
            return RoundWinner::DEALER;
    }
    else
    {
        if (p_dealer <= 21)
            return RoundWinner::DEALER;
        else
            return RoundWinner::PLAYER;
    }

    return RoundWinner::TIE;
}

void Game::checkGame()
{
    int p_dealer = m_dealer.getMaxPoints();
    int p_player = m_player.getMaxPoints();
    
    m_status_msg = "";
    
    if (p_player == 21 && m_player.numCards() == 2) m_status_msg += "player blackjacked, ";
    if (p_dealer == 21 && m_dealer.numCards() == 2) m_status_msg += "dealer blackjacked, ";
    
    if (p_player > 21) m_status_msg += "player busted, ";
    if (p_dealer > 21) m_status_msg += "player busted, ";
    
    RoundWinner result = checkWinner(p_player, p_dealer);
    if (result == RoundWinner::TIE)
    {
        m_status_msg += "it is a tie";
        m_scores.ties++;
    }
    else if (result == RoundWinner::DEALER)
    {
        m_status_msg += "dealer wins";
        m_scores.dealer++;
    }
    else
    {
        m_status_msg += "player wins";
        m_scores.player++;
    }

    m_state = WAIT;
}

void Game::gameLoop()
{
    int c;

    fflush(stdin);
    
    if (m_state == PLAY &&
        m_player.getMaxPoints() == 21 &&
        m_player.numCards() == 2)
    {
        m_status_msg = "player backjack!!";
        draw();
        sleep(2);
        dealerPlays();
        checkGame();
    }
    
    do
    {
        draw();
        
        c = getch();
        c = tolower(c);
        if (c == 'x') break;
        
        if (m_state == PLAY)
        {
            if (c == 'h')
            {
                m_player.giveCard(m_deck.pop());
                
                int p_player = m_player.getMaxPoints();
                
                if (p_player >= 21)
                {
                    dealerPlays();
                    checkGame();
                }
            }
            else if (c == 's')
            {
                dealerPlays();
                checkGame();
            }
        }
        else if (m_state == WAIT)
        {
            initialiseRound();
            m_status_msg = "";
            m_state = PLAY;
        }
    }while(true);
    
    endwin();
    
    
}
