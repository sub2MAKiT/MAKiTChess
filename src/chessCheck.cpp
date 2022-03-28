#include "chessCheck.h"

bool ChessCheck::moveSim(std::vector<ChessPiece> GameState, bool &playerTurn, Turn player1, Turn player2, int mX, int mY, int pieceSelected, bool saverFromLoop, bool &Castle, bool &selected, int &castleRook)
{
    std::vector<ChessPiece> GameStateCopy = GameState;
    bool moveCorrect = false;
    bool move1 = false;
    bool move2 = false;
    bool moveDone = false;
    char correctColour;
    bool correctTurn;
    int pSPX = GameState[pieceSelected].PositionX;
    int pSPY = GameState[pieceSelected].PositionY;
    Castle = false;
    if(player1.Player == playerTurn)
    {
        correctTurn = true;
        correctColour = 'W';
    } else {
        correctTurn = false;
        correctColour = 'B';
    }
    if(GameState[pieceSelected].Colour == correctColour)
    {
        if(!saverFromLoop)
            DEBUGVALUE("\ncheckCheck1 %d %d",mX, mY);
        if(GameState[pieceSelected].Piece == 'P' )
        {
            for(int i = 0; i < GameState.size(); i++)
            {
                if((GameState[i].PositionX == pSPX && GameState[i].PositionY == pSPY - ((playerTurn + 1) * 2 - 3)) || ( GameState[i].PositionX == pSPX && (pSPY == abs(((playerTurn + 1) * (playerTurn + 1) * (playerTurn + 1)) - 2 && GameState[i].PositionY == pSPY - (((playerTurn + 1) * 2 - 3) * 2)))) || ((((pSPY == 6 && GameState[i].PositionY == 4) && pSPX == GameState[i].PositionX)&& mY != 5)||(((pSPY == 1 && GameState[i].PositionY == 3) && pSPX == GameState[i].PositionX)&& mY != 2)))
                    move1 = true;
                if((((mX == pSPX + 1 || mX == pSPX - 1) && mX == GameState[i].PositionX) && mY == GameState[i].PositionY)&& mY == pSPY - ((playerTurn + 1) * 2 - 3))
                    move2 = true;
            }
            //                               
            if(move2 || ((mX == pSPX && (!move1 && (mY == pSPY - ((playerTurn + 1) * 2 - 3) || ( pSPY == abs(((playerTurn + 1) * (playerTurn + 1) * (playerTurn + 1)) - 2) && mY == pSPY - (((playerTurn + 1) * 2 - 3) * 2)))))))
            {
                if(!saverFromLoop)
                    DEBUG("\ncheckCheck2");
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                DEBUG("182\n");
                selected = false; 
            }
            
        }
        if(GameState[pieceSelected].Piece == 'R' )
        {
            if(!((mX == pSPX && mY == pSPY)||!(mX == pSPX || mY == pSPY)))
                {
                    if(mX > pSPX)
                    {
                        for(int a = pSPX + 1; a < mX; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == pSPY)
                                    move1 = true;
                            }
                        }
                    } else if(mX < pSPX) {
                        for(int a = pSPX - 1; a > mX; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == pSPY)
                                    move1 = true;
                            }
                        }
                    } else if(mY > pSPY){
                        for(int a = pSPY + 1; a < mY; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == pSPX)
                                    move1 = true;
                            }
                        }
                    } else {
                            for(int a = pSPY - 1; a > mY; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == pSPX)
                                    move1 = true;
                            }
                        }
                    }
                } else {
                    move1 = true;
                }
            if(!move1)
            {
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                DEBUG("237\n");
                selected = false; 
            }
            
        }
        if(GameState[pieceSelected].Piece == 'B')
        {
            if(mX != pSPX && mY != pSPY)
            {
                if(abs(mX - pSPX) == abs(mY - pSPY))
                {
                    for(int a = 0; a < GameState.size(); a++)
                    {
                        for(int i = (abs(mX  - pSPX) - 1) *(abs(mX  - pSPX) / (mX  - pSPX)); i != 0; i += -1 * (abs(i) / i))
                        {
                            if(pSPX + i == GameState[a].PositionX && pSPY + abs(i) * (abs(mY - pSPY)/(mY - pSPY)) == GameState[a].PositionY)
                            {
                                move1 = true;
                            }
                        }
                    }
                } else {
                    move1 = true;
                }
            } else {
                move1 = true;
            }
            if(!move1)
            {
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                DEBUG("269\n");
                selected = false; 
            }
        }
        if(GameState[pieceSelected].Piece == 'C')
        {
            for(int i = pSPX - 2;i <= pSPX + 2; i += 1)
            {
                if(i - pSPX != 0)
                {
                    if(mX == i && (mY == pSPY + (3 - abs(i - pSPX)) || mY == pSPY - (3 - abs(i - pSPX))))
                        move1 = true;
                }
            }
            if(move1)
            {
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                DEBUG("288\n");
                selected = false; 
            }
        }
        if(GameState[pieceSelected].Piece == 'Q')
        {
            if(!((mX == pSPX && mY == pSPY)||!(mX == pSPX || mY == pSPY)))
                {
                    if(mX > pSPX)
                    {
                        for(int a = pSPX + 1; a < mX; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == pSPY)
                                    move1 = true;
                            }
                        }
                    } else if(mX < pSPX) {
                        for(int a = pSPX - 1; a > mX; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == pSPY)
                                    move1 = true;
                            }
                        }
                    } else if(mY > pSPY){
                        for(int a = pSPY + 1; a < mY; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == pSPX)
                                    move1 = true;
                            }
                        }
                    } else {
                            for(int a = pSPY - 1; a > mY; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == pSPX)
                                    move1 = true;
                            }
                        }
                    }
                } else {
                    move1 = true;
                }
            
            if(mX != pSPX && mY != pSPY)
            {
                if(abs(mX - pSPX) == abs(mY - pSPY))
                {
                    for(int a = 0; a < GameState.size(); a++)
                    {
                        for(int i = (abs(mX  - pSPX) - 1) *(abs(mX  - pSPX) / (mX  - pSPX)); i != 0; i += -1 * (abs(i) / i))
                        {
                            if(pSPX + i == GameState[a].PositionX && pSPY + abs(i) * (abs(mY - pSPY)/(mY - pSPY)) == GameState[a].PositionY)
                            {
                                move2 = true;
                            }
                        }
                    }
                } else {
                    move2 = true;
                }
            } else {
                move2 = true;
            }
            if(!move1 || !move2)
            {
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                DEBUG("363\n");
                selected = false; 
            }
        }
        if(GameState[pieceSelected].Piece == 'K')
        {
            if((abs(mX - pSPX) <= 1 && abs(mY - pSPY) <= 1) && (abs(mX - pSPX) != 0 || abs(mY - pSPY) != 0))
                move1 = true;
            for(int m = 0; m < GameState.size();m++)
            {
                if(((GameState[m].Piece == 'R' && GameState[m].Colour == correctColour) && (GameState[m].PositionX == mX && GameState[m].PositionY == mY))&& (GameState[m].Moved == false && GameState[pieceSelected].Moved == false))
                {
                    castleRook = m;
                    Castle = true;
                }
            }
            if(move1)
            {
                moveDone = true;
            } else if(Castle) {
            } else {
                GameState[pieceSelected].Pressed = false;
                DEBUG("376\n");
                selected = false;
            }
        }
    }
    if(moveDone)
    {
        moveCorrect = true;
        DEBUGVALUE("\nmove done, %d\n",moveCorrect);
        GameStateCopy[pieceSelected].PositionX = mX;
                DEBUGVALUE("\nmove done1, %d\n",moveCorrect);
        GameStateCopy[pieceSelected].PositionY = mY;
                DEBUGVALUE("\nmove done2, %d\n",moveCorrect);
        for(int i = 0; i < GameStateCopy.size(); i++)
        {
            for(int a = 0; a < GameStateCopy.size(); a++)
            {
                if(a != i)
                {
                    if(!Castle)
                    {
                        if((GameStateCopy[i].PositionX == GameStateCopy[a].PositionX && GameStateCopy[i].PositionY == GameStateCopy[a].PositionY) && GameStateCopy[i].Colour == GameStateCopy[a].Colour)
                        {                
                            DEBUGVALUE("%d",moveCorrect);
                            moveCorrect = false;
                        }
                    }
                }
            }
        }
                DEBUGVALUE("\nmove done3, %d\n",moveCorrect);
    }
    if(Castle)
    {
        DEBUG("\nCastle\n");
        moveCorrect = true;
        bool somethingInTheWayThatIsNotABatmanReference = false;
        if(!GameState[pieceSelected].Moved && !GameState[castleRook].Moved)
        {
            for(int i = 0; i < GameState.size();i++)
            {
                if(GameState[i].PositionY == pSPY)
                    if((GameState[i].PositionX < pSPX && GameState[i].PositionX > GameState[castleRook].PositionX) || (GameState[i].PositionX > pSPX && GameState[i].PositionX < GameState[castleRook].PositionX))
                        somethingInTheWayThatIsNotABatmanReference = true;
            }
        }
        if(!somethingInTheWayThatIsNotABatmanReference)
        {
            moveCorrect = CheckCheck(GameStateCopy, playerTurn, player1, player2, GameStateCopy[pieceSelected].PositionX, GameStateCopy[pieceSelected].PositionY, Castle, selected, castleRook);
            Castle = true;
            return moveCorrect;
        } else {
            moveCorrect = false;
        }
    }
    int kingPos;
    DEBUGVALUE("\nmove done4, %d\n",moveCorrect);
    DEBUGVALUE("\nmoved before deletion, %d\n",moveCorrect);

    for(int i = 0; i < GameStateCopy.size(); i++)
        {
            for(int a = 0; a < GameStateCopy.size(); a++)
            {
                if(a != i)
                {
                    if(GameStateCopy[i].PositionX == GameStateCopy[a].PositionX)
                    {
                        if(GameStateCopy[i].PositionY == GameStateCopy[a].PositionY)
                        {
                            if(GameStateCopy[i].Colour == 'B')
                            {
                                if(!correctTurn)
                                {
                                    GameStateCopy.erase(GameStateCopy.begin()+a);
                                } else {
                                    GameStateCopy.erase(GameStateCopy.begin()+i);
                                }
                            } else {
                                if(correctTurn)
                                {
                                    GameStateCopy.erase(GameStateCopy.begin()+a);
                                } else {
                                    GameStateCopy.erase(GameStateCopy.begin()+i);
                                }
                            }
                        }
                    }
                }
            }
        }
    DEBUGVALUE("\nmoved after deletion, %d\n",moveCorrect);
    for(int i = 0; i < GameStateCopy.size(); i++)
    {
        if(GameStateCopy[i].Piece == 'K')
        if(GameStateCopy[i].Colour == correctColour)
        kingPos = i;
    }
    DEBUGVALUE("\nmoved before cc, %d\n",moveCorrect);
    if(moveCorrect)
        if(saverFromLoop)
            moveCorrect = CheckCheck(GameStateCopy, playerTurn, player1, player2, GameStateCopy[kingPos].PositionX, GameStateCopy[kingPos].PositionY, Castle, selected, castleRook);
    DEBUGVALUE("\nmoved after cc, %d\n",moveCorrect);
    if(moveCorrect)
        GameState[pieceSelected].Moved = true;
    return moveCorrect;
}
bool ChessCheck::CheckCheck(std::vector<ChessPiece> GameState, bool playerTurn, Turn player1, Turn player2, int kPX, int kPY, bool Castle, bool selected, int castleRook)
    {
        // true means no check
        bool PlayerTurn = !playerTurn;
        bool temp = true;
        DEBUG("crash Test 1");
        std::vector<ChessPiece> copyPieces = GameState;
        DEBUG("crash Test 2");
        char colour;
        if(playerTurn == true)
            colour = 'B';
        else
            colour = 'W';
        DEBUG("\nCheckCheck checker");
        DEBUGVALUE("\nCheckCheck check for checking %d",temp);
        for(int i = 0; i < copyPieces.size(); i++)
        {
            DEBUGVALUE("%d",kPY);
            if(moveSim(copyPieces, PlayerTurn, player1, player2, kPX, kPY, i, false, Castle, selected, castleRook))
            {
                DEBUGVALUE("\n%c,%c,%d",copyPieces[i].Colour, copyPieces[i].Piece,i);
                temp = false;
                break;
            }
        }
        DEBUGVALUE("\nCheckCheck checking %d\n", temp);
        return temp;
    }