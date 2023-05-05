#pragma once

#include <core/renderer/interfaces.h>
#include <core/scene/object.h>

namespace en61 {
	
class CrosshairModel: public ModelInterface {
public:
	CrosshairModel();

	void Draw() override;

protected:
	VertexArray _array;
	VertexBuffer _buffer;
	std::vector<float> _data;
};


class Crosshair: public Object {
public:
	Crosshair();

	void Render(const glm::mat4 &view, const glm::mat4 &proj) override;
	void SetColor(glm::vec3 color);

protected:
	glm::vec3 _color = {1, 1, 1};
};

}
