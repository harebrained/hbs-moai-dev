// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFONTSHADERRGB_VSH_H
#define	MOAIFONTSHADERRGB_VSH_H

#define SHADER(str) #str

static cc8* _fontShaderRGBVSH = SHADER (

	attribute vec4 position;
	attribute vec2 uv;
	attribute vec4 color;

	varying vec4 colorVarying;
	varying vec2 uvVarying;

	void main () {
		gl_Position = position;
		uvVarying = uv;
		colorVarying = color;
	}
);

#endif
