attribute vec3 position;
attribute vec4 color;
uniform mat4 matrix;
varying vec4 frag_color;

void main(void)
{
    gl_Position = matrix * vec4(position, 1);
    frag_color = color;
}
