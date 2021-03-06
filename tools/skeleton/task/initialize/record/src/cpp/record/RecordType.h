/*
 * Copyright 2010-2013 DIMA Research Group, TU Berlin
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

#ifndef ${uc{record_name}}_H_
#define ${uc{record_name}}_H_

#include "record/AbstractRecord.h"

namespace ${{dgen_ns}} {

// forward declarations
class ${{record_name}}Generator;
class ${{record_name}}SetterChain;

// ${{record_name}} class
class ${{record_name}}: public Myriad::AbstractRecord
{
public:

    ${{record_name}}()
    {
    }

private:

};

} // namespace ${{dgen_ns}}


namespace Myriad {

// record traits specialization
template<> struct RecordTraits<${{dgen_ns}}::${{record_name}}>
{
    typedef ${{dgen_ns}}::${{record_name}}Generator GeneratorType;
    typedef ${{dgen_ns}}::${{record_name}}SetterChain SetterChainType;
};

// forward declaration of the collector method specialization
template<> void OutputTraits<${{dgen_ns}}::${{record_name}}>::CollectorType::collect(const ${{dgen_ns}}::${{record_name}}& record);

} // namespace Myriad

#endif /* ${uc{record_name}}_H_ */
