#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>

#include "Ch_MainCharacter.h"
#include "CollisionManager.h"
#include "CubeActor.h"


//++ToDo Graphiques � faire:
//++ToDo rajouter une skybox https://www.raylib.com/examples/models/loader.html?name=models_skybox
//++ToDo rajouter lighting https://www.raylib.com/examples/shaders/loader.html?name=shaders_basic_lighting
//++ToDo rajouter post process hachurer et le colorer pour rendu cool https://www.raylib.com/examples/shaders/loader.html?name=shaders_postprocessing
//++ToDO rajouter un petit fog https://www.raylib.com/examples/shaders/loader.html?name=shaders_fog

using namespace std;

//Editor Variable
void Update();
void Draw();
void DrawUi();
void Start();

//Setup la taille de l'�cran
int const screenWidth = 960;
int const screenHeight = 540;

Ch_MainCharacter character;
CollisionManager collisionManager;

std::vector<CubeActor*> Terrain; //Stoquage des acteurs obstacles et sol


int main(int argc, char* argv[])
{

    //Cr�er un �cran et on met les fps � 60
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

    Terrain.push_back(new CubeActor({ 0,0,0 }, { 32.0f,0.5f, 32.0f },{239, 123, 69, 255}));//Cr�er le sol
    //Terrain.at(0)->GetCollision()->checkingCollision = true;


    
    const int MAX_COLUMNS = 30;

    float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };

    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        Vector3 scale = { GetRandomValue(1, 5), GetRandomValue(4, 15), GetRandomValue(1,8) };
        Vector3 positions = { GetRandomValue(-15, 15), GetRandomValue(scale.y / 2.0f,scale.y ), GetRandomValue(-15, 15) };
        Color color = { GetRandomValue(169, 122), GetRandomValue(109, 89), GetRandomValue(163, 128), 255 };
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
    ClearBackground({4,42,43,255});

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
    DrawText(TextFormat("rot x: % 02.02f", character.GetFirstPersonCam().offsetTransform.rotation.x), 10, 10, 10, WHITE);
    DrawText(TextFormat("rot y: % 02.02f", character.GetFirstPersonCam().offsetTransform.rotation.y), 10, 20 , 10, WHITE);
    DrawText(TextFormat("rot z: % 02.02f", character.GetFirstPersonCam().offsetTransform.rotation.z), 10, 30, 10, WHITE);

}