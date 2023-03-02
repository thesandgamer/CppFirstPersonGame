#include "LevelTest.h"
#include "LevelManager.h"

LevelTest::LevelTest()
{
}

LevelTest::~LevelTest()
{
}

void LevelTest::Start()
{
    Level::Start();

    //-----------------------------------------
    Color color = { GetRandomValue(169, 122), GetRandomValue(109, 89), GetRandomValue(163, 128), 255 };
    std::vector<CubeActor* > cubes = {
        new CubeActor({ 0,1,0 }, { 3,2, 3 },color),
        new CubeActor({ 5,2,5 }, { 2,4, 2 },color),
    };
    Terrain.assign(cubes.begin(), cubes.end());

    std::vector<Ennemy* > ennmis = {
       new Ennemy({ 20,5,20 }, 10)
    };
    Ennemies.assign(ennmis.begin(), ennmis.end());

    Terrain.push_back(new CubeActor({ 0,0,0 }, { 64.0f,0.5f, 64.0f }, { 239, 123, 69, 255 }));//Créer le sol
    
    /*
    const int MAX_COLUMNS = 30;

    float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };

    
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        Vector3 scale = { GetRandomValue(1, 5), GetRandomValue(4, 15), GetRandomValue(1,8) };
        Vector3 positions = { GetRandomValue(-15, 15), GetRandomValue(scale.y / 2.0f,scale.y), GetRandomValue(-15, 15) };
        Color color = { GetRandomValue(169, 122), GetRandomValue(109, 89), GetRandomValue(163, 128), 255 };
        Terrain.push_back(new CubeActor(
            positions,
            scale,
            color));

    }*/

    endTrigger.AddFunctionToTrigger((std::bind(&(LevelManager::GoToNextLevel), LevelManager::GetInstance())));
    endTrigger.Start();

}

void LevelTest::Update()
{
    Level::Update();
    endTrigger.Update();
}

void LevelTest::Draw()
{
    Level::Draw();
    endTrigger.Draw();
}

void LevelTest::DrawUi()
{
    Level::DrawUi();

}
