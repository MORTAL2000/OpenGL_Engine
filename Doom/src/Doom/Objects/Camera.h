#pragma once
#include "../Core/Listener.h"
#include "../vendor/glm/glm.hpp"
#include "../Input/Input.h"
#include "../Enums/KeyCode.h"
#include "OpenGl/FrameBuffer.h"

namespace Doom {

	class DOOM_API Camera : public Listener {
	public:

		enum CameraTypes {
			ORTHOGRAPHIC = 0,
			PERSPECTIVE = 1,
		};

		CameraTypes m_Type = ORTHOGRAPHIC;

		FrameBuffer* m_FrameBufferColor = nullptr;
		FrameBuffer* m_FrameBufferShadowMap = nullptr;
		FrameBuffer* m_FrameBufferUI = nullptr;
		std::vector<FrameBuffer* > m_FrameBufferBlur;

		Camera();
		~Camera();

		glm::vec3 GetRotation();
		glm::vec3 GetMouseDirVec();

		inline glm::vec3 GetPosition() const { return m_Position; }
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMat4; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMat4; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMat4; }
		inline float GetAspectRatio() const { return m_Ratio; }
		inline double GetZoomLevel() const { return m_ZoomLevel; }

		void OnWindowResize(void* _props);
		void WindowResize();
		void Increase();
		void SetOnStart();
		void CameraMovement();
		void RecalculateViewMatrix();
		void Zoom(float zoomlevel);
		void MovePosition(const glm::vec3 position);
		void SetPosition(const glm::vec3 position);
		void SetPerspective(float fovy, float width, float height, float znear, float zfar);
		void SetFov(float fov);
		void SetOrthographic(float ratio);
		void SetRotation(glm::vec3 rot);

		float GetRationWH() const;
		float GetRationHW() const;
		float GetFOV() { return m_Fov; }

		friend class Editor;
		friend class Batch;
	private:

		std::mutex m_Mtx;
		glm::vec3 m_Position = glm::vec3(0);
		glm::mat4 m_ProjectionMat4;
		glm::mat4 m_ViewMat4;
		glm::mat4 m_ViewProjectionMat4;
		float m_Zfar = 10;
		float m_Znear = 0.1f;
		float m_Fov = 1;
		float m_Ratio = 0;
		float m_ZoomLevel = 1.0f;
		float m_Roll = 0.0f;
		float m_Pitch = 0.0f;
		float m_Yaw = 0.0f;
		float m_AspectRatio[4]; 
		int* m_Props = nullptr;
		bool m_IsWindowResized = false;
	public:

		glm::vec3 forwardV = { 0,0,-1 };
		float m_ZnearSM = -50.0f;
		float m_ZfarSM = 50.0f;
		float m_RationProjectionSM = 50.0f;
	};

}