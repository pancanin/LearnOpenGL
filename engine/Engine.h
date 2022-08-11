#include <memory>
#include <string>

#include "../graphics/Graphics.h"
#include "../ui/Window.h"
#include "../models/TypeDefs.h"
#include "../graphics/ShaderProgram.h"
#include "../input/KeyboardInput.h"
#include "../graphics/RectComponent.h"
#include "../attributes/RectAttributeConfigurer.h"
#include "../serialisation/RectBufferSerialiser.h"
#include "../attributes/TexturedRectAttributeConfigurer.h"
#include "../serialisation/TexturedRectBufferSerialiser.h"
#include "../utils/TextureComponent.h"

class Engine {
public:
	void start();
protected:
	virtual void init(int width, int height, const std::string& label, const Color& clearScreenColor);
	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void onStop() = 0;
	void loadTexture(int textureId, const std::string& pathToTexture);

	std::shared_ptr<Rect> createRect(Point3D origin, float width, float height);
	std::shared_ptr<TexturedRect> createRect(Point3D origin, float width, float height, unsigned int textureId);

	ShaderProgram shaderProgram;
	KeyboardInput keyboardInput;
	std::shared_ptr<Window> window;
	RectComponent<Rect> rectComp;
	RectComponent<TexturedRect> trectComp;
private:
	Graphics graphics;
	RectAttributeConfigurer rectAttributeConfigurer;
	std::shared_ptr<RectBufferSerialiser> rectSerialisationPtr;
	

	TexturedRectAttributeConfigurer trectAttributeStrategy;
	std::shared_ptr<TexturedRectBufferSerialiser> trectSerialisationPtr;
	
	std::vector<std::shared_ptr<TextureComponent>> textures;

	TextureComponent wallTexture;
	TextureComponent containerTexture;

	const std::string textureVarPrefix = "texture";
};