#include <iostream>

#include "RBXMesh.h"

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		std::cout << "Usage: RBXMeshConverter <files>" << std::endl;
		std::cin.get();
		return 1;
	}

	for (int i = 1; i < argc; ++i)
	{
		std::string filename = argv[i];

		objl::Loader obj;
		if (!obj.LoadFile(filename))
		{
			std::cout << "Could not load \"" << filename << "\"!" << std::endl;
			std::cin.get();
			return 1;
		}

		std::ofstream result(filename + ".mesh", std::ios::binary);

		RBXMesh mesh(obj);
		mesh.Write(result);

		result.close();
	}

	return 0;
}
