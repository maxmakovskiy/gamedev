#pragma once

enum class Player : int {
    player_1 = 0,
    player_2,
    unknown
};

enum class BoardState : int {
    player1_win = 0,
    player2_win,
    draw,
    not_end
};

class GameArea {
    Player* area;

    // strategy of winning
    const int strategy [8][3]= {
        // horizontal
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        // vertical
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        // diagonals
        {0, 4, 8},
        {2, 4, 6},
    };
    
    bool Check(const int winRow[3]) const
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
    void GetWinner(Player* winner) const
    {
        for (int i = 0; i < 8; i++)
        {
            if (Check(strategy[i]) && (area[strategy[i][0]] == Player::player_1))
                *winner = Player::player_1;
            else if (Check(strategy[i]) && (area[strategy[i][0]] == Player::player_2))
                *winner = Player::player_2;

        }
    }

    // Board have free steps?
    bool IsFull() const
    {
        for (int i = 0; i < 9; i++)
        {
            if (area[i] == Player::unknown)
                return false;
        }

        return true;
    }

public:
    void makeStep(Player pl, int index)
    {
        area[index] = pl;
    }

    const Player* GetArea() const
    {
        return area;
    }
   
    // Calls after every user step
    // and check who is win or gameboard is full and occurs draw situation
    BoardState VictoryCheck()
    { 
        Player temp;
        GetWinner(&temp);
        if (temp == Player::player_1)
            return BoardState::player1_win;
        else if (temp == Player::player_2)
            return BoardState::player2_win;
        // if AREA is FULL
        else if (IsFull())
            return BoardState::draw;
        else
            return BoardState::not_end;
    }

    bool IsOccupied(int indexCell) const
    {
        return area[indexCell] != Player::unknown;
    }

    GameArea() 
    {
        area = new Player[9];
        for (int i = 0; i < 9; i++)
            area[i] = Player::unknown;
    }

    ~GameArea()
    {
        delete[] area;
    }
};
