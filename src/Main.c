#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Sudoku.h"

Sudoku_Move selection;
Sudoku sudo;

void Setup(AlxWindow* w){
	Random_Set(Time_Nano());

    sudo = Sudoku_New();
	selection = (Sudoku_Move){
		.i = 0U,
		.j = 0U
	};
}

void Update(AlxWindow* w){
    Sudoku_Update(&sudo,w->Strokes,GetMouse());
	
	if(Stroke(ALX_MOUSE_L).PRESSED){
        const Vec2 wm = TransformedView_ScreenWorldPos(&sudo.tv,GetMouse());
		const Sudoku_Move selection_m = Sudoku_ToMove(&sudo,(unsigned int)wm.x,(unsigned int)wm.y);

		if(selection_m.j < SUDOKU_FIELDCOUNT2 && selection_m.i < SUDOKU_FIELDCOUNT2){
			selection = selection_m;
		}
    }
	if(Stroke(ALX_MOUSE_R).PRESSED){
        const Vec2 wm = TransformedView_ScreenWorldPos(&sudo.tv,GetMouse());
		const Sudoku_Move selection_m = Sudoku_ToMove(&sudo,(unsigned int)wm.x,(unsigned int)wm.y);

		if(selection_m.j < SUDOKU_FIELDCOUNT2 && selection_m.i < SUDOKU_FIELDCOUNT2){
			selection = selection_m;
			Sudoku_Remove(&sudo,selection);
		}
    }
	if(Stroke(ALX_KEY_N).PRESSED){
        Sudoku_Reset(&sudo);
    }
	if(Stroke(ALX_KEY_M).PRESSED){
        Sudoku_Solve(&sudo);
    }

	Sudoku_Number entry = SUDOKU_INVALID;
	if(Stroke(ALX_KEY_0).PRESSED) entry = 0U;
	if(Stroke(ALX_KEY_1).PRESSED) entry = 1U;
	if(Stroke(ALX_KEY_2).PRESSED) entry = 2U;
	if(Stroke(ALX_KEY_3).PRESSED) entry = 3U;
	if(Stroke(ALX_KEY_4).PRESSED) entry = 4U;
	if(Stroke(ALX_KEY_5).PRESSED) entry = 5U;
	if(Stroke(ALX_KEY_6).PRESSED) entry = 6U;
	if(Stroke(ALX_KEY_7).PRESSED) entry = 7U;
	if(Stroke(ALX_KEY_8).PRESSED) entry = 8U;
	if(Stroke(ALX_KEY_9).PRESSED) entry = 9U;
	
	if(entry != SUDOKU_INVALID){
        const Sudoku_Number number = sudo.fields[selection.i][selection.j];
		const Sudoku_Number new_number = number * 10U + entry;
		Sudoku_Entry(&sudo,selection,new_number);
    }

    Clear(BLACK);

	Sudoku_Render(&sudo,WINDOW_STD_ARGS);
}
void Delete(AlxWindow* w){
	Sudoku_Free(&sudo);
}

int main(){
	if(Create("Sudoku",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}