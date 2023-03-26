#include <core/renderer/mesh.h>

#include <core/resource.h>

#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace en61 {

void Mesh::load(const std::string &path) {

	std::string full_path = locate_file(path);
	std::ifstream ifs(full_path);

	if (!ifs.is_open()) {
	    std::cerr << "Mesh not found: " << full_path << std::endl;
	}

	std::vector<glm::vec3> temp_positions;
	std::vector<glm::vec3> temp_normals;	
	std::vector<glm::vec2> temp_uvs;

	std::vector<glm::vec3> tangents;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	std::string line;

	while (std::getline(ifs, line)) {

		std::stringstream ss(line);
		std::string type; ss >> type;

		if (type == "v") {
			float x, y, z;
			ss >> x >> y >> z;
			temp_positions.emplace_back(x, y, z);
		}
		else if (type == "vt") {
			float x, y;
			ss >> x >> y;
			// Note: do not invert y if you want to use TGA or BMP loaders
			temp_uvs.emplace_back(x, -y);
		}
		else if (type == "vn") {
			float x, y, z;
			ss >> x >> y >> z;
			temp_normals.emplace_back(x, y, z);
		}
		else if (type == "f") {
			std::string copy = ss.str();
			copy.erase(0, 2);
			std::replace(copy.begin(), copy.end(), '/', ' ');
			ss = std::stringstream(copy);

			size_t pos_id, uv_id, norm_id;
			for (size_t i = 0; i < 3; i++) {
				ss >> pos_id >> uv_id >> norm_id;

				positions.push_back(temp_positions[pos_id - 1]);
				uvs.push_back(temp_uvs[uv_id - 1]);
				normals.push_back(temp_normals[norm_id - 1]);
			}
		}
	}
	ifs.close();
	_vnum = positions.size();

	// generating tangents
	for (size_t i = 0; i < _vnum; i += 3) {

		glm::vec3 edge_1 = positions[i + 1] - positions[i];
		glm::vec3 edge_2 = positions[i + 2] - positions[i];
		float delta_u1 = uvs[i + 1].x - uvs[i].x;
		float delta_v1 = uvs[i + 1].y - uvs[i].y;
		float delta_u2 = uvs[i + 2].x - uvs[i].x;
		float delta_v2 = uvs[i + 2].y - uvs[i].y;

		float scalar_fraction = 1.0f / (delta_u1 * delta_v2 - delta_u2 * delta_v1);

		glm::vec3 tangent;
		tangent.x = scalar_fraction * (delta_v2 * edge_1.x - delta_v1 * edge_2.x);
		tangent.y = scalar_fraction * (delta_v2 * edge_1.y - delta_v1 * edge_2.y);
		tangent.z = scalar_fraction * (delta_v2 * edge_1.z - delta_v1 * edge_2.z);
		glm::normalize(tangent);

		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);
	}

	// setting vertex array
	_array.bind();

	_position_buffer.set(positions);
	_position_buffer.enable_attribute(0, 3);

	_normal_buffer.set(normals);
	_normal_buffer.enable_attribute(1, 3);

	_uv_buffer.set(uvs);
	_uv_buffer.enable_attribute(2, 2);

	_tangent_buffer.set(tangents);
	_tangent_buffer.enable_attribute(3, 3);

	_array.unbind();

	_position_buffer.disable_attribute(0);
	_normal_buffer.disable_attribute(1);
	_uv_buffer.disable_attribute(2);
	_tangent_buffer.disable_attribute(3);
}

void Mesh::draw() {
	_array.draw_triangles(_vnum);
}

} // namespace en61
