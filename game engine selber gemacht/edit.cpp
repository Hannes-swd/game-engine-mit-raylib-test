#include "anzeigefenster.h"
#include "objeckte.h"
#include "rlImGui.h"
#include <cmath>
#include <string>
void zeichneEditFenster() {
	ImGui::Begin("Edit Fenster");
	ImGui::Separator();
	std::string offenesObjeckt = "akktuelles objecktnahme";
	ImGui::Text(offenesObjeckt);
	ImGui::Separator();
	ImGui::End();
}