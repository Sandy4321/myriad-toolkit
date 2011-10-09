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
 * @author: Alexander Alexandrov <alexander.s.alexandrov@campus.tu-berlin.de>
 */

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <Poco/Exception.h>

namespace Myriad {

POCO_DECLARE_EXCEPTION(, ConfigException, Poco::Exception)
POCO_DECLARE_EXCEPTION(, FeatureConfigurationException, Poco::Exception)
POCO_DECLARE_EXCEPTION(, IntegerOverflowException, Poco::LogicException)

}  // namespace Myriad

#endif /* EXCEPTIONS_H_ */
