/******************************************************************************
 *
 * Purpose:  Declaration of the CPCIDSK_BLUT class.
 *
 ******************************************************************************
 * Copyright (c) 2015
 * PCI Geomatics, 90 Allstate Parkway, Markham, Ontario, Canada.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ****************************************************************************/
#ifndef INCLUDE_SEGMENT_PCIDSK_BLUT_H
#define INCLUDE_SEGMENT_PCIDSK_BLUT_H

#include "pcidsk_config.h"
#include "pcidsk_blut.h"
#include "pcidsk_buffer.h"
#include "segment/cpcidsksegment.h"


namespace PCIDSK
{
    class PCIDSKFile;

    /************************************************************************/
    /*                            CPCIDSK_BLUT                               */
    /************************************************************************/

    class CPCIDSK_BLUT : virtual public CPCIDSKSegment,
                        public PCIDSK_BLUT
    {
    public:
        CPCIDSK_BLUT( PCIDSKFile *file, int segment, const char *segment_pointer);

        virtual     ~CPCIDSK_BLUT();

        virtual void ReadBLUT( std::vector<BLUTEntry>& vBLUT ) override;
        virtual void WriteBLUT( const std::vector<BLUTEntry>& vBLUT ) override;
    };
} // end namespace PCIDSK

#endif // INCLUDE_SEGMENT_PCIDSK_BLUT_H
