static Texture master;

void load_master_texture(void);
void unload_master_texture(void);

void draw_sprite(int index, Vector2 position);

/* -- LINE BREAK -- */

void load_master_texture(void) {
	master = LoadTexture("assets/dodger_master.png");
}

void unload_master_texture(void) {
	UnloadTexture(master);
}

void draw_sprite(int index, Vector2 position) {
	Rectangle rect = {
		index * 48.0,
		0.0,
		48.0,
		48.0
	};

	DrawTextureRec(master, rect, position, WHITE);
}
