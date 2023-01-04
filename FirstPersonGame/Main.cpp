#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>

#include "Ch_MainCharacter.h"
#include "CollisionManager.h"

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

BoxCollision groundCol;

void Start()
{
    character.Start();
    collisionManager.Start();

    collisionManager.AddCollider(&character.collisionBox);
    Vector3 goundPos{ 0,0,0 };
    groundCol = { &goundPos,{32,0.2f,32} };
    //groundCol = { &goundPos,{1,12,1} };
    collisionManager.AddCollider(&groundCol);

    
}

void Update()
{
    character.Update();
    collisionManager.Update();

}

void Draw()
{
    BeginDrawing();
    ClearBackground(RED);

    BeginMode3D(character.GetCamera());

    collisionManager.Draw();

    groundCol.Draw();
    DrawPlane({ 0.0f, 0.0f, 0.0f },{ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
    character.Draw();


    EndMode3D();

    DrawUi();
    EndDrawing();
}

void DrawUi()
{

}