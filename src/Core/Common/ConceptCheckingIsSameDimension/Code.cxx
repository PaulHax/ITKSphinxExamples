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
#include "itkConceptChecking.h"

template <typename TImage, unsigned int VDimension>
void
CheckIfDimensionIsTheSame(const TImage * const)
{
  itkConceptMacro(nameOfCheck, (itk::Concept::SameDimension<TImage::ImageDimension, VDimension>));
}
int
main()
{
  constexpr unsigned int Dimension = 2;
  using PixelType = unsigned char;
  using ImageType = itk::Image<PixelType, Dimension>;
  auto image = ImageType::New();

  CheckIfDimensionIsTheSame<ImageType, 2>(image.GetPointer());

  using ImageType2 = itk::Image<PixelType, Dimension>;

  CheckIfDimensionIsTheSame<ImageType, ImageType2::ImageDimension>(image.GetPointer());

  return EXIT_SUCCESS;
}
