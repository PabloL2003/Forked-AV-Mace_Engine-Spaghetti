#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normals;

out vec2 v_TexCoord;
out vec3 v_Normals;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
	v_Normals = normals;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normals;

uniform sampler2D u_Texture;
uniform bool u_HasTexture;

void main()
{
	if(u_HasTexture){
		vec4 texColor = texture(u_Texture, v_TexCoord);
		color = texColor;
		//color = vec4(v_Normals, 1.0); //debug normals
	}else{
		color = vec4(0.8, 0.8, 0.8, 1.0);
	}
};