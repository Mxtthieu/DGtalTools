/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/
/**
 * @file PBMImageReader.cpp
 * @ingroup Tools
 * @author Nicolas Normand (\c Nicolas.Normand@polytech.univ-nantes.fr)
 * LUNAM Université, Université de Nantes, IRCCyN UMR CNRS 6597
 *
 * @date 2012/09/28
 *
 * LUTBasedNSDistanceTransform computes the 2D translated neighborhood-sequence
 * distance transform of a binary image. It reads the input images from its
 * standard input and writes the result to its standard output.
 *
 * This file is part of the DGtal library.
 */

#include "PBMImageReader.h"
extern "C" {
#include "pbm.h"
}

PBMImageReader::PBMImageReader(ImageConsumer<BinaryPixelType>* consumer, FILE *input) :
    super(consumer),
    _input(input)
{
}

void PBMImageReader::produceAllRows() {
    BinaryPixelType *inputRow;
    int cols, rows;
    int format;

    pbm_readpbminit(_input, &cols, &rows, &format);
    inputRow = pbm_allocrow(cols);
    _consumer->beginOfImage(cols, rows);
    for (int row = 0; row < rows; row++) {
	pbm_readpbmrow(_input, inputRow, cols, format);
	_consumer->processRow(inputRow);
    }
    _consumer->endOfImage();
    pbm_freerow(inputRow);
}