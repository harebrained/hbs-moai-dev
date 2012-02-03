// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIMESH_H
#define	MOAIMESH_H

#include <moaicore/MOAIDeck.h>
#include <moaicore/MOAILua.h>

class MOAITexture;
class MOAIVertexBuffer;

//================================================================//
// MOAIMesh
//================================================================//
/**	@name	MOAIMesh
	@text	Loads a texture and renders the contents of a vertex buffer.
			Grid drawing not supported.
*/
class MOAIMesh :
	public MOAIDeck {
private:

	MOAILuaSharedPtr < MOAITexture	>		mTexture;
	MOAILuaSharedPtr < MOAIVertexBuffer >		mVertexBuffer;

	//----------------------------------------------------------------//
	static int		_setTexture			( lua_State* L );
	static int		_setVertexBuffer	( lua_State* L );

public:
	
	DECL_LUA_FACTORY ( MOAIMesh )
	
	//----------------------------------------------------------------//
	bool			Bind					();
	void			Draw					( const USAffine2D& transform, u32 idx, MOAIDeckRemapper* remapper );
    void            Draw					( const USAffine2D& transform, MOAIGrid& grid, MOAIDeckRemapper* remapper, USVec2D& gridScale, MOAICellCoord& c0, MOAICellCoord& c1 );
    USRect			GetBounds				( u32 idx, MOAIDeckRemapper* remapper );
	void			LoadShader				();
					MOAIMesh				();
					~MOAIMesh				();
	void			RegisterLuaClass		( MOAILuaState& state );
	void			RegisterLuaFuncs		( MOAILuaState& state );
};

#endif
