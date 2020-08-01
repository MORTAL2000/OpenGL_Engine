#ifndef PCH_H
#define PCH_H

#include "Core/Core.h"

#pragma warning(push)

#pragma warning(disable:4251)
#pragma warning(disable:4244)
#pragma warning(disable:4267)

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#include <functional>
#include <limits>
#include <math.h>

#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <glew.h>
#include <glfw3.h>
#include <glfw3native.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Core/DeltaTime.h"
#include "Core/ColorsRGBA.h"
#include "Render/Shader.h"
#include "Render/IndexBuffer.h"
#include "Render/VertexBuffer.h"
#include "Render/VertexBufferLayout.h"
#include "Render/VertexArray.h"
#include "Render/Texture.h"
#include "Objects2D/GameObject.h"
#include <Windows.h>
#include "Core/Timer.h"
#endif // !PCH_H