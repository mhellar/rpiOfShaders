#ifdef GL_ES
precision highp float;
#endif

#extension GL_OES_standard_derivatives : enable

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

vec2 rotate(vec2 p, float ang){
    float c = cos(ang), s = sin(ang);
    return vec2(p.y * c - p.x * s, p.y * s + p.x * c);
}

void main( void ) {

	vec2 p = 1.0*( gl_FragCoord.xy / resolution.xy )-0.5;
	p=rotate(p,time);
	p*=(20.0+80.0*mouse.x);
	p*=sin(p.x)+cos(p.y);
	vec2 pp=vec2(p.x,p.y);
	pp=rotate(pp,time*2.0);
	
	vec3 cc=vec3(sin(pp.x),cos(pp.y),pp.x+pp.y);
	
	gl_FragColor = vec4( cc, 1.0 );

}