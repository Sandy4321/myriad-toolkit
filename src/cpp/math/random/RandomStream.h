/*
 * Copyright 2010-2011 DIMA Research Group, TU Berlin
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 * @author: Alexander Alexandrov <alexander.alexandrov@tu-berlin.de>
 */

#ifndef RANDOMSTREAM_H_
#define RANDOMSTREAM_H_

#include "math/random/CompoundEICG.h"
#include "math/random/HashRandomStream.h"
#include "math/random/NativeRandomStream.h"

using namespace std;

namespace Myriad {

//typedef CompoundEICG RandomStream;
typedef HashRandomStream RandomStream;
//typedef NativeRandomStream RandomStream;

} // namespace Myriad

#endif /* RANDOMSTREAM_H_ */
