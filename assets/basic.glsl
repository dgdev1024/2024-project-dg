#shader vertex
#version 450 core

layout (location = 0) in vec3 in_Position;

void main ()
{
  gl_Position = vec4(in_Position, 1.0);
}

#shader fragment
#version 450 core

uniform vec4 uni_FragColor;
out vec4 out_FragColor;

void main ()
{
  out_FragColor = uni_FragColor;
}
