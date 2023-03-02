#include "raylib.h"
#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>
#include <string>
#include "raylib.h"

#include "rlgl.h"
#include "raymath.h"      // Required for: MatrixPerspective(), MatrixLookAt()

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#include "LevelManager.h"

using namespace std;


//++ToDo: Principe du jeu: homme de slime qui doit s'échapper, peut lancer des boules de slime

//++ToDo Graphiques à faire:
//++ToDo rajouter une skybox https://www.raylib.com/examples/models/loader.html?name=models_skybox
//++ToDo rajouter lighting https://www.raylib.com/examples/shaders/loader.html?name=shaders_basic_lighting
//++ToDo rajouter post process hachurer et le colorer pour rendu cool https://www.raylib.com/examples/shaders/loader.html?name=shaders_postprocessing
//++ToDo rajouter un petit fog https://www.raylib.com/examples/shaders/loader.html?name=shaders_fog

//++ToDo: point de vie avec Ui, 
//++ToDo: true game: main menu avec un bouton pour jouer, et un menu de fin


//++ToDo: ajouter un timer qui se reset quand on reset le jeu: pour pousser le coté speerun
//++ToDo: faire un system porte/intérupteur
//++ToDo: passer au niveau suivant: objet avec collision qui amène au niveau suivant

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

CollisionManager* CollisionManager::instance{ nullptr };


LevelManager levelManager;


int main(int argc, char* argv[])
{
    //Créer un écran et on met les fps à 60
    string windowName = "FirstPersonGame";
    InitWindow(screenWidth, screenHeight, windowName.c_str());

    //ToggleFullscreen();
    SetWindowPosition(0, 10);
    SetTargetFPS(60);

    levelManager.Init();
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
    levelManager.Start();    
}

void Update()
{
    levelManager.Update();

    if (IsKeyPressed(KEY_R))
    {
        ResetGame();
    }
    if (IsKeyPressed(KEY_KP_ADD))
    {
        levelManager.GoToNextLevel();
    }

}

void Draw()
{
    BeginDrawing();
    ClearBackground({4,42,43,255});

    levelManager.Draw();

    EndMode3D();

    DrawUi();
    EndDrawing();
}

void DrawUi()
{
    levelManager.DrawUi();
}



void ResetGame()
{
    levelManager.ResetLevel();
}


