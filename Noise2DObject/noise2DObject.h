//-----------------------------------------------------------------------------
// Copyright (c) 2016 Alex Piola
// Some parts are Copyright (c) 2012 GarageGames, LLC
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//-----------------------------------------------------------------------------

#ifndef _NOISE2DOBJECT_H_
#define _NOISE2DOBJECT_H_


#ifndef _NOISE2D_H_
#include "util/noise2d.h"
#endif // !_NOISE2D_H_

#ifndef _CONSOLEINTERNAL_H_
#include "console/consoleInternal.h"
#endif

class Noise2DObject : public SimObject
{
   typedef SimObject Parent;
protected:
   bool mAutogenerate;
   U32 mNoiseSize;
   Noise2D mNoise;
   Vector<F32> mNoiseData;
   Point2F mMinMaxNoise;
   U32 mSeed;
   U32 mInterval;
   F32 mHeight;
   F32 mOctaves;

public:

   Noise2DObject();
   ~Noise2DObject();

   static void initPersistFields();
   bool onAdd();
   void onRemove();
   void setSeed(U32 seed);
   U32 getSeed();
   void setNoiseSize(U32 noiseSize);
   U32 getNoiseSize();
   void setInterval(U32 interval);
   U32 getInterval();
   void setHeight(F32 height);
   F32 getHeight();
   void setOctaves(F32 octaves);
   F32 getOctaves();

   bool generateFbmNoise();

   F32 getNoise(Point2I position);

   DECLARE_CONOBJECT(Noise2DObject);

   DECLARE_CALLBACK(void, onAdd, (SimObjectId ID) );
   DECLARE_CALLBACK(void, onRemove, (SimObjectId ID) );

};

#endif // !_NOISE2DOBJECT_H_