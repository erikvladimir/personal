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

//-----------------------------------------------
// This file contains the logic of the GAME
// The visual part is in file Visual Game
//-----------------------------------------------

// get sure we reshuffle deck every so often
const size_t RESHUFFLE_RATE_ROUNDS = 6;

Game::Game():
    m_scores{},
    m_state(GameState::WAIT),
    m_deck(),
    m_player("Player"),
    m_dealer("Dealer", false),
    m_roundCount(0)
{
    // set random seed
    std::srand (uint(time(0)));
    
    m_deck.suffle();
    initialiseRound();
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

/** 
 * Dealer plays its hands, it will stop when it gets anything bigger than 17 excepts in soft-17 case
 * The hand is played progressively.
 */
void Game::dealerPlays()
{
    
    m_dealer.showPoints(true);
    m_dealer.showCards();
    
    m_state = DEALER_HAND;
    
    draw();
    sleep(2);
    
    int p_player =  m_player.getMaxPoints();
    
    // on player bust, dealer does not need to play his hand
    if (p_player > 21) return;
    
    do{
        // TODO: getMaxPoints() and getNumPoints() could be merged to avoid re-computing the points
        int p_dealer = m_dealer.getMaxPoints();
        
        // dealer must hit until the sum is less than 17
        // dealer must hit in soft-17
        if (p_dealer >= 17 &&
            !(p_dealer == 17 && m_dealer.getNumPoints() > 1) ) // dealer must also hit in soft-17
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
    
    if (p_player == 21 && m_player.numCards() == 2) m_status_msg += "Player blackjack!, ";
    if (p_dealer == 21 && m_dealer.numCards() == 2) m_status_msg += "Dealer blackjack!, ";
    
    if (p_player > 21) m_status_msg += "Player bust!. ";
    if (p_dealer > 21) m_status_msg += "Dealer bust!. ";
    
    RoundWinner result = checkWinner(p_player, p_dealer);
    if (result == RoundWinner::TIE)
    {
        m_status_msg += "It is a tie!.";
        m_scores.ties++;
    }
    else if (result == RoundWinner::DEALER)
    {
        m_status_msg += "Dealer wins.";
        m_scores.dealer++;
    }
    else
    {
        m_status_msg += "Player wins.";
        m_scores.player++;
    }

    m_state = WAIT;
}

/**
 * Main loop for the game.
 */
void Game::gameLoop()
{

    // lambda func to reduce code duplication
    auto goToDealerHand = [&]() {
        dealerPlays();
        checkGame();
    };

    fflush(stdin);
    
    // check special case in which player makes a blackjack
    // with first two cards
    if (m_state == PLAY &&
        m_player.getMaxPoints() == 21 &&
        m_player.numCards() == 2)
    {
        m_status_msg = "player backjack!!";
        draw();
        sleep(2);
        goToDealerHand();
    }
    
    // we loop and process actions according to current game status
    do
    {
        // refresh visual output
        draw();
        
        // take a key that will be processed according to current game status
        char c = getch();
        c = tolower(c);
        if (c == 'x') break;
        
        if (m_state == PLAY)
        {
            // player hits
            if (c == 'h')
            {
                // give it a card from deck
                m_player.giveCard(m_deck.pop());
                
                // check for bust or blackjack
                if (m_player.getMaxPoints() >= 21)
                {
                    goToDealerHand();
                }
            }
            // player stands
            else if (c == 's')
            {
                goToDealerHand();
            }
        }
        else if (m_state == WAIT)
        {
            // if we were in wait status and user pressed any key,
            // we reinitialise the round and move to play status
            initialiseRound();
            m_status_msg = "";
            m_state = PLAY;
        }
    }while(true);    
    
    endwin();
}
