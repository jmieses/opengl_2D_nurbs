#include "Shader.h"
#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

static const char* vertex_shader_source = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
static const char* fragment_shader_source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

static const char* vertex_shader_source_2 = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
static const char* fragment_shader_source_2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

// Shader::Shader(const char* vertex_shader, const char* fragment_shader){
// 	int verShader = glCreateShader(GL_VERTEX_SHADER);
//     int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
//     shader_id = glCreateProgram();

//     BuildShader(verShader, fragShader, vertex_shader, fragment_shader);
//     LinkShader(verShader, fragShader, shader_id);
// }

Shader::Shader(const char * vertex_shader_path, const char * fragment_shader_path){
	// 1. Retrieve the vertex/fragment source code from the file path.
	std::string vertex_code;
	std::string fragment_code;
	std::ifstream vertex_shader_file;
	std::ifstream fragment_shader_file;
	// enable ifstream exceptions
	vertex_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragment_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try{
		// open files
		vertex_shader_file.open(vertex_shader_path);
		fragment_shader_file.open(fragment_shader_path);
		std::stringstream vertex_shader_stream, fragment_shader_stream;
		// read file's buffer content into streams
		vertex_shader_stream << vertex_shader_file.rdbuf();
		fragment_shader_stream << fragment_shader_file.rdbuf();
		// close file handlers
		vertex_shader_file.close();
		fragment_shader_file.close();
		// convert stream into string
		vertex_code = vertex_shader_stream.str();
		fragment_code = fragment_shader_stream.str();
	}
	catch(std::ifstream::failure& e){
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n"; 
	}
	const char * vertex_shader_code = vertex_code.c_str();
	const char * fragment_shader_code = fragment_code.c_str();
	// 2. Compile shaders
	unsigned int vertex, fragment;
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_shader_code, NULL);
	glCompileShader(vertex);
	CheckCompilerErrors(vertex, "VERTEX");
	// fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_shader_code, NULL);
	glCompileShader(fragment);
	CheckCompilerErrors(fragment, "FRAGMENT");
	// shader program
	shader_id = glCreateProgram();
	glAttachShader(shader_id, vertex);
	glAttachShader(shader_id, fragment);
	glLinkProgram(shader_id);
	//CheckCompilerErrors(shader_id, "PROGRAM");
	// delete shaders after the've been linked.
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::CheckCompilerErrors(unsigned int shader, std::string type){
	int success;
	char infoLog[1024];
	if(type != "PROGRAM"){
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success){
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << '\n' << infoLog << "n -- ------------------------------ --\n";
		}
	}else{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if(!success){
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_LINKING_ERROR of type: " << type << '\n' << infoLog << "n -- ------------------------------ --\n";
		}
	}
}

void Shader::Use() const{
	glUseProgram(shader_id);
}

void Shader::BuildShader(int vertexShader, int fragmentShader, const char* vertex_shader, const char* fragment_shader) {
    int success;
    char infoLog[512];

    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
   
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Shader::LinkShader(int vertexShader, int fragmentShader, int shaderProgram) {
    int success;
    char infoLog[512];
    // link shaders

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}