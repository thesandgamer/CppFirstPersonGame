#include <iostream>
#include <stdio.h>  
#include <math.h> 
#include <vector>

#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"      // Required for: MatrixPerspective(), MatrixLookAt()



#define RLIGHTS_IMPLEMENTATION

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#include "LevelManager.h"
#include "Utility.h"

using namespace std;


//++ToDo: Principe du jeu: homme de slime qui doit s'échapper, peut lancer des boules de slime

//++ToDo Graphiques à faire:
//++ToDo rajouter une skybox https://www.raylib.com/examples/models/loader.html?name=models_skybox
//++ToDo rajouter lighting https://www.raylib.com/examples/shaders/loader.html?name=shaders_basic_lighting
//++ToDo rajouter post process hachurer et le colorer pour rendu cool https://www.raylib.com/examples/shaders/loader.html?name=shaders_postprocessing
//++ToDo rajouter un petit fog https://www.raylib.com/examples/shaders/loader.html?name=shaders_fog

//++ToDo: true game: main menu avec un bouton pour jouer, et un menu de fin


//++ToDo: ajouter un timer qui se reset quand on reset le jeu: pour pousser le coté speerun
//++ToDo: quand on meurt reset le niveau
//++ToDo: rajouter des sons

//Editor Variable
void Init();
void Update();
void Draw();
void DrawUi();
void Start();

//
void ResetGame();

//Setup la taille de l'écran

Utility* Utility::instance{nullptr};

CollisionManager* CollisionManager::instance{ nullptr };

LevelManager* LevelManager::instance{ nullptr };



int main(int argc, char* argv[])
{
    //Créer un écran et on met les fps à 60
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
    string windowName = "FirstPersonGame";
    InitWindow(screenWidth, screenHeight, windowName.c_str());

    InitAudioDevice();      // Initialize audio device


    Init();
    ToggleFullscreen();

    SetWindowPosition(0, 10);
    SetTargetFPS(60);

    Utility::GetInstance()->Start();
    LevelManager::GetInstance()->Init();
    Start();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        Update();
        // Draw
        Draw();       
    }

    Utility::GetInstance()->Unload();

    CloseAudioDevice();

    CloseWindow();

    return 0;


}

Shader shader;

void Init()
{
   
#pragma region Basic Lighting shader
  // Load basic lighting shader
    
    /*
  shader = LoadShader(TextFormat("../resources/shaders/glsl%i/lighting.vs", GLSL_VERSION),
                      TextFormat("../resources/shaders/glsl%i/lighting.fs", GLSL_VERSION));
  */
    /*
    shader = LoadShader(TextFormat("../resources/shaders/glsl%i/Phong.vs", GLSL_VERSION),
                        TextFormat("../resources/shaders/glsl%i/Phong.fs", GLSL_VERSION));
  */
  shader = LoadShader(TextFormat("../resources/shaders/glsl%i/base.vs", GLSL_VERSION),
                      TextFormat("../resources/shaders/glsl%i/base.fs", GLSL_VERSION));

  // Get some required shader locations
  shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
  // NOTE: "matModel" location name is automatically assigned on shader loading,
  // no need to get the location again if using that uniform name
 // shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

   // Ambient light level (some basic lighting)
  int ambientLoc = GetShaderLocation(shader, "ambient");    //récupère la location de l'ambiant du shader
  float values[4] = { 0.1f, 0.1f, 0.1f, 1.0f };             //Change les valeurs de l'ambiant
  SetShaderValue(shader, ambientLoc, &values, SHADER_UNIFORM_VEC4); //Set la valeur de l'ambiant du shader

#pragma endregion


    //Set the shader link in the utility
    Utility::GetInstance()->shader = &shader;




}


void Start()
{
    LevelManager::GetInstance()->Start();
}

void Update()
{
    LevelManager::GetInstance()->Update();

    if (IsKeyPressed(KEY_R))
    {
        ResetGame();
    }
    if (IsKeyPressed(KEY_KP_ADD))
    {
        LevelManager::GetInstance()->GoToNextLevel();
    }

}

void Draw()
{
    BeginDrawing();
    ClearBackground({4,42,43,255});

    LevelManager::GetInstance()->Draw();

    EndMode3D();

    DrawUi();
    EndDrawing();
}

void DrawUi()
{
    LevelManager::GetInstance()->DrawUi();
}



void ResetGame()
{
    LevelManager::GetInstance()->ResetLevel();
}


