// GdiPlus.h: interface for the CGdiPlus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDIPLUS_H__41B5F6AC_E7D4_49CA_9E2F_96FDA94EBB28__INCLUDED_)
#define AFX_GDIPLUS_H__41B5F6AC_E7D4_49CA_9E2F_96FDA94EBB28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////

/*
#include <gdiplusflat.h>

//---------------------------------------------------------------------------
// GDI+ classes for forward reference
//---------------------------------------------------------------------------

class Graphics;
class Pen;
class Brush;
class Matrix;
class Bitmap;
class Metafile;
class GraphicsPath;
class PathIterator;
class Region;
class Image;
class TextureBrush;
class HatchBrush;
class SolidBrush;
class LinearGradientBrush;
class PathGradientBrush;
class Font;
class FontFamily;
class FontCollection;
class InstalledFontCollection;
class PrivateFontCollection;
class ImageAttributes;
class CachedBitmap;

//---------------------------------------------------------------------------
// Private GDI+ classes for internal type checking
//---------------------------------------------------------------------------
class GpGraphics {};

class GpBrush {};
class GpTexture : public GpBrush {};
class GpSolidFill : public GpBrush {};
class GpLineGradient : public GpBrush {};
class GpPathGradient : public GpBrush {};
class GpHatch : public GpBrush {};

class GpPen {};
class GpCustomLineCap {};
class GpAdjustableArrowCap : public GpCustomLineCap {};

class GpImage {};
class GpBitmap : public GpImage {};
class GpMetafile : public GpImage {};
class GpImageAttributes {};

class GpPath {};
class GpRegion {};
class GpPathIterator {};

class GpFontFamily {};
class GpFont {};
class GpStringFormat {};
class GpFontCollection {};
class GpInstalledFontCollection : public GpFontCollection {};
class GpPrivateFontCollection : public GpFontCollection {};

class GpCachedBitmap;
*/

//////////////////////////////////////////////////////////////////////

typedef void* gdix_Graphics;
typedef void* gdix_SolidFill;
typedef void* gdix_Brush;
typedef void* gdix_Pen;
typedef void* gdix_Font;
typedef void* gdix_StringFormat;
typedef void* gdix_Path;
typedef void* gdix_Bitmap;

typedef float gdix_Real;
typedef DWORD gdix_ARGB;

//////////////////////////////////////////////////////////////////////

enum gdix_Status 
{
	gdix_Ok = 0
};

enum gdix_Unit 
{
	gdix_UnitWorld = 0,
	gdix_UnitPixel = 2,
};

enum gdix_SmoothingMode 
{
	gdix_SmoothingModeHighQuality = 2,
	gdix_SmoothingModeAntiAlias = 4,
};

enum gdix_StringAlignment 
{
	gdix_StringAlignmentCenter = 1,
	gdix_StringAlignmentFar = 2
};

enum gdix_FillMode  
{
	gdix_FillModeAlternate = 0
};

//////////////////////////////////////////////////////////////////////

#define gdix_StringFormatFlagsNoWrap   0x00001000
#define gdix_StringFormatFlagsNoClip   0x00004000

//////////////////////////////////////////////////////////////////////

#if _MSC_VER < 1400
#	ifndef ULONG_PTR
		typedef unsigned __int64    ULONG_PTR;
#	endif
#endif

//////////////////////////////////////////////////////////////////////

struct gdix_PointF 
{
	gdix_Real x;
	gdix_Real y;
};

struct gdix_RectF 
{
	gdix_Real x;
	gdix_Real y;
	gdix_Real w;
	gdix_Real h;
};

//////////////////////////////////////////////////////////////////////

class CGdiPlusGraphics
{
public:
	CGdiPlusGraphics(HDC hDC, gdix_SmoothingMode smoothing = gdix_SmoothingModeAntiAlias);
	virtual ~CGdiPlusGraphics();

	operator gdix_Graphics*() { return m_graphics; }

protected:
	gdix_Graphics* m_graphics;
};

//////////////////////////////////////////////////////////////////////

class CGdiPlusPen
{
public:
	CGdiPlusPen(COLORREF color, int nWidth);
	virtual ~CGdiPlusPen();

	operator gdix_Pen*() { return m_pen; }

protected:
	gdix_Pen* m_pen;
};

//////////////////////////////////////////////////////////////////////

/*
class CGdiPlusBrush
{
	CGdiPlusBrush(COLORREF color);
	virtual ~CGdiPlusBrush();

	operator gdix_Brush*() const { return m_brush; }

protected:
	gdix_Brush* m_brush;
};
*/

//////////////////////////////////////////////////////////////////////

class CGdiPlusPointF : public gdix_PointF
{
public:
	CGdiPlusPointF(int nX = 0, int nY = 0);
	CGdiPlusPointF(const POINT& pt);

	operator gdix_PointF*() { return this; }
};

//////////////////////////////////////////////////////////////////////

class CGdiPlusRectF : public gdix_RectF
{
public:
	CGdiPlusRectF(int l = 0, int t = 0, int r = 0, int b = 0);
	CGdiPlusRectF(const POINT& ptTopLeft, const SIZE& size);
	CGdiPlusRectF(const POINT& ptTopLeft, const POINT& ptBottomRight);
	
	operator gdix_RectF*() { return this; }
};

//////////////////////////////////////////////////////////////////////

class CGdiPlus  
{
public:
	static BOOL CreateBitmapFromStream(IStream* stream, gdix_Bitmap **bitmap);
	static BOOL CreateBitmapFromFile(const WCHAR* filename, gdix_Bitmap **bitmap);
	static BOOL CreateHBITMAPFromBitmap(gdix_Bitmap* bitmap, HBITMAP* hbmReturn, gdix_ARGB background);
	static BOOL DeleteBitmap(gdix_Bitmap* bitmap);

	static BOOL CreatePen(gdix_ARGB color, gdix_Real width, gdix_Pen** pen);
	static BOOL DeletePen(gdix_Pen* pen);

	static BOOL CreateGraphics(HDC hdc, gdix_Graphics**);
	static BOOL DeleteGraphics(gdix_Graphics* graphics);
	static BOOL SetSmoothingMode(gdix_Graphics* graphics, gdix_SmoothingMode mode);

	static BOOL DrawLine(gdix_Graphics* graphics, gdix_Pen* pen, const gdix_PointF* from, const gdix_PointF* to);
	static BOOL DrawPolygon(gdix_Graphics* graphics, gdix_Pen* pen, const gdix_PointF* points, int count);
	
	static BOOL DrawLine(CGdiPlusGraphics& graphics, CGdiPlusPen& pen, const POINT& from, const POINT& to);
	static BOOL DrawPolygon(CGdiPlusGraphics& graphics, CGdiPlusPen& pen, const POINT points[], int count);

	static gdix_ARGB MakeARGB(COLORREF color, BYTE alpha = 255);

protected:
	static HMODULE s_hGdiPlus;
	static ULONG_PTR s_GdiToken;

protected:
	static BOOL Initialize(); // initialize on demand
	static void Free();
};

#endif // !defined(AFX_GDIPLUS_H__41B5F6AC_E7D4_49CA_9E2F_96FDA94EBB28__INCLUDED_)