#include <raylib.h>
#include <string.h>
#define num 100

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

    if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE>
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

	InitWindow(1920, 1080, "Aronno's mini spreadsheet");
	TargetFPS(120);

	Rectangle start_button = {800, 450, 320, 100};
	Rectangle chart_button = {600, 450, 320, 100};
	Rectangle spreadsheet_button = {1000, 450, 320, 100};

	Rectangle res1 = {800, 1000, 300, num1};
	Rectangle res2 = {900, 1000, 300, num2};
	Rectangle res3 = {1000, 1000, 300, num3};
	Rectangle res4 = {1100, 1000, 300, num4};
	Rectangle res5 = {1200, 1000, 300, num5};

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

		bool hovering_input1 = CheckCollisionPointRec(mouse, input1);
		bool hovering_input2 = CheckCollisionPointRec(mouse, input2);
		bool hovering_input3 = CheckCollisionPointRec(mouse, input3);
		bool hovering_input4 = CheckCollisionPointRec(mouse, input4);
		bool hovering_input5 = CheckCollisionPointRec(mouse, input5);

		bool input_triggered = IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsGestureDetected(GESTURE_TAP);
d
		if (input_triggered) {
			if (!start && hovering_start) {
				start = true;
			}
			if(start && hovering_chart) {
				chart = true;
			}
			if(start && hovering_spreadsheet) {
				spreadsheet = true;
			}
			else if (chart) {
				if(hovering_input1) {
					int1 = true;
				}
				if(hovering_input1) {
					int2 = true;
				}
				if(hovering
