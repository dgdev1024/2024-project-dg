#shader vertex
#version 450 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_TexCoords;

out vec2 var_TexCoords;

void main ()
{
  gl_Position = vec4(in_Position, 1.0);
  var_TexCoords = in_TexCoords;
}

#shader fragment
#version 450 core

in vec2 var_TexCoords;
uniform sampler2D uni_Texture;
out vec4 out_FragColor;

void main ()
{
  out_FragColor = texture(uni_Texture, var_TexCoords);
}
