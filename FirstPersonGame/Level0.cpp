#include "Level0.h"

Level0::Level0()
{
}

Level0::~Level0()
{
}

void Level0::Start()
{
    //----------------------------
    Level::Start();


    //----------Cr�ation du terrain---------
    Color color = { GetRandomValue(169, 122), GetRandomValue(109, 89), GetRandomValue(163, 128), 255 };
    std::vector<CubeActor* > cubes = {
        //new CubeActor({ 0,1,0 }, { 3,2, 3 },color),
        //new CubeActor({ 5,2,5 }, { 2,4, 2 },color),
        new CubeActor({0,4,17},{32,8,2},BLUE),
        new CubeActor({30,0,-90},{15,8,2},BLUE),
        new CubeActor({60,0,-65},{2,8,15},BLUE),
        new CubeActor({45,0,-45},{2,8,15},BLUE),

        new CubeActor({-6,4,-35},{2,8,14},GREEN),//Mur 1
        //new CubeActor({6,4,-35},{2,8,14},GREEN), //Mur 2
        new CubeActor({6,4,-65},{2,8,25},GREEN), // Mur 3
        new CubeActor({-6,4,-65},{2,8,25},GREEN),// Mur 4
        new CubeActor({10,4,-77},{10,8,2},GREEN),// Mur 5


    };
    Terrain.assign(cubes.begin(), cubes.end());

    std::vector<Ennemy* > ennmis = {
       //new Ennemy({ 15,5,10 }, 10)
    };
    Ennemies.assign(ennmis.begin(), ennmis.end());

    Terrain.push_back(new CubeActor({ 0,0,0 }, { 32.0f,0.5f, 32.0f }, { 239, 123, 69, 255 }));//Cr�er le sol
    Terrain.push_back(new CubeActor({ 0,0,-35 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));// Sol A
    Terrain.push_back(new CubeActor({ 0,0,-60 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));// Sol B
    Terrain.push_back(new CubeActor({ 0,0,-70 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));// Sol C
    Terrain.push_back(new CubeActor({ 5,0,-81 }, { 20.0f, 0.5f, 7.0f }, { 239, 123, 69, 255 })); // Sol D
    Terrain.push_back(new CubeActor({ 50,0,-80 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));//Sol E
    Terrain.push_back(new CubeActor({ 85,0,-30 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));//Sol F
    Terrain.push_back(new CubeActor({ 65,0,-30 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));


}

void Level0::Update()
{
    Level::Update();
}

void Level0::Draw()
{
    Level::Draw();
}

void Level0::DrawUi()
{
    Level::DrawUi();
}
