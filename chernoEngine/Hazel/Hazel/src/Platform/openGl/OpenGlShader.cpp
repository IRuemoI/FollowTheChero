#include "hzpch.h"
#include "OpenGlShader.h"
#include <fstream>

#include "Glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
#include "Hazel/Core/Timer.h"


#include <shaderc/shaderc.hpp>
#include <spirv_cross/spirv_cross.hpp>
#include <spirv_cross/spirv_glsl.hpp>

namespace Hazel
{
	namespace Utils {

		static GLenum ShaderTypeFromString(const std::string& type)
		{
			if (type == "vertex")
				return GL_VERTEX_SHADER;
			if (type == "fragment" || type == "pixel")
				return GL_FRAGMENT_SHADER;

			HZ_CORE_ASSERT(false, "Unknown shader type!");
			return 0;
		}

		static shaderc_shader_kind GLShaderStageToShaderC(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:   return shaderc_glsl_vertex_shader;
			case GL_FRAGMENT_SHADER: return shaderc_glsl_fragment_shader;
			}
			HZ_CORE_ASSERT(false, "Unknown shader stage!");
			return (shaderc_shader_kind)0;
		}

		static const char* GLShaderStageToString(GLenum stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
			case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
			}
			HZ_CORE_ASSERT(false, "Unknown shader stage!");
			return nullptr;
		}

		static const char* GetCacheDirectory()
		{
			// TODO: make sure the assets directory is valid
			return "assets/cache/shader/opengl";
		}

		static void CreateCacheDirectoryIfNeeded()
		{
			std::string cacheDirectory = GetCacheDirectory();
			if (!std::filesystem::exists(cacheDirectory))
				std::filesystem::create_directories(cacheDirectory);
		}

		static const char* GLShaderStageCachedOpenGLFileExtension(uint32_t stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:    return ".cached_opengl.vert";
			case GL_FRAGMENT_SHADER:  return ".cached_opengl.frag";
			}
			HZ_CORE_ASSERT(false, "Unknown shader stage!");
			return "";
		}

		static const char* GLShaderStageCachedVulkanFileExtension(uint32_t stage)
		{
			switch (stage)
			{
			case GL_VERTEX_SHADER:    return ".cached_vulkan.vert";
			case GL_FRAGMENT_SHADER:  return ".cached_vulkan.frag";
			}
			HZ_CORE_ASSERT(false, "Unknown shader stage!");
			return "";
		}


	}



	OpenGlShader::OpenGlShader(const std::string& Filepath)
		:m_filePath(Filepath)
	{
		HZ_PROFILE_FUNCTION();

		Utils::CreateCacheDirectoryIfNeeded();

		std::string source = readFile(Filepath);
		auto shaderSources = preProcess(source);
		{
			Timer timer;
			CompileOrGetVulkanBinaries(shaderSources);
			CompileOrGetOpenGLBinaries();
			CreateProgram();
			HZ_CORE_WARN("Shader creation took {0} ms", timer.ElapsedMillis());
		}


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
		HZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSource;
		shaderSource[GL_VERTEX_SHADER] = vertexsrc;
		shaderSource[GL_FRAGMENT_SHADER] = fragmentsrc;

		shaderCompile(shaderSource);

		m_name = name;

	};

	OpenGlShader::~OpenGlShader()
	{
		HZ_PROFILE_FUNCTION();
		glDeleteProgram(m_rendererID);



	}

	void OpenGlShader::shaderCompile(const std::unordered_map<GLenum, std::string>& shadersSource)
	{

		HZ_PROFILE_FUNCTION();


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
				HZ_CORE_ASSERT(false, "OpenGl Error: compilate failed!");

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

	void OpenGlShader::CompileOrGetVulkanBinaries(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();

		shaderc::Compiler compiler;  //spirv ������ , shaderc: shadersource::
		shaderc::CompileOptions options; 
		options.SetTargetEnvironment(shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_2); //����Ŀ����뻷�� , Ŀ�껷���汾

		const bool optimize = true;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);
		//���ش�Ŷ�����spirv��������Ŀ¼ (cache/opengl)
		std::filesystem::path cacheDirectory = Utils::GetCacheDirectory(); //���ش洢shader��Ŀ¼

		auto& shaderData = m_VulkanSPIRV; //�����ʽ,���ø�ֵ m_VulkanSPIRV�����Ŷ��������Ķ��������shader ���ֽ���
		
		shaderData.clear();
		for (auto&& [stage, source] : shaderSources) //stage���Ϊ�׶λ����� ��.vert ������ .frag ƬԪ
		{
			std::filesystem::path shaderFilePath = m_filePath;

			//ƴ��shader���·��
			//shaderFilePath.filename()�ƺ�ֱ�ӷ���·��ָ���ļ���
			std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + Utils::GLShaderStageCachedVulkanFileExtension(stage)); 
			
			//ifstream in (ios::in ���� ios::binary �������ֽ���)
			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (in.is_open())
			{
				//���ù��(�������ô���,�ŵ�end ,���λ�� offset =0)
				in.seekg(0, std::ios::end);
				auto size = in.tellg();//���߹��λ��

				in.seekg(0, std::ios::beg);

				auto& data = shaderData[stage];//����Ȼ�� д�뵽shaderData
				//resize����??
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}
			//�������in(������Vulkan�������ļ�),��ô�ֳ�����,shaderData������ֱ�ӷ��Ⱥ��ġ� ->��ε�Bugԭ����,�ϴ�ʧ�ܵı����ļ�(Ϊ��)û�����,���Զ�,��û���ֳ�����,���������ǿյ�
			//�޸�����,ʧ����Ҫɾ���ļ�...����ʧ���˲����½��ļ��İ�??���ļ�����ô������??
			else
			{
				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderStageToShaderC(stage), m_filePath.c_str(), options);
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					HZ_CORE_ERROR(module.GetErrorMessage());
					HZ_CORE_ASSERT(false);
				}

				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					auto& data = shaderData[stage];
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}

		for (auto&& [stage, data] : shaderData)
			Reflect(stage, data);
	}

	void OpenGlShader::CompileOrGetOpenGLBinaries()
	{
		auto& shaderData = m_OpenGLSPIRV;

		shaderc::Compiler compiler;
		shaderc::CompileOptions options;
		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
		const bool optimize = false;
		if (optimize)
			options.SetOptimizationLevel(shaderc_optimization_level_performance);

		std::filesystem::path cacheDirectory = Utils::GetCacheDirectory();

		shaderData.clear();
		m_OpenGLSourceCode.clear();
		for (auto&& [stage, spirv] : m_VulkanSPIRV)
		{
			std::filesystem::path shaderFilePath = m_filePath;
			std::filesystem::path cachedPath = cacheDirectory / (shaderFilePath.filename().string() + Utils::GLShaderStageCachedOpenGLFileExtension(stage));

			std::ifstream in(cachedPath, std::ios::in | std::ios::binary);
			if (in.is_open())
			{
				in.seekg(0, std::ios::end);
				auto size = in.tellg();
				in.seekg(0, std::ios::beg);

				auto& data = shaderData[stage];
				data.resize(size / sizeof(uint32_t));
				in.read((char*)data.data(), size);
			}
			else
			{
				spirv_cross::CompilerGLSL glslCompiler(spirv);
				m_OpenGLSourceCode[stage] = glslCompiler.compile();
				auto& source = m_OpenGLSourceCode[stage];

				shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderStageToShaderC(stage), m_filePath.c_str());
				if (module.GetCompilationStatus() != shaderc_compilation_status_success)
				{
					HZ_CORE_ERROR(module.GetErrorMessage());
					HZ_CORE_ASSERT(false);
				}
				//���ǰѱ�����(uint32�ֽ���ɵ�������)���
				shaderData[stage] = std::vector<uint32_t>(module.cbegin(), module.cend());

				std::ofstream out(cachedPath, std::ios::out | std::ios::binary);
				if (out.is_open())
				{
					auto& data = shaderData[stage];
					out.write((char*)data.data(), data.size() * sizeof(uint32_t));
					out.flush();
					out.close();
				}
			}
		}
	}


	//CreateProgram , more step shaders -> truly rendererpipe
	void OpenGlShader::CreateProgram()
	{
		GLuint program = glCreateProgram();

		std::vector<GLuint> shaderIDs;
		for (auto&& [stage, spirv] : m_OpenGLSPIRV)
		{
			GLuint shaderID = shaderIDs.emplace_back(glCreateShader(stage));

			//3:binaryFormat :ָ���������ļ��а�������ɫ���������ļ��ĸ�ʽ
			//4:binary :ָ������Ԥ�����������ɫ��������ֽ�����ĵ�ַ��
			//5:length :ָ�����ַ�Զ�������ʽ����������ĳ��ȡ�-> �ֽ����СΪ 4���ֽ�
			glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));

			//����ָ��Ҫʹ�õ���ڵ�(ִ�п�ʼ)����Ϊ����ڵ�ʹ�õ��κ�ר�û������ṩֵ������ͨ������������ɵ�
			glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
			glAttachShader(program, shaderID);
		}

		glLinkProgram(program);

		GLint isLinked;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, infoLog.data());
			HZ_CORE_ERROR("Shader linking failed ({0}):\n{1}", m_filePath, infoLog.data());

			glDeleteProgram(program);

			for (auto id : shaderIDs)
				glDeleteShader(id);
		}


		//������Ӻ�ɾ���м������(��objһ��),ֻ����������ɵ�program
		for (auto id : shaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}

		m_rendererID = program;
	}

	//�ƺ�ֻ�Ǵ�ӡshader��Ϣ? �������Ϊģ��GPUshader���������Ϣ��ʾ?
	void OpenGlShader::Reflect(GLenum stage, const std::vector<uint32_t>& shaderData)
	{
		spirv_cross::Compiler compiler(shaderData);
		spirv_cross::ShaderResources resources = compiler.get_shader_resources();

		HZ_CORE_TRACE("OpenGLShader::Reflect - {0} {1}", Utils::GLShaderStageToString(stage), m_filePath);
		HZ_CORE_TRACE("    {0} uniform buffers", resources.uniform_buffers.size());
		HZ_CORE_TRACE("    {0} resources", resources.sampled_images.size());

		HZ_CORE_TRACE("Uniform buffers:");
		for (const auto& resource : resources.uniform_buffers)
		{
			const auto& bufferType = compiler.get_type(resource.base_type_id);
			uint32_t bufferSize = compiler.get_declared_struct_size(bufferType);
			uint32_t binding = compiler.get_decoration(resource.id, spv::DecorationBinding);
			int memberCount = bufferType.member_types.size();

			HZ_CORE_TRACE("  {0}", resource.name);
			HZ_CORE_TRACE("    Size = {0}", bufferSize);
			HZ_CORE_TRACE("    Binding = {0}", binding);
			HZ_CORE_TRACE("    Members = {0}", memberCount);
		}
	}

	std::string OpenGlShader::readFile(const std::string& filepath)
	{
		HZ_PROFILE_FUNCTION();


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


	std::unordered_map<GLenum, std::string> OpenGlShader::preProcess(const std::string& source)
	{
		HZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos); //begin from pos to find
			HZ_CORE_ASSERT(eol != std::string::npos, "Syntax error");//eol: the end pos of the line
			size_t begin = pos + typeTokenLength + 1; //the pos after "#type"
			std::string type = source.substr(begin, eol - begin);
			HZ_CORE_ASSERT(Utils::ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
			HZ_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
			pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

			shaderSources[Utils::ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
		}

		return shaderSources;

	}









	void OpenGlShader::Bind() const
	{
		HZ_PROFILE_FUNCTION();

		GLCall(glUseProgram(m_rendererID));

	};
	void OpenGlShader::UnBind() const
	{
		HZ_PROFILE_FUNCTION();

		glUseProgram(0); // T_T	

	}

	void OpenGlShader::SetMat4(const std::string& name, const glm::mat4& mat4)
	{
		HZ_PROFILE_FUNCTION();


		UploadUniformMat4(name, mat4);
	}

	void OpenGlShader::SetMat3(const std::string& name, const glm::mat3& mat3)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformMat3(name, mat3);
	}

	void OpenGlShader::SetFloat4(const std::string& name, const glm::vec4& vec4)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformFloat4(name, vec4);

	}

	void OpenGlShader::SetFloat3(const std::string& name, const glm::vec3& vec3)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformFloat3(name, vec3);

	}

	void OpenGlShader::SetFloat2(const std::string& name, const glm::vec2& vec2)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformFloat2(name, vec2);

	}

	void OpenGlShader::SetFloat(const std::string& name, float value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);

	}

	void OpenGlShader::SetInt(const std::string& name, int value)
	{
		HZ_PROFILE_FUNCTION();
		UploadUniformInt(name, value);
	}

	void OpenGlShader::SetIntArray(const std::string& name, int* value, uint32_t count)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformIntArray(name, value, count);
	}

	void OpenGlShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1) HZ_CORE_WARN("uniform {0} in shader {1},didn't find",name,m_rendererID);
		GLCall(glUniform1i(location,(GLint)value)); //transPos �Ƿ�ת��

	}

	void OpenGlShader::UploadUniformIntArray(const std::string& name, int* value, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_rendererID, name.c_str());
		if (location == -1) HZ_CORE_WARN("uniform {0} in shader {1},didn't find", name, m_rendererID);
		GLCall(glUniform1iv(location, count,value)); //transPos �Ƿ�ת��
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






	

}