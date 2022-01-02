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
	void setVec3(const std::string& name, const glm::vec3& value);
	void setVec4(const std::string& name, const glm::vec4& value);
	void setMat3(const std::string& name, const glm::mat3& mat);
	void setMat4(const std::string& name, const glm::mat4& mat);


private:

	void checkCompileErrors(unsigned int obj, std::string type);

};

#endif

