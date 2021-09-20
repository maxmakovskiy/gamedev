#include "game_area.h"

bool GameArea::Check(const int winRow[3]) const
{
    if (area[winRow[0]] == area[winRow[1]] &&
        area[winRow[0]] == area[winRow[2]] &&
        area[winRow[1]] == area[winRow[2]])
    {
        return true;
    }

    return false;
}

// returns Winner by given strategy
const int* GameArea::GetWinner(Player* winner)
{
    for (int i = 0; i < 8; i++)
    {
        if (Check(strategy[i]) && (area[strategy[i][0]] == Player::player_1))
        {
            *winner = Player::player_1;
            return strategy[i];
        }
        else if (Check(strategy[i]) && (area[strategy[i][0]] == Player::player_2))
        {
            *winner = Player::player_2;
            return strategy[i];
        }
    }
}

// Board have free steps?
bool GameArea::IsFull() const
{
    for (int i = 0; i < 9; i++)
    {
        if (area[i] == Player::unknown)
            return false;
    }

    return true;
}
   
// Calls after every user step
// and check who is win or gameboard is full and occurs draw situation
const int* GameArea::VictoryCheck(BoardState &state)
{ 
    const int* winnerComb;
    Player temp;
    winnerComb = GetWinner(&temp);
    if (temp == Player::player_1)
        state = BoardState::player1_win;
    else if (temp == Player::player_2)
        state = BoardState::player2_win;
    // if AREA is FULL
    else if (IsFull())
        state = BoardState::draw;
    else
        state = BoardState::not_end;

    return winnerComb;
}

void GameArea::Clean()
{
    for (int i = 0; i < 9; i++)
    {
        area[i] = Player::unknown;
    }
}

bool GameArea::IsEmpty() const
{
    for (int i = 0; i < 9; i++)
    {
        if (area[i] == Player::player_1 ||
            area[i] == Player::player_2)
        {
            return false;
        }
    }

    return true;
}

GameArea::GameArea() 
{
    area = new Player[9];
    for (int i = 0; i < 9; i++)
        area[i] = Player::unknown;
}

GameArea::~GameArea()
{
    delete[] area;
}