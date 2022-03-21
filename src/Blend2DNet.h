#pragma once
#include "blend2d.h"

using namespace std;
class BLImage;
class Blend2DNet_BLImage;

class Blend2DNet
{
public:
  //BLImage* CreateImage(int width, int height, BLFormat format);
  virtual Blend2DNet_BLImage* CreateImage(int w, int h, BLFormat f) = 0;
};

class Blend2DNetImpl : public Blend2DNet
{
public:
  Blend2DNet_BLImage* CreateImage(int w, int h, BLFormat f);
};

Blend2DNet* CreateInstance()
{
  return new Blend2DNetImpl();
};

class Blend2DNet_BLImage
{
public:
  virtual void Init(int w, int h, BLFormat f) = 0;
};

