#pragma once
#include <iostream>
#include "../Core/Core.h"
#include "Mesh.h"
#include <map>

namespace Doom {

	class DOOM_API MeshManager {
	private:
		static std::map<std::string, Mesh*> Meshes;
		static std::multimap<std::string, void*> meshQueue;
		static bool dispatch;
	public:
		static void LoadMesh(std::string name, std::string filepath);
		static void AsyncLoadMesh(std::string name, std::string filepath);

		static Mesh* GetMesh(std::string name);

		static void GetMeshWhenLoaded(std::string name, void* r);

		static void DeleteMesh(std::string name);

		static void DeleteMesh(Mesh* mesh);

		static void ShutDown();

		static void DispatchLoadedMeshes();

		friend class Renderer;

	};

}