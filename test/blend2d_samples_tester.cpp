// blend2d_samples_tester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../../src/blend2d.h"
#include "../../src/Blend2DNet.h"

void DirectCall() {

  BLImage img(480, 480, BL_FORMAT_PRGB32);

  // Attach a rendering context into `img`.
  BLContext ctx(img);

  // Clear the image.
  ctx.setCompOp(BL_COMP_OP_SRC_COPY);
  ctx.setFillStyle(BLRgba32(0xFF00FFFF));
  ctx.fillAll();

  // Fill some path.
  BLPath path;
  path.moveTo(26, 31);
  path.cubicTo(642, 132, 587, -136, 25, 464);
  path.cubicTo(882, 404, 144, 267, 27, 31);

  ctx.setCompOp(BL_COMP_OP_SRC_OVER);
  ctx.setFillStyle(BLRgba32(0xFFFFFFFF));
  ctx.fillPath(path);

  // Detach the rendering context from `img`.
  ctx.end();

  // Let's use some built-in codecs provided by Blend2D.
  BLImageCodec codec;
  codec.findByName("PNG");
  img.writeToFile("bl-getting-started-1.png", codec);
}

void ProxyCall() {
  auto instance = CreateInstance();
  auto img = instance->CreateImage(480, 480, BL_FORMAT_PRGB32);
  auto ctx = instance->CreateContext(img);
  ctx->SetCompOp(BL_COMP_OP_SRC_COPY);
  BLRgba32 rgba(0xFF00FFFF);
  ctx->SetFillStyle(rgba);
  ctx->FillAll();
  auto path = instance->CreatePath();
  path->MoveTo(26, 31);
  path->CubicTo(642, 132, 587, -136, 25, 464);
  path->CubicTo(882, 404, 144, 267, 27, 31);
  ctx->SetCompOp(BL_COMP_OP_SRC_OVER);
  BLRgba32 rgba32(0xFFFFFFFF);
  ctx->SetFillStyle(rgba32);
  ctx->End();
  auto codec = instance->CreateImageCodec();
  wchar_t str[4] = L"PNG";
  codec->FindByName(str);
  wchar_t str1[25] = L"bl-getting-started-1.png";
  img->WriteToFile(str1, codec);
}

int main()
{
  //DirectCall();
  ProxyCall();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
