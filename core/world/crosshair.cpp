#include <core/world/crosshair.h>

namespace en61 {

CrosshairModel::CrosshairModel() {
	_data = {
		-0.02, 0, 0.02, 0,
		0, -0.04, 0, 0.04,
	};

	_array.Bind();
	_buffer.Set(_data);
	_buffer.EnableAttribute(0, 2);
	_array.Unbind();
}

void CrosshairModel::Draw() {
	glLineWidth(3.f);
	_array.DrawLines(4);
}


Crosshair::Crosshair() {
	auto shader = MakeRef<Shader>();
	auto model = MakeRef<CrosshairModel>();

	shader->Load("../../assets/crosshair.vs", "../../assets/crosshair.fs");

	SetShader(shader);
	SetModel(model);
}

void Crosshair::Render(const glm::mat4 &view, const glm::mat4 &proj) {
	SetUniform("color", _color);
	DrawModel();
}

void Crosshair::SetColor(glm::vec3 color) {
	_color = color;	
}

} // namespace en61
