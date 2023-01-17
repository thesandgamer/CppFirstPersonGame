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


//++ToDo: Principe du jeu: homme de slime qui doit s'échapper, peut lancer des boules de slime

//++ToDo Graphiques à faire:
//++ToDo rajouter une skybox https://www.raylib.com/examples/models/loader.html?name=models_skybox
//++ToDo rajouter lighting https://www.raylib.com/examples/shaders/loader.html?name=shaders_basic_lighting
//++ToDo rajouter post process hachurer et le colorer pour rendu cool https://www.raylib.com/examples/shaders/loader.html?name=shaders_postprocessing
//++ToDo rajouter un petit fog https://www.raylib.com/examples/shaders/loader.html?name=shaders_fog

//++ToDo: On à déjà: déplacement, saut, tir, il faudrait pour avoir un jeu: une carte, des ennemis, point de vie avec Ui, 
//++ToDo: true game: main menu avec un bouton pour jouer, et un menu de fin

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
CollisionManager* CollisionManager::instance = nullptr;

std::vector<CubeActor*> Terrain; //Stoquage des acteurs obstacles et sol
std::vector<Ennemy*> Ennemies; //Stoquage des acteurs obstacles et sol


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




    
    //----------Création aléatire du terrain---------
    Color color = { GetRandomValue(169, 122), GetRandomValue(109, 89), GetRandomValue(163, 128), 255 };
    vector<CubeActor* > cubes = {
        new CubeActor({ 0,1,0 }, { 3,2, 3 },color),
        new CubeActor({ 5,2,5 }, { 2,4, 2 },color),
        new CubeActor({0,4,17},{32,8,2},BLUE),
        new CubeActor({10,4,-68},{10,8,2},BLUE),
        new CubeActor({6,4,-73},{2,8,10},BLUE),
        new CubeActor({-6,4,-73},{2,8,10},BLUE),
        

    };
    Terrain.assign(cubes.begin(), cubes.end());

    vector<Ennemy* > ennmis = {
       new Ennemy({ 15,5,10 }, 10)


    };
    Ennemies.assign(ennmis.begin(), ennmis.end());

    Terrain.push_back(new CubeActor({ 0,0,0 }, { 32.0f,0.5f, 32.0f }, { 239, 123, 69, 255 }));//Créer le sol
    Terrain.push_back(new CubeActor({ 0,0,-35 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));
    Terrain.push_back(new CubeActor({ 0,0,-60 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));
    Terrain.push_back(new CubeActor({ 10,0,-60 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));
    Terrain.push_back(new CubeActor({ 0,0,-73 }, { 10.0f, 0.5f, 15.0f }, { 239, 123, 69, 255 }));

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

    CollisionManager::GetInstance()->Update();//Check les collisions


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
}
