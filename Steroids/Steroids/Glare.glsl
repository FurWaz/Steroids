#version 130

uniform sampler2D texture;
float threshold = 0.1;
float texture_inverse = 0.003;
uniform float multiply = 0.3;
int blur_radius = 4;

void main() {
    vec3 current_color = texture2D(texture, gl_TexCoord[0].xy).rgb;
    vec4 pixel =  vec4(0.0, 0.0, 0.0, 1.0);
    float brightness = dot(current_color.rgb, vec3(0.2126, 0.7152, 0.0722));
    if (brightness >= threshold){
        pixel = texture2D(texture, gl_TexCoord[0].xy);
    }

    vec4 sum = pixel;
    for (int i = 0; i < blur_radius; ++i){
        sum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2(1, 0));
        sum += texture2D(texture, gl_TexCoord[0].xy - (i * texture_inverse) * vec2(1, 0));
        sum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2(0, 1));
        sum += texture2D(texture, gl_TexCoord[0].xy - (i * texture_inverse) * vec2(0, 1));
        sum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2(0.7, 0.7));
        sum += texture2D(texture, gl_TexCoord[0].xy - (i * texture_inverse) * vec2(0.7, 0.7));
        sum += texture2D(texture, gl_TexCoord[0].xy + (i * texture_inverse) * vec2(-0.7, 0.7));
        sum += texture2D(texture, gl_TexCoord[0].xy - (i * texture_inverse) * vec2(-0.7, 0.7));
    }
    gl_FragColor = sum * multiply / (blur_radius * 8 + 1);
}