#include "Player.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"

Player::Player() : j2Entity(ENTITY_TYPE::PLAYER)
{
}

Player::~Player()
{
}

bool Player::Start()
{
	entity_rect = { 13,4,32,57 };
	entity_tex = App->tex->Load("textures/entities_sprites.png");

	return true;
}

bool Player::Update(float dt, bool do_logic)
{
	iPoint last_pos = position;

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		position.y -= 5;

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		position.y += 5;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		position.x -= 5;

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		position.x += 5;

	App->render->FollowPlayer(position.x - last_pos.x, position.y - last_pos.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
	{
		App->render->camera.x = -position.x + (App->win->width / 2);
		App->render->camera.y = -position.y + (App->win->height / 2);
	}
	return true;
}

bool Player::CleanUp()
{
	App->tex->UnLoad(entity_tex);
	return true;
}

void Player::Draw()
{
	App->render->Blit(entity_tex, position.x - 16, position.y -64, &entity_rect);
}
