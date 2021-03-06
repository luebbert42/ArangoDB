////////////////////////////////////////////////////////////////////////////////
/// @brief JSON data container
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2004-2012 triagens GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2012, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#include "Rest/JsonContainer.h"

namespace triagens {
  namespace rest {

////////////////////////////////////////////////////////////////////////////////
/// @brief constructs a JSON data container
////////////////////////////////////////////////////////////////////////////////

    JsonContainer::JsonContainer (TRI_memory_zone_t* zone, TRI_json_t* data)
      : _memoryZone(zone), _data(data) {
    }

////////////////////////////////////////////////////////////////////////////////
/// @brief destroys a JSON container
////////////////////////////////////////////////////////////////////////////////
    
    JsonContainer::~JsonContainer () {
      if (_data) {
        TRI_FreeJson(_memoryZone, _data);
      } 
    }
  }
}
