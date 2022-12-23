#define is_down(b) input-> buttons[b].is_down
#define pressed(b) (input-> buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input-> buttons[b].is_down && input->buttons[b].changed)

float player_pos_x = 0.f;
float player_pos_y = 0.f;

float player_1_p, player_1_dp, player_2_p, player_2_dp;
float arena_half_size_x = 45, arena_half_size_y = 20;
float player_half_size_x = 1.5, player_half_size_y = 5;

static void simulate_game(Input* input, float time) {
	clear_screen(0xff5500);

	draw_rectangle(0, 0, arena_half_size_x, arena_half_size_y, 0xf1c40f);

	//if (pressed(BUTTON_UP)) player_pos_y += speed;
	//if (pressed(BUTTON_DOWN)) player_pos_y -= speed;
	//if (pressed(BUTTON_RIGHT)) player_pos_x += player_1_ddp;
	//if (pressed(BUTTON_LEFT)) player_pos_x -= player_1_ddp;

	float player_1_ddp = 0.f;
	if (is_down(BUTTON_UP)) player_1_ddp += 2000;
	if (is_down(BUTTON_DOWN)) player_1_ddp -= 2000;

	float player_2_ddp = 0.f;
	if (is_down(BUTTON_W)) player_2_ddp += 2000;
	if (is_down(BUTTON_S)) player_2_ddp -= 2000;

	player_1_ddp -= player_1_dp * 10.f;

	player_1_p = player_1_p + player_1_dp * time + player_1_ddp * time * time * .5f;
	player_1_dp = player_1_dp + player_1_ddp * time;

	if (player_1_p + player_half_size_y > arena_half_size_y) {
		player_1_p = arena_half_size_y - player_half_size_y;
		player_1_dp = 0;
	}
	else if (player_1_p - player_half_size_y < -arena_half_size_y) {
		player_1_p = -arena_half_size_y + player_half_size_y;
		player_1_dp = 0;
	}

	player_2_ddp -= player_2_dp * 10.f;

	player_2_p = player_2_p + player_2_dp * time + player_2_ddp * time * time * .5f;
	player_2_dp = player_2_dp + player_2_ddp * time;

	if (player_2_p + player_half_size_y > arena_half_size_y) {
		player_2_p = arena_half_size_y - player_half_size_y;
		player_2_dp = 0;
	}
	else if (player_2_p - player_half_size_y < -arena_half_size_y) {
		player_2_p = -arena_half_size_y + player_half_size_y;
		player_2_dp = 0;
	}

	draw_rectangle(0, 0, 1, 1, 0xffffff);
	draw_rectangle(40, player_1_p, player_half_size_x, player_half_size_y, 0xff0000);
	draw_rectangle(-40, player_2_p, 1.5, 5, 0xff0000);
}