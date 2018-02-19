#ifdef GL_ES
precision mediump float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;

void main( void ) {

	vec2 pos = gl_FragCoord.xy;
	float d = dot(pos, vec2(sqrt(pos.x), sqrt(pos.y + time)));
	gl_FragColor = vec4(sin(d), cos(d), tan(d), 1.0);
}