/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#include "itkImage.h"
#include "itkBinaryFunctorImageFilter.h"
#include "itkAndImageFilter.h"

using ImageType = itk::Image<unsigned char, 2>;
static void
CreateImage(ImageType::Pointer image);

int
main()
{
  auto image1 = ImageType::New();
  CreateImage(image1);
  image1->FillBuffer(2);

  auto image2 = ImageType::New();
  CreateImage(image2);
  image2->FillBuffer(5);

  using FilterType =
    itk::BinaryFunctorImageFilter<ImageType, ImageType, ImageType, itk::Functor::AND<ImageType::PixelType>>;

  auto filter = FilterType::New();
  filter->SetInput1(image1);
  filter->SetInput2(image2);
  filter->Update();

  itk::Index<2> pixelIndex;
  pixelIndex.Fill(0);

  ImageType::PixelType input1PixelValue = image1->GetPixel(pixelIndex);
  ImageType::PixelType input2PixelValue = image2->GetPixel(pixelIndex);
  ImageType::PixelType outputPixelValue = filter->GetOutput()->GetPixel(pixelIndex);

  std::cout << "pixel1 was = " << input1PixelValue << std::endl;
  std::cout << "pixel2 was = " << input2PixelValue << std::endl;
  std::cout << "output is = " << outputPixelValue << std::endl;

  return EXIT_SUCCESS;
}

void
CreateImage(ImageType::Pointer image)
{
  ImageType::IndexType start;
  start.Fill(0);

  ImageType::SizeType size;
  size.Fill(10);

  ImageType::RegionType region(start, size);
  image->SetRegions(region);
  image->Allocate();
}
