#pragma once
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include <vector>
#include <string>

enum formen {
    Rechteck,
    Kreis,
    Dreieck,
};

struct Objeckte {
    std::string name;
    formen form;
    float PositionX;
    float PositionY;
    Color farbe;
};

extern std::vector<Objeckte> objeckteListe;
extern int selectedObjectIndex;
extern const char* items[];
extern int selected;

void objecktaddbutton();
void addObjeckt(formen form);
void zeigeObjeckte();
void zeichneObjeckte();