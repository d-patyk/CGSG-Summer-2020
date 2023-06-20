/***************************************************************
 * Copyright (C) 2020-3030
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE NAME   : vert.glsl
 * PURPOSE     : Vertex shader.
 * PROGRAMMER  : Dmitriy Patyk.
 * LAST UPDATE : 31.07.2020
 * NOTE        : dpgl
 *
 * No part of this file may be changed without agreement of 
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */
#version 420

layout(location = 0) in vec3 InPosition;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec3 InNormal;
layout(location = 3) in vec4 InColor;

uniform mat4 MatrWVP;
uniform mat4 MatrW;

uniform float Time;

out vec4 DrawColor;
out vec3 DrawPos;
out vec3 DrawNormal;
out vec2 DrawTexCoord;

/* Shader entry point */
void main( void )
{
  gl_Position = MatrWVP * vec4(InPosition, 1);
  DrawColor = InColor;
  DrawNormal = transpose(inverse(mat3(MatrW))) * InNormal;
  DrawPos = (MatrW * vec4(InPosition, 1)).xyz;
  DrawTexCoord = InTexCoord;
} /* End of 'main' function */

/* END OF 'vert.glsl' FILE */
