/** @file DG/OpenGL/GLShader.cpp */

#include <DG/Core/FileIo.hpp>
#include <DG/OpenGL/GLShader.hpp>

namespace dg
{

  Shared<Shader> Shader::make (const Path& path)
  {
    return std::make_shared<OpenGL::ShaderImpl>(path);
  }

  Shared<Shader> Shader::make (const String& vertexCode, const String& fragmentCode)
  {
    return std::make_shared<OpenGL::ShaderImpl>(vertexCode, fragmentCode);
  }

}

namespace dg::OpenGL
{

  ShaderImpl::ShaderImpl (const Path& path) :
    Shader {}
  {
    String* codePtr = nullptr;

    bool result = FileIo::loadTextFile(
      path,
      [&] (StringView line, Index number)
      {
        if (line.starts_with("#shader ")){
          if (line.ends_with("vertex")) { codePtr = &m_vertexCode; }
          else if (line.ends_with("fragment")) { codePtr = &m_fragmentCode; }
          else {
            DG_ENGINE_ERROR("Invalid #shader directive.");
            return false;
          }
        } else {
          if (codePtr == nullptr) {
            DG_ENGINE_ERROR("No #shader directive set.");
            return false;
          } else {
            *codePtr += line;
            *codePtr += "\n";
          }
        }

        return true;
      }
    );

    if (result == false) {
      DG_ENGINE_ERROR("Could not parse GLSL shader file '{}'.", path);
      return;
    }

    m_valid = build();
    if (m_valid == false) {
      DG_ENGINE_ERROR("Could not build GLSL shader from file '{}'.", path);
    }
  }

  ShaderImpl::ShaderImpl (const String& vertexCode, const String& fragmentCode) :
    Shader {},
    m_vertexCode { vertexCode },
    m_fragmentCode { fragmentCode }
  {
    m_valid = build();
    if (m_valid == false) {
      DG_ENGINE_ERROR("Could not build GLSL shader from source code.");
    }
  }

  ShaderImpl::~ShaderImpl ()
  {
    glDeleteProgram(m_handle);
  }

  void ShaderImpl::bind () const
  {
    glUseProgram(m_handle);
  }

  void ShaderImpl::unbind () const
  {
    glUseProgram(0);
  }

  bool ShaderImpl::setInteger (const String& key, I32 value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);

    glUniform1i(uniform, value);
    return true;
  }

  bool ShaderImpl::setUnsignedInteger (const String& key, U32 value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);

    glUniform1ui(uniform, value);
    return true;
  }

  bool ShaderImpl::setFloat (const String& key, F32 value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);

    glUniform1f(uniform, value);
    return true;
  }

  bool ShaderImpl::setDouble (const String& key, F64 value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);

    glUniform1d(uniform, value);
    return true;
  }

  bool ShaderImpl::setBoolean (const String& key, bool value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);

    glUniform1i(uniform, value);
    return true;
  }

  bool ShaderImpl::setVector2i (const String& key, const Vector2i& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform2i(uniform, value.x, value.y);
    return true;    
  }

  bool ShaderImpl::setVector2u (const String& key, const Vector2u& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform2ui(uniform, value.x, value.y);
    return true;    
  }

  bool ShaderImpl::setVector2f (const String& key, const Vector2f& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform2f(uniform, value.x, value.y);
    return true;    
  }

  bool ShaderImpl::setVector2d (const String& key, const Vector2d& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform2d(uniform, value.x, value.y);
    return true;    
  }

  bool ShaderImpl::setVector2b (const String& key, const Vector2b& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform2i(uniform, value.x, value.y);
    return true;    
  }

  bool ShaderImpl::setVector3i (const String& key, const Vector3i& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform3i(uniform, value.x, value.y, value.z);
    return true;    
  }

  bool ShaderImpl::setVector3u (const String& key, const Vector3u& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform3ui(uniform, value.x, value.y, value.z);
    return true;    
  }

  bool ShaderImpl::setVector3f (const String& key, const Vector3f& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform3f(uniform, value.x, value.y, value.z);
    return true;    
  }

  bool ShaderImpl::setVector3d (const String& key, const Vector3d& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform3d(uniform, value.x, value.y, value.z);
    return true;    
  }

  bool ShaderImpl::setVector3b (const String& key, const Vector3b& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform3i(uniform, value.x, value.y, value.z);
    return true;    
  }

  bool ShaderImpl::setVector4i (const String& key, const Vector4i& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform4i(uniform, value.x, value.y, value.z, value.w);
    return true;    
  }

  bool ShaderImpl::setVector4u (const String& key, const Vector4u& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform4ui(uniform, value.x, value.y, value.z, value.w);
    return true;    
  }

  bool ShaderImpl::setVector4f (const String& key, const Vector4f& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform4f(uniform, value.x, value.y, value.z, value.w);
    return true;    
  }

  bool ShaderImpl::setVector4d (const String& key, const Vector4d& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform4d(uniform, value.x, value.y, value.z, value.w);
    return true;    
  }

  bool ShaderImpl::setVector4b (const String& key, const Vector4b& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniform4i(uniform, value.x, value.y, value.z, value.w);
    return true;    
  }

  bool ShaderImpl::setMatrix2f (const String& key, const Matrix2f& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniformMatrix2fv(uniform, 1, GL_TRUE, value.getPointer());
    return true;   
  }

  bool ShaderImpl::setMatrix3f (const String& key, const Matrix3f& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniformMatrix3fv(uniform, 1, GL_TRUE, value.getPointer());
    return true;  
  }

  bool ShaderImpl::setMatrix4f (const String& key, const Matrix4f& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniformMatrix4fv(uniform, 1, GL_TRUE, value.getPointer());
    return true;  
  }

  bool ShaderImpl::setMatrix2d (const String& key, const Matrix2d& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniformMatrix2dv(uniform, 1, GL_TRUE, value.getPointer());
    return true;  
  }

  bool ShaderImpl::setMatrix3d (const String& key, const Matrix3d& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniformMatrix2dv(uniform, 1, GL_TRUE, value.getPointer());
    return true;  
  }

  bool ShaderImpl::setMatrix4d (const String& key, const Matrix4d& value)
  {
    if (m_valid == false || m_handle == 0) {
      DG_ENGINE_THROW(std::runtime_error,
        "Attempt to set uniform on an invalid shader!");
    }

    I32 uniform = findUniform(key);
    if (uniform == -1) { return false; }

    glUseProgram(m_handle);
    
    glUniformMatrix2dv(uniform, 1, GL_TRUE, value.getPointer());
    return true;  
  }

  bool ShaderImpl::build ()
  {
    // The length of the status info log string.
    static constexpr I32 INFO_LOG_LENGTH = 512;

    // Ensure that both vertex and fragment shader code was provided.
    if (m_vertexCode.empty()) {
      DG_ENGINE_ERROR("No vertex shader code provided.");
      return false;
    } else if (m_fragmentCode.empty()) {
      DG_ENGINE_ERROR("No fragment shader code provided.");
      return false;
    }

    // Keep track of a status code and an info log.
    I32 status = 0;
    Char infoLog[INFO_LOG_LENGTH];

    // We will need the C-string forms of the shader's source code strings.
    const Char* vertexCode = m_vertexCode.c_str();
    const Char* fragmentCode = m_fragmentCode.c_str();

    // Begin by compiling the vertex shader code, then check the compilation
    // status.
    U32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCode, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(vertexShader, INFO_LOG_LENGTH, nullptr, infoLog);
    if (status != GL_TRUE) {
      DG_ENGINE_ERROR("Error compiling GLSL vertex shader: {}", infoLog);
      glDeleteShader(vertexShader);
      return false;
    } else if (infoLog[0] != '\0') {
      DG_ENGINE_WARN("GLSL vertex shader compiled with warning: {}", infoLog);
    }

    // Repeat this now for the fragment shader.
    U32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(fragmentShader, INFO_LOG_LENGTH, nullptr, infoLog);
    if (status != GL_TRUE) {
      DG_ENGINE_ERROR("Error compiling GLSL fragment shader: {}", infoLog);
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);
      return false;
    } else if (infoLog[0] != '\0') {
      DG_ENGINE_WARN("GLSL fragment shader compiled with warning: {}", infoLog);
    }

    // Next, create the shader program and attach the above-compiled shaders
    // to it.
    U32 shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link the program, then check status.
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    glGetProgramInfoLog(shaderProgram, INFO_LOG_LENGTH, nullptr, infoLog);
    if (status != GL_TRUE) {
      DG_ENGINE_ERROR("Error linking GLSL shader program: {}", infoLog);
      glDeleteProgram(shaderProgram);
      glDeleteShader(vertexShader);
      glDeleteShader(fragmentShader);
      return false;
    } else if (infoLog[0] != '\0') {
      DG_ENGINE_WARN("GLSL shader program linked with warning: {}", infoLog);
    }

    // Delete the shader objects now.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Now that the new shader program has been successfully built, if there was another shader
    // program present, delete that program now.
    if (m_handle != 0) {
      glDeleteProgram(m_handle);
    }

    m_handle = shaderProgram;
    return true;     
  }

  I32 ShaderImpl::findUniform (StringView key)
  {
    if (isValid() == false || key.empty()) { return -1; }
    return glGetUniformLocation(m_handle, key.data());    
  }

}
