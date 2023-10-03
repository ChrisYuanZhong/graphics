#include <gl\glew.h>
#include <iostream>
#include <fstream>
#include <MeGlWindow.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <Primitives\Vertex.h>
#include <Primitives\ShapeGenerator.h>
using namespace std;
using glm::vec3;
using glm::mat4;

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);
GLuint programID;
GLuint num3DIndices;
GLuint num2DIndices;

void sendDataToOpenGL()
{
	ShapeData shape = ShapeGenerator::makeCube();
	ShapeData tri = ShapeGenerator::makeTriangle();

	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize() + tri.vertexBufferSize(), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, shape.vertexBufferSize(), shape.vertices);
	glBufferSubData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), tri.vertexBufferSize(), tri.vertices);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	GLuint indexArrayBufferID;
	glGenBuffers(1, &indexArrayBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize() + tri.indexBufferSize(), 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, shape.indexBufferSize(), shape.indices);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), tri.indexBufferSize(), tri.indices);

	num3DIndices = shape.numIndices;
	num2DIndices = tri.numIndices;

	shape.cleanup();
	tri.cleanup();

	//GLuint vertexBufferID;
	//glGenBuffers(1, &vertexBufferID);
	//glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	//glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3));

	//GLuint indexArrayBufferID;
	//glGenBuffers(1, &indexArrayBufferID);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexArrayBufferID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	//numIndices = shape.numIndices;
	//shape.cleanup();
}

void MeGlWindow::paintGL()
{
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//glViewport(0, 0, width(), height());

	//mat4 projectionMatrix = glm::perspective(70.0f, ((float)width()) / height(), 0.1f, 10.0f);
	//mat4 projectionTranslationMatrix = glm::translate(projectionMatrix, vec3(0.0f, 0.0f, -6.0f));
	//mat4 fullTransformMatrix = glm::rotate(projectionTranslationMatrix, 45.0f, vec3(1.0f, 1.0f, 1.0f));

	//GLint fullTransformMatrixUniformLocation =
	//	glGetUniformLocation(programID, "fullTransformMatrix");

	//glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1,
	//	GL_FALSE, &fullTransformMatrix[0][0]);

	//// Cube
	//glDrawElements(GL_TRIANGLES, num3DIndices, GL_UNSIGNED_SHORT, 0);

	// Rewrite the above code to draw both the cube and the triangle, using the same vertex buffer object.
	// The triangle should be a 2D object at the upper right corner of the screen.

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	mat4 projectionMatrix = glm::perspective(70.0f, ((float)width()) / height(), 0.1f, 10.0f);
	mat4 projectionTranslationMatrix = glm::translate(projectionMatrix, vec3(0.0f, 0.0f, -6.0f));
	mat4 fullTransformMatrix = glm::rotate(projectionTranslationMatrix, 45.0f, vec3(1.0f, 1.0f, 1.0f));

	GLint fullTransformMatrixUniformLocation =
		glGetUniformLocation(programID, "fullTransformMatrix");

	glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1,
		GL_FALSE, &fullTransformMatrix[0][0]);

	// Cube
	glDrawElements(GL_TRIANGLES, num3DIndices, GL_UNSIGNED_SHORT, 0);

	// Triangle 1
	mat4 projectionMatrix2 = glm::perspective(70.0f, ((float)width()) / height(), 0.1f, 10.0f);
	mat4 projectionTranslationMatrix2 = glm::translate(projectionMatrix2, vec3(-4.0f, 1.0f, -4.0f));
	mat4 fullTransformMatrix2 = glm::rotate(projectionTranslationMatrix2, 120.0f, vec3(1.0f, 1.0f, 1.0f));
	
	GLint fullTransformMatrixUniformLocation2 =
		glGetUniformLocation(programID, "fullTransformMatrix");

	glUniformMatrix4fv(fullTransformMatrixUniformLocation2, 1,
		GL_FALSE, &fullTransformMatrix2[0][0]);

	glDrawElements(GL_TRIANGLES, num2DIndices, GL_UNSIGNED_SHORT, (void*)(sizeof(GLushort) * num3DIndices));

	// Triangle 2
	mat4 projectionMatrix3 = glm::perspective(70.0f, ((float)width()) / height(), 0.1f, 10.0f);
	mat4 projectionTranslationMatrix3 = glm::translate(projectionMatrix3, vec3(4.0f, -1.0f, -4.0f));
	mat4 fullTransformMatrix3 = glm::rotate(projectionTranslationMatrix3, 120.0f, vec3(1.0f, 1.0f, 1.0f));

	GLint fullTransformMatrixUniformLocation3 =
		glGetUniformLocation(programID, "fullTransformMatrix");

	glUniformMatrix4fv(fullTransformMatrixUniformLocation3, 1,
		GL_FALSE, &fullTransformMatrix3[0][0]);

	glDrawElements(GL_TRIANGLES, num2DIndices, GL_UNSIGNED_SHORT, (void*)(sizeof(GLushort) * num3DIndices));
}

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string readShaderCode(const char* fileName)
{
	ifstream meInput(fileName);
	if ( ! meInput.good())
	{
		cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());
}

void installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if( ! checkShaderStatus(vertexShaderID) || ! checkShaderStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if ( ! checkProgramStatus(programID))
		return;

	glUseProgram(programID);
}

void MeGlWindow::initializeGL()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	sendDataToOpenGL();
	installShaders();
}