#include <raylib.h>
#include "tree.h"
#include "rules_setup.h"

int main() 
{    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    Tree tree(
        {400, 550},
        80.0f,
        -90.0f,
        0,
        Symbol::Leaf,
        nullptr
    );

    RuleSet rules = CreateTreeRules();
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    float timer = 0.0f;
    
    while (!WindowShouldClose())
    {        
        float dt = GetFrameTime(); // seconds since last frame
        timer += dt;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse = GetMousePosition();
            float bestDist = 20.0f; // click radius
            Tree* nearest = tree.FindNearest(mouse, bestDist);
            if (nearest)
            {
                nearest->PruneSelf();
            }
        }

        if (timer >= 1.0f)
        {
            std::vector<Tree*> candidates;
            tree.collectGrowable(candidates);

            if (!candidates.empty())
            {
                int i = GetRandomValue(0, candidates.size() - 1);
                rules.Apply(*candidates[i]);
            }
            timer -= 1.0f;   // keep leftover time
        }
        BeginDrawing();
        ClearBackground({230, 200, 160, 255});

        tree.Draw();

        EndDrawing();
    }
    
    CloseWindow();
}