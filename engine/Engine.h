#include <memory>
#include <string>

#include "../graphics/Graphics.h"
#include "../ui/Window.h"
#include "../models/TypeDefs.h"
#include "../graphics/ShaderProgram.h"
#include "../input/KeyboardInput.h"
#include "../graphics/RectComponent.h"
#include "../attributes/RectAttributeStrategy.h"
#include "../serialisation/RectSerialisationStrategy.h"
#include "../attributes/TexturedRectAttributeStrategy.h"
#include "../serialisation/TexturedRectSerialisationStrategy.h"

class Engine {
public:
	void start();
protected:
	virtual void init(int width, int height, const std::string& label, const Color& clearScreenColor);
	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void onStop() = 0;
	void loadTexture(int textureId, const std::string& pathToTexture) const;

	std::shared_ptr<Rect> createRect(Point3D origin, float width, float height);
	std::shared_ptr<TexturedRect> createRect(Point3D origin, float width, float height, unsigned int textureId);

	ShaderProgram shaderProgram;
	KeyboardInput keyboardInput;
	std::shared_ptr<Window> window;
private:
	Graphics graphics;
	RectAttributeStrategy rectAttributeStrategy;
	std::shared_ptr<RectSerialisationStrategy> rectSerialisationPtr;
	RectComponent<Rect> rectComp;

	TexturedRectAttributeStrategy trectAttributeStrategy;
	std::shared_ptr<TexturedRectSerialisationStrategy> trectSerialisationPtr;
	RectComponent<TexturedRect> trectComp;

	const std::string textureVarPrefix = "texture";
};