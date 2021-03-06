// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
 
// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef _FX_XML_H_
#define _FX_XML_H_
#ifndef _FX_BASIC_H_
#include "fx_basic.h"
#endif
class CXML_AttrItem : public CFX_Object
{
public:
    CFX_ByteStringL	m_QSpaceName;
    CFX_ByteStringL	m_AttrName;
    CFX_WideStringL	m_Value;

    void	Empty(IFX_Allocator* pAllocator = NULL)
    {
        m_QSpaceName.Empty(pAllocator);
        m_AttrName.Empty(pAllocator);
        m_Value.Empty(pAllocator);
    }
};
class CXML_AttrMap : public CFX_Object
{
public:
    CXML_AttrMap()
    {
        m_pMap = NULL;
    }
    ~CXML_AttrMap()
    {
        RemoveAll(NULL);
    }
    const CFX_WideStringL*	Lookup(FX_BSTR space, FX_BSTR name) const;
    void					SetAt(FX_BSTR space, FX_BSTR name, FX_WSTR value, IFX_Allocator* pAllocator = NULL);
    void					RemoveAt(FX_BSTR space, FX_BSTR name, IFX_Allocator* pAllocator = NULL);
    void					RemoveAll(IFX_Allocator* pAllocator = NULL);
    int						GetSize() const;
    CXML_AttrItem&			GetAt(int index) const;
    CFX_ObjectArray<CXML_AttrItem>*	m_pMap;
};
class CXML_Content : public CFX_Object
{
public:
    CXML_Content() : m_bCDATA(FALSE), m_Content() {}
    ~CXML_Content()
    {
        Empty(NULL);
    }
    void	Empty(IFX_Allocator* pAllocator = NULL)
    {
        m_Content.Empty(pAllocator);
    }
    void	Set(FX_BOOL bCDATA, FX_WSTR content, IFX_Allocator* pAllocator = NULL)
    {
        m_bCDATA = bCDATA;
        m_Content.Set(content, pAllocator);
    }
    FX_BOOL			m_bCDATA;
    CFX_WideStringL	m_Content;
};
class CXML_Element : public CFX_Object
{
public:

    static CXML_Element*	Parse(const void* pBuffer, size_t size, FX_BOOL bSaveSpaceChars = FALSE, FX_FILESIZE* pParsedSize = NULL, IFX_Allocator* pAllocator = NULL);

    static CXML_Element*	Parse(IFX_FileRead *pFile, FX_BOOL bSaveSpaceChars = FALSE, FX_FILESIZE* pParsedSize = NULL, IFX_Allocator* pAllocator = NULL);

    static CXML_Element*	Parse(IFX_BufferRead *pBuffer, FX_BOOL bSaveSpaceChars = FALSE, FX_FILESIZE* pParsedSize = NULL, IFX_Allocator* pAllocator = NULL);

    CXML_Element(FX_BSTR qSpace, FX_BSTR tagName, IFX_Allocator* pAllocator = NULL);

    CXML_Element(FX_BSTR qTagName, IFX_Allocator* pAllocator = NULL);

    CXML_Element(IFX_Allocator* pAllocator = NULL);

    ~CXML_Element();

    void	Empty();



    CFX_ByteString			GetTagName(FX_BOOL bQualified = FALSE) const;
    void					GetTagName(CFX_ByteStringL &tagName, FX_BOOL bQualified = FALSE) const;

    CFX_ByteString			GetNamespace(FX_BOOL bQualified = FALSE) const;
    void					GetNamespace(CFX_ByteStringL &nameSpace, FX_BOOL bQualified = FALSE) const;

    CFX_ByteString			GetNamespaceURI(FX_BSTR qName) const;
    void					GetNamespaceURI(FX_BSTR qName, CFX_ByteStringL &uri) const;

    CXML_Element*			GetParent() const
    {
        return m_pParent;
    }

    FX_DWORD				CountAttrs() const
    {
        return m_AttrMap.GetSize();
    }

    void					GetAttrByIndex(int index, CFX_ByteString &space, CFX_ByteString &name, CFX_WideString &value) const;
    void					GetAttrByIndex(int index, CFX_ByteStringL &space, CFX_ByteStringL &name, CFX_WideStringL &value) const;

    FX_BOOL					HasAttr(FX_BSTR qName) const;

    FX_BOOL					GetAttrValue(FX_BSTR name, CFX_WideString& attribute) const;
    CFX_WideString			GetAttrValue(FX_BSTR name) const
    {
        CFX_WideString attr;
        GetAttrValue(name, attr);
        return attr;
    }
    const CFX_WideStringL*	GetAttrValuePtr(FX_BSTR name) const;

    FX_BOOL					GetAttrValue(FX_BSTR space, FX_BSTR name, CFX_WideString& attribute) const;
    CFX_WideString			GetAttrValue(FX_BSTR space, FX_BSTR name) const
    {
        CFX_WideString attr;
        GetAttrValue(space, name, attr);
        return attr;
    }
    const CFX_WideStringL*	GetAttrValuePtr(FX_BSTR space, FX_BSTR name) const;

    FX_BOOL					GetAttrInteger(FX_BSTR name, int& attribute) const;
    int						GetAttrInteger(FX_BSTR name) const
    {
        int attr = 0;
        GetAttrInteger(name, attr);
        return attr;
    }

    FX_BOOL					GetAttrInteger(FX_BSTR space, FX_BSTR name, int& attribute) const;
    int						GetAttrInteger(FX_BSTR space, FX_BSTR name) const
    {
        int attr = 0;
        GetAttrInteger(space, name, attr);
        return attr;
    }

    FX_BOOL					GetAttrFloat(FX_BSTR name, FX_FLOAT& attribute) const;
    FX_FLOAT				GetAttrFloat(FX_BSTR name) const
    {
        FX_FLOAT attr = 0;
        GetAttrFloat(name, attr);
        return attr;
    }

    FX_BOOL					GetAttrFloat(FX_BSTR space, FX_BSTR name, FX_FLOAT& attribute) const;
    FX_FLOAT				GetAttrFloat(FX_BSTR space, FX_BSTR name) const
    {
        FX_FLOAT attr = 0;
        GetAttrFloat(space, name, attr);
        return attr;
    }

    FX_DWORD				CountChildren() const;

    enum ChildType { Invalid, Element, Content};

    ChildType				GetChildType(FX_DWORD index) const;

    CFX_WideString			GetContent(FX_DWORD index) const;
    const CFX_WideStringL*	GetContentPtr(FX_DWORD index) const;

    CXML_Element*			GetElement(FX_DWORD index) const;

    CXML_Element*			GetElement(FX_BSTR space, FX_BSTR tag) const
    {
        return GetElement(space, tag, 0);
    }

    FX_DWORD				CountElements(FX_BSTR space, FX_BSTR tag) const;

    CXML_Element*			GetElement(FX_BSTR space, FX_BSTR tag, int index) const;

    FX_DWORD				FindElement(CXML_Element *pChild) const;




    void					SetTag(FX_BSTR qSpace, FX_BSTR tagname);

    void					SetTag(FX_BSTR qTagName);

    void					RemoveChildren();

    void					RemoveChild(FX_DWORD index);


protected:

    CXML_Element*			m_pParent;

    CFX_ByteStringL			m_QSpaceName;

    CFX_ByteStringL			m_TagName;

    CXML_AttrMap			m_AttrMap;

    CFX_PtrArray			m_Children;
    friend class CXML_Parser;
    friend class CXML_Composer;
};
#endif
