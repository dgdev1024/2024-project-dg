#shader vertex
#version 450 core

layout (location = 0) in vec3  in_Position;
layout (location = 1) in vec2  in_TexCoords;
layout (location = 2) in vec4  in_Color;
layout (location = 3) in float in_TexIndex;
layout (location = 4) in float in_EntityId;

uniform mat4 uni_CameraProduct = mat4(1.0);

     out vec2 var_TexCoords;
flat out int  var_TexIndex;
     out vec4 var_Color;
flat out int  var_EntityId;

void main ()
{
  gl_Position = uni_CameraProduct * vec4(in_Position, 1.0);
  var_TexCoords = in_TexCoords;
  var_TexIndex = int(in_TexIndex);
  var_Color = in_Color;
  var_EntityId = int(in_EntityId);
}


#shader fragment
#version 450 core

     in vec2 var_TexCoords;
flat in int  var_TexIndex;
     in vec4 var_Color;
flat in int  var_EntityId;

uniform sampler2D uni_TexSlots[16];

layout (location = 0) out vec4 out_Color;
layout (location = 1) out int  out_EntityId;

void main ()
{
  vec4 textureColor = vec4(1.0);

  switch (var_TexIndex) {
    case 1:  textureColor = texture(uni_TexSlots[1],  var_TexCoords); break;
    case 2:  textureColor = texture(uni_TexSlots[2],  var_TexCoords); break;
    case 3:  textureColor = texture(uni_TexSlots[3],  var_TexCoords); break;
    case 4:  textureColor = texture(uni_TexSlots[4],  var_TexCoords); break;
    case 5:  textureColor = texture(uni_TexSlots[5],  var_TexCoords); break;
    case 6:  textureColor = texture(uni_TexSlots[6],  var_TexCoords); break;
    case 7:  textureColor = texture(uni_TexSlots[7],  var_TexCoords); break;
    case 8:  textureColor = texture(uni_TexSlots[8],  var_TexCoords); break;
    case 9:  textureColor = texture(uni_TexSlots[9],  var_TexCoords); break;
    case 10: textureColor = texture(uni_TexSlots[10], var_TexCoords); break;
    case 11: textureColor = texture(uni_TexSlots[11], var_TexCoords); break;
    case 12: textureColor = texture(uni_TexSlots[12], var_TexCoords); break;
    case 13: textureColor = texture(uni_TexSlots[13], var_TexCoords); break;
    case 14: textureColor = texture(uni_TexSlots[14], var_TexCoords); break;
    case 15: textureColor = texture(uni_TexSlots[15], var_TexCoords); break;
    default: break;
  }

  out_Color = textureColor * var_Color;
  out_EntityId = var_EntityId;
}