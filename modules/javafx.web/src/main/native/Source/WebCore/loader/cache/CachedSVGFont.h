/*
 * Copyright (C) 2007-2021 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "CachedFont.h"

namespace WebCore {

class FontCreationContext;
class SVGFontFaceElement;
class Settings;

class CachedSVGFont final : public CachedFont {
public:
    CachedSVGFont(CachedResourceRequest&&, PAL::SessionID, const CookieJar*, const Settings&);
    CachedSVGFont(CachedResourceRequest&&, CachedSVGFont&);

    bool ensureCustomFontData(const AtomString& remoteURI) override;

    RefPtr<Font> createFont(const FontDescription&, const AtomString& remoteURI, bool syntheticBold, bool syntheticItalic, const FontCreationContext&) override;

private:
    FontPlatformData platformDataFromCustomData(const FontDescription&, bool bold, bool italic, const FontCreationContext&);

    SVGFontElement* getSVGFontById(const String&) const;

    SVGFontElement* maybeInitializeExternalSVGFontElement(const AtomString& remoteURI);
    SVGFontFaceElement* firstFontFace(const AtomString& remoteURI);

    RefPtr<SharedBuffer> m_convertedFont;
    RefPtr<SVGDocument> m_externalSVGDocument;
    SVGFontElement* m_externalSVGFontElement;
    const Ref<const Settings> m_settings;
};

} // namespace WebCore

SPECIALIZE_TYPE_TRAITS_CACHED_RESOURCE(CachedSVGFont, CachedResource::Type::SVGFontResource)
