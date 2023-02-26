#include "Level0.h"

void Level0::Start()
{
    //---------------------
    character.Start();
    CollisionManager::GetInstance()->Start();

    deathzone = new CubeActor({ 0,-50,0 }, { 256, 10, 256 }, BLACK);
    deathzone->GetCollision()->layer = Layer5;
    deathzone->GetCollision()->collideWithLayer = Layer3;
    deathzone->GetCollision()->checkingCollision = true;



    //----------Création aléatire du terrain---------
    Color color = { GetRandomValue(169, 122), GetRandomValue(109, 89), GetRandomValue(163, 128), 255 };
    std::vector<CubeActor* > cubes = {
        new CubeActor({ 0,1,0 }, { 3,2, 3 },color),
        new CubeActor({ 5,2,5 }, { 2,4, 2 },color),
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
       new Ennemy({ 15,5,10 }, 10)
    };
    Ennemies.assign(ennmis.begin(), ennmis.end());

    Terrain.push_back(new CubeActor({ 0,0,0 }, { 32.0f,0.5f, 32.0f }, { 239, 123, 69, 255 }));//Créer le sol
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
    character.Update();


    for each (CubeActor * element in Terrain)
    {
        element->Update();
    }
    for each (Ennemy * element in Ennemies)
    {
        element->Update();
    }
    deathzone->Update();

    CollisionManager::GetInstance()->Update();//Check les collisions

    if (deathzone->GetCollision()->IsColliding())
    {
        character.Death();
    }
}

void Level0::Draw()
{
    CollisionManager::GetInstance()->Draw();

    for each (CubeActor * element in Terrain)
    {
        element->Draw();
    }
    for each (Ennemy * element in Ennemies)
    {
        element->Draw();
    }
    deathzone->Draw();


    character.Draw();
}

void Level0::DrawUi()
{
    /*
   DrawText(TextFormat("rot x: % 02.02f", QuaternionToEuler(character.transf.rotation).x), 10, 10, 10, WHITE);
   DrawText(TextFormat("rot y: % 02.02f", QuaternionToEuler(character.transf.rotation).y ), 10, 20 , 10, WHITE);
   DrawText(TextFormat("rot z: % 02.02f", QuaternionToEuler(character.transf.rotation).z ), 10, 30, 10, WHITE);
   */
    DrawText(TextFormat("pos x: % 02.02f", character.transf.translation.x), 10, 10, 10, WHITE);
    DrawText(TextFormat("pos y: % 02.02f", character.transf.translation.y), 10, 20, 10, WHITE);
    DrawText(TextFormat("pos z: % 02.02f", character.transf.translation.z), 10, 30, 10, WHITE);
    //DrawText(TextFormat("rb vel: % 02.02f", character.gravity.velocity.y), 10, 20, 10, WHITE);

    DrawText(TextFormat("Is grounded: % 02i", character.IsGrounded()), 100, 10, 10, WHITE);
}
