#define BASE_ENEMY_SPEED 48.0

typedef struct Enemy {
	Vector2 position;
	Rectangle hitbox;
	float speed_multiplier;
} Enemy;

Enemy enemy;

void init_enemy(Enemy *p_enemy) {	
	p_enemy->position.x = (float) SCREEN_WIDTH;
	p_enemy->position.y = (float) SCREEN_HEIGHT + 48.0;
	p_enemy->speed_multiplier = 0.0;

	p_enemy->hitbox.x = p_enemy->position.x;
	p_enemy->hitbox.y = p_enemy->position.y;
	p_enemy->hitbox.width = 48.0;
	p_enemy->hitbox.height = 48.0;
}

void move_enemy(Enemy *p_enemy, float dt) {
	p_enemy->position.y += BASE_ENEMY_SPEED * p_enemy->speed_multiplier * dt;
	p_enemy->hitbox.x = p_enemy->position.x;
	p_enemy->hitbox.y = p_enemy->position.y;
}

void draw_enemy(Enemy *p_enemy) {
	draw_sprite(1, p_enemy->position);
}

bool enemy_is_offscreen(Enemy *p_enemy) {
	return p_enemy->position.y > SCREEN_HEIGHT;
}

void spawn_enemy(Enemy *p_enemy) {
	int rand_x = rand() % (SCREEN_WIDTH - 47);

	p_enemy->position.x = (float) rand_x;
	p_enemy->position.y = 0.0;

	int rand_multiplier = (rand() % 10) + 1;
	p_enemy->speed_multiplier = (float) rand_multiplier;
}
