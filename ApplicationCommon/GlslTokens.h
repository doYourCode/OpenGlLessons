#include <array>
#include <string>

const std::array< const std::string, 388 > glslBuiltinFunctions =
{
	// ------------------------------ abs ------------------------------ //
	"abs",
	R"(
	abs - return the absolute value of the parameter

	Declaration
	genType abs(genType x);
	genIType abs(genIType x);
	genDType abs(genDType x);
 
	Parameters
	x - Specify the value of which to return the absolute.

	Description - abs returns the absolute value of x.

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	abs (genType)    X       X       X       X       X       X       X       X       X       X       X       X
	abs (genIType)   -       -       X       X       X       X       X       X       X       X       X       X
	abs (genDType)   -       -       -       -       -       -       -       X       X       X       X       X

	See Also
	sign
	)",

	// ------------------------------ acos ------------------------------ //
	"acos",
	R"(
	acos - return the arccosine of the parameter

	Declaration
	genType acos(genType x);
 
	Parameters
	x - Specify the value whose arccosine to return.

	Description - acos returns the angle whose trigonometric cosine is x.
	- The range of values returned by acos is [0,PI].
	- The result is undefined if |x|>1.

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	acos (genType)   X       X       X       X       X       X       X       X       X       X       X       X

	See Also
	sin, cos, asin, tan
	)",
	
	// ------------------------------ acosh ------------------------------ //
	"acosh",
	R"(
	acosh - return the arc hyperbolic cosine of the parameter

	Declaration
	genType acosh(genType x)
 
	Parameters
	x - Specify the value whose arc hyperbolic cosine to return.

	Description - acosh returns the arc hyperbolic cosine of x; the non-negative inverse of cosh.
	- The result is undefined if x<1. 

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	acosh (genType)  -       -       X       X       X       X       X       X       X       X       X       X

	See Also
	sin, cos, sinh, cosh
	)",
	
	// ------------------------------ all ------------------------------ //
	"all",
	R"(
	all - check whether all elements of a boolean vector are true

	Declaration
	bool all(bvec x);
 
	Parameters
	x - Specifies the vector to be tested for truth.

	Description - all returns true if all elements of x are true and false otherwise.
	- It is functionally equivalent to:

    bool all(bvec x)       // bvec can be bvec2, bvec3 or bvec4
    {
        bool result = true;
        int i;
        for (i = 0; i < x.length(); ++i)
        {
            result &= x[i];
        }
        return result;
    }

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	all (bvec)       X       X       X       X       X       X       X       X       X       X       X       X

	See Also
	any, not
	)",

	// ------------------------------ any ------------------------------ //
	"any",
	R"(
	any - check whether any element of a boolean vector is true

	Declaration
	bool any(bvec x);
 
	Parameters
	x - Specifies the vector to be tested for truth. 

	Description - any returns true if any element of x is true and false otherwise.
	- It is functionally equivalent to:

    bool any(bvec x) {     // bvec can be bvec2, bvec3 or bvec4
        bool result = false;
        int i;
        for (i = 0; i < x.length(); ++i) {
            result |= x[i];
        }
        return result;
    }

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	any (bvec)       X       X       X       X       X       X       X       X       X       X       X       X

	See Also
	all, not
	)",

	// ------------------------------ asin ------------------------------ //
	"asin",
	R"(
	asin - return the arcsine of the parameter

	Declaration
	genType asin(genType x)
 
	Parameters
	x - Specify the value whose arcsine to return.

	Description - asin returns the angle whose trigonometric sine is x. The range of values returned by asin is [−π2,π2].
	- The result is undefined if |x|>1.

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	asin (genType)   X       X       X       X       X       X       X       X       X       X       X       X

	See Also
	sin, cos, acos, tan
	)",

	// ------------------------------ asinh ------------------------------ //
	"asinh",
	R"(
	asinh - return the arc hyperbolic sine of the parameter

	Declaration
	genType asinh(genType x)
 
	Parameters
	x - Specify the value whose arc hyperbolic sine to return. 

	Description - asinh returns the arc hyperbolic sine of x; the inverse of sinh.

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	asinh (genType)  -       -       X       X       X       X       X       X       X       X       X       X

	See Also
	sin, cos, sinh, cosh
	)",

	// ------------------------------ atan ------------------------------ //
	"atan",
	R"(
	atan - return the arc-tangent of the parameters

	Declaration
	genType atan(genType y, genType x);
	genType atan(genType y_over_x);
 
	Parameters
	y - Specify the numerator of the fraction whose arctangent to return.
	x - Specify the denominator of the fraction whose arctangent to return.
	y_over_x - Specify the fraction whose arctangent to return.

	Description - atan returns either the angle whose trigonometric arctangent is yx or y_over_x, depending on which overload is invoked.
	- In the first overload, the signs of y and x are used to determine the quadrant that the angle lies in.
		The value returned by atan in this case is in the range [−pi,pi].
		The result is undefined if x = 0.
	- For the second overload, atan returns the angle whose tangent is y_over_x.
		The value returned in this case is in the range [−pi/2,pi/2]. 

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	atan (genType)   X       X       X       X       X       X       X       X       X       X       X       X

	See Also
	sin, cos, tan
	)",

	// ------------------------------ atanh ------------------------------ //
	"atanh",
	R"(
	atanh - return the arc hyperbolic tangent of the parameter

	Declaration
	genType atanh(genType x)
 
	Parameters
	x - Specify the value whose arc hyperbolic tangent to return.

	Description - atanh returns the arc hyperbolic tangent of x; the inverse of tanh.
	- The result is undefined if |x|>1. 

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	atanh (genType)  X       X       X       X       X       X       X       X       X       X       X       X

	See Also
	sin, cos, sinh, cosh
	)",

	"atomicAdd",
	"",

	"atomicAnd",
	"",

	"atomicCompSwap",
	"",

	"atomicCounter",
	"",

	"atomicCounterDecrement",
	"",

	"atomicCounterIncrement",
	"",

	"atomicExchange",
	"",

	"atomicMax",
	"",

	"atomicMin",
	"",
		
	"atomicOr",
	"",

	"atomicXor",
	"",

	"barrier",
	"",

	"bitCount",
	"",

	"bitfieldExtract",
	"",

	"bitfieldInsert",
	"",

	"bitfieldReverse",
	"",

	// ------------------------------  ceil ------------------------------ //
	"ceil",
	R"(
	ceil - find the nearest integer that is greater than or equal to the parameter

	Declaration
	genType ceil(genType x);
	genDType ceil(genDType x);
 
	Parameters
	x - Specify the value to evaluate.

	Description - ceil returns a value equal to the nearest integer that is greater than or equal to x. 

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	ceil (genType)   X       X       X       X       X       X       X       X       X       X       X       X
	ceil (genDType)  -       -       -       -       -       -       X       X       X       X       X       X

	See Also
	floor, round
	)",

	// ------------------------------  clamp ------------------------------ //
	"clamp",
	R"(
	clamp - constrain a value to lie between two further values

	Declaration
	genType clamp(genType x, genType minVal, genType maxVal);
	genType clamp(genType x, float minVal, float maxVal);
	genDType clamp(genDType x, genDType minVal, genDType maxVal);
	genDType clamp(genDType x, double minVal, double maxVal);
	genIType clamp(genIType x, genIType minVal, genIType maxVal);
	genIType clampgenIType x, int minVal, int maxVal);
	genUType clamp(genUType x, genUType minVal, genUType maxVal);
	genUType clamp(genUType x, uint minVal, uint maxVal);
 
	Parameters
	x - Specify the value to constrain.
	minVal - Specify the lower end of the range into which to constrain x.
	maxVal - Specify the upper end of the range into which to constrain x.

	Description - clamp returns the value of x constrained to the range minVal to maxVal.
	- The returned value is computed as min(max(x, minVal), maxVal).  

	Version Support
	Function Name  OpenGL Shading Language Version
					1.10    1.20    1.30    1.40    1.50    3.30    4.00    4.10    4.20    4.30    4.40    4.50
	clamp (genType)  X       X       X       X       X       X       X       X       X       X       X       X
	clamp (genIType) -       -       X       X       X       X       X       X       X       X       X       X
	clamp (genUType) -       -       X       X       X       X       X       X       X       X       X       X
	clamp (genDType) -       -       -       -       -       -       X       X       X       X       X       X

	See Also
	min, max
	)",
	
	// ------------------------------ cos ------------------------------ //
	"cos",
	"",
	
	// ------------------------------ cosh ------------------------------ //
	"cosh",
	"",

	// ------------------------------ cross ------------------------------ //
	"cross",
	"",

	// ------------------------------ degrees ------------------------------ //
	"degrees",
	"",

	// ------------------------------ dFdx ------------------------------ //
	"dFdx",
	"",

	"dFdxCoarse",
	"",

	"dFdxFine",
	"",

	// ------------------------------ dFdy ------------------------------ //
	"dFdy",
	"",
		
	"dFdyCoarse",
	"",

	"dFdyFine",
	"",

	// ------------------------------ distance ------------------------------ //
	"distance",
	"",

	// ------------------------------ dot ------------------------------ //
	"dot",
	"",

	"EmitStreamVertex",
	"",

	"EmitVertex",
	"",

	"EndPrimitive",
	"",

	"EndStreamPrimitive",
	"",

	// ------------------------------ equal ------------------------------ //
	"equal",
	"",

	// ------------------------------ exp ------------------------------ //
	"exp",
	"",

		// ------------------------------ exp2 ------------------------------ //
	"exp2",
	"",

	"faceforward",
	"",

	"findLSB",
	"",

	"findMSB",
	"",

	"floatBitsToInt",
	"",

	"floatBitsToUint",
	"",

	// ------------------------------ floor ------------------------------ //
	"floor",
	"",

	"fma",
	"",

	"fract",
	"",

	"frexp",
	"",

	"fwidth",
	"",

	"fwidthCoarse",
	"",

	"fwidthFine",
	"",

	// ------------------------------  atanh ------------------------------ //
	"greaterThan",
	"",

	"greaterThanEqual",
	"",

	"groupMemoryBarrier",
	"",

	"imageAtomicAdd",
	"",

	"imageAtomicAnd",
	"",

	"imageAtomicCompSwap",
	"",

	"imageAtomicExchange",
	"",

	"imageAtomicMax",
	"",

	"imageAtomicMin",
	"",

	"imageAtomicOr",
	"",

	"imageAtomicXor",
	"",

	"imageLoad",
	"",

	"imageSamples",
	"",

	"imageSize",
	"",

	"imageStore",
	"",

	"imulExtended",
	"",

	"intBitsToFloat",
	"",

	"interpolateAtCentroid",
	"",

	"interpolateAtOffset",
	"",

	"interpolateAtSample",
	"",

	// ------------------------------  atanh ------------------------------ //
	"inverse",
	"",

	// ------------------------------  atanh ------------------------------ //
	"inversesqrt",
	"",

	"isinf",
	"",

	"isnan",
	"",

	"ldexp",
	"",

	// ------------------------------  atanh ------------------------------ //
	"length",
	"",

	// ------------------------------  atanh ------------------------------ //
	"lessThan",
	"",

	// ------------------------------  atanh ------------------------------ //
	"lessThanEqual",

	// ------------------------------  atanh ------------------------------ //
	"log",
	"",

		// ------------------------------  atanh ------------------------------ //
	"log2",
	"",

	"matrixCompMult",
	"",

	// ------------------------------  atanh ------------------------------ //
	"max",
	"",

	"memoryBarrier",
	"",

	"memoryBarrierAtomicCounter",
		
	"memoryBarrierBuffer",
	"",
		
	"memoryBarrierImage",
	"",

	"memoryBarrierShared",
	"",

	// ------------------------------  atanh ------------------------------ //
	"min",
	"",

	// ------------------------------  atanh ------------------------------ //
	"mix",
	"",

	"mod",
	"",

	"modf",
	"",

	"noise",
	"",

	"noise1",
	"",

	"noise2",
	"",

	"noise3",
	"",

	"noise4",
	"",

	"normalize",
	"",

	// ------------------------------  atanh ------------------------------ //
	"not",
	"",

	// ------------------------------  atanh ------------------------------ //
	"notEqual",
	"",

	"outerProduct",
	"",

	"packDouble2x32",
	"",

	"packHalf2x16",
	"",

	"packSnorm2x16",
	"",

	"packSnorm4x8",
	"",

	"packUnorm",
	"",

	"packUnorm2x16",
	"",

	"packUnorm4x8",
	"",

	// ------------------------------  atanh ------------------------------ //
	"pow",
	"",

	// ------------------------------  atanh ------------------------------ //
	"radians",
	"",

	// ------------------------------  atanh ------------------------------ //
	"reflect",
	"",

	// ------------------------------  atanh ------------------------------ //
	"refract",
	"",

	"removedTypes",
	"",

	// ------------------------------  atanh ------------------------------ //
	"round",
	"",

	"roundEven",
	"",

	// ------------------------------  atanh ------------------------------ //
	"sign",
	"",

	// ------------------------------  atanh ------------------------------ //
	"sin",
	"",

	// ------------------------------  atanh ------------------------------ //
	"sinh",
	"",

	// ------------------------------  atanh ------------------------------ //
	"smoothstep",
	"",

	// ------------------------------  atanh ------------------------------ //
	"sqrt",
	"",

	// ------------------------------  atanh ------------------------------ //
	"step",
	"",

	// ------------------------------  atanh ------------------------------ //
	"tan",
	"",

	// ------------------------------  atanh ------------------------------ //
	"tanh",
	"",

	"texelFetch",
	"",

	"texelFetchOffset",
	"",

	// ------------------------------  atanh ------------------------------ //
	"texture",
	"",
	
	"textureGather",
	"",
	
	"textureGatherOffset",
	"",

	"textureGatherOffsets",
	"",

	"textureGrad",
	"",

	"textureGradOffset",
	"",
	
	"textureLod",
	"",
	
	"textureLodOffset",
	"",

	"textureOffset",
	"",

	"textureProj",
	"",

	"textureProjGrad",
	"",

	"textureProjGradOffset",
	"",

	"textureProjLod",
	"",

	"textureProjLodOffset",
	"",

	"textureProjOffset",
	"",

	"textureQueryLevels",
	"",

	"textureQueryLod",
	"",

	"textureSamples",
	"",

	"textureSize",
	"",

	// ------------------------------  atanh ------------------------------ //
	"transpose",
	"",

	// ------------------------------  atanh ------------------------------ //
	"trunc",
	"",

	"uaddCarry",
	"",

	"uintBitsToFloat",
	"",

	"umulExtended",
	"",

	"unpackDouble2x32",
	"",

	"unpackHalf2x16",
	"",

	"unpackSnorm2x16",
	"",

	"unpackSnorm4x8",
	"",
	
	"unpackUnorm",
	"",

	"unpackUnorm2x16",
	"",

	"unpackUnorm4x8",
	"",

	"usubBorrow",
	"",
};

const std::array< const std::string, 220 > glslTypes =
{
	"bool",
	R"(
	Conditional type, values may be either true or false.
	)",

	"int",
	R"(
	A signed 32-bit integer in the range [-n, n - 1].
	)",

	"uint",
	R"(
	An unsigned 32-bit integer in the range [0, n].
	)",

	"float",
	R"(
	An IEEE-754 single-precision floating point number.
	)",

	"double",
	R"(
	An IEEE-754 double-precision floating point number.
	)",

	"bvec2",
	R"(
	A vector of two booleans.
	- Any of the N boolean values can be accessed by using such syntax as vector.xy, vector.rg or vector[n - 1].
	)",

	"bvec3",
	R"(
	A vector of three booleans.
	- Any of the N boolean values can be accessed by using such syntax as vector.xyz, vector.rgb or vector[n - 1].
	)",

	"bvec4",
	R"(
	A vector of four booleans.
	- Any of the N boolean values can be accessed by using such syntax as vector.xyzw, vector.rgba or vector[n - 1].
	)",

	"ivec2",
	R"(
	A vector of two signed 32-bit integers.
	- Any of the N integer values can be accessed by using such syntax as vector.xy, vector.rg or vector[n - 1].
	)",

	"ivec3",
	R"(
	A vector of three signed 32-bit integers.
	- Any of the N integer values can be accessed by using such syntax as vector.xyz, vector.rgb or vector[n - 1].
	)",

	"ivec4",
	R"(
	- Any of the N integer values can be accessed by using such syntax as vector.xyzw, vector.rgba or vector[n - 1].
	)",

	"uvec2",
	R"(
	A vector of two unsigned 32-bit integers.
	- Any of the N unsigned integer values can be accessed by using such syntax as vector.xy, vector.rg or vector[n - 1].
	)",

	"uvec3",
	R"(
	A vector of three unsigned 32-bit integers.
	- Any of the N unsigned integer values can be accessed by using such syntax as vector.xyz, vector.rgb or vector[n - 1].
	)",

	"uvec4",
	R"(
	A vector of four unsigned 32-bit integers.
	- Any of the N unsigned integer values can be accessed by using such syntax as vector.xyzw, vector.rgba or vector[n - 1].
	)",

	"vec2",
	R"(
	A vector of two single-precision floating point numbers.
	- Any of the N single-precision floating-point values can be accessed by using such syntax as vector.xy, vector.rg or vector[n - 1].
	)",

	"vec3",
	R"(
	A vector of three single-precision floating point numbers.
	- Any of the N single-precision floating-point values can be accessed by using such syntax as vector.xyz, vector.rgb or vector[n - 1].
	)",

	"vec4",
	R"(
	A vector of four single-precision floating point numbers.
	- Any of the N single-precision floating-point values can be accessed by using such syntax as vector.xyzw, vector.rgba or vector[n - 1].
	)",

	"dvec2",
	R"(
	A vector of two double-precision floating point numbers.
	- Any of the N double-precision floating point values can be accessed by using such syntax as vector.xy, vector.rg or vector[n - 1].
	)",

	"dvec3",
	R"(
	A vector of three double-precision floating point numbers.
	- Any of the N double-precision floating point values can be accessed by using such syntax as vector.xyz, vector.rgb or vector[n - 1].
	)",

	"dvec4",
	R"(
	A vector of four double-precision floating point numbers.
	- Any of the N double-precision floating point values can be accessed by using such syntax as vector.xyzw, vector.rgba or vector[n - 1].
	)",

	"mat2",
	"",

	"mat3",
	"",

	"mat4",
	"",

	"mat2x2",
	"",

	"mat2x3",
	"",

	"mat2x4",
	"",

	"mat3x2",
	"",

	"mat3x3",
	"",

	"mat3x4",
	"",

	"mat4x2",
	"",

	"mat4x3",
	"",
	"mat4x4",
	"",

	"dmat2",
	"",

	"dmat3",
	"",

	"dmat4",
	"",

	"dmat2x2",
	"",

	"dmat2x3",
	"",

	"dmat2x4",
	"",

	"dmat3x2",
	"",

	"dmat3x3",
	"",

	"dmat3x4",
	"",

	"dmat4x2",
	"",

	"dmat4x3",
	"",

	"dmat4x4",
	"",
		
	"sampler1D",
	"",

	"sampler2D",
	"",

	"sampler3D",
	"",

	"samplerCube",
	"",

	"sampler1DShadow",
	"",

	"sampler2DShadow",
	"",

	"samplerCubeShadow",
	"",

	"sampler1DArray",
	"",

	"sampler2DArray",
	"",

	"sampler1DArrayShadow",
	"",

	"sampler2DArrayShadow",
	"",

	"sampler2DMS",
	"",

	"sampler2DMSArray",
	"",

	"samplerBuffer",
	"",

	"sampler2DRect",
	"",

	"sampler2DRectShadow",
	"",

	"isampler1D",
	"",

	"isampler2D",
	"",

	"isampler3D",
	"",

	"isamplerCube",
	"",

	"isampler1DArray",
	"",

	"isampler2DArray",
	"",

	"isampler2DMS",
	"",

	"isampler2DMSArray",
	"",

	"isamplerBuffer",
	"",

	"isampler2DRect",
	"",

	"usampler1D",
	"",

	"usampler2D",
	"",

	"usampler3D",
	"",

	"usamplerCube",
	"",

	"usampler1DArray",
	"",

	"usampler2DArray",
	"",

	"usampler2DMS",
	"",

	"usampler2DMSArray",
	"",

	"usamplerBuffer",
	"",

	"usampler2DRect",
	"",

	"image1D",
	"",

	"image2D",
	"",

	"image3D",
	"",

	"imageCube",
	"",

	"image1DArray",
	"",

	"image2DArray",
	"",

	"image2DMS",
	"",

	"image2DMSArray",
	"",

	"imageBuffer",
	"",

	"image2DRect",
	"",

	"iimage1D",
	"",

	"iimage2D",
	"",

	"iimage3D",
	"",

	"iimageCube",
	"",

	"iimage1DArray",
	"",

	"iimage2DArray",
	"",

	"iimage2DMS",
	"",

	"iimage2DMSArray",
	"",

	"iimageBuffer",
	"",

	"iimage2DRect",
	"",

	"uimage1D",
	"",

	"uimage2D",
	"",

	"uimage3D",
	"",

	"uimageCube",
	"",

	"uimage1DArray",
	"",

	"uimage2DArray",
	"",

	"uimage2DMS",
	"",

	"uimage2DMSArray",
	"",

	"uimageBuffer",
	"",

	"uimage2DRect",
	"",
};