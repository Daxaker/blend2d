#include "Blend2DNet.h"

//BLImage* Blend2DNet::CreateImage(int w, int h, BLFormat f) {
//  BLImage* img = new BLImage(w, h, f);
//  return img; 
//}

class Blend2DNet_BLImageImpl : public Blend2DNet_BLImage {
public:
  virtual void Init(int w, int h, BLFormat f);
private:
  BLImage img;
};

Blend2DNet_BLImage* Blend2DNetImpl::CreateImage(int w, int h, BLFormat f)
{
  Blend2DNet_BLImageImpl* instance = new Blend2DNet_BLImageImpl();
  instance->Init(w, h, f);
  return instance;
}

void Blend2DNet_BLImageImpl::Init(int w, int h, BLFormat f)
{
  blImageInitAs(&img, w, h, f);
}
