#include "chessCheck.h"

bool ChessCheck::moveSim(std::vector<ChessPiece> GameState, bool playerTurn, int mX, int mY, int pieceSelected, bool saverFromLoop, bool &Castle, int &castleRook)
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
    if(playerTurn)
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
        if(GameState[pieceSelected].Piece == 'P')
        {
            for(int i = 0; i < GameState.size(); i++)
            {
                if((GameState[i].PositionX == GameState[pieceSelected].PositionX && GameState[i].PositionY == GameState[pieceSelected].PositionY - ((playerTurn + 1) * 2 - 3)) || ( GameState[i].PositionX == GameState[pieceSelected].PositionX && (GameState[pieceSelected].PositionY == abs(((playerTurn + 1) * (playerTurn + 1) * (playerTurn + 1)) - 2 && GameState[i].PositionY == GameState[pieceSelected].PositionY - (((playerTurn + 1) * 2 - 3) * 2)))) || ((((GameState[pieceSelected].PositionY == 6 && GameState[i].PositionY == 4) && GameState[pieceSelected].PositionX == GameState[i].PositionX)&& mY != 5)||(((GameState[pieceSelected].PositionY == 1 && GameState[i].PositionY == 3) && GameState[pieceSelected].PositionX == GameState[i].PositionX)&& mY != 2)))
                    move1 = true;
                if((((mX == GameState[pieceSelected].PositionX + 1 || mX == GameState[pieceSelected].PositionX - 1) && mX == GameState[i].PositionX) && mY == GameState[i].PositionY)&& mY == GameState[pieceSelected].PositionY - ((playerTurn + 1) * 2 - 3))
                    move2 = true;
            }
            //                               
            if(move2 || ((mX == GameState[pieceSelected].PositionX && (!move1 && (mY == GameState[pieceSelected].PositionY - ((playerTurn + 1) * 2 - 3) || ( GameState[pieceSelected].PositionY == abs(((playerTurn + 1) * (playerTurn + 1) * (playerTurn + 1)) - 2) && mY == GameState[pieceSelected].PositionY - (((playerTurn + 1) * 2 - 3) * 2)))))))
            {
                if(!saverFromLoop)
                    DEBUG("\ncheckCheck2");
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                DEBUG("182\n");

            }
            
        }
        if(GameState[pieceSelected].Piece == 'R' )
        {
            if(!((mX == GameState[pieceSelected].PositionX && mY == GameState[pieceSelected].PositionY)||!(mX == GameState[pieceSelected].PositionX || mY == GameState[pieceSelected].PositionY)))
                {
                    if(mX > GameState[pieceSelected].PositionX)
                    {
                        for(int a = GameState[pieceSelected].PositionX + 1; a < mX; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == GameState[pieceSelected].PositionY)
                                    move1 = true;
                            }
                        }
                    } else if(mX < GameState[pieceSelected].PositionX) {
                        for(int a = GameState[pieceSelected].PositionX - 1; a > mX; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == GameState[pieceSelected].PositionY)
                                    move1 = true;
                            }
                        }
                    } else if(mY > GameState[pieceSelected].PositionY){
                        for(int a = GameState[pieceSelected].PositionY + 1; a < mY; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == GameState[pieceSelected].PositionX)
                                    move1 = true;
                            }
                        }
                    } else {
                            for(int a = GameState[pieceSelected].PositionY - 1; a > mY; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == GameState[pieceSelected].PositionX)
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

            }
            
        }
        if(GameState[pieceSelected].Piece == 'B')
        {
            if(mX != GameState[pieceSelected].PositionX && mY != GameState[pieceSelected].PositionY)
            {
                if(abs(mX - GameState[pieceSelected].PositionX) == abs(mY - GameState[pieceSelected].PositionY))
                {
                    for(int a = 0; a < GameState.size(); a++)
                    {
                        for(int i = (abs(mX  - GameState[pieceSelected].PositionX) - 1) *(abs(mX  - GameState[pieceSelected].PositionX) / (mX  - GameState[pieceSelected].PositionX)); i != 0; i += -1 * (abs(i) / i))
                        {
                            if(GameState[pieceSelected].PositionX + i == GameState[a].PositionX && GameState[pieceSelected].PositionY + abs(i) * (abs(mY - GameState[pieceSelected].PositionY)/(mY - GameState[pieceSelected].PositionY)) == GameState[a].PositionY)
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

            }
        }
        if(GameState[pieceSelected].Piece == 'C')
        {
            for(int i = GameState[pieceSelected].PositionX - 2;i <= GameState[pieceSelected].PositionX + 2; i += 1)
            {
                if(i - GameState[pieceSelected].PositionX != 0)
                {
                    if(mX == i && (mY == GameState[pieceSelected].PositionY + (3 - abs(i - GameState[pieceSelected].PositionX)) || mY == GameState[pieceSelected].PositionY - (3 - abs(i - GameState[pieceSelected].PositionX))))
                        move1 = true;
                }
            }
            if(move1)
            {
                moveDone = true;
            } else {
                GameState[pieceSelected].Pressed = false;
                DEBUG("288\n");

            }
        }
        if(GameState[pieceSelected].Piece == 'Q')
        {
            if(!((mX == GameState[pieceSelected].PositionX && mY == GameState[pieceSelected].PositionY)||!(mX == GameState[pieceSelected].PositionX || mY == GameState[pieceSelected].PositionY)))
                {
                    if(mX > GameState[pieceSelected].PositionX)
                    {
                        for(int a = GameState[pieceSelected].PositionX + 1; a < mX; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == GameState[pieceSelected].PositionY)
                                    move1 = true;
                            }
                        }
                    } else if(mX < GameState[pieceSelected].PositionX) {
                        for(int a = GameState[pieceSelected].PositionX - 1; a > mX; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionX == a && GameState[i].PositionY == GameState[pieceSelected].PositionY)
                                    move1 = true;
                            }
                        }
                    } else if(mY > GameState[pieceSelected].PositionY){
                        for(int a = GameState[pieceSelected].PositionY + 1; a < mY; a++)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == GameState[pieceSelected].PositionX)
                                    move1 = true;
                            }
                        }
                    } else {
                            for(int a = GameState[pieceSelected].PositionY - 1; a > mY; a--)
                        {
                            for(int i = 0; i < GameState.size(); i++)
                            {
                                if(GameState[i].PositionY == a && GameState[i].PositionX == GameState[pieceSelected].PositionX)
                                    move1 = true;
                            }
                        }
                    }
                } else {
                    move1 = true;
                }
            
            if(mX != GameState[pieceSelected].PositionX && mY != GameState[pieceSelected].PositionY)
            {
                if(abs(mX - GameState[pieceSelected].PositionX) == abs(mY - GameState[pieceSelected].PositionY))
                {
                    for(int a = 0; a < GameState.size(); a++)
                    {
                        for(int i = (abs(mX  - GameState[pieceSelected].PositionX) - 1) *(abs(mX  - GameState[pieceSelected].PositionX) / (mX  - GameState[pieceSelected].PositionX)); i != 0; i += -1 * (abs(i) / i))
                        {
                            if(GameState[pieceSelected].PositionX + i == GameState[a].PositionX && GameState[pieceSelected].PositionY + abs(i) * (abs(mY - GameState[pieceSelected].PositionY)/(mY - GameState[pieceSelected].PositionY)) == GameState[a].PositionY)
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

            }
        }
        if(GameState[pieceSelected].Piece == 'K')
        {
            if((abs(mX - GameState[pieceSelected].PositionX) <= 1 && abs(mY - GameState[pieceSelected].PositionY) <= 1) && (abs(mX - GameState[pieceSelected].PositionX) != 0 || abs(mY - GameState[pieceSelected].PositionY) != 0))
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
                if(GameState[i].PositionY == GameState[pieceSelected].PositionY)
                    if((GameState[i].PositionX < GameState[pieceSelected].PositionX && GameState[i].PositionX > GameState[castleRook].PositionX) || (GameState[i].PositionX > GameState[pieceSelected].PositionX && GameState[i].PositionX < GameState[castleRook].PositionX))
                        somethingInTheWayThatIsNotABatmanReference = true;
            }
        }
        if(!somethingInTheWayThatIsNotABatmanReference)
        {
            moveCorrect = CheckCheck(GameStateCopy, playerTurn, GameStateCopy[pieceSelected].PositionX, GameStateCopy[pieceSelected].PositionY, Castle, castleRook);
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
        {
            moveCorrect = CheckCheck(GameStateCopy, playerTurn, GameStateCopy[kingPos].PositionX, GameStateCopy[kingPos].PositionY, Castle, castleRook);
            DEBUG("finished the CheckCheck");
        }
    if(moveCorrect)
        GameState[pieceSelected].Moved = true;
    DEBUG("Returned the move");
    return moveCorrect;
}
bool ChessCheck::CheckCheck(std::vector<ChessPiece> GameState, bool playerTurn, int kPX, int kPY, bool Castle, int castleRook)
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
            if(moveSim(copyPieces, PlayerTurn, kPX, kPY, i, false, Castle, castleRook))
            {
                DEBUGVALUE("\n%c,%c,%d",copyPieces[i].Colour, copyPieces[i].Piece,i);
                DEBUG("found it");
                temp = false;
                break;
            }
        }
        DEBUG("checked");
        return temp;
    }