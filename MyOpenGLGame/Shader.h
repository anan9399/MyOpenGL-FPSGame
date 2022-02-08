#pragma once

#include<string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;

	enum Slot
	{
		DIFFUSE,
		SPECULAR,
		EMISSION
	};

	void use();
	void stop();
	void setUniform1f(const std::string& name, float value) const;
	void setUniform1i(const std::string& name, int slot) const;
	void setUniform3f(const std::string& name, const glm::vec3 value) const;
	void setUniform4f(const std::string& name, const glm::vec4 value) const;
	void setUniform4m(const std::string& name, const glm::mat4& mat) const;
	

};
