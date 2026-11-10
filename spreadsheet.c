#include <raylib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define BABYBLUE (Color){35, 78, 128, 255}
#define num 100

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
        float num1 = 0;
        float num2 = 0;
        float num3 = 0;
        float num4 = 0;
        float num5 = 0;
        float chartBottom = 900;
        const char *title = "Aronno's Mini Spreadsheet";
        int text_width = MeasureText(title, 30);

        InitWindow(1920, 1080, "Aronno's mini spreadsheet");
        SetTargetFPS(120);
        Texture2D banner = LoadTexture("BlueBanner_1080p.png");

        Rectangle start_button = {800, 450, 320, 100};
        Rectangle chart_button = {600, 450, 320, 100};
        Rectangle spreadsheet_button = {1000, 450, 320, 100};
        Rectangle save = {800, 790, 320, 100 };

        Rectangle res1 = {300, 1000, 300, num1};
        Rectangle res2 = {600, 1000, 300, num2};
        Rectangle res3 = {900, 1000, 300, num3};
        Rectangle res4 = {1200, 1000, 300, num4};
        Rectangle res5 = {1500, 1000, 300, num5};

        Rectangle input1 = {520, 320, 700, 50};
        Rectangle input2 = {520, 410, 700, 50};
        Rectangle input3 = {520, 500, 700, 50};
        Rectangle input4 = {520, 590, 700, 50};
        Rectangle input5 = {520, 680, 700, 50};

        bool chart = false;
        bool spreadsheet = false;
        bool start = false;
        bool result_chart = false;
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
                        else if(start && hovering_chart) {
                                chart = true;
                        }
                        else if(start && hovering_spreadsheet) {
                                spreadsheet = true;
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
                        DrawText(title, 800, 380, 37, BABYBLUE);
                        DrawRectangleRec(start_button, hovering_start ? SKYBLUE : LIGHTGRAY);
                        DrawText("start", 915, 485, 35, BLACK);
                }
                else if(!chart && !spreadsheet) {
                        DrawText("choose a mode UwU", 850, 350, 35, BABYBLUE);
                        DrawRectangleRec(chart_button, hovering_chart ? SKYBLUE : LIGHTGRAY);
                        DrawRectangleRec(spreadsheet_button, hovering_spreadsheet ? SKYBLUE : LIGHTGRAY);
                        DrawText("chart", 715, 487, 35, BLACK);
                        DrawText("spreadsheet", 1060, 487, 35, BLACK);
                }

                else if (result_chart) {
                        DrawRectangleRec(res1, SKYBLUE);
                        DrawRectangleRec(res2, SKYBLUE);
                        DrawRectangleRec(res3, SKYBLUE);
                        DrawRectangleRec(res4, SKYBLUE);
                        DrawRectangleRec(res5, SKYBLUE);

                        DrawText(info1, res1.x, res1.y + 30, 25, BABYBLUE);
                        DrawText(info2, res2.x, res2.y + 30, 25, BABYBLUE);
                        DrawText(info3, res3.x, res3.y + 30, 25, BABYBLUE);
                        DrawText(info4, res4.x, res4.y + 30, 25, BABYBLUE);
                        DrawText(info5, res5.x, res5.y + 30, 25, BABYBLUE);
                }

                else if(chart) {
                        DrawText("box 1", 520, input1.y - 35, 25, BABYBLUE);
                        DrawRectangleRec(input1, LIGHTGRAY);
                        DrawText("box 2", 520, input2.y - 35, 25, BABYBLUE);
                        DrawRectangleRec(input2, LIGHTGRAY);
                        DrawText("box 3", 520, input3.y - 35, 25, BABYBLUE);
                        DrawRectangleRec(input3, LIGHTGRAY);
                        DrawText("box 4", 520, input4.y - 35, 25, BABYBLUE);
                        DrawRectangleRec(input4, LIGHTGRAY);
                        DrawText("box 5", 520, input5.y -35, 25, BABYBLUE);
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
                        DrawText(info1, input1.x + 12, input1.y + 10, 30, DARKBLUE);
                        DrawText(info2, input2.x + 12, input2.y + 10, 30, DARKBLUE);
                        DrawText(info3, input3.x + 12, input3.y + 10, 30, DARKBLUE);
                        DrawText(info4, input4.x + 12, input4.y + 10, 30, DARKBLUE);
                        DrawText(info5, input5.x + 12, input5.y + 10, 30, DARKBLUE);
                        DrawRectangleRec(save, _save ? SKYBLUE : LIGHTGRAY);
                        DrawText("Display", 920, save.y + 35, 35, DARKBLUE);
                }
                EndDrawing();
        }
        UnloadTexture(banner);
        return 0;
}
