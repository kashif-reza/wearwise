#include "WearWiseSystem.h"
#include <iostream>
#include <limits>
using namespace std;

void WearWiseSystem::generateAIPrompt() {
    cout << "\n======================================================================\n";
    cout << "                 AI VIRTUAL TRY-ON PROMPT GENERATOR                   \n";
    cout << "======================================================================\n";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string top, bottom, footwear, accessories, setting, pose, extra;
    cout << "Top garment (or 0 to cancel): ";
    getline(cin, top);
    if (top == "0") return;

    cout << "Bottom garment: ";
    getline(cin, bottom);
    cout << "Footwear: ";
    getline(cin, footwear);
    cout << "Accessories (optional): ";
    getline(cin, accessories);
    cout << "Background / setting: ";
    getline(cin, setting);
    cout << "Pose or camera angle (optional): ";
    getline(cin, pose);
    cout << "Any extra details (optional): ";
    getline(cin, extra);

    if (top.empty() || bottom.empty() || footwear.empty() || setting.empty()) {
        cout << "Top, bottom, footwear, and setting are required. No prompt generated.\n";
        return;
    }

    cout << "\n======================= YOUR TRY-ON PROMPT ===========================\n";
    cout << "Create a photorealistic, full-body fashion virtual try-on image of a "
         << user.targetGroup << " person, approximately " << user.heightCm
         << " cm tall, with a " << user.preferredFit << " fit preference. "
         << "Preserve realistic human anatomy, natural body proportions, and believable garment sizing.\n";
    cout << "OUTFIT: wearing " << top << " with " << bottom << ", paired with " << footwear << ".";
    if (!accessories.empty()) cout << " Accessories: " << accessories << ".";
    cout << "\nSTYLE: " << user.primaryStyle << "; preferred colours " << user.favoriteColor1
         << " and " << user.favoriteColor2 << "; avoid " << user.avoidedColor << " where possible.\n";
    cout << "SETTING: " << setting << ".\n";
    if (!pose.empty()) cout << "POSE / CAMERA: " << pose << ".\n";
    if (!extra.empty()) cout << "ADDITIONAL DETAILS: " << extra << ".\n";
    cout << "QUALITY: realistic fabric texture, accurate folds and fit, natural lighting, balanced colours, "
         << "sharp details, editorial fashion photography. Keep the complete outfit visible head to toe.\n";
    cout << "======================================================================\n";
    cout << "Copy this prompt into an external image-generation or virtual try-on tool.\n";
    cout << "WearWise creates the prompt; the external tool creates the image.\n";
    cout << "Press Enter to return...";
    cin.get();
}
