#pragma once
#include "blend2d.h"

using namespace std;
class Blend2DNetImpl;
class Blend2DNet_BLImage;
class Blend2DNet_BLContext;
class Blend2DNet_BLPath;
class Blend2DNet_BLImageCodec;

class Blend2DNet
{
public:
  virtual Blend2DNet_BLImage* CreateImage(int w, int h, BLFormat f) = 0;
  virtual Blend2DNet_BLImage* CreateImage() = 0;
  virtual Blend2DNet_BLContext* CreateContext(Blend2DNet_BLImage* img) = 0;
  virtual Blend2DNet_BLPath* CreatePath() = 0;
  virtual Blend2DNet_BLImageCodec* CreateImageCodec() = 0;
};

class Blend2DNet_BLImageCodec {
public:
  BLImageCodec codec;
  virtual BLResult FindByName(wchar_t* name) = 0;
};

class Blend2DNet_BLPath
{
public:
  virtual BLResult MoveTo(double, double) = 0;
  virtual BLResult CubicTo(double x1, double y1, double x2, double y2, double x3, double y3) = 0;
};

class Blend2DNet_BLImage
{
public:
  virtual BLResult ReadFromFile(wchar_t*) = 0;
  virtual BLResult WriteToFile(wchar_t*, Blend2DNet_BLImageCodec*) = 0;
  BLImage img;
protected:
  virtual void Init(int w, int h, BLFormat f) = 0;
private:
  friend class Blend2DNet;
};

class Blend2DNet_BLContext {
public:
  virtual BLResult SetCompOp(BLCompOp) = 0;
  virtual BLResult FillAll() = 0;
  virtual BLResult SetFillStyle(BLRgba32& rgba) = 0;
  virtual BLResult FillPath(Blend2DNet_BLPath* path) = 0;
  virtual BLResult End() = 0;
};

extern "C"
{
  __declspec(dllexport) Blend2DNet* CreateInstance();
  __declspec(dllexport) int TestInterop();  
}

