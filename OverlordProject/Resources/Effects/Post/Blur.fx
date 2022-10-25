//=============================================================================
//// Shader uses position and texture
//=============================================================================

Texture2D gTexture;

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
	
	// Step 2: calculate dx and dy (UV space for 1 pixel)
	const float dx = 1.f / textureWidth;
	const float dy = 1.f / textureHeight;
	
	// Step 3: Create a double for loop (5 iterations each)
	//		   Inside the loop, calculate the offset in each direction. Make sure not to take every pixel but move by 2 pixels each time
	//			Do a texture lookup using your previously calculated uv coordinates + the offset, and add to the final color
	
	float3 finalColour = float3(0.f, 0.f, 0.f);
	
	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			float x = 0.f, y = 0.f;
			
            float xOffset = (-2.f * (dx * 2.f)) + (j * (dx * 2.f)); // move by 2 pixels every time
            float yOffset = (-2.f * (dy * 2.f)) + (i * (dy * 2.f)); // move by 2 pixels every time
			
			x = input.TexCoord.x + xOffset;
			y = input.TexCoord.y + yOffset;
		
			finalColour += gTexture.Sample(samPoint, float2(x, y)).xyz;
		}
	}
	
	// Step 4: Divide the final color by the number of passes (in this case 5*5)
	finalColour.x /= 25.f;
	finalColour.y /= 25.f;
	finalColour.z /= 25.f;
	
	// Step 5: return the final color
	return float4(finalColour, 1.0f);
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