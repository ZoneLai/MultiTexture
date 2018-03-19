const char* camera_play_frag = STRINGIFY(

precision mediump float;

uniform sampler2D   u_Texture;
uniform sampler2D   u_Texture1;
uniform float		u_MixValue;
varying vec2        v_TextCoord;

void main()
{
    vec4 v_Color0   = texture2D(u_Texture, v_TextCoord);
	vec4 v_Color1   = texture2D(u_Texture1, v_TextCoord);
	gl_FragColor    = mix(v_Color0, v_Color1, u_MixValue);
}
);