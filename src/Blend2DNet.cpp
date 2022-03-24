#include "Blend2DNet.h"

class Blend2DNet_BLImageCodecImpl : public Blend2DNet_BLImageCodec {
public:
  virtual BLResult FindByName(wchar_t* name) override
  {
    size_t len = wcslen(name);
    char* buf = new char[len + 1];
    size_t newLen = wcstombs(buf, name, len);
    if (newLen > 0u)
      buf[newLen] = '\0';
    auto res = codec.findByName(buf);
    delete[] buf;
    return res;
  }
protected:
  friend class Blend2DNet_BLImageImpl;
};

class Blend2DNet_BLPathImpl : public Blend2DNet_BLPath {
public:
  virtual BLResult MoveTo(double p0, double p1) override {
    return path.moveTo(p0,p1);
  }
  virtual BLResult CubicTo(double x1, double y1, double x2, double y2, double x3, double y3) override {
    return path.cubicTo(x1, y1, x2, y2, x3, y3);
  }
private:
  friend class Blend2DNet_BLContextImpl;
};

class Blend2DNet_BLImageImpl : public Blend2DNet_BLImage {
public:
  virtual BLResult ReadFromFile(wchar_t* filePath) override {
    size_t len = wcslen(filePath);
    char* buf = new char[len+1];
    size_t newLen = wcstombs(buf, filePath, len);
    if (newLen > 0u)
      buf[newLen] = '\0';
    BLResult res = img.readFromFile(buf);
    delete[] buf;
    return res;
  }

  virtual BLResult WriteToFile(wchar_t* filePath, Blend2DNet_BLImageCodec* codec) override
  {
    size_t len = wcslen(filePath);
    char* buf = new char[len + 1];
    size_t newLen = wcstombs(buf, filePath, len);
    if (newLen > 0u)
      buf[newLen] = '\0';
    auto result = img.writeToFile(buf, codec->codec);
    delete[] buf;
    return result;
  }
protected:
  virtual void Init(int w, int h, BLFormat f) override {
    blImageInitAs(&img, w, h, f);
  }
private:

  friend class Blend2DNetImpl;
};

class Blend2DNet_BLContextImpl : public Blend2DNet_BLContext {
public:
  virtual BLResult SetCompOp(BLCompOp compOp) override
  {
    return context.setCompOp(compOp);
  }
  virtual BLResult FillAll() override
  {
    return context.fillAll();
  }
  virtual BLResult SetFillStyle(BLRgba32& rgba) override
  {
    return context.setFillStyle(rgba);
  }
  virtual BLResult FillPath(Blend2DNet_BLPath* path) override
  {
    return context.fillPath(path->path);
  }
  virtual BLResult End() override {
    return context.end();
  }
protected:
  void Init(BLImage& img) {
    blContextInitAs(&context, &img, nullptr);
  }
  BLContext context;

  friend class Blend2DNetImpl;
};

class Blend2DNetImpl : public Blend2DNet
{
public:
  virtual Blend2DNet_BLImage* Blend2DNetImpl::CreateImage(int w, int h, BLFormat f)
  {
    Blend2DNet_BLImageImpl* instance = new Blend2DNet_BLImageImpl();
    instance->Init(w, h, f);
    return instance;
  }

  virtual Blend2DNet_BLImage* CreateImage() override
  {
    Blend2DNet_BLImageImpl* instance = new Blend2DNet_BLImageImpl();
    return instance;
  }

  virtual Blend2DNet_BLContext* Blend2DNetImpl::CreateContext(Blend2DNet_BLImage* img) override
  {
    Blend2DNet_BLContextImpl* instance = new Blend2DNet_BLContextImpl();
    instance->Init(img->img);
    return instance;
  }

  virtual Blend2DNet_BLPath* CreatePath() override
  {
    Blend2DNet_BLPathImpl* path = new Blend2DNet_BLPathImpl();
    return path;
  };

  virtual Blend2DNet_BLImageCodec* CreateImageCodec() override
  {
    Blend2DNet_BLImageCodecImpl* codec= new Blend2DNet_BLImageCodecImpl();
    return codec;
  }
};

Blend2DNet* CreateInstance()
{
  return new Blend2DNetImpl();
};

int TestInterop()
{
  return 42;
};
