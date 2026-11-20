#include <raylib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

#define BABYBLUE (Color){35, 78, 128, 255}
#define num 100
#define DrawPText(text, x, y, size, color) \
    DrawTextEx(PFont, text, (Vector2){x, y}, size, 1, color)

bool ExtractNumber(const char *input, float *result);

void LoadConfig(const char *directory,
                char *info[], float values[])
{
    char path[256];
    snprintf(path, sizeof(path), "%s/chartFile.txt", directory);

    FILE *fp = fopen(path, "r");

    if (fp == NULL) {
        perror("fopen");
        return;
    }

    char buffer[num];

    for (int i = 0; i < 5; i++) {
        info[i][0] = '\0';
        values[i] = 0;
    }

    int i = 0;

    while (i < 5 && fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        snprintf(info[i], num, "%s", buffer);

        ExtractNumber(info[i], &values[i]);

        i++;
    }

    fclose(fp);
}

void SaveConfig(const char *directory,const char *info)
{
        chdir(directory);

    FILE *fp = fopen("chartFile.txt", "a");

    fprintf(fp,
        "%s\n",
        info
    );

    fclose(fp);
}

bool ExtractNumber(const char *input, float *result)
{
    const char *comma = strchr(input, ',');

    if (comma == NULL)
        return false;

    char *end;
    float value = strtof(comma + 1, &end);

    if (end == comma + 1)
        return false;

    while (isspace((unsigned char)*end))
        end++;

    if (*end != '\0')
        return false;

    *result = value;
    return true;
}

void InputText(char *buffer, int max_len)
{
    int key = GetCharPressed();

    while (key > 0) {
        int len = strlen(buffer);

        if (key >= 32 && key <= 125 && len < max_len - 1) {
            buffer[len] = (char)key;
            buffer[len + 1] = '\0';
        }

        key = GetCharPressed();
    }

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
        int len = strlen(buffer);
        if (len > 0) {
            buffer[len - 1] = '\0';
        }
    }
}

int main() {
        char info1[num] = "";
        char info2[num] = "";
        char info3[num] = "";
        char info4[num] = "";
        char info5[num] = "";
        char cellInput[num] = "";

        float num1 = 0;
        float num2 = 0;
        float num3 = 0;
        float num4 = 0;
        float num5 = 0;
        float chartBottom = 900;
        const char *title = "Aronno's Mini Spreadsheet";
        int text_width = MeasureText(title, 40);

        InitWindow(1920, 1080, "Aronno's mini spreadsheet");
        SetTargetFPS(120);
        Texture2D banner = LoadTexture("BlueBanner_1080p.png");
        Font PFont = LoadFont("Crayonsoft-Regular.ttf");

        Rectangle start_button = {800, 450, 320, 100};
        Rectangle chart_button = {450, 450, 320, 100};
        Rectangle spreadsheet_button = {chart_button.x + 350, 450, 320, 100};
        Rectangle back1 = {spreadsheet_button.x + 350, 450, 320, 100};
        Rectangle save = {250, 790, 320, 100};
        Rectangle save_data = {save.x + 350, 790, 320, 100};
        Rectangle back = {save_data.x + 350, 790, 320, 100};
        Rectangle load = {back.x + 350, 790, 320, 100};

        Rectangle res1 = {300, 1000, 240, num1};
        Rectangle res2 = {600, 1000, 240, num2};
        Rectangle res3 = {900, 1000, 240, num3};
        Rectangle res4 = {1200, 1000, 240, num4};
        Rectangle res5 = {1500, 1000, 240, num5};

        Rectangle grid[10][10];

        int i = 0;
        while (i < 10) {
                grid[0][i] = (Rectangle){100 + i * 200, 100, 200, 60};
                i++;
        }
        i = 0;
        while (i < 10) {
                grid[1][i] = (Rectangle){100 + i * 200, grid[0][0].y + 60, 200, 60};
                i++;
        }
        i = 0;
        while (i < 10) {
                grid[2][i] = (Rectangle){100 + i * 200, grid[1][0].y + 60, 200, 60};
                i++;
        }
        i = 0;
        while (i < 10) {
                grid[3][i] = (Rectangle){100 + i * 200, grid[2][0].y + 60, 200, 60};
                i++;
        }
        i = 0;
        while (i < 10) {
                grid[4][i] = (Rectangle){100 + i * 200, grid[3][0].y + 60, 200, 60};
                i++;
        }
        i = 0;
        while(i < 10) {
                grid[5][i] = (Rectangle){100 + i * 200, grid[4][0].y + 60, 200, 60};
                i++;
        }
        i = 0;
        while(i < 10) {
                grid[6][i] = (Rectangle){100 + i * 200, grid[5][0].y + 60, 200, 60};
                i++;
        }
        i = 0;
        while (i < 10) {
                grid[7][i] = (Rectangle){100 + i * 200, grid[6][0].y + 60, 200, 60};
                i++;
        }
        i = 0;
        while (i < 10) {
                grid[8][i] = (Rectangle){100 + i * 200, grid[7][0].y + 60, 200, 60};
                i++;
        }
        i = 0;
        while (i < 10) {
                grid[9][i] = (Rectangle){100 + i * 200, grid[8][0].y + 60, 200, 60};
                i++;
        }
        int selectedRow = -1;
        int selectedCol = -1;

        Rectangle input1 = {520, 320, 700, 50};
        Rectangle input2 = {520, 410, 700, 50};
        Rectangle input3 = {520, 500, 700, 50};
        Rectangle input4 = {520, 590, 700, 50};
        Rectangle input5 = {520, 680, 700, 50};

        bool chart = false;
        bool spreadsheet = false;
        bool start = false;
        bool result_chart = false;
        bool chart_save = false;
        bool _back = false;
        bool _load = false;
        bool edit = false;

        bool int1 = false;
        bool int2 = false;
        bool int3 = false;
        bool int4 = false;
        bool int5 = false;

        while(!WindowShouldClose()) {

                Vector2 mouse = GetMousePosition();

                bool hovering_start = CheckCollisionPointRec(mouse, start_button);
                bool hovering_chart = CheckCollisionPointRec(mouse, chart_button);
                bool hovering_spreadsheet = CheckCollisionPointRec(mouse, spreadsheet_button);
                bool _save = CheckCollisionPointRec(mouse, save);
                bool _data_save_chart = CheckCollisionPointRec(mouse, save_data);
                bool _data_load_chart = CheckCollisionPointRec(mouse, load);
                bool go_back = CheckCollisionPointRec(mouse, back);
                bool go_back_start = CheckCollisionPointRec(mouse, back1);

                bool hovering_cell = false;
                int hoveredRow = -1;
                int hoveredCol = -1;
                i = 0;
                while (i < 10) {
                        if (CheckCollisionPointRec(mouse, grid[0][i])) {
                                hovering_cell = true;
                                hoveredRow = 0;
                                hoveredCol = i;
                        }
                        i++;
                }
                i = 0;
                while (i < 10) {
                        if (CheckCollisionPointRec(mouse, grid[1][i])) {
                                hovering_cell = true;
                                hoveredRow = 1;
                                hoveredCol = i;
                        }
                        i++;
                }
                i = 0;
                while (i < 10) {
                        if (CheckCollisionPointRec(mouse, grid[2][i])) {
                                hovering_cell = true;
                                hoveredRow = 2;
                                hoveredCol = i;
                        }
                        i++;
                }
                i = 0;
                while (i < 10) {
                        if (CheckCollisionPointRec(mouse, grid[3][i])) {
                                hovering_cell = true;
                                hoveredRow = 3;
                                hoveredCol = i;
                        }
                        i++;
                }
                i = 0;
                while (i < 10) {
                        if (CheckCollisionPointRec(mouse, grid[4][i])) {
                                hovering_cell = true;
                                hoveredRow = 4;
                                hoveredCol = i;
                        }
                        i++;
                }
                i = 0;
                while (i < 10) {
                        if (CheckCollisionPointRec(mouse, grid[5][i])) {
                                hovering_cell = true;
                                hoveredRow = 5;
                                hoveredCol = i;
                        }
                        i++;
                }
                i = 0;
                while (i < 10) {
                        if (CheckCollisionPointRec(mouse, grid[6][i])) {
                                hovering_cell = true;
                                hoveredRow = 6;
                                hoveredCol = i;
                        }
                        i++;
                }
                i = 0;
                while (i < 10) {
                        if (CheckCollisionPointRec(mouse, grid[7][i])) {
                                hovering_cell = true;
                                hoveredRow = 7;
                                hoveredCol = i;
                        }
                        i++;
                }
                i = 0;
                while (i < 10) {
                        if (CheckCollisionPointRec(mouse, grid[8][i])) {
                                hovering_cell = true;
                                hoveredRow = 8;
                                hoveredCol = i;
                        }
                        i++;
                }
                i = 0;
                while (i < 10) {
                        if (CheckCollisionPointRec(mouse, grid[9][i])) {
                                hovering_cell = true;
                                hoveredRow = 9;
                                hoveredCol = i;
                        }
                        i++;
                }

                bool hovering_input1 = CheckCollisionPointRec(mouse, input1);
                bool hovering_input2 = CheckCollisionPointRec(mouse, input2);
                bool hovering_input3 = CheckCollisionPointRec(mouse, input3);
                bool hovering_input4 = CheckCollisionPointRec(mouse, input4);
                bool hovering_input5 = CheckCollisionPointRec(mouse, input5);

                bool input_triggered = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsGestureDetected(GESTURE_TAP);

                if (input_triggered) {
                        if (!start && hovering_start) {
                                start = true;
                        }
                        else if(start && go_back_start) {
                                start = false;
                        }
                        else if(start && hovering_chart) {
                                chart = true;
                        }
                        else if(start && hovering_spreadsheet) {
                                spreadsheet = true;
                        }
                        if (spreadsheet && hovering_cell) {
                                edit = true;
                                selectedRow = hoveredRow;
                                selectedCol = hoveredCol;
                                cellInput[0] = '\0';
                        }
                        else if (chart && go_back) {
                                chart = false;
                                _back = true;
                        }
                        else if(chart && _data_save_chart) {
                                ExtractNumber(info1, &num1);
                                ExtractNumber(info2, &num2);
                                ExtractNumber(info3, &num3);
                                ExtractNumber(info4, &num4);
                                ExtractNumber(info5, &num5);

                                SaveConfig("downloads", info1);
                                SaveConfig("downloads", info2);
                                SaveConfig("downloads", info3);
                                SaveConfig("downloads", info4);
                                SaveConfig("downloads", info5);

                                result_chart = true;
                                int1 = int2 = int3 = int4 = int5 = false;
                        }
                        else if (chart && _data_load_chart) {
                                ExtractNumber(info1, &num1);
                                ExtractNumber(info2, &num2);
                                ExtractNumber(info3, &num3);
                                ExtractNumber(info4, &num4);
                                ExtractNumber(info5, &num5);

                                char *info[] = {info1, info2, info3, info4, info5};
                                float values[] = {num1, num2, num3, num4, num5};

                                LoadConfig("downloads", info, values);
                                num1 = values[0];
                                num2 = values[1];
                                num3 = values[2];
                                num4 = values[3];
                                num5 = values[4];

                                res1.height = num1;
                                res1.y = chartBottom - res1.height;
                                res2.height = num2;
                                res2.y = chartBottom - res2.height;
                                res3.height = num3;
                                res3.y = chartBottom - res3.height;
                                res4.height = num4;
                                res4.y = chartBottom - res4.height;
                                res5.height = num5;
                                res5.y = chartBottom - res5.height;

                                result_chart = true;
                                int1 = int2 = int3 = int4 = int5 = false;

                        }
                        else if (chart && _save) {
                                result_chart = true;
                                int1 = int2 = int3 = int4 = int5 = false;
                        }
                        else if (chart) {

                                int1 = int2 = int3 = int4 = int5 = false;

                                if(hovering_input1) {
                                        int1 = true;
                                }
                                else if(hovering_input2) {
                                        int2 = true;
                                }
                                else if(hovering_input3) {
                                        int3 = true;
                                }
                                else if(hovering_input4) {
                                        int4 = true;
                                }
                                else if(hovering_input5) {
                                        int5 = true;
                                }
                        }
                }
                if (spreadsheet && edit) {
                        InputText(cellInput, sizeof(cellInput));
                }
                if (chart) {
                        if(int1) {
                                InputText(info1, num);
                                ExtractNumber(info1, &num1);
                        }
                        else if(int2) {
                                InputText(info2, num);
                                ExtractNumber(info2, &num2);
                        }
                        else if(int3) {
                                InputText(info3, num);
                                ExtractNumber(info3, &num3);
                        }
                        else if(int4) {
                                InputText(info4, num);
                                ExtractNumber(info4, &num4);
                        }
                        else if(int5) {
                                InputText(info5, num);
                                ExtractNumber(info5, &num5);
                        }
                        res1.height = num1;
                        res1.y = chartBottom - res1.height;
                        res2.height = num2;
                        res2.y = chartBottom - res2.height;
                        res3.height = num3;
                        res3.y = chartBottom - res3.height;
                        res4.height = num4;
                        res4.y = chartBottom - res4.height;
                        res5.height = num5;
                        res5.y = chartBottom - res5.height;
                }

                BeginDrawing();
                ClearBackground(RAYWHITE);

                if(!start) {
                        DrawTexture(banner, 0, 0, WHITE);
                        DrawPText(title, 800, 380, 45, BABYBLUE);
                        DrawRectangleRec(start_button, hovering_start ? SKYBLUE : LIGHTGRAY);
                        DrawPText("start", 915, 485, 45, BLACK);
                }
                else if(!chart && !spreadsheet) {
                        DrawPText("choose a mode UwU", chart_button.x + 320, 350, 45, BABYBLUE);
                        DrawRectangleRec(chart_button, hovering_chart ? SKYBLUE : LIGHTGRAY);
                        DrawRectangleRec(spreadsheet_button, hovering_spreadsheet ? SKYBLUE : LIGHTGRAY);
                        DrawRectangleRec(back1, go_back_start ? SKYBLUE : LIGHTGRAY);
                        DrawPText("chart", chart_button.x + 115, 487, 45, BLACK);
                        DrawPText("spreadsheet", spreadsheet_button.x + 60, 487, 45, BLACK);
                        DrawPText("Back", back1.x + 120, back1.y + 35, 45, BLACK);
                }
                else if (spreadsheet) {

                        DrawPText("My Spreadsheet", 200, 150, 40, BABYBLUE);

                        for (int r = 0; r < 10; r++) {
                                for (int c = 0; c < 10; c++) {
                                        DrawRectangleRec(grid[r][c], WHITE);
                                        bool selected = (r == selectedRow && c == selectedCol);
                                        DrawRectangleLinesEx(grid[r][c], selected ? 3.0f : 1.0f, selected ? BABYBLUE : GRAY);
                                        if (selected && edit) {
                                                DrawPText(TextFormat("%s_", cellInput), grid[r][c].x + 8, grid[r][c].y + 15, 22, DARKBLUE);
                                        }
                                }
                        }
                }

                else if (result_chart) {
                        DrawRectangleRec(res1, SKYBLUE);
                        DrawRectangleRec(res2, SKYBLUE);
                        DrawRectangleRec(res3, SKYBLUE);
                        DrawRectangleRec(res4, SKYBLUE);
                        DrawRectangleRec(res5, SKYBLUE);

                        DrawPText(info1, res1.x, res1.y + 30, 30, BABYBLUE);
                        DrawPText(info2, res2.x, res2.y + 30, 30, BABYBLUE);
                        DrawPText(info3, res3.x, res3.y + 30, 30, BABYBLUE);
                        DrawPText(info4, res4.x, res4.y + 30, 30, BABYBLUE);
                        DrawPText(info5, res5.x, res5.y + 30, 30, BABYBLUE);
                }

                else if(chart) {
                        DrawPText("box 1", 520, input1.y - 35, 30, BABYBLUE);
                        DrawRectangleRec(input1, LIGHTGRAY);
                        DrawPText("box 2", 520, input2.y - 35, 30, BABYBLUE);
                        DrawRectangleRec(input2, LIGHTGRAY);
                        DrawPText("box 3", 520, input3.y - 35, 30, BABYBLUE);
                        DrawRectangleRec(input3, LIGHTGRAY);
                        DrawPText("box 4", 520, input4.y - 35, 30, BABYBLUE);
                        DrawRectangleRec(input4, LIGHTGRAY);
                        DrawPText("box 5", 520, input5.y -35, 30, BABYBLUE);
                        DrawRectangleRec(input5, LIGHTGRAY);

                        if (int1) {
                                DrawRectangleLinesEx(input1, 3.0f, BLUE);
                        }
                        else {
                                DrawRectangleLinesEx(input1, 1.0f, GRAY);
                        }
                        if (int2) {
                                DrawRectangleLinesEx(input2, 3.0f, BLUE);
                        }
                        else {
                                DrawRectangleLinesEx(input2, 1.0f, GRAY);
                        }
                        if (int3) {
                                DrawRectangleLinesEx(input3, 3.0f, BLUE);
                        }
                        else {
                                DrawRectangleLinesEx(input3, 1.0f, GRAY);
                        }
                        if (int4) {
                                DrawRectangleLinesEx(input4, 3.0f, BLUE);
                        }
                        else {
                                DrawRectangleLinesEx(input4, 1.0f, GRAY);
                        }
                        if (int5) {
                                DrawRectangleLinesEx(input5, 3.0f, BLUE);
                        }
                        else {
                                DrawRectangleLinesEx(input5, 1.0f, GRAY);
                        }
                        DrawPText(info1, input1.x + 12, input1.y + 10, 30, DARKBLUE);
                        DrawPText(info2, input2.x + 12, input2.y + 10, 30, DARKBLUE);
                        DrawPText(info3, input3.x + 12, input3.y + 10, 30, DARKBLUE);
                        DrawPText(info4, input4.x + 12, input4.y + 10, 30, DARKBLUE);
                        DrawPText(info5, input5.x + 12, input5.y + 10, 30, DARKBLUE);

                        DrawRectangleRec(load, _data_load_chart ? SKYBLUE : LIGHTGRAY);
                        DrawPText("load", load.x + 120, load.y + 35, 40, DARKBLUE);

                        DrawRectangleRec(back, go_back ? SKYBLUE : LIGHTGRAY);
                        DrawPText("Back", back.x + 120, back.y + 35, 40, DARKBLUE);

                        DrawRectangleRec(save_data, _data_save_chart ? SKYBLUE : LIGHTGRAY);
                        DrawPText("Save", save_data.x + 120, save_data.y + 35, 40, DARKBLUE);

                        DrawRectangleRec(save, _save ? SKYBLUE : LIGHTGRAY);
                        DrawPText("Display", save.x + 120, save.y + 35, 40, DARKBLUE);
                }
                EndDrawing();
        }
        UnloadTexture(banner);
        CloseWindow();
        return 0;
}
