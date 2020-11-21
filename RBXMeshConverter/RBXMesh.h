#pragma once

#include "OBJ_Loader.h"

class RBXMesh
{
private:
	const char* const meshVersion = "version 2.00";

	struct MeshHeader
	{
		uint16_t headerSize;
		uint8_t vertexSize;
		uint8_t faceSize;
		uint32_t vertexCount;
		uint32_t faceCount;
	};
public:
	RBXMesh() {}

	RBXMesh(objl::Loader& obj) { FromOBJ(obj); }

	struct MeshVertex
	{
		float vx, vy, vz;
		float nx, ny, nz;
		float tu, tv, tw;
	};

	struct MeshFace
	{
		uint32_t a, b, c;
	};

	std::vector<MeshVertex> vertices;
	std::vector<MeshFace> faces;

	void Write(std::ostream& stream);
	RBXMesh* FromOBJ(objl::Loader& obj);
};
