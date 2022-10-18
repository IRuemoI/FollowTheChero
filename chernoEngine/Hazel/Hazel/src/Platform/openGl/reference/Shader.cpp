#include "Shader.h"
#include <fstream> //for read file
#include <string> //for getline
#include <sstream> // for string stream
#include "Hazel/Renderer/renderer.h"


namespace Hazel
{
	
	
	
	Shader::Shader(const std::string& CodeFilePath)
		:m_Filepath(CodeFilePath),m_renderer(0)
	{
		auto[vertexshader, fragmentshader]= parseShader(CodeFilePath); //vsdebugʱ��Բ������Թ���Ŀ¼(.vcxproj)
		m_renderer = createshader(vertexshader, fragmentshader);
	
	}
	
	Shader::~Shader()
	{
		GLCall(glDeleteProgram(m_renderer));
	}
	
	void Shader::Bind() const
	{
		GLCall(glUseProgram(m_renderer));
	
	}
	
	void Shader::Unbind()const
	{
		GLCall(glUseProgram(0));
	
	}
	
	std::tuple<std::string, std::string> Shader::parseShader(const std::string& filepath)
	{
		enum class shadertype
		{
			NONE = -1, vertex, fragment
		};
	
		shadertype type = shadertype::NONE;
	
		std::ifstream stream(filepath);
		std::stringstream ss[2];
		std::string line;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)//��������Чλ��
			{
				if (line.find("vertex") != std::string::npos)
					//todo:set mode to vertex
					type = shadertype::vertex;
				else if (line.find("fragment") != std::string::npos)
					//...
					type = shadertype::fragment;
			}
			else
			{
				ss[(int)type] << line << "\n";
	
			}
		}
	
		return { ss[0].str(),ss[1].str() };
	
	}
	
	unsigned int Shader::createshader(const std::string& vertexshader, const std::string& fragmentshader)
	{
		//��Դ�뵱���ַ���������,���ᵽһ����ɫ������,�������Ǹ�����(shader)��id
		GLCall(unsigned int program = glCreateProgram());
		unsigned int vs = CompileShader(vertexshader, GL_VERTEX_SHADER);//0xb831����һ��16λint
		unsigned int fs = CompileShader(fragmentshader, GL_FRAGMENT_SHADER);//compile���������м��shader�ļ�
		//����Զ�̲ٿ�GPU,ԭʼ��GPU,����д��Դ��,������Ҫ�ֶ���������
		glAttachShader(program, vs);
		glAttachShader(program, fs);//���ǵĹ�������������ɫ��
		glLinkProgram(program);
		glValidateProgram(program);//validate ��׼,ʹ��Ч;�����Ѿ����Ӳ�����
	
		glDeleteShader(vs);//���ӵ�program��,�����Ѿ�����Ҫ�м��shader�ļ�(Դ��)��
		glDeleteShader(fs);//����cherno��ϲ��,�������õ���,��������Ҳ����
	
		return program;
	}
	
	void Shader::SetUniform4f(const std::string name, float v0, float v1, float v2, float v3)
	{
		GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
	
	}
	void Shader::SetUniformMat4f(const std::string name, const glm::mat4& mat)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));//4f v : vector/array
		//location
		//count:1
		//�Ƿ���Ҫת��(Ϊ���Ų�)
		//float��ַ
	
	}
	void Shader::SetUniform1f(const std::string name, float v0)
	{
		GLCall(glUniform1f(GetUniformLocation(name), v0));
	
	}
	void Shader::SetUniform1i(const std::string name, int v0)
	{
		GLCall(glUniform1i(GetUniformLocation(name), v0));
	
	}
	void Shader::SetUniform1iv(const std::string name,int size,int* v)
	{
		GLCall(glUniform1iv(GetUniformLocation(name),size,v));
	}
	
	int Shader::GetUniformLocation(const std::string& name) const
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];
	
		GLCall(int u_color_location = glGetUniformLocation(m_renderer,name.c_str()));
		//c_str()��������һ��ָ������C�ַ�����ָ�볣��,��c����,ͬʱ�� const GLchar* ����ת��
		//ASSERT(u_color_location != -1); //����
		//����������Ϊ, -1,�Ҳ�����ʱҲ����
		if (u_color_location == -1)
			std::cout << "warning: Uniform "<<'*'<< name <<'*'<< " don't exist " << std::endl;
		
		m_UniformLocationCache[name] = u_color_location;
		return u_color_location;
	
	}
	
	unsigned int  Shader::CompileShader(const std::string& source, unsigned int type)
	{
		GLCall( unsigned int id = glCreateShader(type));
		const char* src = source.c_str(); //����һ����null��β�Ĳ��ɱ������ָ��,������source������,srcҲ��Ч
		GLCall(glShaderSource(id, 1, &src, NULL));
		GLCall(glCompileShader(id));
		//��shader�����Դ�� (id , 
		//Դ���ַ�������, 
		//Դ��stringͷָ���ָ��(��Ϊ��ʱ�����ַ�������) , 
		//һ����������ָ��,����ָ����Ӧ�ַ�����ȡ����(NullĬ���Կս�β,ȫ��һֱ����),<=0��ʾȫ�������0)
		//TODO:cpmile error
		int result;
		GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result)); //�õ�shader�������״̬, i int(id)? v :һ��ʸ��(����)
		if (result == GL_FALSE)
		{
	
			int length;
			GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
			//char message[length]; //length��һ������,�����ڶ������������ڴ�,��ջ�ϲ���ֱ������
			char* message = (char*)alloca(length * sizeof(char)); //cherno�ط�,alloca c����,������ջ�϶�̬�����ڴ�
			GLCall(glGetShaderInfoLog(id, length, &length, message));//���log;
			std::cout << "failed in " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader compiling" << std::endl;
			std::cout << message << std::endl;
			GLCall(glDeleteShader(id));
			return 0;
		}
		return id;
	}
}

