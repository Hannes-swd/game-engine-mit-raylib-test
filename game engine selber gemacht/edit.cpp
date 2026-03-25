#include "anzeigefenster.h"
#include "objeckte.h"
#include "rlImGui.h"
#include <cmath>
#include <string>

void zeichneEditFenster() {
    ImGui::Begin("Edit Fenster");
    ImGui::Separator();

    if (selectedObjectIndex >= 0 && selectedObjectIndex < (int)objeckteListe.size()) {
        Objeckte& aktuellesObjekt = objeckteListe[selectedObjectIndex];
        ImGui::Text("Aktuelles Objekt: %s", aktuellesObjekt.name.c_str());

        static char nameBuffer[256];
        strcpy_s(nameBuffer, aktuellesObjekt.name.c_str());

        if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
            aktuellesObjekt.name = nameBuffer;
        }

        ImGui::DragFloat("Position X", &aktuellesObjekt.PositionX);
        ImGui::DragFloat("Position Y", &aktuellesObjekt.PositionY);
        ImGui::ColorEdit4("Farbe", (float*)&aktuellesObjekt.farbe);
    }
    else {
        ImGui::Text("Kein Objekt ausgewaehlt");
    }

    ImGui::Separator();
    ImGui::End();
}