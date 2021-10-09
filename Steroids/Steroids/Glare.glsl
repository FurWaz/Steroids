#version 130

uniform sampler2D texture;
uniform float texture_inverse = 0.002;
uniform float multiply = 0.3;
float blur_radius = 8;

void main() {
    vec4 sum = texture2D(texture, gl_TexCoord[0].xy);

    for (float i = 0; i < blur_radius; i++) {
        vec4 psum = vec4(0.0, 0.0, 0.0, sum.a);
        psum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2( 1,  0) * 0.5);
        psum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2(-1,  0) * 0.5);
        psum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2( 0, -1) * 0.5);
        psum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2( 0,  1) * 0.5);
        psum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2(-0.7,  0.7));
        psum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2(-0.7, -0.7));
        psum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2( 0.7, -0.7));
        psum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2( 0.7,  0.7));
        float mult = (blur_radius-i) / blur_radius*0.5;
        sum += mult * psum;
    }
    gl_FragColor = sum * multiply / blur_radius;
}