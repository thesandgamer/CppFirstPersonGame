#include "Level01.h"

    Level01::Level01()
    {
    }

    Level01::~Level01()
    {
    }

    void Level01::Start()
    {
        Level::Start();
        //----------Création du terrain---------
        Color color = { GetRandomValue(169, 122), GetRandomValue(109, 89), GetRandomValue(163, 128), 255 };
        std::vector<CubeActor* > cubes = {
            // Murs
            //new CubeActor({ 0,1,0 }, { 3,2, 3 },color),
            
          



        };
        Terrain.assign(cubes.begin(), cubes.end());

       //Sol 
        Terrain.push_back(new CubeActor({ 0,0,0 }, { 32.0f,10.0f, 32.0f }, { 239, 123, 69, 255 }));
        Terrain.push_back(new CubeActor({ 30,3,30 }, { 32.0f,10.0f, 32.0f }, { 239, 123, 69, 255 }));
        Terrain.push_back(new CubeActor({ -30,3,30 }, { 32.0f,10.0f, 32.0f }, { 239, 123, 69, 255 }));
        Terrain.push_back(new CubeActor({ 0,6,30 }, { 32.0f,10.0f, 32.0f }, { 239, 123, 69, 255 }));

        Terrain.push_back(new CubeActor({ -30,3,60 }, { 32.0f,10.0f, 32.0f }, { 239, 123, 69, 255 }));
    }


    void Level01::Update()
    {
        Level::Update();
    }

    void Level01::Draw()
    {
        Level::Draw();
    }

    void Level01::DrawUi()
    {
        Level::DrawUi();
    }
