 #version 400
 in vec2 tex_coord;
 out vec4 color;
 uniform sampler2D tex_buff;

uniform vec2 offset;

 void main()
 {
	 color = texture(tex_buff, vec2(tex_coord.x + offset.x, tex_coord.y + offset.y));
 }