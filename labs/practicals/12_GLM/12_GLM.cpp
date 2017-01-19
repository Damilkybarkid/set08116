#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\projection.hpp>
#include <iostream>

using namespace std;
using namespace glm;

int main() {

	//12.1.1
	vec2 u(1.0, 0.0);
	vec2 v(2.0, 0.0);
	vec3 w(1.0, 0.0, 0.0);
	vec3 x(2.0, 0.0, 0.0);
	vec4 y(1.0, 0.0, 0.0, 0.0);
	vec4 z(2.0, 0.0, 0.0, 0.0);

	vec2 a(vec3(1.0, 0.0, 0.0));
	vec2 b(vec4(2.0, 0.0, 0.0, 0.0));
	vec3 c(vec4(1.0, 0.0, 0.0, 0.0));
	vec3 d(0.0, vec2(2.0, 0.0));
	vec4 e(1.0, vec3(0.0, 0.0, 0.0));
	vec4 f(2.0, 0.0, vec2(0.0, 0.0));

	float x = u.x;
	u.y = 10.0f;

	//12.1.2
	vec2 u(1.0, 0.0);
	vec2 v(2.0, 0.0);
	vec3 w(1.0, 0.0, 0.0);
	vec3 x(2.0, 0.0, 0.0);
	vec4 y(1.0, 0.0, 0.0, 0.0);
	vec4 z(2.0, 0.0, 0.0, 0.0);

	vec2 a = u + v;
	vec2 b = u - v;
	vec3 c = w + x;
	vec3 d = w - x;
	vec4 e = y + z;
	vec4 f = y - z;

	//12.1.3
	vec2 u(1.0f, 0.0f);
	vec2 v(2.0f, 0.0f);
	vec3 w(1.0f, 0.0f, 0.0f);
	vec3 x(2.0f, 0.0f, 0.0f);
	vec4 y(1.0f, 0.0f, 0.0f, 0.0f);
	vec4 z(2.0f, 0.0f, 0.0f, 0.0f);

	vec2 a = 5.0f * u;
	vec2 b = u / 5.0f;
	vec3 c = 5.0f * w;
	vec3 d = w / 5.0f;
	vec4 e = 5.0f * y;
	vec4 f = y / 5.0f;

	//12.1.4
	float l2d = length(u);
	float l3d = length(w);
	float l4d = length(y);

	//12.1.5
	vec2 n2d = normalize(u);
	vec3 n3d = normalize(w);
	vec4 n4d = normalize(y);

	//12.1.6
	float d2d = dot(u, v);
	float d3d = dot(w, x);
	float d4d = dot(y, z);

	vec2 p2d = proj(u, v);
	vec3 p3d = proj(w, x);
	vec4 p4d = proj(y, z);

	//12.1.7
	vec3 c3d = cross(w, x);

	//12.2.1
	mat4 m(1.0f);
	mat4 o(3.0f);

	mat3 n(mat4(1.0f));

	//12.2.2
	mat4 ma = m + o;

	//12.2.3
	mat4 ms = 5.0f * m;
	mat4 os = o / 5.0f;

	//12.2.4
	mat4 mm = m * o;

	vec4 my = m * y;

	//12.3.1
	mat4 t = translate(mat4(1.0f), vec3(x, y, z));

	vec4 tt = t * vec4(w, 1.0f);

	//12.3.2
	float pi = radians(180);
	mat4 Rx = rotate(mat4(1.0f), pi/2, vec3(1.0f, 0.0f, 0.0f));

	vec4 rr = Rx * vec4(w, 1.0f);

}