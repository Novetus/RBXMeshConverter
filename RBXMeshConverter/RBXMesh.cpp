#include "RBXMesh.h"

void RBXMesh::Write(std::ostream& stream)
{
	MeshHeader header
	{
		sizeof(MeshHeader),
		sizeof(MeshVertex),
		sizeof(MeshFace),
		(uint32_t)vertices.size(),
		(uint32_t)faces.size()
	};

	stream << meshVersion << std::endl;
	stream.write((char*)&header, sizeof(MeshHeader));
	stream.write((char*)&vertices[0], std::streamsize(sizeof(MeshVertex)) * vertices.size());
	stream.write((char*)&faces[0], std::streamsize(sizeof(MeshFace)) * faces.size());
}

RBXMesh* RBXMesh::FromOBJ(objl::Loader& obj)
{
	vertices.clear();
	faces.clear();

	for (auto& vertex : obj.LoadedVertices)
	{
		vertices.push_back(
			MeshVertex
			{
				vertex.Position.X,
				vertex.Position.Y,
				vertex.Position.Z,

				vertex.Normal.X,
				vertex.Normal.Y,
				vertex.Normal.Z,

				vertex.TextureCoordinate.X,
				1.f - vertex.TextureCoordinate.Y // For some reason this axis is flipped?
			});
	}

	for (auto it = obj.LoadedIndices.begin(); it != obj.LoadedIndices.end(); it += 3)
	{
		faces.push_back(
			MeshFace
			{
				(uint32_t)*it,
				(uint32_t)*(it + 1),
				(uint32_t)*(it + 2)
			});
	}

	return this;
}
