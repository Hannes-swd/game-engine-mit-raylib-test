#include "objeckte.h"
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include <vector>
#include <string>
#include <iostream>

std::vector<Objeckte> objeckteListe;
int selectedObjectIndex = -1;
const char* items[] = { "Rechteck", "Kreis", "Dreieck" };
int selected = 0;

void objecktaddbutton() {
    if (ImGui::BeginCombo("##form_auswahl", items[selected])) {
        for (int i = 0; i < 3; i++) {
            if (ImGui::Selectable(items[i], selected == i)) {
                selected = i;

                if (i == 0)
                    addObjeckt(Rechteck);
                else if (i == 1)
                    addObjeckt(Kreis);
                else if (i == 2)
                    addObjeckt(Dreieck);
            }
        }
        ImGui::EndCombo();
    }
}

void addObjeckt(formen form) {
    Objeckte neuesObjekt;
    neuesObjekt.name = "Objeckt_" + std::to_string(objeckteListe.size() + 1);
    neuesObjekt.form = form;
    neuesObjekt.PositionX = 400;
    neuesObjekt.PositionY = 300;
    neuesObjekt.farbe = { 255, 0, 0, 255 };

    objeckteListe.push_back(neuesObjekt);
}

void zeigeObjeckte() {
    for (size_t i = 0; i < objeckteListe.size(); i++) {
        Objeckte& obj = objeckteListe[i];

        std::string label = obj.name + "| ";

        switch (obj.form) {
        case Rechteck: label += "Rechteck"; break;
        case Kreis: label += "Kreis"; break;
        case Dreieck: label += "Dreieck"; break;
        }

        label += " (X: " + std::to_string((int)obj.PositionX) +
            ", Y: " + std::to_string((int)obj.PositionY) + ")";

        bool isSelected = (selectedObjectIndex == (int)i);

        ImGui::PushID(i);

        // Lösch-Button zuerst (links), damit das Selectable daneben korrekt endet
        if (ImGui::Button("X")) {
            objeckteListe.erase(objeckteListe.begin() + i);
            if (selectedObjectIndex == (int)i) {
                selectedObjectIndex = -1;
            }
            else if (selectedObjectIndex > (int)i) {
                selectedObjectIndex--;
            }
            ImGui::PopID();
            break;
        }

        ImGui::SameLine();

        // Selectable füllt den restlichen Platz in der Zeile
        float selectableWidth = ImGui::GetContentRegionAvail().x;
        if (ImGui::Selectable(label.c_str(), isSelected,
            ImGuiSelectableFlags_AllowDoubleClick, ImVec2(selectableWidth, 0))) {
            if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) && isSelected) {
                selectedObjectIndex = -1;
            }
            else if (!ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left)) {
                selectedObjectIndex = (int)i;
            }
        }

        if (ImGui::BeginDragDropSource()) {
            ImGui::SetDragDropPayload("DND_OBJECT", &i, sizeof(size_t));
            ImGui::Text("Verschiebe: %s", obj.name.c_str());
            ImGui::EndDragDropSource();
        }

        // Drag & Drop Ziel
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_OBJECT")) {
                size_t sourceIndex = *(const size_t*)payload->Data;
                if (sourceIndex != i) {
                    Objeckte temp = objeckteListe[sourceIndex];
                    objeckteListe.erase(objeckteListe.begin() + sourceIndex);

                    size_t targetIndex = i;
                    if (sourceIndex < targetIndex) {
                        targetIndex--;
                    }
                    objeckteListe.insert(objeckteListe.begin() + targetIndex, temp);

                    if (selectedObjectIndex == (int)sourceIndex) {
                        selectedObjectIndex = (int)targetIndex;
                    }
                    else if (selectedObjectIndex > (int)sourceIndex && selectedObjectIndex <= (int)targetIndex) {
                        selectedObjectIndex--;
                    }
                    else if (selectedObjectIndex < (int)sourceIndex && selectedObjectIndex >= (int)targetIndex) {
                        selectedObjectIndex++;
                    }
                }
            }
            ImGui::EndDragDropTarget();
        }

        ImGui::PopID();
        ImGui::Separator();
    }
}

void zeichneObjeckte() {
    //    for (const auto& obj : objeckteListe) {
    //        switch (obj.form) {
    //        case Rechteck:
    //            DrawRectangle(obj.PositionX, obj.PositionY, 50, 50, obj.farbe);
    //            break;
    //        case Kreis:
    //            DrawCircle(obj.PositionX, obj.PositionY, 25, obj.farbe);
    //            break;
    //        case Dreieck:
    //            DrawTriangle(
    //                { obj.PositionX, obj.PositionY - 25 },
    //                { obj.PositionX - 25, obj.PositionY + 25 },
    //                { obj.PositionX + 25, obj.PositionY + 25 },
    //                obj.farbe
    //            );
    //            break;
    //        }
    //    }
    //
    //    // Optional: Ausgewähltes Objekt hervorheben
    //    if (selectedObjectIndex >= 0 && selectedObjectIndex < (int)objeckteListe.size()) {
    //        const auto& obj = objeckteListe[selectedObjectIndex];
    //        switch (obj.form) {
    //        case Rechteck:
    //            DrawRectangleLines(obj.PositionX, obj.PositionY, 50, 50, YELLOW);
    //            break;
    //        case Kreis:
    //            DrawCircleLines(obj.PositionX, obj.PositionY, 25, YELLOW);
    //            break;
    //        case Dreieck:
    //            DrawTriangleLines(
    //                { obj.PositionX, obj.PositionY - 25 },
    //                { obj.PositionX - 25, obj.PositionY + 25 },
    //                { obj.PositionX + 25, obj.PositionY + 25 },
    //                YELLOW
    //            );
    //            break;
    //        }
    //    }
}