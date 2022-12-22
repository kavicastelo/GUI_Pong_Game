#define is_down(b) input-> buttons[b].is_down
#define pressed(b) (input-> buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input-> buttons[b].is_down && input->buttons[b].changed)

float player_pos_x = 0.f;
float player_pos_y = 0.f;

static void simulate_game(Input* input) {
	clear_screen(0xff5500);
	if (pressed(BUTTON_UP)) player_pos_y += 1.f;
	if (pressed(BUTTON_DOWN)) player_pos_y -= 1.f;
	if (pressed(BUTTON_RIGHT)) player_pos_x += 1.f;
	if (pressed(BUTTON_LEFT)) player_pos_x -= 1.f;
		draw_rectangle(player_pos_x, player_pos_y, 5, 2, 0x00ff00);
	draw_rectangle(.2, .8, .3, .5, 0xff0000);
	draw_rectangle(1, 2, .5, 1, 0xff0000);
	draw_rectangle(0, 0, .2, .2, 0xff0000);
}