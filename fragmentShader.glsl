in vec2 TexCoord;

uniform sampler2D texture;

void main()
{
    vec4 reverseTexture2 = texture(texture, TexCoord);
}