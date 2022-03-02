#pragma once
#include "Color.h"
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <filesystem>
#include "Error.h"

using namespace std;
enum Mode { REGULAR, SAVE, LOAD, SILENT };

void gotoxy(short x, short y);
void setTextColor(Color);
void hideCursor();
void readFiles(std::vector<string>& screenFiles);
bool hasEnding(string fullString, string  ending);
