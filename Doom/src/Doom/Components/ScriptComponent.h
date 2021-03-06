#pragma once

namespace Doom {

	class LuaState;

	class DOOM_API ScriptComponent : public Component
	{
	private:

		LuaState* m_LState = nullptr;
	public:

		void AssignScript(const char* filePath);

		ScriptComponent(const ScriptComponent& rhs);
		ScriptComponent();
		~ScriptComponent();
	};

}

