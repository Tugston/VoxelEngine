/*
* File: Application.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-17 (yyyy/mm/dd)
*
* Description: Distinct class that drives the entire application, user's game, and editor
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once

/**
* @file Application.h
* @brief The overarching class for engine processes
* 
* @details This is the main driver signleton class that controls all the backend engine tasks such as rendering, calculating delta, engine setup, providing api, etc.
* 
* @warning Be sure to define CreateApplication in your game, see the \ref create_application "CreateApplication" function for specific details.
* @note For a list of all functions available for use in your game, check the @ref engine_api_group "Engine API".
* 
* @author Vincent Pierce
* @date February 17, 2025
*/

//ENGINE
#include "Core/Core.h"
#include "Renderer/Core/Renderer.h"
#include "Input/Input.h"
#include "Core/Window.h"
#include "Core/Debug/DebugUI.h"
#include "Scene/SceneManager.h"
#include "Core/Cameras/PerspectiveCamera.h"

//STND
#include <cstdint>
#include <functional>

namespace Engine
{
	class Layer;

	class Application
	{
	public:
		/**
		* @name Construction, Initialization, Destruction
		* @details The Constructors, Destructor, and any other helper setup functions. These may be useful in various situations.
		* @{
		*/

		/**
		* @brief Create application with all default settings
		* @details Calls Initialize() for setup. The application name is 'Voxel Game' and render target is set to a Window by default
		*/
		Application();

		/**
		* @brief Create an application with a custom name.
		* @details Calls Initialize() for setup. The render target is still set to a Window by default.
		* @param[in] applicationName A string_view used to set the name of the application window.
		*/
		Application(std::string_view applicationName);

		/**
		* @brief Create application with custom render target
		* @details Calls Initialize() for setup. The name is set to the default name of 'Voxel Game', useful for making a custom editor
		* @param[in] renderTarget Used to specify window or texture rendering preferences for the renderer
		*/
		Application(Renderer::Renderer::RenderTarget renderTarget);

		/**
		* @brief Create application with both a name as well as render target
		* @details Calls Initialize() for setup. Both the name and render target may be set to the desired value, useful for making a custom editor
		* @param[in] applicationName Sets the name of the application window at the top.
		* @param[in] renderTarget Used to specify window or texture rendering preferences for the renderer
		*/
		Application(std::string_view applicationName, Renderer::Renderer::RenderTarget renderTarget);

		/**
		* @brief Cleans up the entire application upon closing
		* @details The application is shutting down by this point, so cleanup is fairly redundant. However, this destructor cleans up the layer stack just in case.
		*/
		~Application();
	private:

		/**
		* @brief Sets up the engine's core systems, static instance, and resources.
		* @details Sets the static instance first, calls InitializeEngineRootSystems(), and sets the window resize callback function. Log's a warning when all critical systems have been initialized properly.
		* 
		* @post The static instance should be valid, m_Window receives the resize callback from the renderer
		*/
		void Initialize();
		/// @}
	
		//*************//
		//*ENGINE API*//
		//************//

		/***
		* @name Engine API
		* @anchor engine_api_group
		* @details These functions are meant to be utilized within the child game class. Public ones may be used anywhere
		* @{	
		*/

	public:
		/**
		* @brief Starts the process of running the game and starting runtime systems
		* @details As of right now the start function calls the script systems construct and start events. This will change in the future. 
		* 
		* @note This start function MUST be called at the very top of the game's Start function to ensure all systems are setup.
		*/
		virtual void Start();

		/**
		* @brief Begin the main event loop of the entire application
		* @details Tick immediately calls CalculateDeltaTime() for the next update, then input events are processed, Tick is called for all scripts, the m_Window polls for events, and finally Draw() is called.
		* 
		* @note The Tick function does not incorprate the loop itself. This must be created in the game's Tick. Also, the engine's Tick function must be called last inside the loop. Various systems are polling for events that the Engine Tick handles. Delta Time can be acquired by calling GetDeltaTime().
		*/
		virtual void Tick();

	protected:	

		/**
		* @brief Delta time getter.
		* @details The function does not modify the application class, just a wrapper to ensure modifying m_DeltaTime through CalculateDeltaTime() remains private.
		* @return The time between the last and current frame.
		*/
		inline const float GetDeltaTime() const { return m_DeltaTime; };

		/**
		* @brief Utilize the Scene::SceneManager to create a new level.
		* @details This function just calls the Create Scene function inside the Scene::SceneManager class, and passes the levelName.
		* 
		* @param[in] levelName Provide the unique name identifier for the generated level
		*/
		void CreateLevel(std::string_view levelName);

		/**
		* @brief Open an existing level
		* @note This functionality is still a work in progress as of Engine version 0.0.2.
		* 
		* @param[in] levelName Provide the name of the level wanting to be loaded, if level name does not exist do nothing.
		*/
		void LoadLevel(std::string_view levelName); 
		
		///Returns the currently loaded scene in the Scene::SceneManager
		inline const Scene::Scene* GetWorld() { return m_SceneManager.GetCurrentScene(); }

	public:
		/**
		* @brief Returns the m_Running variable
		* @note This is inside a getter because QuitGame() is responsible for cleanup and some systems may screw up if game abruptly ends.
		*/
		inline bool ShouldRun() { return m_Running; };

		/**
		* @brief Quits the game completely
		* @details Set m_Running to false and call destroy on Window class.
		* @note In the future the function will listen and await a dispatched event from the game and do final cleanup once game is clean. Currently not implemented in version 0.0.2. 
		*/
		static void QuitGame();
		
		/**
		* @brief Frame rate getter.
		* @details This function allows anything to access and the m_FrameRate without modifying the true.
		* @return The current frame rate calculated in the CalculateDeltaTime() function.
		*/
		static const inline unsigned int GetFrameRate() { return s_Instance->m_FrameRate; };

		/**
		* @brief Free flying editor camera.
		* @details This is an editor camera and strictly meant for an editor or game debugging view. A game should utilize a Scene::ECS::Components::PerspectiveCamera or a Scene::ECS::Components::OrthographicCamera for playing.
		* 
		* @warning The pointer is not checked for validity. This can return null. However, a camera should always be valid.
		* @note As of version 0.0.2 the camera components do not exist yet. So, the Camera::EditorCamera may turn into more of a camera management system. The editor camera itself will just be a ECS component... maybe?
		* 
		* @return The current pointer stored in m_Camera variable.
		*/
		static inline Camera::EditorCamera* GetCamera() { return s_Instance->m_Camera.lock().get(); };

		/**
		* @brief Set the default camera to the one created in the editor.
		* @post The m_Camera pointer value is now valid, assuming it is properly set and not null.
		* @note See GetCamera() documents for more information.
		*/
		void SetViewTargetCamera(std::shared_ptr<Camera::EditorCamera> camera) { m_Camera = camera; };	
		
		
		///@}

		//*************//
		//*ENGINE API*//
		//************//
	
	private:
		/**
		* @name Rendering
		* @details This group of functions represents every utility that has to do with rendering the scene in some form.
		* @{
		*/

		/**
		* @brief Handles all draw calls in the application
		* @details Begins the frame rendering using the m_Renderer by calling Renderer::Renderer::BeginRender() and supplying the current camera. Performs all rendering calls in proper order and then calls Renderer::Renderer::EndRender() to finalize the drawing, cleanup, and render the scene. Finally calls SwapBuffer() to display the frame. 
		* 
		* @param[in] deltaTime The current value for m_DeltaTime calculated in CalculateDeltaTime().
		*/
		void Draw(float deltaTime);

		/**
		* @brief Swap the back buffer to the front
		* @details This function calls the m_Window swap buffers function in Engine::Window 
		*/
		virtual void SwapBuffer() { m_Window.SwapBuffers(); }

		/**
		* @brief Calculates the delta time between each frame
		* @details This function calculates delta time by subtracting the glfw runtime by m_PreviousTime, then assigns it as the new m_PreviousTime. This functions handles the calculation for the m_FrameRate as well.
		*
		* @post The m_DeltaTime and m_FrameRate values are set each frame
		*/
		void CalculateDeltaTime();

		///@}
	
		/**
		* @brief Sets up all the critical systems for the engine
		* @details As of version 0.0.2, this initializes the InputSystem, LayerStack, and Utility::InitializeRandomGenerators()
		* @post The systems are initialized with a corresponding log stating success or failure.
		*/
		void InitializeEngineRootSystems() const;

		/**
		* @brief Input polling for each layer
		* @details Loops through each layer and provides the input event. Allows the layers to consume the input value to not propogate to the next layers.
		* @note as of version 0.0.2 the layers do not consume or process input at all. This is a work in progress feature.
		*/
		void ProcessInput() const;

	protected:
		///Manages the scene processes
		Scene::SceneManager m_SceneManager;
			
		//Editor Specifics & MetaData
		/**
		* @name Editor Specifics & MetaData
		* @details Functions that are mostly meant for an editor application to take advantage of, but also provide general metadata of the engine.
		* @{
		*/

		/**
		* @brief Used by the editor to render the camera view onto a texture pane.
		* @return The integer texture from Renderer::Renderer::GetRenderTexture() 
		*/
		unsigned int GetRenderScreenTexture() { return m_Renderer->GetRenderTexture(); }
		
		/**
		* @brief Getter for the window name
		* @details Call the Engine::Window::GetName() function on the m_Window variable in order to access the application's name within the application for whatever reason.
		* @return The name stored in Engine::Window
		*/
		const std::string_view GetWindowName() { return m_Window.GetName(); }

		///@}
		//Editor Specifics & MetaData

	private:
		///The time taken to render the current and last frame
		float m_DeltaTime = 0;

		/**
		* @brief Temporary value for the m_DeltaTime calculation
		* @details The CalculateDeltaTime() function needs a way to remember the previous runtime before this value is set. So, it needs a variable storage value and cannot be a static variable in the function because the value is needed before.
		*/
		float m_PreviousTime = 0;

		///How many frames are running per second
		unsigned int m_FrameRate = 0;

		///Application run control, true is running and false immediately terminates
		bool m_Running = true;

		///The application window
		Window m_Window;

		/**
		* @brief The renderer for drawing
		* @details The renderer is instantiated on the heap due to it's large size. In version 0.0.2 it does not currently contain a bunch of packet types. However, the renderer will quickly grow in size as more draw calls are added. See Renderer::Renderer for more details.
		*/
		std::unique_ptr<Renderer::Renderer> m_Renderer;

		///reference to the current active Camera::EditorCamera in the application.
		std::weak_ptr<Camera::EditorCamera> m_Camera;

	//class instance just hidden away down here
	public:
		///Class instance
		static Application* s_Instance;

		///Returns the window or crashes, should always return a value
		inline const static Window* GetWindow() { if (&s_Instance->m_Window) return &s_Instance->m_Window;
		else { Logger::LogMessage(Logger::LogType::Critical, "Window Invalid!"); EG_ASSERT(false); }};
	};

	/**
	* @fn extern Application* CreateApplication()
	* @brief Application creation
	* @details This function must be defined in your application in order to supply the proper application class
	*
	* @post Instantiates and returns the game's custom application
	*
	* @return A raw pointer to the custom game instance
	*
	* ### Example Usage
	* @code
	* class YourCustomGame : public Engine::Application { ... };
	*
	* Engine::Application* Engine::CreateApplication() {
	*	return new YourCustomGame();
	* }
	* @endcode
	*
	* @note In future versions of the engine this may be deprecated
	* 
	* \anchor create_application
	*/
	extern Application* CreateApplication();
}

//quaternions and what not
#define GLM_ENABLE_EXPERIMENTAL