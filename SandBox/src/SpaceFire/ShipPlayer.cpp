#include "pch.h"
#include "ShipPlayer.h"
#include "Core/ViewPort.h"
#include "Bullet.h"
#include "Core/Timer.h"
#include "Ammo.h"

void ShipPlayer::ShipMovement()
{
	if(speed.x > 0)
		speed.x -= acceleration * accelerationDecrease;
	else if(speed.x < 0)
		speed.x += acceleration * accelerationDecrease;

	if (speed.y > 0)
		speed.y -= acceleration * accelerationDecrease;
	else if (speed.y < 0)
		speed.y += acceleration * accelerationDecrease;

	if (abs(speed.x) < 0.0001)
		speed.x = 0;
	if (abs(speed.y) < 0.0001)
		speed.y = 0;

	if (Input::IsKeyDown(Keycode::KEY_W)) {
		if(speed.y < MaxSpeed)
			speed.y += acceleration;
	}
	if (Input::IsKeyDown(Keycode::KEY_S)) {
		if (speed.y > -MaxSpeed)
			speed.y += -acceleration;
	}
	if (Input::IsKeyDown(Keycode::KEY_D)) {
		if (speed.x < MaxSpeed)
			speed.x += acceleration;
	}
	if (Input::IsKeyDown(Keycode::KEY_A)) {
		if (speed.x > -MaxSpeed)
			speed.x += -acceleration;
	}

	tr->Move(speed.x, speed.y, speed.z);
	dir = glm::vec3(ViewPort::GetInstance()->GetMousePositionToWorldSpace(), 0);
	dir.x -= GetPosition().x;
	dir.y -= GetPosition().y;
	
	tr->RotateOnce(dir, glm::vec3(0, 0, 1));
}

void ShipPlayer::ScreenBorders()
{
	double xBorder = (Window::GetCamera().GetAspectRatio() * Window::GetCamera().GetZoomLevel());
	if (GetPosition().x > xBorder - sr->GetWidth() * 0.5) {
		tr->Translate(xBorder - sr->GetWidth() * 0.5, GetPosition().y);
	}
	else if (GetPosition().x < -xBorder + sr->GetWidth() * 0.5) {
		tr->Translate(-xBorder + sr->GetWidth() * 0.5, GetPosition().y);
	}

	double yBorder = (1 * Window::GetCamera().GetZoomLevel());
	if (GetPosition().y > yBorder - sr->GetHeight() * 0.5) {
		tr->Translate(GetPosition().x, yBorder - sr->GetHeight() * 0.5);
	}
	else if (GetPosition().y < -yBorder + sr->GetHeight() * 0.5) {
		tr->Translate(GetPosition().x,-yBorder + sr->GetHeight() * 0.5);
	}
}

ShipPlayer::ShipPlayer(std::string name, float x, float y) : GameObject(name,x,y)
{
	SoundManager::CreateSoundAsset("fire", fireSound);
	bulletsPlaceHolder = new GameObject("bulletsPlaceHolder", 0, 0);
	bulletsPlaceHolder->m_Enable = false;
	AddChild((void*)bulletsPlaceHolder);
	EventSystem::GetInstance()->RegisterClient(EventType::ONUPDATE, (GameObject*)this);
	EventSystem::GetInstance()->RegisterClient(EventType::ONSTART, (GameObject*)this);
	EventSystem::GetInstance()->RegisterClient(EventType::ONCOLLSION, (GameObject*)this);
	col = GetComponentManager()->AddComponent<RectangleCollider2D>();
	tr = GetComponentManager()->GetComponent<Transform>();
	sr = GetComponentManager()->AddComponent<SpriteRenderer>();;
	tr->Scale(5, 5);
	sr->m_Texture = (texture);
	col->GetOwnerOfComponent()->m_Tag = ("Player");
	col->m_IsTrigger = true;
	for (unsigned int i = 0; i < amountOfBulletsInPool; i++)
	{
		bullets.push_back(new Bullet("Bullet",dir,"Bullet" + std::to_string(i), GetPosition().x, GetPosition().y));
		bullets[i]->isActive = false;
		bulletsPlaceHolder->AddChild((void*)bullets[i]);
		bullets[i]->m_Enable = false;
		bullets[i]->col->m_Enable = false;
		bullets[i]->damage = 15.f;
	}
}

void ShipPlayer::Death()
{
	m_Enable = false;
	col->m_Enable = false;
	isDead = true;
}

void ShipPlayer::Respawn()
{
	timerFire = 0;
	ammo = 100;
	hp = 100;
	m_Enable = true;
	col->m_Enable = true;
	isDead = false;
	tr->Translate(0, 0);
	kills = 0;
}

void ShipPlayer::OnStart() {
	
}

void ShipPlayer::OnUpdate() {
	if (isDead == true)
		return;
	ShipMovement();
	ScreenBorders();
	//ThreadPool::Instance()->enqueue([=] {
		col->IsCollidedSAT();
	//});
	if (hp <= 0) {
		Death();
	}

	if (kills == 5) {
		currentStage = FIRST;
	}
	if (kills == 15) {
		currentStage = SECOND;
	}

	Fire();
}

void ShipPlayer::OnCollision(void * _col)
{
	RectangleCollider2D* __col = static_cast<RectangleCollider2D*>(_col);
	if (__col->GetOwnerOfComponent()->m_Tag == "EnemyBullet") {
		Bullet* bullet = static_cast<Bullet*>(__col->GetOwnerOfComponent());
		hp -= bullet->damage;
		bullet->Death();
	}
	else if (__col->GetOwnerOfComponent()->m_Tag == "Ammo") {
		Ammo* a = static_cast<Ammo*>(__col->GetOwnerOfComponent());
		ammo += a->GetAmmo();
		SoundManager::Play(SoundManager::GetSound("pickUp"));
		World::DeleteObject(a->m_Id);
	}
}

void ShipPlayer::Fire(float xOffset,float yOffset) {
	if (ammo > 0 && timerFire > TimePerBullet && Input::IsMouseDown(GLFW_MOUSE_BUTTON_1)) {
		float worldVertexPositions[8];
		sr->GetTransformedVertices(worldVertexPositions);
		timerFire = 0;
		int amount = currentStage;
		if (currentStage != ZERO) {
			xOffset = worldVertexPositions[0] * 0.3f;
			yOffset = worldVertexPositions[1] * 0.3f;
		}
		for (size_t i = 0; i < amount; i++)
		{
			if (ammo <= 0)
				return;
			if (usedBulletCounter == amountOfBulletsInPool)
				usedBulletCounter = 0;
			bullets[usedBulletCounter]->SetMoveDirection(dir);
			bullets[usedBulletCounter]->tr->Translate(GetPosition().x + xOffset, GetPosition().y + yOffset);
			bullets[usedBulletCounter]->m_Enable = true;
			bullets[usedBulletCounter]->col->m_Enable = true;
			bullets[usedBulletCounter]->isActive = true;
			bullets[usedBulletCounter]->lifeTimer = 0;
			usedBulletCounter++;
			ammo--;
			if (amount == 2) {
				xOffset = worldVertexPositions[2] * 0.3f;
				yOffset = worldVertexPositions[3] * 0.3f;
			}
			else if (amount == 3) {
				if (i == 0) {
					xOffset = 0;
					yOffset = 0;
				}
				else if (i == 1) {
					xOffset = worldVertexPositions[2] * 0.3f;
					yOffset = worldVertexPositions[3] * 0.3f;
				}
			}
		}
		SoundManager::Play(fireSound);
	}
	timerFire += DeltaTime::s_Deltatime;
}