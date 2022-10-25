//=============================================================================
//// Shader uses position and texture
//=============================================================================

Texture2D gTexture;
float gPixelSizeX = 3.f;
float gPixelSizeY = 3.f;

SamplerState samPoint
{
    Filter = MIN_MAG_MIP_POINT;
    AddressU = Mirror;
    AddressV = Mirror;
};

DepthStencilState EnableDepthWriting
{
	DepthWriteMask = ALL;
};

RasterizerState BackCulling
{
	CullMode = BACK;
};


//IN/OUT STRUCTS
//--------------
struct VS_INPUT
{
    float3 Position : POSITION;
	float2 TexCoord : TEXCOORD0;

};

struct PS_INPUT
{
    float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD1;
};


//VERTEX SHADER
//-------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Position = float4(input.Position, 1.f);
	output.TexCoord = input.TexCoord;
	
	return output;
}


//PIXEL SHADER
//------------
float4 PS(PS_INPUT input): SV_Target
{
	// Step 1: find the dimensions of the texture (the texture has a method for that)
	float textureWidth = 0.f, textureHeight = 0.f;
	gTexture.GetDimensions(textureWidth, textureHeight);
	
	// Step 2: calculate dx and dy (UV space for 1 pixel) while adjusting for the 'amount' of pixels we want
	const float dx = gPixelSizeX * (1.f / textureWidth);
	const float dy = gPixelSizeY * (1.f / textureHeight);
	
	input.TexCoord.x = dx * floor(input.TexCoord.x / dx);
	input.TexCoord.y = dy * floor(input.TexCoord.y / dy);
	
	return gTexture.Sample(samPoint, input.TexCoord);
}


//TECHNIQUE
//---------
technique11 Blur
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
    
		SetRasterizerState(BackCulling);       
		SetDepthStencilState(EnableDepthWriting, 0);
	}
}