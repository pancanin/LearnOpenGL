#include <memory>
#include <string>

#include "./core/Graphics.h"
#include "./ui/Window.h"
#include "./models/TypeDefs.h"
#include "../opengl/shader/ShaderProgram.h"
#include "./input/KeyboardInput.h"
#include "./camera/FPSCamera.h"
#include "./core/PhysicsSystem.h"
#include "./storage/BagOfObjects.h"
#include "./storage/BagOfLines.h"
#include "../opengl/texture/TextureComponent.h"
#include "input/MouseInput.h"

struct GLFWwindow;

class Engine {
public:
	void start();
	void init();
protected:
	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void onStop() = 0;

	virtual void processInput() = 0;
	virtual void onMouseMove(double xpos, double ypos) = 0;

	void loadTexture(int textureId, const std::string& pathToTexture);
	Object& addCube(Point3D position, Vector3D scaleFactor, int textureId, bool isIntersectable);
	Line& addLine(Point3D start, Point3D end, Color color);

	bool isKeyActioned(int keyId, int action);
	
private:
	Graphics graphics;
protected:
	FPSCamera cam;
	Window window;
	PhysicsSystem physics;
	BagOfLines bagLines;
	BagOfObjects bag;
	MouseInput mouseIn;
private:
	std::vector<TextureComponent> textures;

	friend void mouse_callback(Engine& engine, GLFWwindow* window, double xpos, double ypos);
};