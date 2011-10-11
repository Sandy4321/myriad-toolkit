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

#ifndef OUTPUTSTREAM_H_
#define OUTPUTSTREAM_H_

#include "config/GeneratorConfig.h"
#include "record/Record.h"

#include <Poco/FileStream.h>
#include <Poco/Logger.h>

using namespace Poco;

namespace Myriad {

class MyriadOutputStream: public FileOutputStream
{
};

class OutputCollector
{
public:

	OutputCollector(const String& generatorName, const GeneratorConfig& config) :
		_isOpen(false), _logger(Logger::get("collector."+generatorName))
	{
		Path path(config.getString(format("generator.%s.output-file", generatorName)));
		path.makeAbsolute(config.getString("application.output-dir"));

		_path = path.toString();
	}

	OutputCollector(const OutputCollector& o) : _path(o._path), _isOpen(false), _logger(Logger::get(o._logger.name()))
	{
		if (o._isOpen)
		{
			open();
		}
	}

	~OutputCollector()
	{
		close();
	}

	void open()
	{
		if (!_isOpen)
		{
			_out.open(_path, std::ios::trunc | std::ios::binary);
			_isOpen = true;
		}
		else
		{
			throw LogicException(format("Can't open already opened FileOutputStream %s", _path));
		}
	}

	void close()
	{
		if (_isOpen)
		{
			_logger.debug(format("Closing output file %s", _path));
			_out.close();
		}
	}

	/**
	 * Output collection method.
	 */
	template<typename RecordType> void collect(const RecordType& record);

private:

	/**
	 * The path of the underlying OutputStream.
	 */
	std::string _path;

	/**
	 * The underlying output stream.
	 */
	MyriadOutputStream _out;

	/**
	 * A boolean flag indicating that the underlying output stream is open.
	 */
	bool _isOpen;

	/**
	 * Logger instance.
	 */
	Logger& _logger;
};

template<typename RecordType> inline void OutputCollector::collect(const RecordType& record)
{
	_out << record;
}

} // namespace Myriad

#endif /* GENERATOROUTPUTSTREAM_H_ */
