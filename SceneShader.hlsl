#include "Shaders.hlsl"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//#define _WITH_VERTEX_LIGHTING

struct VS_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct VS_OUTPUT
{
    float4 positionH : SV_POSITION;
    float3 positionW : POSITION;
    float3 normalW : NORMAL;
#ifdef _WITH_VERTEX_LIGHTING
	float4 color : COLOR;
#endif
};

VS_OUTPUT VSScene(VS_INPUT input)
{
    VS_OUTPUT output;

    output.positionW = mul(float4(input.position, 1.0f), gmtxGameObject).xyz;
    output.positionH = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);
    float3 normalW = mul(input.normal, (float3x3) gmtxGameObject);
#ifdef _WITH_VERTEX_LIGHTING
	output.color = Lighting(output.positionW, normalize(normalW));
	output.color = float4(0.5f * normalize(gvCameraPosition - output.positionW) + 0.5f, 1.0f);
#else
    output.normalW = normalW;
#endif

    return (output);
}

float4 PSScene(VS_OUTPUT input) : SV_TARGET
{
#ifdef _WITH_VERTEX_LIGHTING
//	return(float4(input.positionW, 1.0f));
	return(input.color);
#else
    float3 normalW = normalize(input.normalW);
    float4 cIllumination = Lighting(input.positionW, normalW);
   
    return (cIllumination );
#endif
}
