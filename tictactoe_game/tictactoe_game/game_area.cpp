#pragma once

enum class Player  {
    player_1,
    player_2,
    unknown
};

class GameArea {
    Player* area;

public:
    void makeStep(Player pl, int index)
    {
        area[index] = pl;
    }

    const Player* GetArea() const
    {
        return area;
    }

    GameArea() {
        area = new Player[9];
        for (int i = 0; i < 9; i++)
            area[i] = Player::unknown;
    }

    ~GameArea()
    {
        delete[] area;
    }
};
