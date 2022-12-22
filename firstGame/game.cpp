#define is_down(b) input-> buttons[b].is_down
#define pressed(b) (input-> buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input-> buttons[b].is_down && input->buttons[b].changed)

float player_pos_x = 0.f;
float player_pos_y = 0.f;

static void simulate_game(Input* input, float time) {
	clear_screen(0xff5500);

	float speed = 50.f; // units per seconds
	if (is_down(BUTTON_UP)) player_pos_y += speed * time;
	if (is_down(BUTTON_DOWN)) player_pos_y -= speed * time;
	if (is_down(BUTTON_RIGHT)) player_pos_x += speed * time;
	if (is_down(BUTTON_LEFT)) player_pos_x -= speed * time;
		draw_rectangle(player_pos_x, player_pos_y, 5, 2, 0x00ff00);
	draw_rectangle(.2, .8, .3, .5, 0xff0000);
	draw_rectangle(1, 2, .5, 1, 0xff0000);
	draw_rectangle(0, 0, .2, .2, 0xff0000);
}