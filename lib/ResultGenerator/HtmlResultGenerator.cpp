////////////////////////////////////////////////////////////////////////////////
/// @brief html result generators
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2011 triagens GmbH, Cologne, Germany
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
/// @author Dr. Frank Celler
/// @author Achim Brandt
/// @author Copyright 2008-2011, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#include "HtmlResultGenerator.h"

#include <math.h>

#include <Logger/Logger.h>
#include <Basics/StringBuffer.h>
#include <Basics/StringUtils.h>
#include <Variant/VariantArray.h>
#include <Variant/VariantBlob.h>
#include <Variant/VariantBoolean.h>
#include <Variant/VariantDate.h>
#include <Variant/VariantDatetime.h>
#include <Variant/VariantDouble.h>
#include <Variant/VariantFloat.h>
#include <Variant/VariantInt16.h>
#include <Variant/VariantInt32.h>
#include <Variant/VariantInt64.h>
#include <Variant/VariantMatrix2.h>
#include <Variant/VariantNull.h>
#include <Variant/VariantString.h>
#include <Variant/VariantUInt16.h>
#include <Variant/VariantUInt32.h>
#include <Variant/VariantUInt64.h>
#include <Variant/VariantVector.h>

using namespace triagens::basics;

namespace triagens {
  namespace rest {

    // -----------------------------------------------------------------------------
    // output methods
    // -----------------------------------------------------------------------------

    namespace {
      void generateVariantArray (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        VariantArray* array = dynamic_cast<VariantArray*>(object);
        vector<string> const& attributes = array->getAttributes();
        vector<VariantObject*> const& values = array->getValues();

        // generate attributes
        vector<string>::const_iterator ai = attributes.begin();
        vector<VariantObject*>::const_iterator vi = values.begin();

        output.appendText("<table border=\"1\">\n");

        for (;  ai != attributes.end() && vi != values.end();  ++ai, ++vi) {
          output.appendText("<tr>\n");

          output.appendText("<th>\n");
          output.appendText(StringUtils::escapeHtml(*ai));
          output.appendText("</th>\n");

          output.appendText("<td>\n");
          generator->generateVariant(output, *vi);
          output.appendText("</td>\n");

          output.appendText("</tr>\n");
        }

        output.appendText("</table>\n");
      }



      void generateVariantBoolean (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantBoolean*>(object)->getValue());
      }



      void generateVariantBlob (ResultGenerator const*, StringBuffer& output, VariantObject* object) {
        VariantBlob* blob = dynamic_cast<VariantBlob*>(object);

        string v(blob->getValue(), blob->getLength());

        output.appendText(StringUtils::escapeHtml(StringUtils::escapeUnicode(v)));
      }



      void generateVariantDate (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantDate*>(object)->getValue());
      }



      void generateVariantDatetime (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantDatetime*>(object)->getValue());
      }



      void generateVariantDouble (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantDouble*>(object)->getValue());
      }



      void generateVariantFloat (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantFloat*>(object)->getValue());
      }



      void generateVariantInt16 (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantInt16*>(object)->getValue());
      }



      void generateVariantInt32 (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantInt32*>(object)->getValue());
      }



      void generateVariantInt64 (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantInt64*>(object)->getValue());
      }



      void generateVariantMatrix2 (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        VariantMatrix2* matrix2 = dynamic_cast<VariantMatrix2*>(object);
        output.appendText("<table border=\"1\" cellspacing=\"0\">\n");

        output.appendText("<tr><th></th>\n");

        vector<string> const& dx = matrix2->getDimension(0);
        vector<string> const& dy = matrix2->getDimension(1);

        for (vector<string>::const_iterator i = dy.begin();  i != dy.end();  ++i) {
          output.appendText("<th>");
          generator->generateAtom(output, *i);
          output.appendText("</th>\n");
        }

        size_t x = 0;

        for (vector<string>::const_iterator j = dx.begin();  j != dx.end();  ++j, ++x) {
          output.appendText("<tr>\n");

          output.appendText("<th>");
          generator->generateAtom(output, *j);
          output.appendText("</th>\n");

          size_t y = 0;

          for (vector<string>::const_iterator i = dy.begin();  i != dy.end();  ++i, ++y) {
            VariantObject* obj = matrix2->getValue(x, y);

            output.appendText("<td>");

            if (obj != 0) {
              generator->generateVariant(output, obj);
            }

            output.appendText("</td>\n");
          }

          output.appendText("</tr>\n");
        }

        output.appendText("</tr>\n");

        output.appendText("</table>\n");
      }



      void generateVariantNull (ResultGenerator const*, StringBuffer& output, VariantObject*) {
        output.appendText("[null]");
      }



      void generateVariantString (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantString*>(object)->getValue());
      }



      void generateVariantUInt16 (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantUInt16*>(object)->getValue());
      }



      void generateVariantUInt32 (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantUInt32*>(object)->getValue());
      }



      void generateVariantUInt64 (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        generator->generateAtom(output, dynamic_cast<VariantUInt64*>(object)->getValue());
      }



      void generateVariantVector (ResultGenerator const* generator, StringBuffer& output, VariantObject* object) {
        VariantVector* vec = dynamic_cast<VariantVector*>(object);
        vector<VariantObject*> const& values = vec->getValues();
        size_t pos = values.size();

        output.appendText("<table border=\"1\" cellspacing=\"0\">\n");
        output.appendText("<tr>");

        for (vector<VariantObject*>::const_iterator vi = values.begin();  vi != values.end();  ++pos, ++vi) {
          output.appendText("<td>");
          generator->generateVariant(output, *vi);
          output.appendText("</td>\n");
        }

        output.appendText("</tr>");
        output.appendText("</table>");
      }
    }

    // -----------------------------------------------------------------------------
    // static public methods
    // -----------------------------------------------------------------------------

    void HtmlResultGenerator::initialise () {
      registerObject(VariantObject::VARIANT_ARRAY, RESULT_GENERATOR_HTML, generateVariantArray);
      registerObject(VariantObject::VARIANT_BOOLEAN, RESULT_GENERATOR_HTML, generateVariantBoolean);
      registerObject(VariantObject::VARIANT_BLOB, RESULT_GENERATOR_HTML, generateVariantBlob);
      registerObject(VariantObject::VARIANT_DATE, RESULT_GENERATOR_HTML, generateVariantDate);
      registerObject(VariantObject::VARIANT_DATETIME, RESULT_GENERATOR_HTML, generateVariantDatetime);
      registerObject(VariantObject::VARIANT_DOUBLE, RESULT_GENERATOR_HTML, generateVariantDouble);
      registerObject(VariantObject::VARIANT_FLOAT, RESULT_GENERATOR_HTML, generateVariantFloat);
      registerObject(VariantObject::VARIANT_INT16, RESULT_GENERATOR_HTML, generateVariantInt16);
      registerObject(VariantObject::VARIANT_INT32, RESULT_GENERATOR_HTML, generateVariantInt32);
      registerObject(VariantObject::VARIANT_INT64, RESULT_GENERATOR_HTML, generateVariantInt64);
      registerObject(VariantObject::VARIANT_MATRIX2, RESULT_GENERATOR_HTML, generateVariantMatrix2);
      registerObject(VariantObject::VARIANT_NULL, RESULT_GENERATOR_HTML, generateVariantNull);
      registerObject(VariantObject::VARIANT_STRING, RESULT_GENERATOR_HTML, generateVariantString);
      registerObject(VariantObject::VARIANT_UINT16, RESULT_GENERATOR_HTML, generateVariantUInt16);
      registerObject(VariantObject::VARIANT_UINT32, RESULT_GENERATOR_HTML, generateVariantUInt32);
      registerObject(VariantObject::VARIANT_UINT64, RESULT_GENERATOR_HTML, generateVariantUInt64);
      registerObject(VariantObject::VARIANT_VECTOR, RESULT_GENERATOR_HTML, generateVariantVector);
    }

    // -----------------------------------------------------------------------------
    // ResultGenerator methods
    // -----------------------------------------------------------------------------

    void HtmlResultGenerator::generateResultBegin (StringBuffer& output, VariantObject*) const {
      output.appendText("<html>\n<head>\n<title>Result</title>\n</head>\n<body>\n");
    }



    void HtmlResultGenerator::generateResultEnd (StringBuffer& output, VariantObject*) const {
      output.appendText("</body>\n</html>\n");
    }



    void HtmlResultGenerator::generateAtom (StringBuffer& output, string const& value) const {
      output.appendText(StringUtils::escapeHtml(value));
    }



    void HtmlResultGenerator::generateAtom (StringBuffer& output, char const* value) const {
      if (value == 0) {
        output.appendText("");
      }
      else {
        output.appendText(StringUtils::escapeHtml(value));
      }
    }



    void HtmlResultGenerator::generateAtom (StringBuffer& output, char const* value, size_t length, bool) const {
      if (value == 0) {
        output.appendText("");
      }
      else {
        string v(value, length);
        output.appendText(StringUtils::escapeHtml(v));
      }
    }



    void HtmlResultGenerator::generateAtom (StringBuffer& output, bool value) const {
      output.appendText(value ? "true" : "false");
    }


#ifdef _WIN32
    void HtmlResultGenerator::generateAtom (StringBuffer& output, double value) const {

      if (value == 0.0) {
        output.appendText("0.0", 3);
        return;
      }

      int intType = _fpclass(value);

      switch (intType) {
        case _FPCLASS_PN:
        case _FPCLASS_NN:
        case _FPCLASS_NZ:
        case _FPCLASS_PZ: {
          output.appendDecimal(value);
          break;
        }
        case _FPCLASS_NINF: {
          generateAtom(output, "-INF");
          break;
        }
        case _FPCLASS_PINF: {
          generateAtom(output, "INF");
          break;
        }
        default: {
          generateAtom(output, "NAN");
          break;
        }
      }
    }


    void HtmlResultGenerator::generateAtom (StringBuffer& output, float value) const {

      if (value == 0.0) {
        output.appendText("0.0", 3);
        return;
      }

      int intType = _fpclass(value);

      switch (intType) {
        case _FPCLASS_PN:
        case _FPCLASS_NN:
        case _FPCLASS_NZ:
        case _FPCLASS_PZ: {
          output.appendDecimal(value);
          break;
        }
        case _FPCLASS_NINF: {
          generateAtom(output, "-INF");
          break;
        }
        case _FPCLASS_PINF: {
          generateAtom(output, "INF");
          break;
        }
        default: {
          generateAtom(output, "NAN");
          break;
        }
      }
    }

#else
    void HtmlResultGenerator::generateAtom (StringBuffer& output, double value) const {
      if (value == 0.0) {
        output.appendText("0.0", 3);
      }
      else if (isnormal(value)) {
        output.appendDecimal(value);
      }
      else {
        int a = isinf(value);

        if (a == -1) {
          generateAtom(output, "-INF");
        }
        else if (a == 1) {
          generateAtom(output, "INF");
        }
        else /* if (isnan(value)) */ {
          generateAtom(output, "NAN");
        }
      }
    }



    void HtmlResultGenerator::generateAtom (StringBuffer& output, float value) const {
      if (value == 0.0) {
        output.appendText("0.0", 3);
      }
      else if (isnormal(value)) {
        output.appendDecimal(value);
      }
      else {
        int a = isinf(value);

        if (a == -1) {
          generateAtom(output, "-INF");
        }
        else if (a == 1) {
          generateAtom(output, "INF");
        }
        else /* if (isnan(value)) */ {
          generateAtom(output, "NAN");
        }
      }
    }
#endif


    void HtmlResultGenerator::generateAtom (StringBuffer& output, int16_t value) const {
      output.appendInteger(value);
    }



    void HtmlResultGenerator::generateAtom (StringBuffer& output, int32_t value) const {
      output.appendInteger(value);
    }



    void HtmlResultGenerator::generateAtom (StringBuffer& output, int64_t value) const {
      output.appendInteger(value);
    }



    void HtmlResultGenerator::generateAtom (StringBuffer& output, uint16_t value) const {
      output.appendInteger(value);
    }



    void HtmlResultGenerator::generateAtom (StringBuffer& output, uint32_t value) const {
      output.appendInteger(value);
    }



    void HtmlResultGenerator::generateAtom (StringBuffer& output, uint64_t value) const {
      output.appendInteger(value);
    }
  }
}
