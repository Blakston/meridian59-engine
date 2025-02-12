/***********************************************************************
	created:	Sun Jun 11 2006
	author:		Tomas Lindquist Olsen
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2006 Paul D Turner & The CEGUI Development Team
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

#include "CEGUI/widgets/ClippedContainer.h"
#include "CEGUI/CoordConverter.h"

// Start of CEGUI namespace section
namespace CEGUI
{
const String ClippedContainer::WidgetTypeName("ClippedContainer");
const String ClippedContainer::EventNamespace("ClippedContainer");

ClippedContainer::ClippedContainer(const String& type, const String& name) :
    Window(type, name),
    d_clipArea(0,0,0,0),
    d_clipperWindow(0)
{
}

ClippedContainer::~ClippedContainer(void)
{
}

Rectf ClippedContainer::getUnclippedInnerRect_impl(bool skipAllPixelAlignment) const
{
    // This is obviously doing nothing.  The reason being that whas this
    // used to to is now handled correctly via the fixed 'inner rect' usage,
    // meaning that the looknfeel named areas can be employed to do the correct
    // clipping.  Fixing the inner rect support actually broke this anyhow,
    // since it only worked because the inner rect support was broken.  As
    // such, ClippedContainer serves no useful purpose and will be removed.
    return Window::getUnclippedInnerRect_impl(skipAllPixelAlignment);
}

const Rectf& ClippedContainer::getClipArea(void) const
{
    return d_clipArea;
}

Window* ClippedContainer::getClipperWindow() const
{
    return d_clipperWindow;
}

void ClippedContainer::setClipArea(const Rectf& r)
{
    if (d_clipArea != r)
    {
        d_clipArea = r;
        invalidate();
        notifyClippingChanged();
    }
}

void ClippedContainer::setClipperWindow(Window* w)
{
    if (d_clipperWindow != w)
    {
        d_clipperWindow = w;
        invalidate();
        notifyClippingChanged();
    }
}

} // End of  CEGUI namespace section
