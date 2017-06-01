//
//  VisualGame.hpp
//  blackjack0
//
//  Created by Erik V. Ortega on 31/05/2017.
//  Copyright © 2017 Erik V. Ortega. All rights reserved.
//

#ifndef VisualGame_hpp
#define VisualGame_hpp

#include <stdio.h>

#include "Game.hpp"

class VisualGame : public Game
{
private:
    void drawScores() const;
    void drawRoundMenu() const;
public:
    VisualGame();
    ~VisualGame();
    
    void initialise();
    void deinitialise();
    
    virtual void draw();
    static void showText(uint y, uint x, const char* format, ...);
    void showMessageBox(uint y, uint x, uint lines, uint columns, std::string message);
};


#endif /* VisualGame_hpp */
