#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>

#include "Ch_MainCharacter.h"
#include "CollisionManager.h"
#include "CubeActor.h"
#include "Ennemy.h"
using namespace std;


//++ToDo: Principe du jeu: homme de slime qui doit s'échapper, peut lancer des boules de slime

//++ToDo Graphiques à faire:
//++ToDo rajouter une skybox https://www.raylib.com/examples/models/loader.html?name=models_skybox
//++ToDo rajouter lighting https://www.raylib.com/examples/shaders/loader.html?name=shaders_basic_lighting
//++ToDo rajouter post process hachurer et le colorer pour rendu cool https://www.raylib.com/examples/shaders/loader.html?name=shaders_postprocessing
//++ToDo rajouter un petit fog https://www.raylib.com/examples/shaders/loader.html?name=shaders_fog

//++ToDo: On à déjà: déplacement, saut, tir, il faudrait pour avoir un jeu: une carte, des ennemis, point de vie avec Ui, 
//++ToDo: true game: main menu avec un bouton pour jouer, et un menu de fin


//++ToDo: Dead zone
//++ToDo: ajouter un timer qui se reset quand on reset le jeu: pour pousser le coté speerun

//Editor Variable
void Update();
void Draw();
void DrawUi();
void Start();

//
void ResetGame();

//Setup la taille de l'écran
int const screenWidth = 960;
int const screenHeight = 540;

Ch_MainCharacter character;
CollisionManager* CollisionManager::instance = nullptr;

std::vector<CubeActor*> Terrain; //Stoquage des acteurs obstacles et sol
std::vector<Ennemy*> Ennemies; //Stoquage des acteurs obstacles et sol

CubeActor* deathzone;


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
    CollisionManager::GetInstance()->Start();

    deathzone = new CubeActor({0,-50,0}, { 256, 10, 256 },BLACK);
    deathzone->GetCollision()->collideWithLayer = Layer3;
    //deathzone->GetCollision()->checkingCollision = true;


    
    //----------Création aléatire du terrain---------
    Color color = { GetRandomValue(169, 122), GetRandomValue(109, 89), GetRandomValue(163, 128), 255 };
    vector<CubeActor* > cubes = {
        new CubeActor({ 0,1,0 }, { 3,2, 3 },color),
        new CubeActor({ 5,2,5 }, { 2,4, 2 },color),
        new CubeActor({0,4,17},{32,8,2},BLUE),
        new CubeActor({30,0,-90},{15,8,2},BLUE),
        new CubeActor({60,0,-65},{2,8,15},BLUE),
        new CubeActor({45,0,-45},{2,8,15},BLUE),
        new CubeActor({105,0,-49},{15,8,15},BLUE),
        new CubeActor({120,0,-37},{2,8,20},BLUE),
        

        new CubeActor({-6,4,-35},{2,8,14},GREEN),//Mur 1
        //new CubeActor({6,4,-35},{2,8,14},GREEN), //Mur 2
        new CubeActor({6,4,-65},{2,8,25},GREEN), // Mur 3
        new CubeActor({-6,4,-65},{2,8,25},GREEN),// Mur 4
        new CubeActor({10,4,-77},{10,8,2},GREEN),// Mur 5
        

    };
    Terrain.assign(cubes.begin(), cubes.end());

    vector<Ennemy* > ennmis = {
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
    Terrain.push_back(new CubeActor({ 120,0,-75 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));
    /*
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

    }*/
    //-----------------------
    
    
}

void Update()
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

    if (IsKeyPressed(KEY_R))
    {
        ResetGame();
    }

    if (deathzone->GetCollision()->IsColliding())
    {
        ResetGame();
    }


}

void Draw()
{
    BeginDrawing();
    ClearBackground({4,42,43,255});

    BeginMode3D(character.GetCamera());

    CollisionManager::GetInstance()->Draw();


    for each (CubeActor* element in Terrain)
    {
        element->Draw();
    }
    for each (Ennemy * element in Ennemies)
    {
        element->Draw();
    }
    deathzone->Draw();


    character.Draw();


    EndMode3D();

    DrawUi();
    EndDrawing();
}

void DrawUi()
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



void ResetGame()
{
    character.SetPos({ 4,20,4 });
}