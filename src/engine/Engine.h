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
#include "./storage/BagOf.h"
#include "../opengl/texture/TextureComponent.h"
#include "input/MouseInput.h"
#include "render/Renderer.h"

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
	virtual void onMouseClick(int button, int action) = 0;

	void loadTexture(int textureId, const std::string& pathToTexture);
	Object& addCube(const Point3D& position, const Vector3D& scaleFactor, int textureId, bool isIntersectable);
	Object& addTriangle(
		const Point3D& position,
		const Vector3D& scaleFactor,
		const Vector3D& rotationAxis,
		float rotationAngle,
		int textureId,
		bool isIntersectable);
	Line& addLine(const Point3D& start, const Point3D& end, const Color& color);

	bool isKeyActioned(int keyId, int action);
private:
	Graphics graphics;
protected:
	FPSCamera cam;
	Window window;
	PhysicsSystem physics;
	BagOf<Object> objects;
	BagOf<Line> lines;
	MouseInput mouseIn;
	Renderer renderer;
private:
	std::vector<TextureComponent> textures;
	std::shared_ptr<ShaderProgram> defaultObjectShader;
	int fps = 60;

	friend void mouse_callback(Engine& engine, GLFWwindow* window, double xpos, double ypos);

	Object& addObject(
		ObjectType type,
		const Point3D& position,
		const Vector3D& scaleFactor,
		const Vector3D& rotationAxis,
		float rotationAngle,
		int textureId,
		std::shared_ptr<ShaderProgram> shader,
		bool isIntersectable);

	Object& addObject(
		ObjectType type,
		const Point3D& position,
		const Vector3D& scaleFactor,
		const Vector3D& rotationAxis,
		float rotationAngle,
		int textureId,
		bool isIntersectable);
};