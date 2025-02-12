/***********************************************************************
    created:    Fri Oct 07 2011
    author:     Paul D Turner <paul@cegui.org.uk>
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2011 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#include "CEGUI/Precompiled.h"

#include "CEGUI/FactoryRegisterer.h"
#include "CEGUI/Logger.h"

// Start of CEGUI namespace section
namespace CEGUI
{
//----------------------------------------------------------------------------//
FactoryRegisterer::FactoryRegisterer(const String& type) :
    d_type(type)
{}

//----------------------------------------------------------------------------//
FactoryRegisterer::~FactoryRegisterer()
{}

//----------------------------------------------------------------------------//
void FactoryRegisterer::registerFactory() const
{
    if (this->isAlreadyRegistered())
        CEGUI::Logger::getSingleton().logEvent(
            "Factory for '" + CEGUI::String(d_type) +
            "' appears to be  already registered, skipping.",
            CEGUI::Informative);
    else
        this->doFactoryAdd();
}

//----------------------------------------------------------------------------//

} // End of  CEGUI namespace section

