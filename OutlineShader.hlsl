#include"Shaders.hlsl"

struct VS_OUTLINE_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct VS_OUTLINE_OUTPUT
{
    float4 position : SV_POSITION;
    float3 positionW : POSITION;
//	nointerpolation float3 normalW : NORMAL;
#ifdef _WITH_VERTEX_LIGHTING
	float4 color : COLOR;
#else
    float3 normalW : NORMAL;
#endif
};

VS_OUTLINE_OUTPUT VSLighting(VS_OUTLINE_INPUT input)
{
    VS_OUTLINE_OUTPUT output;

    output.positionW = (float3) mul(float4(input.position, 1.0f), gmtxGameObject);
    float fScale = 1.40175f + length(gvCameraPosition - output.positionW) * 0.00035f;
   // output.positionW = (float3) mul(float4(input.position*, 1.0f), gmtxGameObject);
    output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
    float3 normalW = mul(input.normal, (float3x3) gmtxGameObject);
#ifdef _WITH_VERTEX_LIGHTING
	output.color = Lighting(output.positionW, normalize(normalW));
#else
    output.normalW = normalW;
#endif

    return (output);
}

float4 PSLighting(VS_OUTLINE_OUTPUT input) : SV_TARGET
{
#ifdef _WITH_VERTEX_LIGHTING
	return(input.color);
#else
    float3 normalW = normalize(input.normalW);
    float4 cColor = Lighting(input.positionW, normalW);
    return (cColor);
    //return (float4(1.0f, 0.2f, 0.2f, 1.0f));
#endif
}

#define _WITH_SCALING
//#define _WITH_NORMAL_DISPLACEMENT
//#define _WITH_PROJECTION_SPACE

#define FRAME_BUFFER_WIDTH		640
#define FRAME_BUFFER_HEIGHT		480

VS_OUTLINE_OUTPUT VSOutline(VS_OUTLINE_INPUT input)
{
    VS_OUTLINE_OUTPUT output;

#ifdef _WITH_SCALING
//Scaling
    output.positionW = (float3) mul(float4(input.position, 1.0f), gmtxGameObject);
    float fScale = 1.00175f + length(gvCameraPosition - output.positionW) * 0.00035f;
    output.positionW = (float3) mul(float4(input.position * fScale, 1.0f), gmtxGameObject);
    output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
#endif

#ifdef _WITH_NORMAL_DISPLACEMENT
//Normal Displacement
	output.positionW = (float3)mul(float4(input.position, 1.0f), gmtxGameObject);
	float3 normalW = normalize(mul(input.normal, (float3x3)gmtxGameObject));
	float fScale = length(gvCameraPosition - output.positionW) * 0.01f;
	output.positionW += normalW * fScale;

	output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
#endif

#ifdef _WITH_PROJECTION_SPACE
//Projection Space
	output.position = mul(mul(mul(float4(input.position, 1.0f), gmtxGameObject), gmtxView), gmtxProjection);
	float3 normal = mul(mul(input.normal, (float3x3)gmtxGameObject), (float3x3)mul(gmtxView, gmtxProjection));
	float2 f2Offset = normalize(normal.xy) / float2(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT) * output.position.w * 3.5f;
	output.position.xy += f2Offset;
	output.position.z += 0.0f;
#endif

    return (output);
}

float4 PSOutline(VS_OUTLINE_OUTPUT input) : SV_TARGET
{
    return (float4(1.0f, 0.2f, 0.2f, 1.0f));
}

