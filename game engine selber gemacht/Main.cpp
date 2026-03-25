#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include <vector>
#include <string>
#include "objeckte.h"
#include "anzeigefenster.h"
#include "edit.h"

int main()
{
    // Raylib initialisieren
    InitWindow(1280, 800, "Game engine");
    SetTargetFPS(144);

    // rlImGui initialisieren
    rlImGuiSetup(true);

    // Hauptschleife
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Zeichne alle Objekte im Raylib-Fenster
        zeichneObjeckte();

        // ImGui beginnen
        rlImGuiBegin();

        ImGui::Begin("Objekt Liste");

        objecktaddbutton();

        ImGui::Separator();
        ImGui::Text("Vorhandene Objekte: %zu", objeckteListe.size());
        ImGui::Separator();

        zeigeObjeckte();

        ImGui::End();

        zeigeAnzeigeFenster();
        zeichneEditFenster();
        // ImGui beenden
        rlImGuiEnd();
        EndDrawing();
    }

    // Aufräumen
    rlImGuiShutdown();
    CloseWindow();

    return 0;
}