// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFONT_H
#define	MOAIFONT_H

#include <moaicore/MOAIGlyph.h>
#include <moaicore/MOAILua.h>

class MOAIDataBuffer;
class MOAIImage;
class MOAITexture;

//================================================================//
// MOAIFont
//================================================================//
/**	@name	MOAIFont
	@text	Font class.
*/
class MOAIFont :
	public virtual MOAILuaObject {
private:

	USLeanArray < MOAIGlyph >	mByteGlyphs;
	USLeanArray < u8 >			mByteGlyphMap;
	u8							mByteGlyphMapBase;

	USLeanArray < MOAIGlyph >	mWideGlyphs;
	USLeanArray < u32 >			mWideGlyphMap;

	float mScale;
	float mLineSpacing;

	bool mIsRGB;
	
	MOAIGlyph mDummy;

	MOAILuaSharedPtr < MOAITexture >	mTexture;
	MOAILuaSharedPtr < MOAIImage >		mImage;

	//----------------------------------------------------------------//
	static int		_getImage			( lua_State* L );
	static int		_getLineScale		( lua_State* L );
	static int		_getScale			( lua_State* L );
	static int		_getTexture			( lua_State* L );
	static int		_load				( lua_State* L );
	static int		_loadFromBMFont		( lua_State* L );
	static int		_loadFromTTF		( lua_State* L );
	static int		_saveToBMFont		( lua_State* L );
	static int		_setImage			( lua_State* L );
	static int		_setTexture			( lua_State* L );

	//----------------------------------------------------------------//
	void			DrawGlyph			( u32 c, float points, float x, float y );
	u32				GetIDForChar		( u32 c );
	MOAIGlyph&		GetGlyphForID		( u32 id );
	bool			IsWideChar			( u32 c );

public:

	DECL_LUA_FACTORY ( MOAIFont )
	
	friend class MOAITextFrame;

	enum {
		LEFT_JUSTIFY,
		RIGHT_JUSTIFY,
		CENTER_JUSTIFY,
	};

	GET_SET ( float, Scale, mScale )
	GET_SET ( float, LineSpacing, mLineSpacing )
	GET( bool, IsRGB, mIsRGB )
	
	//----------------------------------------------------------------//
	MOAIFont*		Bind				();
					MOAIFont			();
					~MOAIFont			();
	MOAIGlyph&		GetGlyphForChar		( u32 c );
	void			Init				( cc8* charCodes );
	void			LoadFont			( MOAIDataBuffer& fontImageData, cc8* charCodes );
	void			LoadFont			( cc8* fontImageFileName, cc8* charCodes );
	void			LoadFontFromBMFont  ( cc8* filename );
	void			LoadFontFromTTF		( cc8* filename, cc8* charCodes, float points, u32 dpi );
	void			RegisterLuaClass	( MOAILuaState& state );
	void			RegisterLuaFuncs	( MOAILuaState& state );
	void			Render				();
	void			SaveToBMFont		( cc8* filename );
	void			SerializeIn			( MOAILuaState& state, MOAIDeserializer& serializer );
	void			SerializeOut		( MOAILuaState& state, MOAISerializer& serializer );
	void			SetGlyph			( const MOAIGlyph& glyph );
	void			SetImage			( MOAIImage* image );
	void			SetTexture			( MOAITexture* texture );
	u32				Size				();
};

#endif
