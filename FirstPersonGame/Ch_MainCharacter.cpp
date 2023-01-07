#include "Ch_MainCharacter.h"

void Ch_MainCharacter::Start()
{
    camera.SetParent(&transf);

    groundBox.SetParent(&transf);
    bodyBox.SetParent(&transf);
    forwardRay.SetParent(&transf);//Ajoute le component

    camera.Start();
    gravity.SetPos(&pos);

    forwardRay.Offset.translation = { 0,-1.f,0 };

    bodyBox.checkingCollision = true;

    groundBox.Offset.translation = { 0,-1.8f,0 };//Place le rayon au pieds
    groundBox.checkingCollision = true;

    forwardRay.checkingCollision = true;

}

void Ch_MainCharacter::Draw()
{
    camera.Draw();
    DrawCube({pos.x,pos.y-0.5f,pos.z}, 0.1f, 0.1f, 0.1f, LIME);//Dessine son corps
   
    if (forwardRay.IsColliding()) DrawText("Col ray", 50, 50, 20, WHITE);

    groundBox.Draw();
    bodyBox.Draw();

    forwardRay.Draw();


}

void Ch_MainCharacter::Update()
{
    //Process Gravity
    gravity.canFall = (groundBox.IsColliding()) ? false : true;
    gravity.Update();

    //Process inputs
    ProcessInputs();

    //Change State
    state = (groundBox.IsColliding()) ? InAir : Grounded;


    Move();

    camera.Update();

    ProcessJump();

    //++ToDo: faire en sorte que le rayon forward rotate en fonction de la rotation de la camera

}

void Ch_MainCharacter::ProcessInputs()
{
    dir[0] = IsKeyDown(KEY_W);
    dir[1] = IsKeyDown(KEY_S);
    dir[2] = IsKeyDown(KEY_D);
    dir[3] = IsKeyDown(KEY_A);

    if (IsKeyPressed(KEY_SPACE)) Jump();
    if (IsKeyReleased(KEY_SPACE)) StopJumping();
    
}



//++ To do : faire accélération et décélération
//++ camera bubble activable avec varaible exposé de force
void Ch_MainCharacter::Move()
{
    //---------------------Gère la direction dans laquelle aller
    //On regarde tous les inputs pour faire les diagonales 
    float xValue = 
       (sinf(camera.GetAngle().x) * dir[1] -
        sinf(camera.GetAngle().x) * dir[0] -
        cosf(camera.GetAngle().x) * dir[3] +
        cosf(camera.GetAngle().x) * dir[2]) ;

    float yValue = 
       (cosf(camera.GetAngle().x) * dir[1] -
        cosf(camera.GetAngle().x) * dir[0] +
        sinf(camera.GetAngle().x) * dir[3] -
        sinf(camera.GetAngle().x) * dir[2]) ;


    //------------------Va déplacer le character
   // BaseMovement(xValue, yValue);
    AccelerationFrictionMove(xValue, yValue);
    /*
    Matrix translation = MatrixTranslate(pos.x, pos.y, pos.z);
    Matrix rotation = MatrixRotateXYZ({ PI * 2 - camera.GetAngle().y, PI * 2 - camera.GetAngle().x, 0});
    transform = MatrixMultiply(translation, rotation);

    */
   // transform = MatrixTranslate(pos.x, pos.y, pos.z);
    transf.translation = pos;
    //++ToDo: ajouter la rotation dans le transform
    transf.rotation = camera.offsetTransform.rotation;
}

void Ch_MainCharacter::BaseMovement(float xValue, float yValue)
{
    maxSpeed = 10;

    xValue *= maxSpeed;
    yValue *= maxSpeed;

    pos.x += xValue * GetFrameTime();
    pos.z += yValue * GetFrameTime();
}

void Ch_MainCharacter::AccelerationFrictionMove(float xValue, float yValue)
{
    float dt = GetFrameTime();

    maxSpeed = 100;
    deceleration = -8;
    acceleration = 8;

    //On défnit les valeur maxes
    xValue *= maxSpeed;
    yValue *= maxSpeed;

    acc.x = xValue;
    acc.y = yValue;

    //Fricction : on réduit l'accélération
    acc.x += deceleration * vel.x;
    acc.y += deceleration * vel.y;

    //On repositionne avec une accélération
    pos.x += dt * vel.x + 0.5f * acc.x * dt * dt;
    pos.z += dt * vel.y + 0.5f * acc.y * dt * dt;

    //On augmente la vélocité
    vel.x += dt * acc.x;
    vel.y += dt * acc.y;

    acc = { 0,0 };
}

void Ch_MainCharacter::MoveWithEasing(float xValue, float yValue)
{
    //Utiliser du lerp avec du easing pour lerper la valeur de 
    //actual speed entre 0 et max speed
    //puis changer la position avec xValue * actual speed
}


void Ch_MainCharacter::Jump()
{
   // if (state == InAir) return;
    gravity.velocity = { 0,jumpVelocity,0 };//Ajoute une force de saut
    inJump = true;
    //Pour désactiver la collision pour pouvoir décoller du sol
    groundBox.checkingCollision = false;
    groundBox.collisions = {};

}

void Ch_MainCharacter::ProcessJump()
{
    float dt = GetFrameTime();

    if (gravity.velocity.y < 0) //Quand on chute
    {
        gravity.velocity.y += 1 * -GRAVITY_VALUE * (fallMultiplier - 1) * dt;
        groundBox.checkingCollision = true;


    }
    else if (gravity.velocity.y > 0 && !IsKeyDown(KEY_SPACE))//Quand on est en saut sans appuyer sur la touche de saut
    {
        gravity.velocity.y += 1 * -GRAVITY_VALUE * (lowJumpMultiplier - 1) * dt;

    }
}

void Ch_MainCharacter::StopJumping()
{

}