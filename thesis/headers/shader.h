#ifndef SHADER_H
#define SHADER_H

#include "useful_headers.h"

class Shader {

public:
	// Program ID
	unsigned int ID = 0;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);

private:

	void checkCompileErrors(unsigned int obj, std::string type);

};

#endif

