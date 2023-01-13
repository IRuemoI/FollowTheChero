#pragma once
#include "Hazel.h"
#include "ImGui/imgui.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

namespace Hazel
{

	class EditorLayer :public Layer
	{
	public:



		EditorLayer();

		virtual void OnAttach()override;
		virtual void OnDetach()override;
		virtual void OnImGuiRender() override;
		void OnUpdate(Timestep deltaime) override;
		void OnEvent(Event& e) override;//���ȵĽ���ж���application ��Onevent ,���ù�


	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMousebuttomPressed(MouseButtonPressedEvent& e);
		void SaveSceneAs();
		void SaveScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void NewScene();

		//UI Panel
		void UI_Toolbar();

		void OnScenePlay();
		void OnSceneStop();

		void OnDuplicateEntity();

		void SerializeScene( Ref<Scene> scene , const std::filesystem::path& filePath);
	private:
		struct  ProfileResult
		{
			const char* Name;
			float Time;
		};

#if 0

		//old ref
		Ref<VertexArray> m_squareVA; //for 
		Ref<Texture2D> m_boardTexture, m_quancifangTexture;
		Ref<Texture2D> m_spriteSheet;
		Ref<SubTexture2D> m_spriteHair, m_spriteTree;


		OrthographicCameraController m_cameraController; //cherno��position�������?? 

		//Paricle 
		ParticleSystem m_particleSystem;
		ParticleProps m_particle;
#endif

		Ref<Scene> m_activeScene;
		Ref<Scene> m_editScene ;
		Ref<FrameBuffer> m_frameBuffer;
		//Ref<FrameBuffer> m_entityIDBuffer;

		std::filesystem::path	m_editorScenePath;


		glm::vec4 m_flatColor = { 0.2,0.3f,0.8f,0.4f };
		glm::vec2 m_ViewPortSize;
		glm::vec2 m_viewPortBounds[2];

		//Entity: quad and Camera
		Entity m_quadEntity;
		Entity m_cameraEntity;
		Entity m_secondCamera;
		bool m_primaryCamera =false;


		std::unordered_map<char, Hazel::Ref<SubTexture2D>> m_TextureMap; //for char to texture
		uint32_t m_mapWidth, m_mapHeight;
		bool m_viewPortIsFocus =true, m_viewPortIsHover =false;

		//UI:gizmo
		int m_gizmoMod = -1;

		//editorCamera
		EditorCamera m_editorCamera;

		Entity m_hoveredEntity = {};
		
		//UI
		SceneHierarchyPanel m_sceneHierarchyPanel; 	
		ContentBrowserPanel m_contentBrowserPanel;

		//EditResource
		Ref<Texture2D> m_IconPlay;
		Ref<Texture2D> m_IconStop;

		
		enum class SceneState
		{
			Edit = 0, Play = 1
		};

		SceneState m_sceneState = SceneState::Edit;


	};

}

