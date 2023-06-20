/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : frag.glsl
 * PURPOSE     : Fragment shader.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#version 420

layout(location = 0) out vec4 OutColor; // --> gl_FragColor;

in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawNormal;
in vec2 DrawTexCoord;

uniform vec3 Ka, Kd, Ks;
uniform float Ph;
uniform float Trans;

/*
uniform mat4 ShadowMatr;
uniform vec3 LightDir, LightColor;
*/

/*
layout(binding = 0) uniform sampler2D Texture0;
layout(binding = 8) uniform sampler2D ShadowMap;
uniform bool IsTexture0;
*/

uniform float GlobalTime;
uniform float Time;
uniform vec3 CamLoc;

vec3 Shade( vec3 P, vec3 N, vec3 L, vec3 LColor )
{
  vec3 color = vec3(0);
  vec3 V = normalize(P - CamLoc);
  L = normalize(L);
  N = normalize(N);

  // Ambient
  color += min(vec3(0.1), Ka);

  // Duffuse
  float nl = dot(N, L);
  if (nl > 0)
  {
    vec3 diff = LColor * Kd * nl;
    /*
    if (IsTexture0)
      diff *= texture(Texture0, DrawTexCoord).rgb;
    */
    color += diff;

    // Specular
    vec3 R = reflect(V, N);
    float rl = dot(R, L);
    if (rl > 0)
      color += LColor * Ks * pow(rl, Ph);
  }
  return color;
}

/* Shader entry point */
void main( void )
{
  vec3 color = DrawColor.rgb * Shade(DrawPos, DrawNormal, LightDir, LightColor);
  OutColor = vec4(color * sh, Trans);
} /* End of 'main' function */

/* END OF 'frag.glsl' FILE */
