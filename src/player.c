typedef struct Player {
	Vector2 position;
	Rectangle hitbox;
} Player;
Player player;

void init_player(void) {
	player.position.x = (SCREEN_WIDTH / 2.0) - 24.0;
	player.position.y = SCREEN_HEIGHT - 96.0;

	player.hitbox.x = player.position.x;
	player.hitbox.y = player.position.y;
	player.hitbox.width = 48.0;
	player.hitbox.height = 48.0;
}

void move_player(int move_direction, float dt) {
	player.position.x += (float) move_direction * (7.5 * 48.0 * dt);
	if ( player.position.x <= 0.0 )
		player.position.x = 0.0;
	else if ( player.position.x >= SCREEN_WIDTH - 48.0 )
		player.position.x = SCREEN_WIDTH - 48.0;

	player.hitbox.x = player.position.x;
	player.hitbox.y = player.position.y;
}

void draw_player(void) {
	draw_sprite(0, player.position);
}
