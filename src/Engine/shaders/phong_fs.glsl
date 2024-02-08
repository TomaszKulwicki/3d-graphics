#version 460

layout(location=0) out vec4 vFragColor;

#if __VERSION__ > 410
layout(std140, binding=0) uniform Modifiers {
#else
    layout(std140) uniform Color {
    #endif
    vec4 Kd;
    vec4 Ks;
    vec4 Ka;
    bool use_map_Kd;
    float Ns;
};

in vec2 vertex_texcoords;
in vec4 vertex_position;
in vec3 vertex_normals;

in vec3 vertex_normals_in_vs;
in vec3 vertex_coords_in_vs;

uniform sampler2D map_Kd;

const int MAX_POINT_LIGHTS=24;

struct PointLight {
    vec3 position_in_ws_space;
    vec3 position_in_vs_space;
    vec3 color;
    float intensity;
    float radius;
} ;

layout(std140) uniform Lights {
    vec3 ambient;
    uint n_p_lights;
    PointLight p_light[MAX_POINT_LIGHTS];
};

void main() {
    if (use_map_Kd) {
        vFragColor = Kd*texture(map_Kd, vertex_texcoords);
    }
    else{

        vec3 normal = normalize(vertex_normals);
        vec3 diffuseLight = vec3(0.0f, 0.0f, 0.0f);
        vec3 specularLight= vec3(0.0f, 0.0f, 0.0f);

        for(uint i = 0u; i < n_p_lights; i++)
        {
            vec3 lightDirection = normalize(p_light[i].position_in_vs_space - vertex_coords_in_vs);
            float diffuse = max(dot(normal, lightDirection), 0.0f);
            diffuseLight += diffuse*p_light[i].color*p_light[i].intensity;

            vec3 viewDirection = -normalize(vertex_coords_in_vs);
            vec3 reflectDirection = reflect(-lightDirection, normal);
            float specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), Ns);
            specularLight += specular * Ks.rgb;
        }

        vFragColor.a = Kd.a;
        vFragColor.rgb = Kd.rgb * (diffuseLight+ambient+specularLight);

    }

}