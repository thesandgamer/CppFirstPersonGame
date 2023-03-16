#include "Level.h"


void Level::Start()
{
    //                                      Position / Orientation / Couleur
    lights[0] = CreateLight(LIGHT_POINT, { 0, 30, 0 }, {10,0,10}, WHITE, *Utility::GetInstance()->shader); // Create sun light
    /*
    lights[1] = CreateLight(LIGHT_POINT,  { 2, 1, 2 }, Vector3Zero(), RED, *Utility::GetInstance()->shader);
    lights[2] = CreateLight(LIGHT_POINT,  { -2, 1, 2 }, Vector3Zero(), GREEN, *Utility::GetInstance()->shader);
    lights[3] = CreateLight(LIGHT_POINT,  { 2, 1, -2 }, Vector3Zero(), BLUE, *Utility::GetInstance()->shader);*/

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
    for each (MovableActor * element in MovablesActors)
    {
        element->Start();
    }
    for each (Interuptor * element in Interuptors)
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
    for each (MovableActor * element in MovablesActors)
    {
        element->Update();
    }
    for each (Interuptor * element in Interuptors)
    {
        element->Update();
    }

    if (deathzone->GetCollision()->IsColliding())
    {
        character.Death();
    }

    //------Update lights

    float cameraPos[3] = { character.GetCamera().position.x,
        character.GetCamera().position.y,
        character.GetCamera().position.z };
    float cameraTarget[3] = { character.GetCamera().target.x, 
        character.GetCamera().target.y,
        character.GetCamera().target.z };

    std::cout << cameraPos[0] << std::endl;
    SetShaderValue(*Utility::GetInstance()->shader, Utility::GetInstance()->shader->locs[SHADER_LOC_VECTOR_VIEW],
        &cameraPos, SHADER_UNIFORM_VEC3);

    for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(*Utility::GetInstance()->shader, lights[i]);
    

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
    for each (MovableActor * element in MovablesActors)
    {
        element->Draw();
    }
    for each (Interuptor * element in Interuptors)
    {
        element->Draw();
    }

    deathzone->Draw();
    character.Draw();



    //------Draw debug sphere to see where lights are
    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (lights[i].enabled) DrawSphereEx(lights[i].position, 0.2f, 8, 8, lights[i].color);
        else DrawSphereWires(lights[i].position, 0.2f, 8, 8, ColorAlpha(lights[i].color, 0.3f));
    }

}

void Level::DrawUi()
{
    character.DrawUi();
    DrawFPS(80, 80);
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
