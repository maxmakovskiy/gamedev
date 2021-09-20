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
    
    bool Check(const int winRow[3]) const;

    // returns Winner by given strategy
    void GetWinner(Player* winner) const;

    // Board have free steps?
    bool IsFull() const;

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
    BoardState VictoryCheck();

    bool IsOccupied(int indexCell) const
    {
        return area[indexCell] != Player::unknown;
    }

    void Clean();

    bool IsEmpty() const;
    
    GameArea();

    ~GameArea();
};
