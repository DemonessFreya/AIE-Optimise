/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <random>
#include <time.h>
#include <vector>
#include "Critter.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Quad.h"
#include "ObjectPool.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "CDDS Optimise Raylib Window");

    //SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    srand(time(NULL));

    TextureManager texManager;
    Texture2D critterTex = texManager.GetTexture("res/10.png");
    Texture2D destroyerTex = texManager.GetTexture("res/9.png");

    // create object pool for critters
    const int POOL_SIZE = 100;
    ObjectPool pool(POOL_SIZE);

    // create some critters
    const int CRITTER_COUNT = 50;
    const int MAX_VELOCITY = 80;

    // define screen boundary for root node in quad tree
    AABB screenBounds(Vector2{ (float)screenWidth / 2.0f, (float)screenHeight / 2.0f }, Vector2{ (float)screenWidth / 2.0f, (float)screenHeight / 2.0f });

    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        //create a random position for the critter to spawn at
        Vector2 position = { (float)(5 + rand() % (screenWidth - 10)), (float)(5 + (rand() % screenHeight - 10)) };
        // create a random direction vector for the velocity
        Vector2 velocity = { -100+(rand()%200), -100+(rand()%200) };
        // normalize and scale by a random speed
        velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);

        // create a critter in a random location
        pool.Spawn(position, velocity, 12.0f, &critterTex);
    }


    Critter destroyer;
    Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
    velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
    destroyer.Init(Vector2{ (float)(screenWidth >> 1), (float)(screenHeight >> 1) }, velocity, 20, &destroyerTex);

    float timer = 1.0f;
    Vector2 nextSpawnPos = destroyer.GetPosition();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float delta = GetFrameTime();

        // update the destroyer
        destroyer.Update(delta);
        // check each critter against screen bounds
        if (destroyer.GetX() < 0) {
            destroyer.SetX(0);
            destroyer.SetVelocity(Vector2{ -destroyer.GetVelocity().x, destroyer.GetVelocity().y });
        }
        if (destroyer.GetX() > screenWidth) {
            destroyer.SetX(screenWidth);
            destroyer.SetVelocity(Vector2{ -destroyer.GetVelocity().x, destroyer.GetVelocity().y });
        }
        if (destroyer.GetY() < 0) {
            destroyer.SetY(0);
            destroyer.SetVelocity(Vector2{ destroyer.GetVelocity().x, -destroyer.GetVelocity().y });
        }
        if (destroyer.GetY() > screenHeight) {
            destroyer.SetY(screenHeight);
            destroyer.SetVelocity(Vector2{ destroyer.GetVelocity().x, -destroyer.GetVelocity().y });
        }

        // update the critters
        // (dirty flags will be cleared during update)
        for (auto& critter : pool.GetPool())
        {
            if (critter.IsDead()) continue;

            critter.Update(delta);

            // check each critter against screen bounds
            if (critter.GetX() < 0) {
                critter.SetX(0);
                critter.SetVelocity(Vector2{ -critter.GetVelocity().x, critter.GetVelocity().y });
            }
            if (critter.GetX() > screenWidth) {
                critter.SetX(screenWidth);
                critter.SetVelocity(Vector2{ -critter.GetVelocity().x, critter.GetVelocity().y });
            }
            if (critter.GetY() < 0) {
                critter.SetY(0);
                critter.SetVelocity(Vector2{ critter.GetVelocity().x, -critter.GetVelocity().y });
            }
            if (critter.GetY() > screenHeight) {
                critter.SetY(screenHeight);
                critter.SetVelocity(Vector2{ critter.GetVelocity().x, -critter.GetVelocity().y });
            }

            // kill any critter touching the destroyer
            // simple circle-to-circle collision check
            float dist = Vector2Distance(critter.GetPosition(), destroyer.GetPosition());
            if (dist < critter.GetRadius() + destroyer.GetRadius())
            {
                critter.Destroy();
                // this would be the perfect time to put the critter into an object pool || done c:
            }
        }

        // instantiate new quad tree for current frame and insert active critters into it
        Quadtree spatialTree(screenBounds);
        for (auto& critter : pool.GetPool()) {
            if (!critter.IsDead()) {
                spatialTree.Insert(&critter);
            }
        }
                
        // check for critter-on-critter collisions
        for (auto& critter : pool.GetPool())
        {
            if (critter.IsDead() || critter.IsDirty()) continue;

            AABB searchArea(critter.GetPosition(), Vector2{ critter.GetRadius() * 2, critter.GetRadius() * 2 });
            std::vector<GameObject*> nearbyObjects;
            spatialTree.Query(searchArea, nearbyObjects);


            for (auto* otherObject : nearbyObjects) {
                Critter* otherCritter = static_cast<Critter*>(otherObject);

                if (&critter == otherCritter || otherCritter->IsDead()) continue;

                float distance = Vector2Distance(critter.GetPosition(), otherCritter->GetPosition());
                if (distance < critter.GetRadius() + otherCritter->GetRadius()) {
                    Vector2 normal = Vector2Normalize(Vector2Subtract(otherCritter->GetPosition(), critter.GetPosition()));

                    critter.SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));
                    critter.SetDirty();

                    if (!otherCritter->IsDirty()) {
                        otherCritter->SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
                        otherCritter->SetDirty();
                    }
                    break;
                }
            }
        }

        timer -= delta;
        if (timer <= 0)
        {
            timer = 1.0f;

            Vector2 normal = Vector2Normalize(destroyer.GetVelocity());
            // get a position behind the destroyer, and far enough away that the critter won't bump into it again
            Vector2 spawnPos = Vector2Add(destroyer.GetPosition(), Vector2Scale(normal, -50));

            pool.Spawn(spawnPos, Vector2Scale(normal, -MAX_VELOCITY), 12.0f, &critterTex);
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // draw quad tree for debug
        spatialTree.Draw();

        // draw the critters using object pool
        for (auto& critter : pool.GetPool())
        {
            if (!critter.IsDead()) {
                critter.Draw();
            }
        }

        // draw the destroyer
        destroyer.Draw();

        DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}