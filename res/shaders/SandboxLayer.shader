 #shader vertex
 #version 330 core

 layout(location = 0) in vec4 position;
 layout(location = 1) in vec4 a_Color;
 layout(location = 2) in vec2 a_Texture;
 layout(location = 3) in float a_TexIndex;

 out vec4 v_Color;
 out vec2 v_Texture;
 out float v_TexIndex;
 void main()
 {
     v_Color = a_Color;
     v_Texture = a_Texture;
     v_TexIndex = a_TexIndex;
     gl_Position =  position;
 };

 #shader fragment
 #version 330 core

 layout(location = 0) out vec4 color;
 in vec4 v_Color;
 in vec2 v_Texture;
 in float v_TexIndex;

 uniform sampler2D u_Textures[2];
 void main()
 {
    int index = int(v_TexIndex);
    color = texture(u_Textures[index],v_Texture);
 };