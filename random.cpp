// HARDCODED CUBE
    vertex cube_vertices[] = {
        {{-1.0f, -1.0f, -1.0f, 1.0f}, {1, 0, 0, 1}, {0, 1}, {-1, 1, -1}}, 
        {{ 1.0f, -1.0f, -1.0f, 1.0f}, {0, 1, 0, 1}, {1, 1}, {1, 1, -1}},  
        {{ 1.0f,  1.0f, -1.0f, 1.0f}, {0, 0, 1, 1}, {1, 0}, {1, -1, -1}}, 
        {{-1.0f,  1.0f, -1.0f, 1.0f}, {1, 1, 0, 1}, {0, 0}, {-1, -1, -1}},
        {{-1.0f, -1.0f,  1.0f, 1.0f}, {1, 0, 1, 1}, {0, 0}, {-1, -1, 1}}, 
        {{ 1.0f, -1.0f,  1.0f, 1.0f}, {0, 1, 1, 1}, {1, 0}, {1, -1, 1}},  
        {{ 1.0f,  1.0f,  1.0f, 1.0f}, {1, 1, 1, 1}, {1, 1}, {1, 1, 1}},   
        {{-1.0f,  1.0f,  1.0f, 1.0f}, {0, 0, 0, 1}, {0, 1}, {-1, 1, 1}},
    };

    uint32_t cube_indices[36] = {

    0, 1, 2,
    0, 2, 3,
    
    5, 4, 7,
    5, 7, 6,
    
    4, 0, 3,
    4, 3, 7,
    
    1, 5, 6,
    1, 6, 2,
    
    3, 2, 6,
    3, 6, 7,

    4, 5, 1,
    4, 1, 0
    };

// FIND TRIANGLE NORMAL FUNCTION
vec3 triangle_vec3_normal (const vec3 &v1, const vec3 &v2, const vec3 &v3) {
    vec3 edge1 = vec3_sub(v2, v1);
    vec3 edge2 = vec3_sub(v3, v1);
    vec3 normal = vec3_normalize(vec3_cross_product(edge1, edge2));
    return normal;
}

// BACKCULLING FUNCTION
bool triangle_backface_cull(const vec4 &v1, const vec4 &v2, const vec4 &v3) {
    vec3 a = vec4_to_ndc(v1);
    vec3 b = vec4_to_ndc(v2);
    vec3 c = vec4_to_ndc(v3);
    return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) < 0.0f;
}

// VIEW MATRIX & PROJECTION MAXTRIX SET UP
mat4 mat4_view(const vec3& pos, const vec3& target, const vec3& up) {
    vec3 f = vec3_normalize(vec3_sub(target, pos));
    vec3 r = vec3_normalize(vec3_cross_product(up, f));
    vec3 u = vec3_cross_product(f, r);

    mat4 mat4_view = {};
    mat4_view.m[0]  = r.x;
    mat4_view.m[4]  = r.y;
    mat4_view.m[8]  = r.z;
    mat4_view.m[12] = -vec3_dot_product(r, pos);
 
    mat4_view.m[1]  = u.x;
    mat4_view.m[5]  = u.y;
    mat4_view.m[9]  = u.z;
    mat4_view.m[13] = -vec3_dot_product(u, pos);

    mat4_view.m[2]  = f.x;
    mat4_view.m[6]  = f.y;
    mat4_view.m[10] = f.z;
    mat4_view.m[14] = -vec3_dot_product(f, pos);

    mat4_view.m[3]  = 0.0f;
    mat4_view.m[7]  = 0.0f;
    mat4_view.m[11] = 0.0f;

    mat4_view.m[15] = 1.0f;

    return mat4_view;
}
mat4 mat4_perspective_projection(float fov, float aspect, float near, float far) {
    mat4 mat4_perspective_projection = {};
    float tangent_half_fov = tan(fov / 2.0f);
    
    mat4_perspective_projection.m[0]  = 1.0f / (aspect * tangent_half_fov);
    mat4_perspective_projection.m[5]  = 1.0f / tangent_half_fov;
    mat4_perspective_projection.m[10] = far / (far - near);
    mat4_perspective_projection.m[11] = 1.0f;
    mat4_perspective_projection.m[14] = -(far * near) / (far - near);
    
    return mat4_perspective_projection;
}
