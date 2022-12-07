#include"Shaders.hlsl"
struct VS_LIGHTING_INPUT
{
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct VS_LIGHTING_OUTPUT
{
    float4 position : SV_POSITION;
    float3 positionW : POSITION;
    float3 normalW : NORMAL;
};

VS_LIGHTING_OUTPUT VSCubeMapping(VS_LIGHTING_INPUT input)
{
VS_LIGHTING_OUTPUT output;

    output.positionW = mul(float4(input.position, 1.0f), gmtxChildGameObject).xyz;
//	output.positionW = (float3)mul(float4(input.position, 1.0f), gmtxWorld);
    output.normalW = mul(float4(input.normal, 0.0f), gmtxChildGameObject).xyz;
//	output.normalW = mul(input.normal, (float3x3)gmtxWorld);
	output.position = mul(mul(float4(output.positionW, 1.0f), gmtxView), gmtxProjection);

	return(output);
}

float4 PSCubeMapping(VS_LIGHTING_OUTPUT input) : SV_Target
{
    input.normalW = normalize(input.normalW);

    float4 cIllumination = Lighting(input.positionW, input.normalW);

    float3 vFromCamera = normalize(input.positionW - gvCameraPosition.xyz);
    float3 vReflected = normalize(reflect(vFromCamera, input.normalW));
    float4 cCubeTextureColor = gtxtCubeMap.Sample(gWrapSamplerState, vReflected);

	//return(float4(vReflected * 0.5f + 0.5f, 1.0f));
    return (cCubeTextureColor);
	//return(cIllumination * cCubeTextureColor);
}
