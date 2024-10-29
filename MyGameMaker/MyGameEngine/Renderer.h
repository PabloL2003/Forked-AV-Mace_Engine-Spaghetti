#pragma once

#include <GL/glew.h>

//#include "VertexArray.h"
//#include "IndexBuffer.h"
#include "Shader.h"

//marcos
#define ASSERT(x) if (!(x)) __debugbreak(); //hace un break en el momento que glcallerror detecta un error
//la marco llama a glclear, despues ejecuta una funcion y despues mira si hay error
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
//#x tranforma el nombre de la funcion a string, __FILE__ y __LINE__ retornan el fichero y linea

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	Renderer() = default;
    void Clear() const;
	void Start() const;
    //void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
private:

};