/*
* File: Window.h
* Project: Voxel Engine
* Author: Vincent Pierce
* Created: 2025-02-25 (yyyy/mm/dd)
*
* Description: Wrapper for GLFW window and supporting functions
*
* Copyright (C) 2025 Vincent Pierce
* SPDX-License-Identifier: GPL-3.0
*
* See License in root directory for additional details.
*/
#pragma once


/**
* @file Window.h
* @brief GLFW window wrapper class
*
* @details This class simplifies some of the GLFW window functions and utilities. Plus it abstracts a lot of the base setup from the application.
*
* @note This class includes functions that modify the native window's properties that are not included in glfw. Please see the @ref native_functions "Native Functions" group.
*
* @author Vincent Pierce
* @date February 25, 2025
*/

#define GLFW_EXPOSE_NATIVE_WIN32 //allow the underlying win32 window to be accessible
#define NOMINMAX //fix the min max collusion with stnd lib

//ENGINE
#include "Core/Core.h"
#include "Maths/Math.h"

//STND
#include <string>

///Forward declaration for the glfw window class
struct GLFWwindow;

namespace Engine
{
	///Shorthand for the std::function callback with two integer parameters
	using WindowResizeCallback = std::function<void(int, int)>;

	class Window
	{
	public:
		/**
		* @name Constructors, Destructors, and Setup
		* @details Group of functions that control the initial setup of a window.
		*/

		/**
		* @brief Sets up a default window with default settings.
		* @details This constructor just calls InitializeGLFW() and SetupWindow() functions without changing #m_Info value.
		* @post The window is fully created. The default window has a width of 800, a height of 500, and title "Voxel Game".
		*/
		Window();

		/**
		* @brief Setup a window with a custom name.
		* @details The constructor sets #m_Info name value to the provided name, then calls InitializeGLFW() and SetupWindow() functions.
		* @param[in] name Provide a string value for the window name.
		* @post The window is fully created. The name is customized, has a width of 800, and a height of 500. 
		*/
		Window(const std::string& name);

		/**
		* @brief Setup a window with a custom name and dimensions.
		* @details The constructor sets #m_Info name value, width value, and height value to the provided values. Then it proceeds to call the InitializeGLFW() and SetupWindow() functions.
		* 
		* @param[in] name Provide a string value for the window name.
		* @param[in] width Assign a width to the window, which is adjustable.
		* @param[in] height Assign a height value to the window, which is adjustable.
		* 
		* @note Width and height params at most will ever need to be 7680 x 4320 for 8k monitor resolutions. An unsigned short provides plenty of overhead above that. Could use an integer, but it never hurts to save a miniscule amount of memory.  
		*/
		Window(const std::string& name, unsigned short width, unsigned short height);

		///Calls DestroyWindow()
		~Window();

		/// @}

		/**
		* @brief Width should not be modified outside of resizing.
		* @return The width value stored in #m_Info.width
		*/
		inline unsigned short GetWidth() const { return m_Info.width; };

		/**
		* @brief Height should not be modified outside of resizing.
		* @return The height value stored in #m_Info.height
		*/
		inline unsigned short GetHeight() const { return m_Info.height; };

		/**
		* @brief Name should remain consistent at all times through application lifespan.
		* @return The name value stored in #m_Info.name
		*/
		inline std::string_view GetName() const { return m_Info.name; };

		/**
		* @brief A const reference to the underlying GLFW window, so it can't be modified. 
		* @return A pointer to the GLFW window.
		* @note The returned pointer is not guaranteed to be valid. It is typically safe to assume it is, since the application itself would not have a window present.
		*/
		inline GLFWwindow* GetGLFWWindow() const { return m_RenderWindow; };

		//*******
		//natives
		//*******

		/**
		* @name Window Natives
		* @anchor native_functions
		* @details These functions are a part of the GLFW3Native library. In combination with the dwmapi standard library, these functions control the window's fine detail customizations and settings.
		* @{
		*/

		/**
		* @brief Sets the thin outside frame color on a bordered window.
		* @details The function is called and receives the color as a param. The GLFW window is checked and the base Win32 window is fetched. The color is logged, confirming the setting. Then the dwmapi is utilized to set the border accordingly.
		* 
		* @param[in] color The R, G, B value with a max of 255. The type is custom from Maths::Vector3
		* 
		* @post The window is adjusted to the provided color.
		* @post If either window is invalid, returns with no changes.
		*/
		void SetWindowBorderColor(const Maths::Vector3<uint8_t>& color) const;

		/**
		* @brief Sets the top bar color on a bordered window.
		* @details The window heading color is received as a param. The GLFW window is checked and the base Win32 window is then fetched. The color is logged for verifications. Finally the dwmapi is utilized to set the header color accordingly. 
		* 
		* @param[in] color The R, G, B value with a max of 255. The type is an engine specific type from Maths::Vector3
		* 
		* @post The window's top heading is adjusted to the provided color.
		* @post If either window is invalid, returns with no changes.
		*/
		void SetWindowHeadingColor(const Maths::Vector3<uint8_t>& color) const;
		
		/// @}

		//*******
		//natives
		//*******

		///Calls glfwPollEvents, just a simple wrapper.
		void PollEvents();
		///Calls glfwDestroyWindow and passes the m_RenderWindow variable.
		void DestroyWindow();
		///Wrapper that calls glfwSwapBuffers and provides m_RenderWindow variable.
		void SwapBuffers();

		/**
		* @brief Registers a callback function to handle framebuffer resize events.
		* @details Stores the provided callback function in the #m_Info variable and registers a GLFW framebuffer size callback. When the framebuffer is resized, GLFW invokes the registered callback, which retrieves the WindowInfo associated with the window and invokes the stored resize callback with the new framebuffer width and height. The callback is invoked only if the window's user pointer resolves to a valid WindowInfo pointer.
		*
		* @param callbackFunction The function to invoke when the framebuffer is resized. Receives the new framebuffer width and height.
		*
		* @note The callback reports framebuffer dimensions in pixels, which may differ from the window dimensions on high-DPI displays.
		*
		* @post The provided callback is stored in the window's internal state, replacing any previously stored resize callback, and the GLFW framebuffer resize callback is registered for this window.
		*/
		void SetFrameSize(WindowResizeCallback callbackFunction);

		/**
		* @brief Retrieves the currently registered #m_Info frame buffer resize callback.
		* @return A copy of the stored resize callback function.
		*/
		inline const WindowResizeCallback GetResizeCallback() { return m_Info.resizeCallback; };

		/**
		* @brief Retrieves the current frame buffer dimensions.
		* @return A pair containing the frame buffer width (first) and height (second), in pixels.
		*/
		inline const std::pair<int, int> GetBufferSize() { return m_Info.bufferSize; };

	private:
		/**
		* @brief Initializes and creates the GLFW rendering window.
		* @details Configures the requested OpenGL context settings. Then, the function creates the window using the dimensions and name stored in the #m_Info that is initialized in the constructor. The initial frame buffer dimensions are retrieved, and the OpenGL context is set. It associates the #m_Info with the window user pointer, and finally sets vsync enabled. Logs the process throughout window creation.
		* 
		* @note As of version 0.0.2 vsync is hard coded into the window. There is an assigned github issue to allow vsync settings to be enabled and disabled.
		* 
		* @pre GLFW must have been successfully initialized before this function is called.
		* @pre The #m_Info struct must be setup in the Window constructor.
		* 
		* @post m_RenderWindow references the created window if successfully created.
		* @post m_Info is set with the appropriate resizeCallback.
		* 
		* @note requests an OpenGL 4.1 core profile with forward compatibility enabled.
		*/
		void SetupWindow();

		/**
		* @brief Calls the glfwInit function and asserts if fails
		* @post GLFW is successfully initialized.
		* @note Extracted this to a function in case this feature becomes publicly accessible. It would allow for this Window class to operate as the glfw window class.
		*/
		void InitializeGLFW();

	private:
		///The underlying glfw window this class wraps around to make the interface simpler.
		GLFWwindow* m_RenderWindow;

		///struct for glfw user pointer.
		struct WindowInfo
		{
		public:
			std::string name = "Voxel Game"; ///display name that appears on the heading title bar of Engine::Window.
			unsigned short width = 800; ///window width measured in screen coordinates.
			unsigned short height = 500; ///window height measured in screen coordinates.
			WindowResizeCallback resizeCallback; ///store the resize callback for the future.
			std::pair<int, int> bufferSize; ///window size measured in pixels.
		};

		///Variable value for the struct.
		WindowInfo m_Info;
	};
}