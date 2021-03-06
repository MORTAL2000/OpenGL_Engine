#pragma once

class DrawLines : public Application {

	std::vector<glm::vec3> dots;
	std::vector<GameObject*> dotsCircles;
	float timer = 0.2f;
	Texture* dotTexture = nullptr;
	float* color = new float[4];
	glm::vec4 veccolor = glm::vec4(1.f);
	double editortimer = 3.f;
	bool isEditorEnable = false;

	virtual void OnStart() override {
		for (size_t i = 0; i < 4; i++)
			color[i] = 255.f;
		dotTexture = Texture::Create("src/Images/WhiteCircle.png");
	}

	virtual void OnUpdate() override {

		if (timer > 0.19f && Input::IsMouseDown(Keycode::MOUSE_BUTTON_1)) {
			glm::vec3 pos;
			if (Input::IsKeyPressed(Keycode::KEY_LEFT_CONTROL) && dotsCircles.size() == 2) {
				pos = glm::vec3(dotsCircles[1]->GetPositions().x, dotsCircles[1]->GetPositions().y,0);
				dots.clear();
				dots.push_back(pos);
				GameObject* dot = new GameObject("Dot", pos.x, pos.y);
				GenerateDot(*dot);
			}
			pos = glm::vec3(ViewPort::GetInstance()->GetMousePositionToWorldSpace().x, ViewPort::GetInstance()->GetMousePositionToWorldSpace().y,0);
			dots.push_back(pos);
			GameObject* dot = new GameObject("Dot", pos.x, pos.y);
			GenerateDot(*dot);
			timer = 0.0f;
		}
		timer += DeltaTime::deltatime;
		if (dots.size() == 2) {
			Line* line = new Line(dots[0], dots[1]);
			line->width = 10.f;
			line->color = veccolor;
			dots.clear();
		}

		if (editortimer > 0.2 && Input::IsKeyPressed(Keycode::KEY_C)) {
			if (isEditorEnable)
				isEditorEnable = false;
			else
				isEditorEnable = true;
			editortimer = 0;
		}
		editortimer += DeltaTime::deltatime;
	}

	void GenerateDot(GameObject& dot) {
		float scaleKoef = Window::GetCamera().GetZoomLevel() / 10;
		dot.GetComponentManager()->GetComponent<Transform>()->Scale(scaleKoef * 0.3f, scaleKoef* 0.3f);
		dot.GetComponentManager()->GetComponent<SpriteRenderer>()->SetTexture(dotTexture);
		if (dotsCircles.size() == 2) {
			Renderer::DeleteObject(dotsCircles[0]->GetId());
			Renderer::DeleteObject(dotsCircles[1]->GetId());
			dotsCircles.clear();
		}
		dotsCircles.push_back(&dot);
	}
};
