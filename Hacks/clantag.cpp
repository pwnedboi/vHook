#include "clantag.h"

void skeet() { // Fuck Skeet
    
    if(!vars.misc.clantag)
        return;
    
    static int Tick = 0;
    Tick++;
    if (Tick > 0 && Tick < 15) {
        SetClanTag("               v", "VLONE.cc");
    }
    else if (Tick > 30 && Tick < 45) {
        SetClanTag("              vl", "VLONE.cc");
    }
    else if (Tick > 60 && Tick < 75) {
        SetClanTag("             vlo", "VLONE.cc");
    }
    else if (Tick > 90 && Tick < 105) {
        SetClanTag("            vlon", "VLONE.cc");
    }
    else if (Tick > 120 && Tick < 135) {
        SetClanTag("           vlone", "VLONE.cc");
    }
    else if (Tick > 150 && Tick < 165) {
        SetClanTag("         vlone.c", "VLONE.cc");
    }
    else if  (Tick > 180 && Tick < 195) {
        SetClanTag("        vlone.cc", "VLONE.cc");
    }
    else if  (Tick > 210 && Tick < 225) {
        SetClanTag("       vlone.cc ", "VLONE.cc");
    }
    else if (Tick > 240 && Tick < 255) {
        SetClanTag("      vlone.cc  ", "VLONE.cc");
    }
    else if (Tick > 270 && Tick < 285) {
        SetClanTag("     vlone.cc   ", "VLONE.cc");
    }
    else if (Tick > 300 && Tick < 315) {
        SetClanTag("    vlone.cc    ", "VLONE.cc");
    }
    else if (Tick > 330 && Tick < 345) {
        SetClanTag("   vlone.cc     ", "VLONE.cc");
    }
    else if (Tick > 360 && Tick < 375) {
        SetClanTag("  vlone.cc      ", "VLONE.cc");
    }
    else if (Tick > 390 && Tick < 405) {
        SetClanTag(" vlone.cc       ", "VLONE.cc");
    }
    else if (Tick > 420 && Tick < 435) {
        SetClanTag("vlone.cc        ", "VLONE.cc");
    }
    else if (Tick > 450 && Tick < 465) {
        SetClanTag("lone.cc         ", "VLONE.cc");
    }
    else if (Tick > 480 && Tick < 495) {
        SetClanTag("one.cc          ", "VLONE.cc");
    }
    else if (Tick > 510 && Tick < 525) {
        SetClanTag("ne.cc           ", "VLONE.cc");
    }
    else if (Tick > 540 && Tick < 555) {
        SetClanTag("e.cc            ", "VLONE.cc");
    }
    else if (Tick > 570 && Tick < 585) {
        SetClanTag(".cc             ", "VLONE.cc");
    }
    else if (Tick > 600 && Tick < 615) {
        SetClanTag("cc              ", "VLONE.cc");
    }
    else if (Tick > 630 && Tick < 645) {
        SetClanTag("c               ", "VLONE.cc");
    }
    else if (Tick > 660 && Tick < 675) {
        SetClanTag("                ", "VLONE.cc");
    }
    
    if (Tick > 675) {
        Tick = 0;
    }
}

auto start = chrono::high_resolution_clock::now();
float TickCounter = 0;

void SetScrollClanTag(string Tag) {
    
    if(!vars.misc.clantag)
        return;
    
    int TagLength = Tag.length();
    string Space;
    
    for (int i = 0; i < TagLength; i++)
        Space += " ";
    
    string SpaceTag = Space + Tag + Space;
    
    if (TickCounter / 1000.0f > TagLength * 2)
        start = chrono::high_resolution_clock::now();
    
    string CurrentSubStr = SpaceTag.substr((int)(TickCounter / 1000.0f), TagLength);
    SetClanTag(CurrentSubStr.c_str(), CurrentSubStr.c_str());
    TickCounter = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count();
}
