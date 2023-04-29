#include <core/scene/crosshair.h>

namespace en61 {

CrosshairMesh::CrosshairMesh() {
	_data = {
		-0.02, 0, 0.02, 0,
		0, -0.04, 0, 0.04,
	};

	_array.Bind();
	_buffer.Set(_data);
	_buffer.EnableAttribute(0, 2);
	_array.Unbind();
}

void CrosshairMesh::Draw() {
	glLineWidth(3.f);
	_array.DrawLines(4);
}


Crosshair::Crosshair() {
	auto shader = MakeRef<Shader>();
	auto mesh = MakeRef<CrosshairMesh>();

	shader->Load("../../assets/crosshair.vert", "../../assets/crosshair.frag");

	SetShader(shader);
	SetMesh(mesh);
}

void Crosshair::Render(const glm::mat4 &view, const glm::mat4 &proj) {
	SetUniform("color", _color);
	DrawMesh();
}

void Crosshair::SetColor(glm::vec3 color) {
	_color = color;	
}

} // namespace en61
