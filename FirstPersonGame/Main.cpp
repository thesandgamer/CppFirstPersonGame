#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>

#include "Ch_MainCharacter.h"
#include "CollisionManager.h"
#include "CubeActor.h"

//++ToDo rajouter une skybox https://www.raylib.com/examples/models/loader.html?name=models_skybox

using namespace std;

//Editor Variable
void Update();
void Draw();
void DrawUi();
void Start();

//Setup la taille de l'écran
int const screenWidth = 960;
int const screenHeight = 540;

Ch_MainCharacter character;
CollisionManager collisionManager;

std::vector<CubeActor*> Terrain;


int main(int argc, char* argv[])
{

    //Créer un écran et on met les fps à 60
    string windowName = "FirstPersonGame";
    InitWindow(screenWidth, screenHeight, windowName.c_str());

    //ToggleFullscreen();
    SetWindowPosition(0, 10);
    SetTargetFPS(60);

    Start();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        Update();
        // Draw
        Draw();       

    }

    CloseWindow();

    return 0;


}

void Start()
{
    character.Start();
    collisionManager.Start();

    collisionManager.AddCollider(character.GetGroundCollider());
    collisionManager.AddCollider(character.GetBodyCollider());

    Terrain.push_back(new CubeActor({ 0,0,0 }, { 32.0f,0.5f, 32.0f },GRAY));//Créer le sol
    //Terrain.at(0)->GetCollision()->checkingCollision = true;


    
    const int MAX_COLUMNS = 16;

    float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        Vector3 scale = { GetRandomValue(1, 15), GetRandomValue(1, 15), GetRandomValue(1,12) };
        Vector3 positions = { (float)GetRandomValue(-15, 15), scale.y / 2.0f, (float)GetRandomValue(-15, 15) };
        Color color = { GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
        Terrain.push_back(new CubeActor(
            positions,
            scale,
            color));

    }
    
    for each (CubeActor * element in Terrain)
    {
        collisionManager.AddCollider( element->GetCollision());
    }

    std::cout << "end \n";
    
    
}

void Update()
{
    character.Update();

    for each (CubeActor * element in Terrain)
    {
        element->Draw();
    }

    collisionManager.Update();
}

void Draw()
{
    BeginDrawing();
    ClearBackground(RED);

    BeginMode3D(character.GetCamera());

    collisionManager.Draw();

    for each (CubeActor* element in Terrain)
    {
        element->Draw();
    }
    DrawCube({ 0,0,0 }, 1.0f, 1.0f, 1.0f, BLUE);

    character.Draw();


    EndMode3D();

    DrawUi();
    EndDrawing();
}

void DrawUi()
{

}