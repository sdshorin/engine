#version 410 core

out vec4 FragColor;

in vec3 vertex_color;  
// in vec2 uv;  
// uniform sampler2D texture_1;
// uniform float mix_scale;

void main()
{
 
    // vec2 face_coord = vec2(1-uv.x, uv.y);
    // if (mix_scale > 0)
	//     FragColor = mix(texture(texture_1, uv), vec4(vertex_color, 1.0), mix_scale);
    // else
    FragColor = vec4(vertex_color, 1.0);



    // FragColor = vec4(vertex_color, 1.0);
} 

