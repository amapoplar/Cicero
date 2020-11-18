#include "cicpch.h"
#include "Game.h"
#include<map>

namespace Cicero {
    int board[90] = {
     8, 9,10,11,12,11,10, 9, 8,
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     0,13, 0, 0, 0, 0, 0,13, 0,
    14, 0,14, 0,14, 0,14, 0,14,
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     7, 0, 7, 0, 7, 0, 7, 0, 7,
     0, 6, 0, 0, 0, 0, 0, 6, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     1, 2, 3, 4, 5, 4, 3, 2, 1
    };
    const double s = 0.6;
    const int WIDTH = 2211*s;
    const int HEIGHT = 2438 * s;

    const int size = 242;
    

    Game::Game()
        :sf::RenderWindow(sf::VideoMode(WIDTH, HEIGHT), "Chinese Chess!"),scale(s)
    {
        tBoard.loadFromFile("images/chessboard.png");
        sBoard.setTexture(tBoard);
        sBoard.setScale(sf::Vector2f(scale, scale));

        tChess.loadFromFile("images/chess.png");
        sChess.setTexture(tChess);
        sChess.setScale(sf::Vector2f(scale, scale));

    }

    void Game::Show()
    {
        while (true)
        {
            sf::Event event;
            while (this->pollEvent(event))
            {
                // Close window: exit
                if (event.type == sf::Event::Closed)
                    this->close();
            }
            Update(event);
            int whowin = checkMate();
            switch (whowin)
            {
                case 1: {
                    std::cout << "Black Wins!" << std::endl;
                    break;
                }
                case 2:
                {
                    std::cout << "Red Wins!" << std::endl;
                    break;
                }
            }
            this->draw(sBoard);
            this->showBorad();
            this->display();
            
        }
    }

    void Game::Update(sf::Event event)
    {
        sf::Vector2i oldpos, newpos;
        if (event.type==sf::Event::MouseButtonPressed)
        {
            if (event.key.code==sf::Mouse::Left)
            {
                if (!isMove)
                {
                    oldpos = sf::Mouse::getPosition(*this);
                    int x = oldpos.x / (size * scale);
                    int y = oldpos.y / (size * scale);
                    oldpos = sf::Vector2i(x, y);
                    for (size_t i = 0; i < sizeof(board) / sizeof(int); i++)
                    {
                        if ((oldpos.x == i % 9) && (oldpos.y == i / 9) && board[i])
                        {
                            int pos = x + y * 9;
                            movingChess = {pos,board[i]};
                            board[i] = 0;
                            isMove = true;
                        }
                    }
                }
                
            }
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.key.code == sf::Mouse::Left)
            {
                if (isMove) {
                    newpos = sf::Mouse::getPosition(*this);
                    int x = newpos.x / (size * scale);
                    int y = newpos.y / (size * scale);
                    newpos = sf::Vector2i(x, y);
                    if (legalQ(x,y)&&checkMate()!=4) {
                        int pos = x + y * 9;
                        board[pos] = movingChess.name;
                        isRed = !isRed;
                    }
                    else {
                        board[movingChess.pos] = movingChess.name;
                    }
                    isMove = false;
                }
                    
            }
        }
    }

    bool Game::legalQ(int x,int y)
    {
        if ((movingChess.name-1)/7!=isRed&&0<=x&&x<9&&0<=y&&y<10&&ruleQ(x,y))
        {

            for (size_t i = 0; i < sizeof(board) / sizeof(int); i++)
            {
                if (( x== i % 9) && (y == i / 9) && board[i])
                {
                    if ((movingChess.name - 1) / 7== (board[i] - 1) / 7)
                    {
                        return false;
                    }
                    else {
                        return true;
                    }
                    
                }
            }
            return true;
        }
        else {
            return false;
        }
    }

    bool Game::ruleQ(int x, int y)
    {
        int w = movingChess.pos % 9;
        int z = movingChess.pos / 9;
        switch ((movingChess.name-1)%7)
        {
        case 0: {
            if (x== w)
            {
                int i = (y < z) ? y : z;
                int j = (y > z) ? y : z;
                for (i++; i < j; i++)
                {
                    if (board[i * 9 + x])
                    {
                        return false;
                    }
                }
                return true;
            }
            if (y == z)
            {
                int i = (x < w) ? x : w;
                int j = (x > w) ? x : w;
                for (i++; i < j; i++)
                {
                    if (board[y * 9 + i])
                    {
                        return false;
                    }
                }
                return true;
            }
            break;
        }

        case 1: {
            if ((abs(w-x)==2&&abs(z-y)==1)|| (abs(w - x) == 1 && abs(z - y) == 2))
            {
                int xfeet = abs(w - x) > abs(z - y) ? (x-w)/2 : 0;
                xfeet += w;
                int yfeet = abs(w - x) > abs(z - y) ? 0 : (y-z)/2;
                yfeet += z;
                if (board[yfeet * 9 + xfeet])
                {
                    return false;
                }
                return true;
            }
            break;
        }
        case 2: {
            if ((abs(w - x) == 2 && abs(z - y) == 2)&& !board[(y+(z - y)/2 )* 9 + x+(w - x)/2])
            {
                if ((y<5&& (movingChess.name-1)/7==0)|| (y > 5 && (movingChess.name - 1) / 7 == 1))
                {
                    return false;
                }
                return true;
            }

            break;
        }

        case 3:{
            if ((abs(w - x) == 1 && abs(z - y) == 1)&&(2 < x && x < 6))
            {
                if ((y < 7 && (movingChess.name - 1) / 7 == 0) || (y > 3 && (movingChess.name - 1) / 7 == 1))
                {
                    return false;
                }
                return true;
            } 
            break;
        }
        case 4: {
            if (((abs(w - x) == 1 &&z==y)|| (abs(z - y) == 1)&&w==x) && (2 < x && x < 6)) {
                if ((y < 7 && (movingChess.name - 1) / 7 == 0) || (y > 3 && (movingChess.name - 1) / 7 == 1))
                {
                    return false;
                }
                return true;
            }
            break;
        }
        case 5: {
            int flag = 0;
            if (x == w)
            {
                int i = (y < z) ? y : z;
                int j = (y > z) ? y : z;
                for (i++; i < j; i++)
                {
                    if (board[i * 9 + x])
                    {
                        flag += 1;
                    }
                }
                if (flag == 0 && board[y * 9 + x])
                    return false;
                return flag < 2;
            }
            if (y == z)
            {
                int i = (x < w) ? x : w;
                int j = (x > w) ? x : w;
                for (i++; i < j; i++)
                {
                    if (board[y * 9 + i])
                    {
                        flag += 1;
                    }
                }
                if (flag == 0 && board[y * 9 + x])
                    return false;
                return flag < 2;
            }

            break;
        }
        case 6: {
            int bools = ((movingChess.name - 1) / 7) * 2 - 1;
            if ((y-z==bools&&w==x)||(abs(w-x)==1&&(y==z)))
            {
                if ((w != x &&y > 4 && (movingChess.name - 1) / 7 == 0) || (w != x && y < 5 && (movingChess.name - 1) / 7 == 1))
                {
                    return false;
                }
                return true;
            }
            break;
        }
        default:
            break;
        }
        return false;
    }

    void Game::showBorad()
    {
        for (size_t i = 0; i < sizeof(board)/sizeof(int); i++)
        {
            if (board[i])
            {
                int Tx = (board[i] - 1) % 7;
                int Ty = (board[i] - 1) / 7;
                int x = i % 9;
                int y = i / 9;
                sChess.setTextureRect(sf::IntRect(Tx*size,Ty*size,size,size));
                sChess.setPosition(sf::Vector2f(x*size*scale,y*size*scale));
                this->draw(sChess);
            }
        }
    }

    int Game::checkMate()
    {
        bool redKingAlive = false, blackKingAlive = false;
        int posblack=-1, posred=-1;
        for (size_t i = 0; i < sizeof(board) / sizeof(int); i++)
        {
            if (board[i]==5)
            {
                blackKingAlive = true;
                posblack = i;
            }
            if (board[i] == 12)
            {
                redKingAlive = true;
                posred = i;
            }
        }
        int flag = 0;
        if ((posred % 9)== (posblack % 9))
        {
            for (size_t i = posred+9; i < posblack; i+=9)
            {
                if (board[i])
                {
                    flag++;
                }
            }
        }
        if (!flag)
        {
            if (posblack==-1||posred==-1)
            {
                return (blackKingAlive << 1) | redKingAlive;
            }
           return 4;
        }
        return (blackKingAlive<<1) | redKingAlive;
    }
}



