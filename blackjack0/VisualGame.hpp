//
//  VisualGame.hpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//

#ifndef VisualGame_hpp
#define VisualGame_hpp

#include <stdio.h>

#include "Game.hpp"
#include "Person.hpp"

class VisualGame : public Game
{
    
private:
    void drawScores() const;
    void drawRoundMenu() const;
    void draw(uint y, uint x, Person person) const;
protected:
    void initialise();
    void deinitialise();
    void showMessageBox(uint y, uint x, uint lines, uint columns, std::string message);
    virtual void draw();
public:
    VisualGame();
    ~VisualGame();
    
    static void showText(uint y, uint x, const char* format, ...);
};


#endif /* VisualGame_hpp */
