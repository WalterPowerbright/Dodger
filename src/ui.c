void draw_title(void) {
	DrawText("DODGER", 24, 144, 64, NOKIA_LIGHT);
	DrawText("<- : Move Left", 24, 240, 24, NOKIA_LIGHT);
	DrawText("-> : Move Right", 24, 272, 24, NOKIA_LIGHT);
	DrawText("Move to Start", 24, 328, 32, NOKIA_LIGHT);
}

void draw_score(int score) {
	DrawRectangle(0, 0, SCREEN_WIDTH, 48, NOKIA_LIGHT);

	const char *display_text = TextFormat("%d", score);
	DrawText(display_text, 16, 2, 48, NOKIA_DARK);
}

void draw_end_screen(int score) {
	DrawText("GAME OVER", 24, 192, 48, NOKIA_LIGHT);

	const char *display_text = TextFormat("You survived for\n%d seconds", score);
	DrawText(display_text, 24, 272, 32, NOKIA_LIGHT);
	DrawText("Press <- or -> to Reset", 24, 368, 32, NOKIA_LIGHT);
}


