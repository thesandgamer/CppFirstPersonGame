#include "Level.h"

void Level::Start()
{
    character.Start();
    CollisionManager::GetInstance()->Start();

    for each (CubeActor * element in Terrain)
    {
        element->Start();
    }
    for each (Ennemy * element in Ennemies)
    {
        element->Start();
    }
    for each (EndPortal * element in EndPortals)
    {
        element->Start();
    }

    //Créer la death zone
    deathzone = new CubeActor({ 0,-50,0 }, { 256, 10, 256 }, BLACK);
    deathzone->GetCollision()->layer = Layer5;
    deathzone->GetCollision()->collideWithLayer = Layer3;
    deathzone->GetCollision()->checkingCollision = true;

}

void Level::Update()
{
         character.Update();
    deathzone->Update();

    CollisionManager::GetInstance()->Update();//Check les collisions

    for each (CubeActor * element in Terrain)
    {
        element->Update();
    }
    for each (Ennemy * element in Ennemies)
    {
        element->Update();
    }
    for each (EndPortal * element in EndPortals)
    {
        element->Update();
    }

    if (deathzone->GetCollision()->IsColliding())
    {
        character.Death();
    }

}

void Level::Draw()
{
    BeginMode3D(character.GetCamera());
    CollisionManager::GetInstance()->Draw();


    for each (CubeActor * element in Terrain)
    {
        element->Draw();
    }
    for each (Ennemy * element in Ennemies)
    {
        element->Draw();
    }
    for each (EndPortal * element in EndPortals)
    {
        element->Draw();
    }

    deathzone->Draw();
    character.Draw();

}

void Level::DrawUi()
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

void Level::ResetLevel()
{
	character.Death();
}
