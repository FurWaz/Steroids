#version 130

uniform sampler2D texture;
uniform vec2 blur_radius = vec2(1, 1);

void main() {
    gl_FragColor = texture2D(texture, gl_TexCoord[0].xy);
}