#include <memory>
#include <string>
#include <cstdint>

#include "./core/Graphics.h"
#include "./ui/Window.h"
#include "./models/TypeDefs.h"
#include "../opengl/shader/ShaderProgram.h"
#include "./camera/FPSCamera.h"
#include "./core/PhysicsSystem.h"
#include "./storage/BagOf.h"
#include "../opengl/texture/TextureComponent.h"
#include "input/MouseInput.h"
#include "render/Renderer.h"
#include "models/Line.h"
#include "models/Object.h"
#include "models/Triangle.h"
#include "models/Rect.h"
#include "models/Point.h"

struct GLFWwindow;
struct Plane;

class Engine {
public:
	void start();
	void init(uint32_t width, uint32_t height, const std::string& title);
protected:
	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void onStop() = 0;

	virtual void processInput() = 0;
	virtual void onMouseMove(double xpos, double ypos) = 0;
	
	virtual void onMouseClick(int button, int action) = 0;

	uint32_t loadTexture(uint32_t textureId, const std::string& pathToTexture);
	Object& addCube(const Point3D& position, const Vector3D& scaleFactor, int textureId, bool isIntersectable);
	Triangle& addTriangle(
		const Point3D& p1,
		const Point3D& p2,
		const Point3D& p3,
		int textureId,
		bool isIntersectable);
	Triangle& addTriangle(
		const Point3D& p1,
		const Point3D& p2,
		const Point3D& p3,
		const Vector3D& scale,
		int textureId,
		bool isIntersectable);
	Line& addLine(const Point3D& start, const Point3D& end, const Color& color);
	Plane& addPlane(const Vector3D& point, const Vector3D& normal, const Color& color);
	Rect& addRect(
		const Point3D& p1,
		const Point3D& p2,
		const Point3D& p3,
		const Point3D& p4,
		const Vector3D& scale,
		int textureId,
		uint32_t textureScale,
		bool isIntersectable);
	Point& addPoint(const Point3D& position, const Color&, float size);
protected:
	std::unique_ptr<Camera> cam;
	Window window;
	PhysicsSystem physics;
	BagOf<Object> objects;
	BagOf<Line> lines;
	BagOf<Triangle> triangles;
	BagOf<Rect> rects;
	BagOf<Point> points;
	MouseInput mouseIn;
	Renderer renderer;
	float width;
	float height;
	bool isFPSCamera = false;

	void setCamera(std::unique_ptr<Camera> cam);
	void setFPS(uint32_t frameRate);
private:
	Graphics graphics;
	std::vector<TextureComponent> textures;
	std::shared_ptr<ShaderProgram> defaultObjectShader;
	std::shared_ptr<ShaderProgram> vertexIdxAwareShader;
	std::shared_ptr<ShaderProgram> pointShader;
	int fps = 60;

	friend void mouse_callback(Engine& engine, GLFWwindow* window, double xpos, double ypos);
	friend void key_callback(Engine&, GLFWwindow*, int key, int scancode, int action, int mods);

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
	void _processInput();
	void _onMouseMove(double xpos, double ypos);
};