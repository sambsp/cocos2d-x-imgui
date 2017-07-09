#ifndef __CC_IMGUI_H__
#define __CC_IMGUI_H__

#include "cocos2d.h"
#include "imgui/imgui.h"

USING_NS_CC;

// ImGuiManager Gives access to the ImGui backend. The main dear imgui loop that will be persistent across layers.
// You'll want to edit this if you want to edit initial "dear imgui"s properties.

class ImGuiManager
{
	public:
		static ImGuiManager* getInstance();
		void addImGuiCallback(std::function<void()> callback, const std::string& name);
		void removeImGuiCallback(const std::string& name);

		//TODO: Add function to add a check if the mouse click actually touched an ImGui window.
		//TODO: We should fire events from ImGui using cocos2d-x event dispatcher somehow. Work on that soon.

		// Warning: Do not runt this outside of the onDraw Layer:
		// Note: There should not be more than 2 ImGui nodes due to this.
		//       But the performance hit is barely noticeable.
		void updateImGUI();

		// Utilities
		void setShowStyleEditor(bool show);

		// Engine callback rewiring so that we can pass raw GLFW events to ImGui
		// Each of these functions will first call the GLViewImpl callback
		// such as onGLFWMouseCallBack, and afterwards they will call the ImGui_Impl callback
		// such as ImGui_ImplGlfw_MouseButtonCallback

		// Note: for some reason there's no need to rewire the mouse button callback.
		// static void rewiredMouseButtonCallback(GLFWwindow*, int button, int action, int /*mods*/);
		static void rewiredScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void rewiredKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void rewiredCharCallback(GLFWwindow* window, unsigned int c);

	private:
		void init(); // Initialize the necessary 

		// Map for storing each of the ImGui functions that can be changed at runtime.
		std::map<std::string, std::function<void()>> _callPipelines;
		std::vector<std::string> _markToDelete;

		bool isShowSetupStyle = true;
		void displaySetupStyle();
		void rewireEngineGLFWCallbacks();
};

#endif // __IMGUILAYER_H__