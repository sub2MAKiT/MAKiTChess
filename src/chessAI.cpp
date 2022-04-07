#include "chessAI.h"

AIMove chessAI::AIMOVE(Turn player, std::vector<ChessPiece> GameState)
{

    AIMove FinalMove;
    chessCheck Check;
    std::vector<ChessBoardsForAI> ALLMOVES;
    ALLMOVES.push_back({GameState,0,0,0,0});

    if(player.AI.option == 'B' || player.AI.option == 'D')
    {
        for(int i = 1; i <= player.AI.depth; i++)
        {
            for(int a = 0; a < ALLMOVES.size(); a++)
            {
                std::vector<ChessBoardsForAI> Temp = {};// I'm sorry
                if(ALLMOVES[a].cDepth == i-1)
                {
                    if(i % 2 != 0)
                        Temp = moveAI(ALLMOVES[a].Board,player.Player,i, ALLMOVES[a].firstId);
                    else
                        Temp = moveAI(ALLMOVES[a].Board,!player.Player,i, ALLMOVES[a].firstId);
                    ALLMOVES.insert(ALLMOVES.end(), Temp.begin(), Temp.end());
                }
            }
        }
        FinalMove = movePicker(ALLMOVES,player.AI.depth,player);
    }


    if(player.AI.option == 'S')
    {
        std::vector<SmartChessBoardsForAI> topDepth = {};
        for(int i = 1; i <= player.AI.depth; i++)
        {
            std::vector<ChessBoardsForAI> Temp = {};
            for(int a = 0; a < ALLMOVES.size(); a++)
            {
                if(i % 2 != 0)
                    Temp = moveAI(ALLMOVES[a].Board,player.Player,i, ALLMOVES[a].firstId);
                else
                    Temp = moveAI(ALLMOVES[a].Board,!player.Player,i, ALLMOVES[a].firstId);
            }
            for(int a = 0; a < Temp.size();a++)
            {
                topDepth.push_back({Temp[a],smartPointCalculator(Temp[a].Board,player.Player)});
            }
            float transformationConstant = (100 + (topDepth.size() - 40)) / 100;
            while(floor(topDepth.size() * transformationConstant) > reallySmartExclamationPoint(i) * player.AI.depth)
            {
                int worst = topDepth[0].points;
                for(int a = 0; a < topDepth.size(); a++)
                {
                    if(topDepth[a].points < worst && topDepth[a].CBFAI.cDepth == i)
                        worst = a;

                }
                topDepth.erase(topDepth.begin()+worst);
            }
            for(int a = 0; a < topDepth.size(); a++)
            {
                ALLMOVES.push_back(topDepth[a].CBFAI);
            }
        }
        FinalMove = movePicker(ALLMOVES,player.AI.depth,player);
    }


    return FinalMove;
}

AIMove chessAI::movePicker(std::vector<ChessBoardsForAI> ALLMOVES,int Depth, Turn player)
{
    AIMove move;
    std::vector<ChessBoardsForAI> lowestMoves = {};
    std::vector<int> points = {};
    for(int i = 0; i < ALLMOVES.size(); i++)
    {
        if(ALLMOVES[i].cDepth == Depth)
            lowestMoves.push_back(ALLMOVES[i]);
    }
    int winner = 0;
    if(player.AI.option == 'B')
    {
        for(int i = 0; i < lowestMoves.size();i++)
        {
            points.push_back(pointCalculator(lowestMoves[i].Board,player));
            if(i != 0)
                if(points[i] > points[winner])
                {
                    winner = i;
                }
        }
        for(int i = 0; i < ALLMOVES.size();i++)
        {
            if(ALLMOVES[i].firstId == lowestMoves[winner].firstId)
            {
                move.mX = ALLMOVES[i].mX;
                move.mY = ALLMOVES[i].mY;
                move.pieceSelected = ALLMOVES[i].pieceSelected;
            }
        }
    }

    if(player.AI.option == 'D')
    {
        int tempFirstID = lowestMoves[0].firstId;
        int averageSum = 0;
        std::vector<int> usedID = {lowestMoves[0].firstId};
        int averageDivider = 0;
        int winnerPoints = 0;
        bool tempBecauseWhyNot = false;
        while(tempFirstID >= 0)
        {
            for(int i = 0; i < lowestMoves.size();i++)
            {
                if(lowestMoves[i].firstId == tempFirstID)
                {
                    averageSum += pointCalculator(lowestMoves[i].Board,player);
                    averageDivider++;
                }
            }
            for(int i = 0; i < lowestMoves.size();i++)
            {
                tempBecauseWhyNot = false;
                for(int a = 0; a < usedID.size();a++)
                {
                    if(lowestMoves[i].firstId == usedID[a])
                    {
                        tempBecauseWhyNot = true;
                        break;
                    }
                }
                if(!tempBecauseWhyNot)
                {
                    if(averageDivider != 0)
                        if(winnerPoints < (averageSum / averageDivider))
                        {
                            winnerPoints = (averageSum / averageDivider);
                            winner = tempFirstID;
                        }
                    averageSum = 0;
                    averageDivider = 0;
                    tempFirstID = lowestMoves[i].firstId;
                    tempFirstID = lowestMoves[i].firstId;
                    usedID.push_back(tempFirstID);
                    i = lowestMoves.size();
                }
            }
            if(tempBecauseWhyNot)
                tempFirstID = -1;

        }
        for(int i = 0; i < ALLMOVES.size();i++)
        {
            if(ALLMOVES[i].firstId == winner && ALLMOVES[i].cDepth == 1)
            {
                move.mX = ALLMOVES[i].mX;
                move.mY = ALLMOVES[i].mY;
                move.pieceSelected = ALLMOVES[i].pieceSelected;
            }
        }
    }

    if(player.AI.option == 'S')
    {
        std::vector<int> tempFirstID = {};
        std::vector<ChessBoardsForAI> tempBoard = {};
        std::vector<SmartChessBoardsForAI> tempTempBoard = {};
        bool isIDTaken = false;
        for(int a = 0; a < lowestMoves.size();a++)
        {
            isIDTaken = false;
            for(int b = 0; b < tempFirstID.size();b++)
            {
                if(lowestMoves[a].firstId == tempFirstID[b])
                    isIDTaken = true;
            }
            if(!isIDTaken)
                tempFirstID.push_back(lowestMoves[a].firstId);
        }
        for(int i = 0; i < tempFirstID.size();i++)
        {
            for(int a = 0; a < lowestMoves.size();a++)
            {
                if(tempFirstID[i] == lowestMoves[a].firstId)
                    tempBoard.push_back(lowestMoves[a]);
            }
            int worstA = 0;
            int worst = smartPointCalculator(tempBoard[0].Board,(Depth % 2 == 0) ? !player.Player : player.Player);
            for(int a = 0; a < tempBoard.size(); a++)
            {
                int sPC = smartPointCalculator(tempBoard[a].Board,(Depth % 2 == 0) ? !player.Player : player.Player);
                if(sPC < worst)
                {
                    worstA = a;
                    worst = sPC;
                }
            }
            tempTempBoard.push_back({tempBoard[worstA],worst});
        }
        int bestA = 0;
        int best = tempTempBoard[0].points;
        for(int a = 0; a < tempTempBoard.size(); a++)
        {
            if(tempTempBoard[a].points > best)
            {
                bestA = a;
                best = tempTempBoard[a].points;
            }
        }
        int allMovesWinner = 0;
        for(int i = 0; i < ALLMOVES.size();i++)
        {
            if(ALLMOVES[i].cDepth == 1 && ALLMOVES[i].firstId == tempTempBoard[bestA].CBFAI.firstId)
                allMovesWinner = i;
        }

        move.mX = ALLMOVES[allMovesWinner].mX;
        move.mY = ALLMOVES[allMovesWinner].mY;
        move.pieceSelected = ALLMOVES[allMovesWinner].pieceSelected;

    }
    return move;
}

std::vector<ChessBoardsForAI> chessAI::moveAI(std::vector<ChessPiece> GameStateOG, bool isWhite, int cDepth, int firstID)
{
    std::vector<ChessPiece> GameStateFirst = GameStateOG;
    std::vector<ChessBoardsForAI> Chess4d = {};
    chessCheck ChessC;
    bool Castle;
    int CastleInt;
    int castleRX;
    int castleKX;
    std::vector<ChessPiece> GameState = GameStateOG;
    for(int i = 0; i < 8; i++)
    {
        for(int a = 0; a < 8; a++)
        {
            for(int b = 0; b < GameState.size(); b++)
            {
                int moveID;
                GameState = GameStateOG;
                Castle = false;
                CastleInt = 0;
                if(ChessC.moveSim(GameState, isWhite, i, a, b, true, Castle, CastleInt))
                {
                    if(cDepth == 1)
                    {
                        moveID = i * 8 * GameState.size() + a * GameState.size() + b;
                    } else {
                        moveID = firstID;
                    }
                    if(Castle)
                    {
                        castleRX = GameState[CastleInt].PositionX;
                        castleKX = GameState[b].PositionX;
                        GameState[b].PositionX = ((castleRX / 7) * 4) + 2;
                        GameState[CastleInt].PositionX = GameState[b].PositionX + (abs(4 - GameState[b].PositionX)/(4 - GameState[b].PositionX));
                        GameState[b].Moved = true;
                        GameState[CastleInt].Moved = true;
                    } else {
                        GameState[b].PositionX = i;
                        GameState[a].PositionY = a;
                    }
                    for(int d = 0; d < GameState.size(); d++)
                    {
                        for(int e = 0; e < GameState.size();e++)
                        {
                            if(d != e)
                                if(GameState[e].PositionX == GameState[d].PositionX && GameState[e].PositionY == GameState[d].PositionY)// this should be on the next line, but it didn't work, soo "if(GameState[b].Colour != GameState[d].Colour)"
                                        if(GameState[e].Colour == 'B')
                                        {
                                            GameState.erase(GameState.begin()+(isWhite ? e : d));
                                        }
                        }
                    }
                    Chess4d.push_back({GameState, i, a, cDepth, moveID,b});
                }
            }
        }
    }

    return Chess4d;
}

int chessAI::pointCalculator(std::vector<ChessPiece> GameState, Turn player)
{
    char Colour;
    if(player.Player)
        Colour = 'W';
    else
        Colour = 'B';
    int points = 100;
    for(int i = 0; i < GameState.size(); i++)
    {
        if(GameState[i].Colour == Colour)
        {
            if(GameState[i].Piece == 'P')
                points++;
            else if(GameState[i].Piece == 'R')
                points += 5;
            else if(GameState[i].Piece == 'B' || GameState[i].Piece == 'C')
                points += 3;
            else if(GameState[i].Piece == 'Q')
                points += 8;
            else
                points += 1;
        }
        if(GameState[i].Colour != Colour)
        {
            if(GameState[i].Piece == 'P')
                points--;
            else if(GameState[i].Piece == 'R')
                points -= 5;
            else if(GameState[i].Piece == 'B' || GameState[i].Piece == 'C')
                points -= 3;
            else if(GameState[i].Piece == 'Q')
                points -= 8;
            else
                points -= 1;
        }
    }
    return points;
}

int chessAI::smartPointCalculator(std::vector<ChessPiece> GameState, bool player)
{
    chessCheck chessC;
    int points = 100;
    for(int i = 0; i < GameState.size(); i++)
    {
        if(GameState[i].Colour == player ? 'W' : 'B')
        {
            if(GameState[i].Piece == 'P')
            {
                points++;
                points += floor(abs(abs(player - 1) * 7 - GameState[i].PositionY) / 3);
                if(GameState[i].PositionY == player ? 0 : 7)
                    points += 4;
            }
            else if(GameState[i].Piece == 'R')
                points += 5;
            else if(GameState[i].Piece == 'B' || GameState[i].Piece == 'C')
                points += 3;
            else if(GameState[i].Piece == 'Q')
                points += 8;
        }
        if(GameState[i].Colour != player ? 'W' : 'B')
        {
            if(GameState[i].Piece == 'P')
                points--;
            else if(GameState[i].Piece == 'R')
                points -= 5;
            else if(GameState[i].Piece == 'B' || GameState[i].Piece == 'C')
                points -= 3;
            else if(GameState[i].Piece == 'Q')
                points -= 8;
            else
            {
                if(!chessC.CheckCheck(GameState, !player, GameState[i].PositionX, GameState[i].PositionY, false, 0))
                    points += 4;
            }
        }
    }
    return points;
}

int chessAI::reallySmartExclamationPoint(int value)
{
    int tempValue = 1;
    for(int i = value; i > 0; i--)
    {
        tempValue *= i;
    }
    return tempValue;
}