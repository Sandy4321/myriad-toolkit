'''
Copyright 2010-2011 DIMA Research Group, TU Berlin

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
 
Created on Oct 14, 2011

@author: Alexander Alexandrov <alexander.s.alexandrov@campus.tu-berlin.de>
'''

import optparse, types

TASK_PREFIX = "abstract"

class TaskOptions(optparse.OptionParser):
    '''
    classdocs
    '''
    
    args_list = []
    
    def __init__(self, qname, dispatcher, description=None):
        optparse.OptionParser.__init__(self, usage="%prog "+qname+" [opts] [args]", description=description, version=dispatcher.VERSION, add_help_option=False)

    def formatUsage(self):
        formatter = optparse.IndentedHelpFormatter(width=80)
        formatter.store_option_strings(self)

        formatter.indent()
        lines = [ formatter._format_text(self.expand_prog_name(self.usage)) + "\n" ]
        formatter.dedent()

        return [ formatter.format_heading("Usage") ] + lines

    def formatDescription(self):
        formatter = optparse.IndentedHelpFormatter(width=80)
        formatter.store_option_strings(self)

        formatter.indent()
        lines = [ formatter.format_description(self.description) ]
        formatter.dedent()

        return [ formatter.format_heading("Description") ] + lines

    def formatArgsHelp(self):
        formatter = optparse.IndentedHelpFormatter(width=80)

        formatter.indent()
        for opt in self.args_list:
            metavar = opt.metavar or opt.dest.upper()
            strings = metavar.upper()
            formatter.option_strings[opt] = strings
        formatter.dedent()
        
        formatter.help_position = 31
        formatter.help_width = formatter.width - formatter.help_position

        formatter.indent()
        lines = [formatter.format_option(opt) for opt in self.args_list]
        formatter.dedent()
        
        return [ formatter.format_heading("Arguments") ] + lines

    def formatOptionsHelp(self):
        formatter = optparse.IndentedHelpFormatter(width=80)

        formatter.indent()
        for opt in self.option_list:
            strings = formatter.format_option_strings(opt)
            formatter.option_strings[opt] = strings
        formatter.dedent()
        
        formatter.help_position = 31
        formatter.help_width = formatter.width - formatter.help_position

        formatter.indent()
        lines = [formatter.format_option(opt) for opt in self.option_list]
        formatter.dedent()

        return [ formatter.format_heading("Options") ] + lines

    def format_help(self, formatter=None):
        class Positional(object):
            def __init__(self, args):
                self.option_groups = []
                self.option_list = args

        positional = Positional(self.positional)
        formatter = optparse.IndentedHelpFormatter()
        formatter.store_option_strings(positional)
        output = ['\n', formatter.format_heading("Positional Arguments")]
        formatter.indent()
        pos_help = [formatter.format_option(opt) for opt in self.positional]
        pos_help = [line.replace('--', '') for line in pos_help]
        output += pos_help
        return optparse.OptionParser.format_help(self, formatter) + ''.join(output)

    def add_positional_argument(self, *args, **kwargs):
        
        if type(args[0]) in types.StringTypes:
            option = self.option_class(*args, **kwargs)
        elif len(args) == 1 and not kwargs:
            option = args[0]
            if not isinstance(option, optparse.Option):
                raise TypeError, "not an Option instance: %r" % option
        else:
            raise TypeError, "invalid arguments"

        self._check_conflict(option)

        self.args_list.append(option)
        option.container = self

        if option.dest is not None:     # option has a dest, we need a default
            if option.default is not ("NO", "DEFAULT"):
                self.defaults[option.dest] = option.default
            elif option.dest not in self.defaults:
                self.defaults[option.dest] = None

        return option
    

class AbstractTask(object):
    '''
    classdocs
    '''
    
    __dispatcher = None
    __group = None
    __name = None
    __description = None
    
    _argsParser = None

    def __init__(self, dispatcher, group="default", name="default", description=""):
        '''
        Constructor
        '''
        self.__dispatcher = dispatcher
        self.__group = group
        self.__name = name
        self.__description = description
        
    def group(self):
        return self.__group
        
    def name(self):
        return self.__name
        
    def qname(self):
        return "%s:%s" % (self.__group, self.__name)
        
    def description(self, *args, **keywargs):
        return self.__description
        
    def argsParser(self):
        if self._argsParser == None:
            self._argsParser = TaskOptions(qname=self.qname(), dispatcher=self.__dispatcher, description=self.__description)
            self._initArgsParser()
        return self._argsParser
    
    def _initArgsParser(self):
        pass