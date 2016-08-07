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

#include "platform/platform.h"
#include "noise2DObject.h"
#include "console/engineAPI.h"


IMPLEMENT_CONOBJECT(Noise2DObject);

ConsoleDocClass(Noise2DObject, "@brief class to generate noise");

IMPLEMENT_CALLBACK(Noise2DObject, onAdd, void, (SimObjectId ID), (ID),
   "Called when this ScriptObject is added to the system.\n"
   "@param ID Unique object ID assigned when created (%this in script).\n");

IMPLEMENT_CALLBACK(Noise2DObject, onRemove, void, (SimObjectId ID), (ID),
   "Called when this ScriptObject is removed from the system.\n"
   "@param ID Unique object ID assigned when created (%this in script).\n");




Noise2DObject::Noise2DObject()
{
   mAutogenerate = false;
   mNoiseSize = 256;
   mMinMaxNoise = Point2F(0.f,0.f);
   mSeed = 1;
   mInterval = 12;
   mHeight = 1.0f;
   mOctaves = 5.0f;
}

Noise2DObject::~Noise2DObject()
{
}

void Noise2DObject::initPersistFields()
{
   addGroup("Noise");
      addField("autogenerate", TypeBool, Offset(mAutogenerate, Noise2DObject),
      "If true, the noise will be generated automatically onAdd.");
      addField("noiseSize", TypeS32, Offset(mNoiseSize, Noise2DObject),
      "The size of the array where the noise is generated.");
      addField("seed", TypeS32, Offset(mSeed, Noise2DObject),
      "The random seed for the noise.");
      addField("interval", TypeS32, Offset(mInterval, Noise2DObject),
      "The interval for the noise.");
      addField("height", TypeF32, Offset(mHeight, Noise2DObject),
      "The height of the noise.");
      addField("octaves", TypeF32, Offset(mOctaves, Noise2DObject),
      "The octaves of the noise.");
   endGroup("Noise");
   Parent::initPersistFields();
}

bool Noise2DObject::onAdd()
{
   if (!Parent::onAdd()) return false;

   mNoiseData.setSize(mNoiseSize*mNoiseSize);

   if (mAutogenerate) generateFbmNoise();

   onAdd_callback(getId());
   return true;
}

void Noise2DObject::onRemove()
{
   onRemove_callback(getId());
   Parent::onRemove();
}

void Noise2DObject::setSeed(U32 seed)
{
   mSeed = seed;
}

U32 Noise2DObject::getSeed()
{
   return mSeed;
}

void Noise2DObject::setNoiseSize(U32 noiseSize)
{
   mNoiseSize = noiseSize;
}

U32 Noise2DObject::getNoiseSize()
{
   return mNoiseSize;
}

void Noise2DObject::setInterval(U32 interval)
{
   mInterval = interval;
}

U32 Noise2DObject::getInterval()
{
   return mInterval;
}

void Noise2DObject::setHeight(F32 height)
{
   mHeight = height;
}

F32 Noise2DObject::getHeight()
{
   return mHeight;
}

void Noise2DObject::setOctaves(F32 octaves)
{
   mOctaves = octaves;
}

F32 Noise2DObject::getOctaves()
{
   return mOctaves;
}


bool Noise2DObject::generateFbmNoise()
{
   mNoise.setSeed(mSeed);
   mNoiseData.setSize(mNoiseSize * mNoiseSize);
   mNoise.fBm(&mNoiseData, mNoiseSize, mInterval, mHeight, mOctaves);

   mNoise.getMinMax(&mNoiseData, &mMinMaxNoise.x, &mMinMaxNoise.y, mNoiseSize);
   return true;
}

F32 Noise2DObject::getNoise(Point2I position)
{
   F32 noiseVal = mNoiseData[(position.x % mNoiseSize) +
      ((position.y % mNoiseSize) * mNoiseSize)];
   return noiseVal;
}


DefineEngineMethod(Noise2DObject, setSeed, void, (S32 seed),,
   "@brief Sets the Noise2DObject random seed.\n"
   "@param S32 seed.\n")
{
   object->setSeed(seed);
}

DefineEngineMethod(Noise2DObject, getSeed, S32, (),,
   "@brief returns the Noise2DObject random seed.\n"
   "@return S32 seed.\n")
{
   return object->getSeed();
}

DefineEngineMethod(Noise2DObject, setNoiseSize, void, (S32 size), ,
   "@brief Sets the Noise2DObject noise array size.\n"
   "@param S32 size.\n")
{
   object->setNoiseSize(size);
}

DefineEngineMethod(Noise2DObject, getNoiseSize, S32, (), ,
   "@brief returns the Noise2DObject noise array size.\n"
   "@return S32 size.\n")
{
   return object->getNoiseSize();
}

DefineEngineMethod(Noise2DObject, setInterval, void, (S32 interval), ,
   "@brief Sets the Noise2DObject noise interval.\n"
   "@param S32 interval.\n")
{
   object->setInterval(interval);
}

DefineEngineMethod(Noise2DObject, getInterval, S32, (), ,
   "@brief returns the Noise2DObject noise interval.\n"
   "@return S32 interval.\n")
{
   return object->getInterval();
}

DefineEngineMethod(Noise2DObject, setHeight, void, (F32 height), ,
   "@brief Sets the Noise2DObject noise height.\n"
   "@param F32 height.\n")
{
   object->setHeight(height);
}

DefineEngineMethod(Noise2DObject, getHeight, F32, (), ,
   "@brief returns the Noise2DObject noise height.\n"
   "@return F32 height.\n")
{
   return object->getHeight();
}

DefineEngineMethod(Noise2DObject, setOctaves, void, (F32 octaves), ,
   "@brief Sets the Noise2DObject noise octaves.\n"
   "@param F32 octaves.\n")
{
   object->setOctaves(octaves);
}

DefineEngineMethod(Noise2DObject, getOctaves, F32, (), ,
   "@brief returns the Noise2DObject noise octaves.\n"
   "@return F32 octaves.\n")
{
   return object->getOctaves();
}


DefineEngineMethod(Noise2DObject, generateFbmNoise, bool, (), ,
   "@brief generate the noise.\n"
   "@return true when done.\n")
{
   return object->generateFbmNoise();
}

DefineEngineMethod(Noise2DObject, getNoise, F32, (Point2I position), ,
   "@brief return the noise at position Point2I(x,y)\n"
   "@return F32 noise height.\n")
{
   return object->getNoise(position);
}