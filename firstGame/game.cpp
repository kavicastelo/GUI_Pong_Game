#define is_down(b) input-> buttons[b].is_down
#define pressed(b) (input-> buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input-> buttons[b].is_down && input->buttons[b].changed)

float player_pos_x = 0.f;
float player_pos_y = 0.f;

float player_1_p, player_1_dp, player_2_p, player_2_dp;
float arena_half_size_x = 45, arena_half_size_y = 20;
float player_half_size_x = 1.5, player_half_size_y = 5;
float ball_p_x, ball_p_y, ball_dp_x = 70, ball_dp_y, ball_half_size = .5f;

int player_1_score, player_2_score;

static void simulate_player(float *p, float *dp, float ddp, float time) {
	ddp -= *dp * 10.f;

	*p = *p + *dp * time + ddp * time * time * .5f;
	*dp = *dp + ddp * time; 

	if (*p + player_half_size_y > arena_half_size_y) {
		*p = arena_half_size_y - player_half_size_y;
		*dp = 0;
	}
	else if (*p - player_half_size_y < -arena_half_size_y) {
		*p = -arena_half_size_y + player_half_size_y;
		dp = 0;
	}
}

enum  game_mode
{
	GM_Meny,
	GM_Play,
};

game_mode current_game_mode;

int hot_button;
bool enemy_is_ai;

static void simulate_game(Input* input, float time) {
	clear_screen(0xff5500);

	draw_rectangle(0, 0, arena_half_size_x, arena_half_size_y, 0xf1c40f); // main background

	if (current_game_mode == GM_Play) {

		float player_1_ddp = 0.f;
		if (is_down(BUTTON_UP)) player_1_ddp += 1000;
		if (is_down(BUTTON_DOWN)) player_1_ddp -= 1000;


		float player_2_ddp = 0.f;
		if (!enemy_is_ai) {
			if (is_down(BUTTON_W)) player_2_ddp += 1000;
			if (is_down(BUTTON_S)) player_2_ddp -= 1000;
		}
		else {
			//if (ball_p_y > player_2_p + 2.f) player_2_ddp += 650;
			//if (ball_p_y < player_2_p - 2.f) player_2_ddp -= 650;
			player_2_ddp = (ball_p_y - player_2_p) * 100;
			if (player_2_ddp > 650) player_2_ddp = 650;
			if (player_2_ddp < -650) player_2_ddp = -650;
		}

		simulate_player(&player_1_p, &player_1_dp, player_1_ddp, time);
		simulate_player(&player_2_p, &player_2_dp, player_2_ddp, time);

		// ball simulate

		ball_p_x += ball_dp_x * time;
		ball_p_y += ball_dp_y * time;

		if (ball_p_x + ball_half_size > 40 - player_half_size_x &&
			ball_p_x - ball_half_size < 40 + player_half_size_x &&
			ball_p_y + ball_half_size > player_1_p - player_half_size_y &&
			ball_p_y + ball_half_size < player_1_p + player_half_size_y) {

			ball_p_x = 40 - player_half_size_x - ball_half_size;
			ball_dp_x *= -1;
			ball_dp_y = (ball_p_y - player_1_p) * 2 + player_1_dp * .75f;
		}
		else if (ball_p_x + ball_half_size > -40 - player_half_size_x &&
			ball_p_x - ball_half_size < -40 + player_half_size_x &&
			ball_p_y + ball_half_size > player_2_p - player_half_size_y &&
			ball_p_y + ball_half_size < player_2_p + player_half_size_y) {

			ball_p_x = -40 + player_half_size_x + ball_half_size;
			ball_dp_x *= -1;
			ball_dp_y = (ball_p_y - player_2_p) * 2 + player_1_dp * .75f;
		}

		if (ball_p_y + ball_half_size > arena_half_size_y) {
			ball_p_y = arena_half_size_y - ball_half_size;
			ball_dp_y *= -1;
		}
		else if (ball_p_y + ball_half_size < -arena_half_size_y) {
			ball_p_y = -arena_half_size_y + ball_half_size;
			ball_dp_y *= -1;
		}

		if (ball_p_x + ball_half_size > arena_half_size_x) {
			ball_dp_x *= -1;
			ball_dp_y = 0;
			ball_p_x = 0;
			ball_p_y = 0;
			player_1_score++;
		}
		else if (ball_p_x - ball_half_size < -arena_half_size_x) {
			ball_dp_x *= -1;
			ball_dp_y = 0;
			ball_p_x = 0;
			ball_p_y = 0;
			player_2_score++;
		}

		draw_number(player_1_score, -10, 22, .5f, 0xaabbff);
		draw_number(player_2_score, 10, 22, .5f, 0xaabbff);


		draw_rectangle(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 0xffffff); // ball
		draw_rectangle(40, player_1_p, player_half_size_x, player_half_size_y, 0xff0000); // playerPads
		draw_rectangle(-40, player_2_p, 1.5, 5, 0xff0000); // container

	}
	else {
		if (pressed(BUTTON_LEFT) || pressed(BUTTON_RIGHT)) {
			hot_button = !hot_button;
		}

		if (pressed(BUTTON_ENTER)) {
			current_game_mode = GM_Play;
			enemy_is_ai = hot_button ? 0 : 1;
		}

		draw_text(0,0,.5f,0xff3456);

		if (hot_button == 0) {
			draw_rectangle(-20, 0, 10, 10, 0xff0000);
			draw_rectangle(20, 0, 10, 10, 0xcccccc);
		}
		else {
			draw_rectangle(-20, 0, 10, 10, 0xcccccc);
			draw_rectangle(20, 0, 10, 10, 0xff0000);
		}
		
	}
}