#include "hzpch.h"
#include "OpenGlShader.h"


#include <sstream>
#include <fstream>
#include <string> //for pareShader

#include "Glad/glad.h"
#include <glm/gtc/type_ptr.hpp>


namespace Hazel
{


	OpenGlShader::OpenGlShader(const std::string& Filepath)
		
	{

		std::string content = readFile(Filepath);

		auto shadersSource = preProcess(content);

		shaderCompile(shadersSource);



		//  shader/shader.glsl / or shader\shader.glsl
		auto lastSlash = Filepath.find_last_of("/\\"); //find_last_of ������ƥ��
		// shader.glsl
		lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash+1;

		auto lastDot = Filepath.rfind('.');
		auto count = lastDot == std::string::npos ? Filepath.size() : lastDot - lastSlash;
		m_name = Filepath.substr(lastSlash, count);


	}
	OpenGlShader::OpenGlShader(const std::string& name , const std::string& vertexsrc, const std::string& fragmentsrc)
	{
		std::unordered_map<GLenum, std::string> shaderSource;
		shaderSource[GL_VERTEX_SHADER] = vertexsrc;
		shaderSource[GL_FRAGMENT_SHADER] = fragmentsrc;

		shaderCompile(shaderSource);

		m_name = name;

	};

	OpenGlShader::~OpenGlShader()
	{

		glDeleteProgram(m_rendererID);
	}

	void OpenGlShader::shaderCompile(const std::unordered_map<GLenum, std::string>& shadersSource)
	{
		//std::vector<GLint> shaderVarry; //shaderVarry(size)ʵ����������size����ռλ,push_back�ӿ�ռλ��ʼ
		//shaderVarry.reserve(shadersSource.size());//����Ԥ��ߴ�,push_back�Դ�0��ʼ,...cherno����vector�ڶ��ϻ���Ӱ������=_=
		HZ_CORE_ASSERT(shadersSource.size() < 3,"too many kinds component shader ");
		std::array<int, 2> shaderVarry;
		uint32_t index=0;

		uint32_t program = glCreateProgram();
		for (auto& i : shadersSource)
		{
			GLint rendererID = glCreateShader(i.first);
			const GLchar* shaderSrc = i.second.c_str();//& ȡ��ַ����÷�,��������ֵ ָ�����Ǳ��洢�ı���,���������Լ��ĵ�ַ,�ұ�ֻ�Ƿ��ص�һ��ֵ����,���ᱻά��
			glShaderSource(rendererID, 1, &shaderSrc, 0);
			glCompileShader(rendererID);

			HZ_CORE_TRACE("shader type:{0} content:{1} ", i.first, i.second.c_str());


			GLint isCompiled;

			glGetShaderiv(rendererID, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(rendererID, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(rendererID, maxLength, &maxLength, &infoLog[0]);

				HZ_CORE_ERROR("OpenGl Log:{0}", infoLog.data());
				HZ_CORE_ASSERT(false, "OpenGl Error: compilate failed!", i.second);

				glDeleteShader(rendererID);
				shaderVarry[index] =(-1); // I 'm smart!!
				continue;

			}

			glAttachShader(program, rendererID);
			shaderVarry[index++]=rendererID;
			
		
		}



		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			
			for (auto& shader : shaderVarry)
			{
				glDeleteShader(shader);
			}

			m_rendererID = -1;

			HZ_CORE_ERROR("OpenGl Log:{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "OpenGl Error: Program link shader failed!");
			return;
		}

		glValidateProgram(program);

		for (auto& shader:shaderVarry)
		{
			glDetachShader(program, shader);
		}

		m_rendererID = program; //��һ����ȷ֮ǰ���� program��������	

	};


	void OpenGlShader::Bind() const
	{
	
		GLCall(glUseProgram(m_rendererID));

	};
	void OpenGlShader::UnBind() const
	{

		glUseProgram(0); // T_T	

	}

	void OpenGlShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1) HZ_CORE_WARN("uniform {0} in shader {1},didn't find",name,m_rendererID);
		GLCall(glUniform1i(location,(GLint)value)); //transPos �Ƿ�ת��

	}
	void OpenGlShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1) HZ_CORE_WARN("uniform {0} in shader {1},didn't find", name, m_rendererID);
		GLCall(glUniform1f(location, (GLfloat)value)); //transPos �Ƿ�ת��
	}
	void OpenGlShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vec)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1) HZ_CORE_WARN("uniform {0} in shader {1},didn't find", name, m_rendererID);
		GLCall(glUniform2fv(location,1,glm::value_ptr(vec))); //transPos �Ƿ�ת��
	}
	void OpenGlShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vec)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1) HZ_CORE_WARN("uniform {0} in shader {1},didn't find", name, m_rendererID);
		GLCall(glUniform3fv(location, 1, glm::value_ptr(vec)));

	}
	void OpenGlShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vec)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1) HZ_CORE_WARN("uniform {0} in shader {1},didn't find", name, m_rendererID);
		GLCall(glUniform4f(location, vec.x, vec.y, vec.z, vec.w));//�ȼ�(����Ҳ��ͬ) 4fv(location,1,float*)); 

	}
	void OpenGlShader::UploadUniformMat3(const std::string& name, const glm::mat3& mat)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1) HZ_CORE_WARN("uniform {0} in shader {1},didn't find", name, m_rendererID);
		GLCall(glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat))); //transPos �Ƿ�ת��
	}
	void OpenGlShader::UploadUniformMat4(const std::string& name, const glm::mat4& mat)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1) HZ_CORE_WARN("uniform {0} in shader {1},didn't find", name, m_rendererID);
		GLCall( glUniformMatrix4fv(location, 1, GL_FALSE,glm::value_ptr(mat))); //transPos �Ƿ�ת��
	}


	std::string OpenGlShader::readFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
			HZ_CORE_ERROR("file error: no such shader file:{0}", filepath);
		return result;

	}

	static GLenum shaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "pixel" || type == "fragment")
			return GL_FRAGMENT_SHADER;

		return 0;
	}
	std::unordered_map<GLenum,std::string> OpenGlShader::preProcess(const std::string& source)
	{
		const char* typeToken = "#type";

		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		std::unordered_map<GLenum, std::string> shaderSource;

		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);//begin from pos to find
			HZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");//eol: the end pos of the line
			size_t begin = pos + typeTokenLength + 1; //the pos after "#type"
			std::string type = source.substr(begin, eol - begin);
			HZ_CORE_ASSERT(shaderTypeFromString(type), "Invalid shader type specific");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);// ��һ������ \r\n ��λ��
			pos = source.find(typeToken, nextLinePos); //��һ��#type��λ��
			shaderSource[shaderTypeFromString(type)] = source.substr(nextLinePos, 
				(pos == std::string::npos) ? (source.size() - nextLinePos):(pos-nextLinePos)); //�о�chernoд����,������... û����һ����ֱ�ӵ���,

		}
		return shaderSource;

	}



	

}