#pragma once
#include "Level.h"

class LevelTest :
    public Level
{
public:
    LevelTest();
    ~LevelTest();

    void Start() override;
    void Update() override;
    void Draw() override;
    void DrawUi()override;

private:

};

