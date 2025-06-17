#version 400
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texc;
out vec2 tex_coord;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    tex_coord = vec2(texc.s, texc.t);
    gl_Position = projection * model * vec4(position, 1.0);
}