#include "stdafx.h"
#include "SpriteFontLoader.h"

SpriteFont* SpriteFontLoader::LoadContent(const ContentLoadInfo& loadInfo)
{
	const auto pReader = new BinaryReader();
	pReader->Open(loadInfo.assetFullPath);

	if (!pReader->Exists())
	{
		Logger::LogError(L"Failed to read the assetFile!\nPath: \'{}\'", loadInfo.assetSubPath);
		return nullptr;
	}

	//TODO_W5(L"Implement SpriteFontLoader >> Parse .fnt file")
	//See BMFont Documentation for Binary Layout (C:\Program Files (x86)\AngelCode\BMFont\doc)

	//Parse the Identification bytes (B,M,F)
	char b = pReader->Read<char>();
	char m = pReader->Read<char>();
	char f = pReader->Read<char>();

	//If Identification bytes doesn't match B|M|F,
	if (b != 'B' || m != 'M' || f != 'F')
	{
		Logger::LogError(L"SpriteFontLoader::LoadContent > Not a valid .fnt font");
		return nullptr;
	}

	//Parse the version (version 3 required)
	char version = pReader->Read<char>();
	//If version is < 3,
	if (version < 3)
	{
		Logger::LogError(L"SpriteFontLoader::LoadContent > Only .fnt version 3 is supported");
		return nullptr;
	}

	//Valid .fnt file >> Start Parsing!
	//use this SpriteFontDesc to store all relevant information (used to initialize a SpriteFont object)
	SpriteFontDesc fontDesc{};

	//**********
	// BLOCK 0 *
	//**********
	{
		//Retrieve the blockId and blockSize
		pReader->Read<char>();
		pReader->Read<UINT32>();

		//Retrieve the FontSize [fontDesc.fontSize]
		fontDesc.fontSize = pReader->Read<UINT16>();

		//Move the binreader to the start of the FontName [BinaryReader::MoveBufferPosition(...) or you can set its position using BinaryReader::SetBufferPosition(...))
		pReader->MoveBufferPosition(12); // pos 14 - 2 from the fontSize
		//Retrieve the FontName [fontDesc.fontName]
		fontDesc.fontName = pReader->ReadNullString();
	}

	//**********
	// BLOCK 1 *
	//**********
	{
		//Retrieve the blockId and blockSize
		pReader->Read<char>();
		pReader->Read<UINT32>();

		//Retrieve Texture Width & Height [fontDesc.textureWidth/textureHeight]
		pReader->MoveBufferPosition(4); // move to start of scaleW
		fontDesc.textureWidth = pReader->Read<UINT16>();
		fontDesc.textureHeight = pReader->Read<UINT16>();

		//Retrieve PageCount
		UINT16 pagecount = pReader->Read<UINT16>();
		//> if pagecount > 1
		if (pagecount > 1)
		{
			Logger::LogError(L"Only one texture per font is allowed!");
			return nullptr;
		}

		//Advance to Block2 (Move Reader)
		pReader->MoveBufferPosition(5);
	}


	//**********
	// BLOCK 2 *
	//**********
	{
		//Retrieve the blockId and blockSize
		pReader->Read<char>();
		pReader->Read<UINT32>();

		//Retrieve the PageName (BinaryReader::ReadNullString)
		std::wstring pageName = pReader->ReadNullString();

		//Construct the full path to the page texture file
		//	>> page texture should be stored next to the .fnt file, pageName contains the name of the texture file
		//	>> full texture path = asset parent_path of .fnt file (see loadInfo.assetFullPath > get parent_path) + pageName (filesystem::path::append)
		fs::path texturePath = loadInfo.assetFullPath.parent_path();
		texturePath.append(pageName);
		
		//	>> Load the texture (ContentManager::Load<TextureData>) & Store [fontDesc.pTexture]
		fontDesc.pTexture = ContentManager::Load<TextureData>(texturePath.wstring());
	}


	//**********
	// BLOCK 3 *
	//**********
	{
		//Retrieve the blockId and blockSize
		pReader->Read<char>();
		UINT32 blockSize = pReader->Read<UINT32>();

		//Retrieve Character Count (see documentation)
		UINT32 charCount = blockSize / 20;

		//Create loop for Character Count, and:
		for (size_t i = 0; i < charCount; i++)
		{
			//> Retrieve CharacterId (store Local) and cast to a 'wchar_t'
			wchar_t characterId = static_cast<wchar_t>(pReader->Read<UINT32>());

			//> Create instance of FontMetric (struct)
			FontMetric metric{};

			//	> Set Character (CharacterId) [FontMetric::character]
			metric.character = characterId;

			//	> Retrieve Xposition (store Local)
			UINT16 xPos = pReader->Read<UINT16>();
			//	> Retrieve Yposition (store Local)
			UINT16 yPos = pReader->Read<UINT16>();

			//	> Retrieve & Set Width [FontMetric::width]
			metric.width = pReader->Read<UINT16>();
			//	> Retrieve & Set Height [FontMetric::height]
			metric.height = pReader->Read<UINT16>();

			//	> Retrieve & Set OffsetX [FontMetric::offsetX]
			metric.offsetX = pReader->Read<UINT16>();
			//	> Retrieve & Set OffsetY [FontMetric::offsetY]
			metric.offsetY = pReader->Read<UINT16>();
			//	> Retrieve & Set AdvanceX [FontMetric::advanceX]
			metric.advanceX = pReader->Read<UINT16>();
			//	> Retrieve & Set Page [FontMetric::page]
			metric.page = pReader->Read<char>();

			//	> Retrieve Channel (BITFIELD!!!) 
			//		> See documentation for BitField meaning [FontMetrix::channel]
			byte channelBitmask = pReader->Read<byte>();
			if (channelBitmask & 1)    metric.channel = 2;
			else if (channelBitmask & 2) metric.channel = 1;
			else if (channelBitmask & 4) metric.channel = 0;
			else if (channelBitmask & 8) metric.channel = 3;
			else if (channelBitmask & 16) metric.channel = 4;
			

			//	> Calculate Texture Coordinates using Xposition, Yposition, fontDesc.TextureWidth & fontDesc.TextureHeight [FontMetric::texCoord]
			metric.texCoord.x = static_cast<float>(xPos) / static_cast<float>(fontDesc.textureWidth);
			metric.texCoord.y = static_cast<float>(yPos) / static_cast<float>(fontDesc.textureHeight);

			//> Insert new FontMetric to the metrics [font.metrics] map
			//	> key = (wchar_t) charId
			//	> value = new FontMetric
			fontDesc.metrics.insert(std::make_pair(characterId, metric));
		}

		//(loop restarts till all metrics are parsed)
	}


	//Done!
	delete pReader;
	return new SpriteFont(fontDesc);
}

void SpriteFontLoader::Destroy(SpriteFont* objToDestroy)
{
	SafeDelete(objToDestroy);
}
