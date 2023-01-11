#include "Ch_MainCharacter.h"

void Ch_MainCharacter::Start()
{
    camera.SetParent(&transf);

    groundBox.SetParent(&transf);

    groundBox.layer = Layer1;
    forwardRay.layer = Layer1;
    //bodyBox.SetParent(&transf);

    forwardRay.SetParent(&transf);//Ajoute le component
    rightRay.SetParent(&transf);//Ajoute le component
    backwarddRay.SetParent(&transf);//Ajoute le component
    leftRay.SetParent(&transf);//Ajoute le component

    camera.Start();
    gravity.SetPos(&pos);

    forwardRay.Offset.translation = { 0,-1.f,0 };
    rightRay.Offset.translation = { 0,-1.f,0 };
    backwarddRay.Offset.translation = { 0,-1.f,0 };
    leftRay.Offset.translation = { 0,-1.f,0 };

    //bodyBox.checkingCollision = true;

    groundBox.Offset.translation = { 0,-1.8f,0 };//Place le rayon au pieds
    groundBox.checkingCollision = true;

    forwardRay.checkingCollision = true;

    shootingComponent.Start();

}

void Ch_MainCharacter::Draw()
{
    camera.Draw();
    DrawCube({pos.x,pos.y-0.5f,pos.z}, 0.1f, 0.1f, 0.1f, LIME);//Dessine son corps
   

    groundBox.Draw();
   // bodyBox.Draw();

    forwardRay.Draw();
    rightRay.Draw();
   // leftRay.Draw();
   // backwarddRay.Draw();


    shootingComponent.Draw();

    //-----------

    /*
    Vector3 startPos = { transf.translation.x + 0,
      transf.translation.y - 1.8f,
      transf.translation.z + 0 };//Son origine

    
    Vector3 direction = { GetVector({0,0,1}).x*10,0,GetVector({0,0,1}).z*10 };
    Vector3 endPos = Vector3Add(direction, startPos);
    DrawLine3D(startPos, endPos, PURPLE);

    direction = { GetVector({1,0,0}).x * 10,0,GetVector({1,0,0}).z * 10};
    endPos = Vector3Add(direction, startPos);
    DrawLine3D(startPos, endPos, PURPLE);
    */

}

void Ch_MainCharacter::Update()
{
    //Process Gravity
    gravity.canFall = (groundBox.IsColliding()) ? false : true;
    gravity.Update();

    //Process inputs
    ProcessInputs();

    //++ToDo: faire en sorte que la rotation en yaw du chara soit celle de la camera
    Quaternion newAngle = QuaternionFromEuler( 0, 0, QuaternionToEuler(camera.offsetTransform.rotation).z * DEG2RAD);
    transf.rotation = newAngle;
    Vector3 eul = QuaternionToEuler(transf.rotation);
    Vector3 camEul = QuaternionToEuler(camera.offsetTransform.rotation);
    /*
    std::cout << " Player: " << QuaternionToEuler(transf.rotation).z * DEG2RAD << "\n";
    std::cout << " Camera: " << QuaternionToEuler(camera.offsetTransform.rotation).z * DEG2RAD << "\n \n";
    */

    //---------
    
    //Vector3 direction = { GetForwardVector().x,0,GetForwardVector().z };//{GetForwardVector().x ,0,GetForwardVector().z};
    forwardRay.SetDirection(GetVector({0,0,-1}));
    rightRay.SetDirection(GetVector({ 1,0,0 }));
    backwarddRay.SetDirection(GetVector({ 0,0,1 }));
    leftRay.SetDirection(GetVector({ -1,0,0 }));
    
    //Change State

    state = (groundBox.IsColliding()) ? InAir : Grounded;
    isGrounded = groundBox.IsColliding();

    if (forwardRay.IsColliding())
    {
        collisionDirection |= Front;    //Ajoute collision front
        dir[0] = false;

    }
    else
    {
        collisionDirection ^= Front;    //Enlève collision front
    }


    Move();

    camera.Update();

    ProcessJump();

    shootingComponent.Update();

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


    //++ToDo: faire en sorte de tirer avec la rotation de la camera
    if (IsMouseButtonDown(0))
    {  
        shootingComponent.Shoot(transf.translation, Vector3Multiply(GetForwardVector(),{20,20,20}));
    }
}



//ToDo++ camera bubble activable avec varaible exposé de force
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

    transf.translation = pos;
    //transf.rotation = camera.offsetTransform.rotation; //Si on veut que la rotation du perso soit celle de la camera
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

Vector3 Ch_MainCharacter::GetForwardVector()
{
    Quaternion rotation = camera.offsetTransform.rotation;//{0,0.38268,0,0.92388};//Rotation à 45°
    rotation = QuaternionInvert(rotation);
    Vector3 dir = { 0,0,-1 };                  //Forward
    return Vector3RotateByQuaternion(dir, rotation);
}

Vector3 Ch_MainCharacter::GetVector(Vector3 dir)
{
    Quaternion rotation = camera.offsetTransform.rotation;//{0,0.38268,0,0.92388};//Rotation à 45°
    //Quaternion rotation = transf.rotation;
    rotation = QuaternionInvert(rotation);
    return Vector3RotateByQuaternion(dir, rotation);
}

void Ch_MainCharacter::Jump()
{
    if (!isGrounded) return;
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