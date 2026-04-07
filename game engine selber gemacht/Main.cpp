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
    int screenWidth = 800;
    int screenHeight = 450;

    // Raylib initialisieren MIT RESIZE-FLAG
    InitWindow(screenWidth, screenHeight, "TrainBuilder");
    SetWindowState(FLAG_WINDOW_RESIZABLE);  // <-- Wichtig: Fenster resizebar machen
    SetTargetFPS(144);

    // rlImGui initialisieren
    rlImGuiSetup(true);

    // Hauptschleife
    while (!WindowShouldClose())
    {
        SetExitKey(KEY_NULL);

        // Aktuelle Fenstergröße abrufen (falls vom Benutzer geändert)
        int currentWidth = GetScreenWidth();
        int currentHeight = GetScreenHeight();

        // Optional: Wenn Sie die Variablen für andere Zwecke brauchen
        if (currentWidth != screenWidth || currentHeight != screenHeight) {
            screenWidth = currentWidth;
            screenHeight = currentHeight;
            // Hier könnten Sie auf Größenänderung reagieren, z.B.:
            // rlImGuiUpdateViewport();
        }

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